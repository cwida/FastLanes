from fls_gen.cuda_unpack import *
from fls_gen.common import *

random.seed(1370)


def generate_gpu_cuda_normal_t32_bitunpack():
    generator = CudaUnpackGenerator(arch=Arch.cuda,
                                    feature=Feature.normal,
                                    prm=Primitive.unpack,
                                    flags='-o3',
                                    mode=Mode.thread32,
                                    mrw=1024,
                                    crws=[32],
                                    ows=[32],
                                    lws=[32],
                                    uf=1,
                                    bw=None)

    generator.generate()


def generate_gpu_cuda_fused_t32_bitunpack():
    generator = CudaUnpackGenerator(arch=Arch.cuda,
                                    feature=Feature.fused,
                                    prm=Primitive.unpack,
                                    flags='-o3',
                                    mode=Mode.thread32,
                                    mrw=1024,
                                    crws=[32],
                                    ows=[32],
                                    lws=[32],
                                    uf=1,
                                    bw=None)

    generator.generate()


def generate_unpack_lib():
    # GPU CUDA
    generate_gpu_cuda_normal_t32_bitunpack()
    generate_gpu_cuda_fused_t32_bitunpack()


def generate_bitpack_lib():
    print_success("BITPACK::UNPACK generator has been started.")
    generate_unpack_lib()
    print_success("FINISHED!.")


if __name__ == "__main__":
    generate_bitpack_lib()
