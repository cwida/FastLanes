# colors used for printing
class Colors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKCYAN = '\033[96m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'


def warning(msg):
    print(Colors.WARNING + '-- ' + msg + Colors.ENDC)


def error(msg):
    print(Colors.FAIL + '-- ' + msg + Colors.ENDC)


def ok(msg):
    print(Colors.OKGREEN + '-- ' + msg + Colors.ENDC)


def ok_bold(msg):
    print(Colors.OKGREEN + Colors.BOLD + '-- ' + msg + Colors.ENDC)


def generated(file):
    ok('GENERATED -- ' + file)


def converted(file):
    ok('CONVERTED -- ' + file)

