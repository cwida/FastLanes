from dataset_lib.common import *
from dataset_lib.public_bi import *
from dataset_lib.ssb import *
from dataset_lib.tpch import *
from dataset_lib.clickbench import *
from dataset_lib.nextia_jd import *

datasets = [
    PublicBI,
    NextiaJD(),
    # Ssb,
    clickbench
]
