import json
import random
import csv
from faker import Faker
from faker.providers import BaseProvider
from pathlib import Path

faker = Faker()

# ---------------------------
# Config
# ---------------------------

VEC_SIZE = 1024
ROW_GROUP_SIZE = 64 * VEC_SIZE


# ---------------------------
# Helper Functions
# ---------------------------

def write_jsonl(dir_path, generate_func, size):
    """Writes data to a JSONL file using a generator function."""
    dir_path.mkdir(parents=True, exist_ok=True)  # <- added
    file_path = dir_path / 'data.jsonl'
    with open(file_path, 'w') as jsonlfile:
        for row_id in range(size):
            jsonlfile.write(json.dumps(generate_func(faker, row_id)) + '\n')


def write_csv(dir_path, generate_func, size):
    """Writes data to a CSV file using a generator function."""
    dir_path.mkdir(parents=True, exist_ok=True)  # <- added
    file_path = dir_path / "generated.csv"
    with open(file_path, 'w', newline='') as csvfile:
        writer = csv.writer(csvfile, delimiter='|', lineterminator='\n')
        writer.writerows(generate_func(faker, row_id) for row_id in range(size))


# ---------------------------
# Faker Providers
# ---------------------------

class LanguageProvider(BaseProvider):
    def language(self):
        return random.choice(['English', 'Chinese', 'Italian', 'Spanish', 'Hindi', 'Japanese'])


class NumberStringsProvider(BaseProvider):
    def number_as_string(self):
        return random.choice(['1', '12', '123', '1234', '12345', '123456'])


faker.add_provider(LanguageProvider)
faker.add_provider(NumberStringsProvider)


# ---------------------------
# Utility Functions
# ---------------------------

def range_x_to_y(x, y):
    return random.randint(x, y)


def constant(value):
    return value


def constant_with_nulls(row_id):
    if row_id % 20 == 1:
        return "NULL"
    return 5


def string_number(value):
    return value


def constant_u08(value):
    return value % 256


def map_value(row_id, map_info):
    original = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
    original_plus = [10000000000000, 10000000000001, 10000000000002, 10000000000003, 10000000000004, 10000000000005,
                     10000000000006, 10000000000007, 10000000000008, 10000000000009]

    str = ['zero', 'one', 'two', 'three', 'four', 'five', 'six', 'seven', 'eight', 'nine']

    chosen_list = []
    if map_info == "original":
        chosen_list = original
    elif map_info == "row_id":
        return row_id
    elif map_info == "row_id_plus":
        return row_id + 10000000000000
    elif map_info == "original_plus":
        chosen_list = original_plus
    elif map_info == "str":
        chosen_list = str

    return chosen_list[row_id % 10]


# ---------------------------
# Data Generators
# ---------------------------

def generate_one_to_one_i64_to_i64(faker, row_id):
    """Generates a list of values for example 1."""
    return [
        constant(row_id % 10),
        constant(row_id % 10 + 10000),
    ]


def generate_all_constant(_faker, row_id):
    """Generates a constant set of values."""
    return [
        constant(100),
        constant_with_nulls(row_id),
        constant(100.1),
        constant("CONSTANT"),
        constant_u08(25),
    ]


def generate_equality_fls_i64(_faker, row_id):
    """Generates a list of integers for equality checks."""
    return [constant(row_id) for _ in range(10)]


def generate_equality_fls_dbl(_faker, row_id):
    """Generates a list of floating-point numbers for equality checks."""
    return [constant(row_id + 0.1) for _ in range(10)]


def generate_equality_fls_str(_faker, row_id):
    """Generates a list of floating-point numbers for equality checks."""
    return [map_value(row_id, "str") for _ in range(10)]


def generate_struct(_faker, row_id):
    """Generates a structured JSON object with one column containing five fields."""
    return {
        'COLUMN_0': {
            'FIELD_0': row_id + 0000000000,
            'FIELD_1': row_id + 1000000000,
            'FIELD_2': row_id + 2000000000,
            'FIELD_3': row_id + 3000000000,
            'FIELD_4': row_id + 4000000000,
        }
    }


def generate_fls_i64(_faker, row_id):
    """Generates a list containing a single integer."""
    return [constant(row_id)]


def generate_irregular_i64_func(_faker, row_id):
    """Generates a list containing a single integer."""
    if row_id == 2056:
        return [constant(999)]
    return [constant(0)]


