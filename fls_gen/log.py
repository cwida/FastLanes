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


LOGGER_PREFIX = '-- '


def print_warning(msg):
    print(Colors.WARNING + LOGGER_PREFIX + msg + Colors.ENDC)


def print_error(msg):
    print(Colors.FAIL + LOGGER_PREFIX + msg + Colors.ENDC)


def print_ok(msg):
    print(Colors.OKGREEN + LOGGER_PREFIX + msg + Colors.ENDC)


def print_success(msg):
    print(Colors.OKGREEN + Colors.BOLD + LOGGER_PREFIX + msg + Colors.ENDC)


def print_generated(file):
    print_ok('GENERATED -- ' + file)
