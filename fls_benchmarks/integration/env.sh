DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
export LSAN_OPTIONS=suppressions=$DIR/lsan_suppress.txt
