import re

from dataset_lib.common import *


def tpch_get_table_list():
    return tpch.table_list


class tpch:
    table_list = \
        [
            'customer',  #
            'lineitem',  #
            'nation',
            'orders',  #
            'part',
            'partsupp',
            'region',
            'supplier'
            #
        ]
    name = "tpch"

    def __init__(self):
        pass
