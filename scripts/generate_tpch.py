#!/usr/bin/env python

from generate import *


def generate_TPCH_using_dgen(sf, dir_path):
    if os.path.exists(dir_path):
        shutil.rmtree(dir_path)

    os.mkdir(dir_path)
    os.chdir(dir_path)
    GIT("clone", "https://github.com/electrum/tpch-dbgen")
    os.chdir("tpch-dbgen")
    MAKE("all")
    DBGEN("s 1")
    pass


def main():
    SCALE_FACTOR = 1
    dir_path = "tpch"
    generate_TPCH_using_dgen(SCALE_FACTOR, dir_path)


if __name__ == "__main__":
    main()
