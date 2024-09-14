import os
import re

from fls_gen.config import *
from fls_gen.log import *

PLACEHOLDER = re.compile('\\$([^\\$ | ^\\{ | ^\\<]+)\$')

column_limit = 120
tab_width = 8


# crw: Current Register Width, which we want to generate code for it.
# mrw : Maximum Register Width, the largest simd register we want to support.
# uf: unroll factor
# generator
class Generator:
    root_dir = os.path.join('.')

    crw = 0

    # generated_files
    generated_files = []

    def __init__(self, arch, feature, prm, flags, mode, mrw, crws, lws, uf):
        self.chunk_size = 0
        self.arch = arch
        self.feature = feature
        self.prm = prm
        self.flags = flags
        self.mode = mode
        self.arch_dir = os.path.join(self.root_dir, arch)
        self.feature_dir = os.path.join(self.arch_dir, self.feature + "_" + mode + "_uf" + str(uf))
        self.name = arch + "_" + feature + "_" + mode + "_" + str(mrw) + "_uf" + str(uf) + "_" + prm
        self.src_file = os.path.join(self.feature_dir, self.name + '_src.cpp')
        self.helper_file = os.path.join(self.feature_dir, self.name + '_helper.hpp')
        self.benchmark_file = os.path.join(self.feature_dir, self.name + '_bench.cpp')
        self.test_file = os.path.join(self.feature_dir, self.name + '_test.cpp')
        self.cmake_file = os.path.join(self.feature_dir, 'CMakeLists.txt')
        self.mrw = mrw
        self.crws = crws
        self.lws = lws
        self.uf = uf
        self.load_v_jump = 0
        self.store_v_jump = 0

    def gen_includes(self, cpp):
        cpp('#include "fls_gen/$prm$/$prm$.hpp"')
        cpp('#include "fls_gen/macros.hpp"')

    def gen_macros(self, cpp):
        pass

    # CPP file
    def generate_src(self):
        file = self.src_file

        cpp = GenFile(file, self)
        self.gen_includes(cpp)
        # self.gen_macros(cpp)

        with cpp.block("namespace $prm$"):
            with cpp.block("namespace $feature$"):
                pass

        cpp(";")
        cpp.close()

        print_generated(file)

    def generate_cmake(self):
        file = os.path.join(self.feature_dir, self.prm + '.cmake')

        cmake = GenFile(file, self)

        cmake('add_library($name$ OBJECT')
        cmake('            $name$_src.cpp)')
        # fixme
        cmake('target_compile_definitions($name$ PRIVATE IS_SCALAR)')
        cmake('set(FLAG $flags$)')
        cmake('check_cxx_compiler_flag(${FLAG} HAS_FLAG)')
        cmake('if(HAS_FLAG)')
        cmake('else()')
        cmake(' message(STATUS "The flag ${FLAG} is not supported by the current compiler")')
        cmake('endif()')
        cmake('target_compile_options($name$ PUBLIC ${FLAG})')
        cmake('cmake_print_properties(TARGETS $name$')
        cmake('                       PROPERTIES COMPILE_DEFINITIONS')
        cmake('                       PROPERTIES COMPILE_OPTIONS)')
        cmake('LIST (APPEND FLS_GENERATED_OBJECT_FILES')
        cmake('      $<TARGET_OBJECTS:$name$>)')
        cmake('get_target_property(TARGET_NAME $name$ NAME)')
        cmake('get_target_property(TARGET_COMPILE_OPTIONS $name$ COMPILE_OPTIONS)')
        cmake('#------------------------------------------------------------------------------------------------------')
        cmake('if (ENABLE_TESTING)')
        cmake('add_executable($name$_test $name$_test.cpp)')
        cmake('target_link_libraries($name$_test PRIVATE $name$)')
        cmake('target_link_libraries($name$_test PRIVATE '
              'fallback_scalar_aav_1024_uf1_pack '
              'fallback_scalar_aav_1024_uf1_ffor)')
        cmake('target_link_libraries($name$_test PRIVATE gtest_main)')
        cmake('target_include_directories($name$_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})')
        cmake('gtest_discover_tests($name$_test)')
        cmake('endif()')
        cmake('#------------------------------------------------------------------------------------------------------')
        cmake('configure_file(${CMAKE_SOURCE_DIR}/fls_bench/fls_bench.hpp ${'
              'CMAKE_CURRENT_BINARY_DIR}/' + self.name + '_bench.hpp)')
        cmake('add_executable($name$_bench $name$_bench.cpp)')
        cmake('target_link_libraries($name$_bench PRIVATE $name$)')
        cmake('target_link_libraries($name$_bench PRIVATE '
              'fallback_scalar_aav_1024_uf1_pack '
              'fallback_scalar_aav_1024_uf1_ffor)')
        cmake('target_include_directories($name$_bench PRIVATE ${CMAKE_CURRENT_BINARY_DIR})')
        cmake('add_fls_benchmark($name$_bench)')

        print_generated(file)

    def declare_bases(self, cpp):
        for self.j in range(self.uf):
            if self.feature is Feature.scalar:
                cpp("[[maybe_unused]] uint$crw$_t base_$j$;")

            elif self.feature is Feature.cuda:
                cpp("[[maybe_unused]] uint$crw$_t base_$j$;")

    # N is the number of registers or variables used inside each loop iteration
    def declare_variables(self, cpp):
        for self.j in range(self.uf):
            if self.feature is Feature.scalar:
                cpp("[[maybe_unused]] uint$crw$_t register_$j$;")
                cpp("[[maybe_unused]] uint$crw$_t tmp_$j$;")

            elif self.feature is Feature.normal or Feature.fused:
                cpp("[[maybe_unused]] uint$crw$_t register_$j$;")
                cpp("[[maybe_unused]] uint$crw$_t tmp_$j$;")

    def save_file_names(self):
        path = os.path.join(self.root_dir, 'generated_files.txt')
        file = GenFile(path, self)
        current_file = os.path.basename(path)
        for name in self.generated_files:
            # save all files except the file that contains name of other generated files
            if name != current_file:
                file(name)

    def load(self, cpp):
        for self.j in range(self.uf):
            if self.feature is Feature.scalar:
                cpp("register_$j$ = *(in + ($j$ * $loop_count$) + (i * $h_jump$) + $load_v_jump$);")

            elif self.feature is Feature.normal or Feature.fused:
                cpp("register_$j$ = *(in + ($j$ * $loop_count$) + (i * $h_jump$) + $load_v_jump$);")

        self.load_v_jump += self.chunk_size

    def store_tmp(self, cpp):
        self.store(cpp, variable='tmp_$j$')

    def store_zero(self, cpp):
        for self.j in range(self.uf):
            cpp("out[($j$ * $loop_count$) + (i * $h_jump$) + ($store_v_jump$)] = 0;")

        self.store_v_jump += self.chunk_size

    def store_register(self, cpp):
        self.store(cpp, variable="register_$j$")

    def store_base(self, cpp):
        self.store(cpp, variable="base_$j$")

    def store(self, cpp, *, variable):
        for self.j in range(self.uf):
            if self.feature is Feature.scalar:
                cpp("out[(i * $h_jump$) + ($j$ * $loop_count$) + $store_v_jump$] = {0};".format(variable))

            elif self.feature is Feature.normal:
                cpp("out[(i * $h_jump$) + ($j$ * $loop_count$) + $store_v_jump$] = {0};".format(variable))

            elif self.feature is Feature.fused:
                cpp("out[i + $i$] = {0};".format(variable))

        self.store_v_jump += self.chunk_size

    def gen_benchmark_main(self, cpp):
        with cpp.block('int main()'):
            cpp('''	benchmark::Benchmark benchmark =
	                     benchmark::create("$name$")
	                    .save()
	                    .at(std::string(SOURCE_DIR) + "/fls_pub/results/" + benchmark::CmakeInfo::getCmakeToolchainFile())
	                    .print()
	                    .add_extra_info(benchmark::CmakeInfo::getCmakeInfo());
	                benchmark_all(benchmark);''')

    def gen_benchmark_all(self, cpp):
        self.num = 0
        with cpp.block('void benchmark_all(benchmark::Benchmark& benchmark)'):
            self.gen_helper_arrays(cpp)
            self.call_bench_func(cpp)

    def gen_benchmark_includes(self, cpp):
        cpp('#include <iostream>')
        cpp('#include "' + self.name + '_bench.hpp"')
        cpp('#include "' + self.name + '_helper.hpp"')
        cpp('#include "fls_gen/$prm$/$prm$.hpp"')

    def handle_src_exceptions(self, file):
        with open(file, 'r') as f:
            file_data = f.read()
        # Write the file out again
        with open(file, 'w') as f:
            f.write(file_data)

    def reinterpret(self, cpp):
        if self.feature is Feature.scalar:
            cpp("[[maybe_unused]] auto out = reinterpret_cast<uint$crw$_t *>(a_out_p);")
            cpp("[[maybe_unused]] const auto in = reinterpret_cast<const uint$crw$_t *>(a_in_p);")

        elif self.feature is Feature.normal or Feature.fused:
            cpp("[[maybe_unused]] auto out = reinterpret_cast<uint$crw$_t *>(a_out_p);")
            cpp("[[maybe_unused]] auto in = reinterpret_cast<const uint$crw$_t *>(a_in_p);")

    def get_benchmark_iteration(self):
        return '''
            #ifdef NDEBUG
            uint64_t iterations = 3000000;
            #else 
            uint64_t iterations = 1;
            #endif
                '''

    def gen_helper_arrays(self, cpp):
        pass

    def call_bench_func(self, cpp):
        pass


