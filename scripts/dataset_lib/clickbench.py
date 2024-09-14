from dataset_lib.datasets import *


class clickbench:
    table_list = ['hits']
    name = "clickbench"

    @staticmethod
    def get_working_dir():
        working_dir = os.path.join(sample_dir_path, clickbench.name)
        return working_dir

    @staticmethod
    def get_dir_path(table_name):
        return '"FastLanes_Data/{1}/{0}"'.format(table_name, clickbench.name)