def generate_irregular_string_func(_faker, row_id):
    """Generates a list containing a single integer."""
    if row_id == 2024 - 1:
        return ["Jasmin"]
    elif row_id == 12 - 1:
        return ["Jasmin"]
    elif row_id == 24 - 1:
        return ["Jasmin"]
    else:
        return [constant("")]


def generate_fls_u08(_faker, row_id):
    """Generates a list containing a single integer."""
    return [constant_u08(row_id)]


def generate_fls_i32(_faker, row_id):
    """Generates a list containing a single integer."""
    return [constant(row_id)]


def generate_fls_i08(_faker, row_id):
    """Generates a list containing a single integer."""
    return [constant(row_id) % 128]


def generate_fls_dbl_func(_faker, row_id):
    """Generates a list containing a single floating-point number."""
    return [constant(row_id + 0.1)]


def generate_float_func(_faker, row_id):
    """Generates a list containing a single floating-point number."""
    return [constant(row_id + 0.32)]


def generate_fls_decimal_func(_faker, row_id):
    """Generates a list containing a single floating-point number."""
    return [constant(row_id + 0.1)]


def generate_languages(faker, row_id):
    """Generates a list containing a single floating-point number."""
    return [faker.language()]


def generate_strings(faker, row_id):
    """Generates a list containing a single floating-point number."""
    LIST = [1]
    size = len(LIST)
    return [LIST[row_id % size]]


def generate_all_types_dbl_i64_struct_str(_faker, row_id):
    """Generates a list of values for example 2."""
    return {
        'COLUMN_1': row_id + 0.1,
        'COLUMN_2': row_id,
        'COLUMN_3': {'FIELD_0': row_id, 'FIELD_1': row_id + 0.1},
        'COLUMN_4': faker.language(),
    }


def generate_x_plus_y_equal_z(faker, row_id):
    """Generates a list of values for example 2."""
    return [
        constant(row_id),
        constant(row_id + 10000000),
        constant(row_id + row_id + 10000000),
    ]


def generate_example_one(faker, row_id):
    NAMES = ["Azim", "Amir", "Ali", "Omid"]

    size_of_list = len(NAMES)

    return [
        NAMES[row_id % size_of_list],
    ]


def generate_mostly_null(faker, row_id):
    NAMES = ["NULL"]

    size_of_list = len(NAMES)

    if row_id % 999 == 0:
        return [row_id + 1000]
    return [
        NAMES[row_id % size_of_list],
    ]


def generate_number_strings_func(faker, row_id):
    NAMES = ["1234", "12335", "135152215", "532552"]

    size_of_list = len(NAMES)

    return [
        NAMES[row_id % size_of_list],
    ]


def generate_decimal_doubles_func(faker, row_id):
    NAMES = ["123.0", "11.0", "105.0", "56.0"]

    size_of_list = len(NAMES)

    return [
        NAMES[row_id % size_of_list],
    ]


def generate_frequency_double_func(faker, row_id):
    if row_id == 924:
        return ["5.5"]
    return ["4.4"]


def generate_frequency_string_func(faker, row_id):
    if row_id == 1:
        return ["EXCEPTION_VALUE_AT_POSITION_1"]
    return ["FREQUENT_VALUE"]


def generate_cross_rle_i16_func(faker, row_id):
    if row_id < 20000:
        return [9999]
    elif row_id < 40000:
        return [8888]
    else:
        return [7777]


def generate_cross_rle_str_func(faker, row_id):
    if row_id < 20000:
        return ["FIRST"]
    elif row_id < 40000:
        return ["SECOND"]
    else:
        return ["THIRD"]


def generate_alp_flt_func(faker, row_id):
    return [row_id + 0.1]


def generate_alp_dbl_func(faker, row_id):
    return [row_id + 0.1]


# ---------------------------
# CSV Generators
# ---------------------------

def one_to_one_i64_to_i64():
    file = Path.cwd() / '..' / 'data' / 'generated' / 'one_to_one'
    write_csv(file, generate_one_to_one_i64_to_i64, VEC_SIZE)


def all_constant():
    file = Path.cwd() / '..' / 'data' / 'generated' / 'all_constant'
    write_csv(file, generate_all_constant, ROW_GROUP_SIZE)


