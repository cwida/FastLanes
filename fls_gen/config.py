# Archs
class Arch:
    fallback = "fallback"
    cuda = "cuda"


# Features
class Feature:
    scalar = "scalar"
    normal = "normal"
    fused = "fused"


# Mode
class Mode:
    aav = "aav"  # annotate the main loop with #pragma clang loop vectorize(enable)
    thread32 = "t32"


# Compressions primitives
class Primitive:
    unpack = "unpack"
    pack = "pack"
    unffor = "unffor"  # FLS FOR, for is a reserved word!
    ffor = "ffor"
    falp = "falp"  # Fused ALP, decode
    unrsum = "unrsum"
    rsum = "rsum"
    normal_rsum = "normal_rsum"
    transpose = "transpose"
    untranspose = "untranspose"
    rsum_and_untranspose = "rsum_and_untranspose"
