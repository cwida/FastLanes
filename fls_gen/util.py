from fls_gen.common import *


# flatten a list of list into a list [[]] -> []
def flatten(t):
    return [item for sublist in t for item in sublist]


def is_last_element(index, size_of_array):
    if size_of_array == index + 1:
        return True
    return False


# random number generator, returns a string
# i.e. random_int_gen(8, 5), generates 8-bit numbers < 2^5, 00011111
def gen_random_int(size, bw):
    result = "{"
    for i in range(0, size):
        if bw == 0:
            result = result + str(0) + "UL" + ","
        else:
            result = result + str(random.getrandbits(bw)) + "UL" + ","
    result = result + "};"

    return result


# random number generator, returns a string
# i.e. random_int_gen(8, 5), generates 8-bit numbers < 2^5, 00011111
def gen_random_int_with_base(size, bw, base):
    result = "{"
    for i in range(0, size):
        if bw == 0:
            result = result + str(base) + "UL" + ","
        else:
            random_num = random.getrandbits(bw)
            if random_num < base:
                random_num = base
            result = result + str(random_num) + "UL" + ","

    result = result + "};"

    return result


#  like range function in python
def gen_string_range(size, bits):
    assert (bits == 8 or bits == 16 or bits == 32 or bits == 64)
    result = "{"
    arr = range(size)
    for i in arr:
        index = i % (2 ** (bits - 1))
        result = result + str(index) + ','
    result = result + "};"

    return result


def to_cpp(arr):
    assert isinstance(arr, list)
    size = len(arr)

    result = "{"
    for i in range(size):
        result = result + str(arr[i]) + ','
    result = result + "};"

    return result


# decorator
def add_column_number(func):
    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        col = args[1]
        result = "//\t"
        for i in range(col):
            result += str(i) + '\t\t'
        result += '\n'
        return result + func(*args, **kwargs)

    return wrapper


@add_column_number
def to_cpp_columnwise(arr, cols):
    assert isinstance(arr, list)

    size = len(arr)
    result = "{"
    for i in range(size):
        if i % cols == 0:
            result = result + '\n\t\t'

        result = result + str(arr[i]) + ',\t\t'
    result = result + "};"

    return result


def extract_pow_of_2(n):
    tmp = int(math.log(n, 2))
    return [1 << i for i in range(tmp)]


# arr is input array, BSZ is block-size
def view_as_blocks(arr, bsz):
    m, n = arr.shape
    M, N = bsz
    return arr.reshape(m // M, M, n // N, N).swapaxes(1, 2).reshape(-1, M, N)


#  like range function in python
def gen_range(size, bits):
    assert (bits == 8 or bits == 16 or bits == 32 or bits == 64)
    assert (size == 1024)

    arr = range(size)
    results = []
    for i in arr:
        index = i % (2 ** (bits - 1))
        results.append(index)

    return results


# a decorator: make sure all values of an arr is less than the limit arg
def less_then(limit):
    def decorator_less_then(func):
        @functools.wraps(func)
        def wrapper(*args, **kwargs):
            arr = func(*args, **kwargs)
            modified_arr = [val % limit for val in arr]
            return modified_arr

        return wrapper

    return decorator_less_then


@less_then(limit=1000)
def random_arr(mrw, ow, seed):
    random.seed(seed)

    assert (ow == 8 or ow == 16 or ow == 32 or ow == 64)
    arr = []
    for i in range(0, mrw):
        # bits - 1, because ints support [-(2 ** (bits - 1), +(2 ** (bits - 1)]
        random_number = random.getrandbits(ow - 1)
        arr.append(random_number)
    return arr


def rand_numbers_with_fixed_sum(_sum, n):
    min_v = 1
    max_v = _sum
    array = [min_v] * n

    diff = _sum - min_v * n
    while diff > 0:
        a = random.randint(0, n - 1)
        if array[a] >= max_v:
            continue
        array[a] += 1
        diff -= 1

    return array


def random_run_arr(mrw, ow, seed, runs_count):
    random.seed(1370)
    # for simplicity values are 0, 1, 2 and ... for
    val_arr = list(range(runs_count))
    len_arr = rand_numbers_with_fixed_sum(mrw, runs_count)

    arr = []
    for i in range(runs_count):
        for _ in range(len_arr[i]):
            arr.append(val_arr[i])

    # subtract 1 from len_arr
    # because 0 could be abused as 1
    len_arr = [val - 1 for val in len_arr]
    return arr, val_arr, len_arr


def random_run_arr_4x256(mrw, ow, seed, runs_count):
    arr, val_arr, len_arr = random_run_arr(mrw, ow, seed, runs_count)

    # get real lengths.
    len_arr = [val + 1 for val in len_arr]

    capacity = 256

    new_val_arr = []
    new_len_arr = []

    def insert(val, len):
        new_val_arr.append(val)
        new_len_arr.append(len)

    def over_flow():
        return curr_len > capacity

    for i in range(runs_count):
        if capacity == 0:
            capacity = 256

        curr_len = len_arr[i]
        curr_val = val_arr[i]
        while over_flow():
            insert(curr_val, capacity)
            curr_len -= capacity
            capacity = 256
        insert(curr_val, curr_len)
        capacity -= curr_len

    new_len_arr = [val - 1 for val in new_len_arr]
    new_runs_count = len(new_len_arr)

    # subtract 1 from len_arr
    if sum(new_len_arr) + new_runs_count != 1024:
        raise ValueError(mrw, ow, seed, runs_count)

    return arr, new_val_arr, new_len_arr, new_runs_count


if __name__ == '__main__':
    pass
