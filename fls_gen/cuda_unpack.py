from fls_gen.generator import *
from fls_gen.util import *


# bw: BitWidth, number of bits used to bit-pack data.
# ow: Output Width, What is the target output width.
# lw: Lane Width, What kinda lane width we want to use.


class CudaUnpackGenerator(Generator):
    # values
    num = 0
    mrw = 0
    ow = 0
    lw = 0
    offset = 0
    h_jump = 0
    loop_count = 0
    chunk_size = 0  # each chunk is equal to the width of current register(crw).
    bitmask = 0
    shift_to_left = 0
    shift_to_right = 0

    # counters
    i = 0  # ow counter
    j = 0  # uf counter
    z = 0  # cvt counters
    x = 0  # cvt counters
    y = 0  # cvt counters

    def __init__(self, *, arch, feature, prm, flags, mode, mrw, crws, ows, lws, uf, bw):
        super().__init__(arch, feature, prm, flags, mode, mrw, crws, lws, uf)
        self.ows = ows
        self.lws = lws
        self.bw = bw
        self.uf = uf
        self.src_file = os.path.join(self.feature_dir, self.name + '_src.cu')
        self.test_file = os.path.join(self.feature_dir, self.name + '_test.cu')
        self.benchmark_file = os.path.join(self.feature_dir, self.name + '_bench.cu')

    def reset_tmp_values(self):
        self.shift_to_left = 0
        self.shift_to_right = 0
        self.offset = 0
        self.offset = 0
        self.store_v_jump = 0
        self.load_v_jump = 0
        self.z = 0

    def generate(self):
        # generate src
        self.generate_src()

        # generate helper, helper is needed for the benchmark and test file;
        # currently it has
        # 1) per-generated array
        self.generate_helper()

        # generate benchmark
        self.generate_benchmark()

        # generate test
        self.generate_gtest_test()

        # generate cmake
        self.generate_cmake()

        # save the name of all generated file names
        # could be used to manage generated filed
        self.save_file_names()

    def get_main_entry_func_signature(self):
        return '__device__ void unpack(const uint$ow$_t *__restrict a_in_p, uint$ow$_t *__restrict a_out_p, uint8_t bw)'

    def iterate_over_config(self, cu, func, *, is_switch):
        self.num = 0
        for self.ow in self.ows:
            if is_switch:
                self.num = 0
                with cu.block(self.get_main_entry_func_signature()):
                    with cu.block(" switch (bw)"):
                        self.iterate(cu, func)

            else:
                self.iterate(cu, func)

    def iterate(self, cu, func):
        for self.bw in range(0, self.ow + 1):
            for self.crw in self.crws:

                self.h_jump = int(self.crw / self.ow)
                self.chunk_size = int(self.mrw / self.crw)

                for self.lw in self.lws:

                    self.reset_tmp_values()

                    if self.feature is Feature.scalar:
                        self.h_jump = 1
                        if (self.bw <= self.crw) and (self.crw == self.ow == self.lw):
                            self.loop_count = int(self.chunk_size / self.uf)
                            func(cu)

                    elif self.feature is Feature.normal or Feature.fused:
                        self.h_jump = 1
                        if (self.bw <= self.crw) and (self.crw == self.ow == self.lw):
                            self.loop_count = int(self.chunk_size / self.uf)
                            func(cu)

    def get_case_condition(self):
        return '   unpack_$bw$bw_$ow$ow_$crw$crw_$uf$uf(a_in_p, a_out_p);'

    def gen_switch(self, cu):
        cu("case $num$:")
        cu(self.get_case_condition())
        cu("   break;")
        self.num = self.num + 1

    def load(self, cu):
        super(CudaUnpackGenerator, self).load(cu)

    def unpack(self, cu):
        # if offset is 0 there is no need to shift
        if self.offset == 0:
            for self.j in range(self.uf):
                if self.feature is Feature.scalar:
                    cu("tmp_$j$ = (register_$j$) & ((1ULL << $shift_to_left$) - 1);")

                elif self.feature is Feature.normal or Feature.fused:
                    cu("tmp_$j$ = (register_$j$) & ((1ULL << $shift_to_left$) - 1);")

        else:
            for self.j in range(self.uf):
                if self.feature is Feature.scalar:
                    cu("tmp_$j$ = (register_$j$ >> $offset$) & ((1ULL << $shift_to_left$) - 1);")

                elif self.feature is Feature.normal or Feature.fused:
                    cu("tmp_$j$ = (register_$j$ >> $offset$) & ((1ULL << $shift_to_left$) - 1);")

    def load_unpack_store(self, cu):
        self.offset = 0
        self.shift_to_left = self.bw

        self.load(cu)
        self.unpack(cu)
        self.store_tmp(cu)

        self.offset = self.offset + self.bw

    def cross_unpack(self, cu):
        for self.j in range(self.uf):
            if self.feature is Feature.scalar:
                cu("tmp_$j$ |= ((register_$j$) & ((1ULL << $shift_to_right$) - 1)) << $shift_to_left$;")

            elif self.feature is Feature.normal or Feature.fused:
                cu("tmp_$j$ |= ((register_$j$) & ((1ULL << $shift_to_right$) - 1)) << $shift_to_left$;")

    def cross_load_unpack_store(self, cu):
        self.shift_to_left = self.lw - self.offset
        self.shift_to_right = self.bw - self.shift_to_left

        self.unpack(cu)
        self.load(cu)
        self.cross_unpack(cu)
        self.store_tmp(cu)

        self.offset = self.shift_to_right

    def unpack_store(self, cu):
        self.shift_to_left = self.bw
        self.unpack(cu)
        self.store_tmp(cu)
        self.offset = self.offset + self.bw

    def gen_before_loop_pragmas(self, cu):
        if self.mode is Mode.aav and self.ow > 46:
            cu("#pragma clang loop vectorize(enable)")

    def get_func_signature(self):
        return '__device__ void unpack_$bw$bw_$ow$ow_$crw$crw_$uf$uf(const uint$ow$_t *__restrict a_in_p, uint$ow$_t ' \
               '*__restrict a_out_p)'

    def gen_func(self, cu):
        with cu.block(self.get_func_signature()):
            super().reinterpret(cu)
            self.declare_variables(cu)
            self.declare_and_set_base(cu)
            self.cuda(cu)

            if self.bw == 0:
                for self.i in range(self.lw):
                    self.store_base(cu)

            elif self.bw == self.ow:
                for self.i in range(self.lw):
                    self.load(cu)
                    self.store_register(cu)

            else:
                self.load(cu)
                for self.i in range(self.lw):
                    if self.offset == self.lw:
                        self.load_unpack_store(cu)

                    elif self.offset + self.bw > self.lw:
                        self.cross_load_unpack_store(cu)

                    else:
                        self.unpack_store(cu)

    def cuda(self, cu):
        cu('''
            int i         = threadIdx.x; // THREAD INDEX
            ''')

    def gen_array(self, cu):
        cu("uint$ow$_t rand_arr_$num$_b$bw$_w$ow$_arr[1024] = ")
        cu(gen_random_int(1024, self.bw))
        self.num = self.num + 1

    def pack_helper_arr(self):
        return 'generated::pack::fallback::scalar::pack(helper::rand_arr_$num$_b$bw$_w$ow$_arr, const_cast<uint$ow$_t*>(' \
               'packed$ow$), $bw$);'

    def unpack_helper_arr(self):
        return "generated::$prm$::$arch$::$feature$::unpack(packed$ow$, unpacked$ow$, $bw$);"

    def gen_gtest_test_suite(self, cu):
        with cu.block('TEST_F({}, test_$num$_bw_$bw$_ow_$ow$)'.format(self.name)):
            cu('''
                    generated::pack::fallback::scalar::pack(helper::rand_arr_$num$_b$bw$_w$ow$_arr, packed$ow$, $bw$);
                    d_encoded_arr = fastlanes::gpu::load_arr(packed$ow$, $ow$ * 1024 / 8);
                    unpack_global<<<n_blc, n_trd>>>(d_encoded_arr, d_decoded_arr, $bw$);
                    CUDA_SAFE_CALL(cudaMemcpy(h_decoded_arr, d_decoded_arr, sizeof(uint32_t) * n_tup, cudaMemcpyDeviceToHost));
                    for (int i = 0; i < n_tup; i++) {
                        ASSERT_EQ(helper::rand_arr_$num$_b$bw$_w$ow$_arr[i], h_decoded_arr[i]);
                    }
                    ''')
        self.num = self.num + 1

    def gen_includes(self, cu):
        cu('#include "fls_gen/$prm$/$prm$.cuh"')
        cu('''
            #include <cuda.h>
            #include <cuda_runtime.h>
            ''')

    def gen_macros(self, cu):
        super().gen_macros(cu)

    def gen_common_includes(self, cu):
        cu('#include "fls_gen/$prm$/$prm$.cuh"')
        cu('#include "fls_gen/pack/pack.hpp"')
        cu('#include "' + self.name + '_helper.hpp"')

    def gen_helper_arrays(self, cu):
        cu("const auto packed8 = new (std::align_val_t {64}) uint8_t[1024];")
        cu("const auto packed16 = new (std::align_val_t {64}) uint16_t[1024];")
        cu("const auto packed32 = new (std::align_val_t {64}) uint32_t[1024];")
        cu("const auto packed64 = new (std::align_val_t {64}) uint64_t[1024];")
        cu("auto unpacked8 = new (std::align_val_t {64}) uint8_t[1024];")
        cu("auto unpacked16 = new (std::align_val_t {64}) uint16_t[1024];")
        cu("auto unpacked32 = new (std::align_val_t {64}) uint32_t[1024];")
        cu("auto unpacked64 = new (std::align_val_t {64}) uint64_t[1024];")

    def gen_test_fixture(self, cu):
        with cu.block('class {}: public ::testing::Test'.format(self.name)):
            cu('''
                    public: 
                    uint64_t  warp_sz {};
                    uint64_t  n_vec {};
                    uint64_t  vec_sz {};
                    uint64_t  n_tup {};
                    uint64_t  v_blc_sz {};
                    uint64_t  n_blc {};
                    uint64_t  n_trd {};
                    uint32_t* d_decoded_arr {nullptr};
                    uint32_t* h_decoded_arr {};
                    uint32_t* packed32;
                    uint32_t* unpacked32;
                    uint32_t* d_encoded_arr;
                    ''')

            with cu.block('void SetUp() override'):
                cu('''		
                        n_tup         = 1024;
                        n_trd         = 32;
                        n_blc         = 1;
                        packed32      = new uint32_t[1024]();
                        unpacked32    = new uint32_t[1024]();
                        h_decoded_arr = new uint32_t[1024]();
                        CUDA_SAFE_CALL(cudaMalloc((void**)&d_decoded_arr, sizeof(uint32_t) * n_tup));
                        ''')

            with cu.block('~{} () override'.format(self.name)):
                pass
        cu(';')

    def gen_benchmark_func(self, cu):
        with cu.block('static void bench$num$_unpack_$bw$bw_$ow$ow_$crw$crw_$uf$uf()'):
            cu('''auto bitwidth = $bw$;
                if (bitwidth == 32) {bitwidth = 31;};
                /* generate random numbers. */
                for (int i = 0; i < n_tup; i++) {
                    h_org_arr[i] = rand() % (1 << bitwidth);
                }
            
                auto in  = h_org_arr;
                auto out = h_encoded_data;
                for (uint64_t vec_idx {0}; vec_idx < n_vec; vec_idx++) {
                    generated::pack::fallback::scalar::pack(in, out, bitwidth);
                    in  = in + vec_sz;
                    out = out + (bitwidth * vec_sz / 32);
                }
            
                auto* d_encoded_arr = fastlanes::gpu::load_to_gpu(h_encoded_data, encoded_arr_bsz, fastlanes::gpu::g_allocator);
                unpack_global<<<n_blc, n_trd>>>(d_encoded_arr, d_decoded_arr, bitwidth);
                CUDA_SAFE_CALL(cudaMemcpy(h_decoded_arr, d_decoded_arr, sizeof(uint32_t) * n_tup, cudaMemcpyDeviceToHost));
        
            	for (int i = 0; i < n_tup; i++) {
                    if (h_org_arr[i] != h_decoded_arr[i]) {
                        std::cout << bitwidth << " failed!" << std::endl;
                        return;
                    }
                }
                std::cout << bitwidth << " succes!" << std::endl;
                
                CLEANUP(d_encoded_arr);
	            ''')
        self.num = self.num + 1

    def gen_call_benchmark(self, cu):
        cu("bench$num$_unpack_$bw$bw_$ow$ow_$crw$crw_$uf$uf();")

        self.num = self.num + 1

    def gen_benchmark_includes(self, cu):
        cu('''
            #include "fls_gen/$prm$/$prm$.cuh"
            #include "fls_gen/pack/pack.hpp"
            #include "fastlanes.cuh"
            #include <iostream>
            ''')

    def gen_benchmark(self, cu):
        self.gen_benchmark_includes(cu)
        self.gen_global_variables(cu)

        # benchmark cases
        self.iterate_over_config(cu, self.gen_benchmark_func, is_switch=False)
        with cu.block('void benchmark_all()'):
            cu('CUDA_SAFE_CALL(cudaMalloc((void**)&d_decoded_arr, sizeof(uint32_t) * n_tup));')
            self.iterate_over_config(cu, self.gen_call_benchmark, is_switch=False)

        self.gen_benchmark_main(cu)

    def gen_benchmark_main(self, cu):
        with cu.block('int main()'):
            cu('''
               benchmark_all();
               ''')

    # cu file
    def generate_src(self):
        file = self.src_file

        cu = GenFile(file, self)
        starter(cu)
        self.gen_includes(cu)

        with cu.block("namespace generated"):
            with cu.block("namespace $prm$::$arch$"):
                with cu.block("namespace $feature$"):
                    self.iterate_over_config(cu, self.gen_func, is_switch=False)
                    self.iterate_over_config(cu, self.gen_switch, is_switch=True)

        cu(";")
        cu.close()

        print_generated(file)

    def generate_helper(self):
        file = self.helper_file
        hpp = GenFile(file, self)
        starter(hpp)
        hpp('#include "fls_gen/$prm$/$prm$.hpp"')

        with hpp.block("namespace helper"):
            self.iterate_over_config(hpp, self.gen_array, is_switch=False)

        print_generated(file)

    # Gtest tests file
    def generate_gtest_test(self):
        file = self.test_file
        cu = GenFile(file, self)
        starter(cu)
        cu('#include "gtest/gtest.h"')
        cu('#include <cuda.h>')
        cu('#include <cuda_runtime.h>')
        cu('#include <fastlanes.cuh>')

        self.gen_common_includes(cu)

        self.gen_test_fixture(cu)
        self.iterate_over_config(cu, self.gen_gtest_test_suite, is_switch=False)

        print_generated(file)

    def generate_benchmark(self):
        file = self.benchmark_file
        cu = GenFile(file, self)
        starter(cu)
        self.gen_benchmark(cu)

        print_generated(file)

    def generate_cmake(self):
        file = os.path.join(self.feature_dir, self.prm + '.cmake')

        cmake = GenFile(file, self)

        cmake('add_library($name$ OBJECT')
        cmake('            $name$_src.cu)')
        # fixme
        cmake('target_compile_definitions($name$ PRIVATE IS_SCALAR)')
        cmake('')
        cmake('target_compile_options($name$ PUBLIC ${FLAG})')
        cmake('cmake_print_properties(TARGETS $name$')
        cmake('                       PROPERTIES COMPILE_DEFINITIONS')
        cmake('                       PROPERTIES COMPILE_OPTIONS)')
        cmake('LIST (APPEND FLS_GENERATED_OBJECT_FILES')
        cmake('      $<TARGET_OBJECTS:$name$>)')
        cmake('get_target_property(TARGET_NAME $name$ NAME)')
        cmake('get_target_property(TARGET_COMPILE_OPTIONS $name$ COMPILE_OPTIONS)')
        cmake('#------------------------------------------------------------------------------------------------------')
        cmake('add_executable($name$_test $name$_test.cu)')
        cmake('target_link_libraries($name$_test PRIVATE $name$)')
        cmake('target_link_libraries($name$_test PRIVATE fastlanes gtest_main fastlanes_gpu)')
        cmake('#------------------------------------------------------------------------------------------------------')
        cmake('add_executable($name$_bench $name$_bench.cu)')
        cmake('target_link_libraries($name$_bench PRIVATE fastlanes $name$ fastlanes_gpu)')

    def generate_all_cmake(self):
        file = self.cmake_file
        cmake = GenFile(file, self)
        cmake('if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/pack.cmake")')
        cmake(' include(${CMAKE_CURRENT_SOURCE_DIR}/pack.cmake)')
        cmake('else()')
        cmake('endif()')

        cmake('if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/unpack.cmake")')
        cmake(' include(${CMAKE_CURRENT_SOURCE_DIR}/unpack.cmake)')
        cmake('else()')
        cmake('endif()')

        cmake('if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/unffor.cmake")')
        cmake(' include(${CMAKE_CURRENT_SOURCE_DIR}/unffor.cmake)')
        cmake('else()')
        cmake('endif()')

        cmake('if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/ffor.cmake")')
        cmake(' include(${CMAKE_CURRENT_SOURCE_DIR}/ffor.cmake)')
        cmake('else()')
        cmake('endif()')

        cmake('if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/unrsum.cmake")')
        cmake(' include(${CMAKE_CURRENT_SOURCE_DIR}/unrsum.cmake)')
        cmake('else()')
        cmake('endif()')

        cmake('if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/rsum.cmake")')
        cmake(' include(${CMAKE_CURRENT_SOURCE_DIR}/rsum.cmake)')
        cmake('else()')
        cmake('endif()')

        cmake('if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/untranspose.cmake")')
        cmake(' include(${CMAKE_CURRENT_SOURCE_DIR}/untranspose.cmake)')
        cmake('else()')
        cmake('endif()')

        cmake('if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/transpose.cmake")')
        cmake(' include(${CMAKE_CURRENT_SOURCE_DIR}/transpose.cmake)')
        cmake('else()')
        cmake('endif()')

        cmake('if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/falp.cmake")')
        cmake(' include(${CMAKE_CURRENT_SOURCE_DIR}/falp.cmake)')
        cmake('else()')
        cmake('endif()')

        cmake('set(FLS_GENERATED_OBJECT_FILES')
        cmake('    ${FLS_GENERATED_OBJECT_FILES} PARENT_SCOPE)')

        print_generated(file)

    def save_file_names(self):
        super().save_file_names()

    def set_base(self, cu):
        cu('*(base$ow$) = 0;')

    def declare_and_set_base(self, cu):
        for self.j in range(self.uf):
            if self.feature is Feature.scalar:
                cu("[[maybe_unused]] uint$crw$_t base_$j$ = 0ULL;")

            elif self.feature is Feature.normal or Feature.fused:
                cu("[[maybe_unused]] uint$crw$_t base_$j$ = 0ULL;")

    def gen_global_variables(self, cu):
        cu('''
        const uint64_t warp_sz         = 32;
        const uint64_t n_vec           = 256 * 1024;
        const uint64_t vec_sz          = 1024;
        const uint64_t n_tup           = vec_sz * n_vec;
        const uint64_t v_blc_sz        = 1;
        const uint64_t n_blc           = n_vec / v_blc_sz;
        const uint64_t n_trd           = v_blc_sz * warp_sz;
        auto*          h_org_arr       = new uint32_t[n_tup];
        auto*          h_encoded_data  = new uint32_t[n_tup];
        uint64_t       encoded_arr_bsz = n_tup * sizeof(int);
        uint32_t*      d_decoded_arr   = nullptr;
        auto*          h_decoded_arr   = new uint32_t[n_tup];
        ''')
