import os
import subprocess
import shutil


def GIT(*args):
    return subprocess.check_call(['git'] + list(args))


def MAKE(*args):
    return subprocess.check_call(['make'] + list(args))


def DBGEN(*args):
    return subprocess.check_call(['./dbgen'] + list(args))

def CMAKE(*args):
    return subprocess.check_call(['cmake'] + list(args))


def CP(*args):
    return subprocess.check_call(['cp'] + list(args))