def equality_fls_i64():
    file = Path.cwd() / '..' / 'data' / 'generated' / 'equality' / 'fls_i64'
    write_csv(file, generate_equality_fls_i64, ROW_GROUP_SIZE)


def equality_fls_dbl():
    file = Path.cwd() / '..' / 'data' / 'generated' / 'equality' / 'fls_dbl'
    write_csv(file, generate_equality_fls_dbl, ROW_GROUP_SIZE)


def equality_fls_str():
    file = Path.cwd() / '..' / 'data' / 'generated' / 'equality' / 'fls_str'
    write_csv(file, generate_equality_fls_str, ROW_GROUP_SIZE)


def struct():
    file = Path.cwd() / '..' / 'data' / 'generated' / 'struct'
    write_jsonl(file, generate_struct, 1024)


def write_fls_i64_to_file(sub_path, generator, size):
    file = Path.cwd() / '..' / 'data' / 'generated' / sub_path
    write_csv(file, generator, size)


def write_fls_i32_to_file(sub_path, generator, size):
    file = Path.cwd() / '..' / 'data' / 'generated' / sub_path
    write_csv(file, generator, size)


def write_fls_i08_to_file(sub_path, generator, size):
    file = Path.cwd() / '..' / 'data' / 'generated' / sub_path
    write_csv(file, generator, size)


def write_fls_u08_to_file(sub_path, generator, size):
    file = Path.cwd() / '..' / 'data' / 'generated' / sub_path
    write_csv(file, generator, size)


def fls_i64():
    # one rowgroup
    write_fls_i64_to_file('single_columns/fls_i64', generate_fls_i64, ROW_GROUP_SIZE)

    # one vec
    write_fls_i64_to_file('one_vector/fls_i64', generate_fls_i64, VEC_SIZE)


def generate_irregular_i64():
    file = Path.cwd() / '..' / 'data' / 'generated' / 'single_columns' / 'irregular_i64'
    write_csv(file, generate_irregular_i64_func, ROW_GROUP_SIZE)


def generate_irregular_string():
    file = Path.cwd() / '..' / 'data' / 'generated' / 'single_columns' / 'irregular_string'
    write_csv(file, generate_irregular_string_func, ROW_GROUP_SIZE)


def fls_u08():
    # one rowgroup
    write_fls_u08_to_file('single_columns/fls_u08', generate_fls_u08, ROW_GROUP_SIZE)


def fls_i32():
    # one rowgroup
    write_fls_i32_to_file('single_columns/fls_i32', generate_fls_i32, ROW_GROUP_SIZE)

    # one vec
    write_fls_i32_to_file('one_vector/fls_i32', generate_fls_i32, VEC_SIZE)


def fls_i08():
    # one rowgroup
    write_fls_i08_to_file('single_columns/fls_i08', generate_fls_i08, ROW_GROUP_SIZE)

    # one vec
    write_fls_i08_to_file('one_vector/fls_i08', generate_fls_i08, VEC_SIZE)


def generate_fls_dbl():
    file = Path.cwd() / '..' / 'data' / 'generated' / 'single_columns' / 'fls_dbl'
    write_csv(file, generate_fls_dbl_func, ROW_GROUP_SIZE)

    file = Path.cwd() / '..' / 'data' / 'generated' / 'one_vector' / 'fls_dbl'
    write_csv(file, generate_fls_dbl_func, VEC_SIZE)


def generate_float():
    file = Path.cwd() / '..' / 'data' / 'generated' / 'single_columns' / 'float'
    write_csv(file, generate_float_func, ROW_GROUP_SIZE)

    file = Path.cwd() / '..' / 'data' / 'generated' / 'one_vector' / 'float'
    write_csv(file, generate_float_func, VEC_SIZE)


def generate_fls_decimal():
    file = Path.cwd() / '..' / 'data' / 'generated' / 'single_columns' / 'decimal'
    write_csv(file, generate_fls_dbl_func, ROW_GROUP_SIZE)

    file = Path.cwd() / '..' / 'data' / 'generated' / 'one_vector' / 'decimal'
    write_csv(file, generate_fls_dbl_func, VEC_SIZE)