class Snippet:
    last = None

    def __init__(self, owner, text, postfix):
        self.owner = owner
        if self.owner.last is not None:
            with self.owner.last:
                pass
        self.owner.write("".join(text))
        self.owner.last = self
        self.postfix = postfix

    def __enter__(self):
        self.owner.write("{")
        self.owner.current_indent += 1
        self.owner.last = None

    def __exit__(self, a, b, c):
        if self.owner.last is not None:
            with self.owner.last:
                pass
        self.owner.current_indent -= 1
        self.owner.write("}" + self.postfix)


class GenFile:
    def __init__(self, filename, generator):
        self.current_indent = 0
        self.last = None

        path = os.path.dirname(filename)
        os.makedirs(path, exist_ok=True)
        self.out = open(filename, "w")

        self.indent = "\t"
        self.generator = generator

        relative_path = os.path.relpath(filename, os.getcwd())

        # only keep track of cpp and hpp files
        if ".cpp" in relative_path or ".hpp" in relative_path or ".cu" in relative_path or ".hu" in relative_path:
            generator.generated_files.append(relative_path)

    def close(self):
        self.out.close()
        self.out = None

    def write(self, x, indent=0):
        self.out.write(self.indent * (self.current_indent + indent) + x + "\n")

    def format(self, text):
        substack = {key: value for key, value in self.generator.__dict__.items() if
                    not key.startswith('__') and not callable(key)}
        while True:
            m = PLACEHOLDER.search(text)
            if m is None:
                return text
            s = None

            for sub in substack:
                if m.group(1) in sub:
                    s = substack[m.group(1)]
                    break
            if s is None:
                raise Exception("Substitution '%s' not set." % m.groups(1))
            text = text[:m.start()] + str(s) + text[m.end():]

    def __call__(self, text):
        self.write(self.format(text))

    def write_without_subs(self, text):
        self.write(text)

    def write_from_file(self, file):
        with open(file, 'r') as f:
            text = f.read()
            self.write(text)

    def write_line(self):
        self.write('\n')
        current_indent = tab_width * self.current_indent
        line = "//"
        for i in range(column_limit - 2 - current_indent):
            line = line + "="
        self.write(line)

    def block(self, text, postfix=""):
        return Snippet(self, self.format(text), postfix)


def starter(cpp):
    cpp('// generated!')
