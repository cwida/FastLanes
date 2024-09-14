#!/usr/bin/env python
import os

import yaml
import json
from dataset_lib.datasets import *


def set_sf(yaml_file: str) -> str:
    return yaml_file.replace("/tables/", "/sf_0_1/tables/")


def yaml_to_hpp(dataset, table):
    customized_table = table  # To only cover the first table of each table.

    if dataset.name == "public_bi":
        customized_table = customized_table + "/" + customized_table + "_1"  # To only cover the first table of each table.
        table = table + "_1"  # To only cover the first table of each table.

    yaml_file = "../FastLanes_Data/{0}".format(dataset.name) + "/tables/" + customized_table + "/schema.yaml"
    json_file = "../FastLanes_Data/{0}".format(dataset.name) + "/tables/" + customized_table + "/schema.json"

    if dataset == Ssb:
        yaml_file = set_sf(yaml_file)
        json_file = set_sf(json_file)

    elif dataset == clickbench:
        yaml_file = dataset.get_working_dir() + "/" + customized_table + "/schema.yaml"
        json_file = dataset.get_working_dir() + "/" + customized_table + "/schema.json"

    elif dataset == NextiaJD:
        json_file = dataset.get_working_dir() + "/" + customized_table + "/schema.json"
        yaml_file = dataset.get_working_dir() + "/" + customized_table + "/schema.yaml"

    with open(yaml_file, 'r') as yaml_in, open(json_file, "w") as json_out:
        yaml_object = yaml.safe_load(yaml_in)  # yaml_object will be a list or a dict
        json.dump(yaml_object, json_out, indent=2)


def main():
    for dataset in datasets:
        for table in dataset.table_list:
            yaml_to_hpp(dataset, table)


if __name__ == "__main__":
    main()