def fls_str():
    file = Path.cwd() / '..' / 'data' / 'generated' / 'single_columns' / 'fls_str'
    write_csv(file, generate_languages, ROW_GROUP_SIZE)

    file = Path.cwd() / '..' / 'data' / 'generated' / 'one_vector' / 'fls_str'
    write_csv(file, generate_strings, VEC_SIZE)

    file = Path.cwd() / '..' / 'data' / 'generated' / 'two_vector' / 'fls_str'
    write_csv(file, generate_strings, 2 * VEC_SIZE)


def all_types_dbl_i64_struct():
    file = Path.cwd() / '..' / 'data' / 'generated' / 'all_types'
    write_jsonl(file, generate_all_types_dbl_i64_struct_str, ROW_GROUP_SIZE)


def x_plus_y_euqal_z():
    file = Path.cwd() / '..' / 'data' / 'generated' / 'whitebox' / 'x_plus_y_equal_z'
    write_csv(file, generate_x_plus_y_equal_z, ROW_GROUP_SIZE)


def null_table():
    file = Path.cwd() / '..' / 'data' / 'generated' / 'mostly_null'
    write_csv(file, generate_mostly_null, ROW_GROUP_SIZE)


def generate_number_strings():
    file = Path.cwd() / '..' / 'data' / 'generated' / 'whitebox' / 'number_strings'
    write_csv(file, generate_number_strings_func, VEC_SIZE)


def generate_decimal_doubles():
    file = Path.cwd() / '..' / 'data' / 'generated' / 'whitebox' / 'decimal_doubles'
    write_csv(file, generate_decimal_doubles_func, VEC_SIZE)


def generate_frequency_double():
    file = Path.cwd() / '..' / 'data' / 'generated' / 'encodings' / 'frequency_dbl'
    write_csv(file, generate_frequency_double_func, VEC_SIZE)


def generate_frequency_string():
    file = Path.cwd() / '..' / 'data' / 'generated' / 'encodings' / 'frequency_str'
    write_csv(file, generate_frequency_string_func, ROW_GROUP_SIZE)


def generate_cross_rle_i16():
    file = Path.cwd() / '..' / 'data' / 'generated' / 'encodings' / 'cross_rle_i16'
    write_csv(file, generate_cross_rle_i16_func, ROW_GROUP_SIZE)


def generate_cross_rle_str():
    file = Path.cwd() / '..' / 'data' / 'generated' / 'encodings' / 'cross_rle_str'
    write_csv(file, generate_cross_rle_str_func, ROW_GROUP_SIZE)


def generate_alp_flt():
    file = Path.cwd() / '..' / 'data' / 'generated' / 'encodings' / 'alp_flt'
    write_csv(file, generate_alp_flt_func, ROW_GROUP_SIZE)


def generate_alp_dbl():
    file = Path.cwd() / '..' / 'data' / 'generated' / 'encodings' / 'alp_dbl'
    write_csv(file, generate_alp_dbl_func, ROW_GROUP_SIZE)


def generate_specific_number_of_values(count):
    # one rowgroup
    write_fls_i64_to_file('any_value_count/' + str(count), generate_fls_i64, count)


# ---------------------------
# Main Generation Functions
# ---------------------------

def generate_nested_data():
    struct()


def generate_single_column():
    fls_i64()
    fls_i32()
    fls_i08()
    fls_u08()
    fls_str()
    generate_fls_dbl()
    generate_fls_decimal()
    generate_float()


def generate_irregular_data():
    generate_irregular_i64()
    generate_irregular_string()


def generate_any_value_count():
    counts = [1, 666, 25570]
    for count in counts:
        generate_specific_number_of_values(count)


def generate_expression_data():
    generate_frequency_double()
    generate_frequency_string()
    generate_cross_rle_i16()
    generate_cross_rle_str()
    generate_alp_flt()
    generate_alp_dbl()


def equality():
    equality_fls_i64()
    equality_fls_dbl()
    equality_fls_str()


def all_types():
    all_types_dbl_i64_struct()


def whitebox():
    x_plus_y_euqal_z()
    generate_number_strings()
    generate_decimal_doubles()


def one_to_one():
    one_to_one_i64_to_i64()


def mostly_null():
    null_table()


# ---------------------------
# Main Function
# ---------------------------

def main():
    all_constant()
    equality()
    generate_single_column()
    generate_nested_data()
    all_types()
    one_to_one()
    whitebox()
    mostly_null()
    generate_expression_data()
    generate_irregular_data()
    generate_any_value_count()


if __name__ == "__main__":
    main()
