from subprocess import call
from fls_gen.log import *
from fls_gen.common import *


def creat_if_not_exist(path):
    is_exist = os.path.exists(path)
    if not is_exist:
        # Create a new directory because it does not exist
        os.makedirs(path)
    os.chdir(path)


def is_comment(line):
    fls_generator_comment_symbol = '//'
    return str(line).startswith(fls_generator_comment_symbol)


def clear_prev_generation():
    with open('generated_files.txt', 'w+') as f:
        for line in f.readlines():
            if is_comment(line):
                print(Colors.OKGREEN + line + Colors.ENDC)
            else:
                file = line.strip()
                if os.path.isfile(file):
                    print_warning(file + " has been removed.")
                    os.remove(file)
                else:
                    print_error(file + " does not exist")


def clang_format():
    #  clang-format --files=generated_files.txt -i
    lc = ["clang-format", "--files=generated_files.txt", "-i"]
    retcode = call(lc)
    sys.exit(retcode)
