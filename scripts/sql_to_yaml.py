#!/usr/bin/env python
import re

import yaml

table_list = [  #
    # "Generico",
    # "TrainsUK1",
    "TrainsUK2"
    # "RealEstate1",
    # "CommonGovernment",
    # "USCensus",
    # "Medicare2",
    # "Bimbo",
    # "Medicare3",
    # "Romance",
    # "PanCreactomy1",
    # "Physicians",
    # "Taxpayer",
    # "Arade",
    # "Provider",
    # "Redfin4",
    # "Uberlandia",
    # "Redfin3",
    # "IGlocations2",
    # "Redfin2",
    # "MedPayment2",
    # "MulheresMil",
    # "Motos",
    # "TableroSistemaPenal",
    # "Telco",
    # "CMSprovider",
    # "RealEstate2",
    # "TrainsUK2",
    # "Corporations",
    # "Medicare1",
    # "Food",
    # "PanCreactomy2",
    # "Rentabilidad",
    # "HashTags",
    # "Hatred",
    # "YaleLanguages",
    # "IGlocations1",
    # "CityMaxCapita",
    # "SalariesFrance",
    # "IUBLibrary",
    # "Wins",
    # "MLB",
    # "NYC",
    # "MedPayment1",
    # "Euro2016",
    # "Redfin1",
    # "Eixo"
    #
]

lt_map = {"integer": "fastlanes::LT::INT64",  #
          "string": "fastlanes::LT::STR",
          "skip": "fastlanes::LT::SKIP",
          "double": "fastlanes::LT::DOUBLE"}  #
VERSION = 0


def yaml_to_hpp(dataset):
    yaml_file = "./public_bi/" + dataset + "/" + dataset + "_1/" + "create_table.sql"

    dataset = dataset + "_1"  # To only cover the first table of each dataset.
    schema_yaml = "schema.yaml"
    namespace_name = dataset + "_tab"
    footer_name = "footer"

    yaml_dict = {"columns": []}

    with open(schema_yaml, "w+") as out:
        with open(yaml_file, "r") as stream:
            for i in stream.readlines()[1:-1]:
                col_name = re.search("\"(.+)\"", i).group(1).replace("/", "_")
                if "integer" in i or "smallint" in i:
                    yaml_dict["columns"].append({"name": col_name, "type": "integer"})
                elif "varchar" in i:
                    yaml_dict["columns"].append({"name": col_name, "type": "string"})
                elif "decimal" in i or "double" in i:
                    yaml_dict["columns"].append({"name": col_name, "type": "double"})
                else:  # "timestamp", "date", "time", "boolean", "bigint"
                    yaml_dict["columns"].append({"name": col_name, "type": "skip"})

        yaml.dump([yaml_dict], out)

    print("-- {0} is generated.".format(schema_yaml))


def main():
    for dataset in table_list:
        yaml_to_hpp(dataset)


if __name__ == "__main__":
    main()
