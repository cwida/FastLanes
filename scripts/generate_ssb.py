from generate import *


def remove_dir(dir_path):
    if os.path.exists(dir_path):
        shutil.rmtree(dir_path)


def fresh_create(dir_path):
    remove_dir(dir_path)
    os.mkdir(dir_path)
    os.chdir(dir_path)


def ssb():
    GIT("clone", "https://github.com/eyalroz/ssb-dbgen/")
    os.chdir("ssb-dbgen")
    CMAKE(".")
    CMAKE("--build", ".")
    DBGEN("s 1")


def move_tables():
    os.system('mv *.tbl ../..')


def generate_SSB(dir_path, sf):
    tmp_dir_path = "tmp"
    fresh_create(dir_path)
    fresh_create(tmp_dir_path)
    ssb()
    move_tables()
    # remove_dir(tmp_dir_path) #todo


def main():
    SCALE_FACTOR = 1
    dir_path = "ssb"
    generate_SSB(dir_path, SCALE_FACTOR)


if __name__ == "__main__":
    print("THE RESULT IS DIFFERENT FROM CRYSTAL PAPER")
    main()
