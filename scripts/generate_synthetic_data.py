import os
from faker import Faker
from faker.providers import BaseProvider
import random
import csv


# create new provider class
class LanguageProvider(BaseProvider):
    def language(self):
        return random.choice(['English', 'Chinese', 'Italian', 'Spanish', 'Hindi', 'Japanese'])


class NumberStrings(BaseProvider):
    def number_as_string(self):
        return random.choice(['1', '12', '123', '1234', '12345', '123456'])


def range_x_to_y(x, y):
    return random.randrange(x, y)


def constant(number):
    return number


def map(row_id, is_string):
    strings = ['one', 'two', 'three', 'four', 'five', 'six', 'seven', 'eight', 'nine', 'ten']
    numbers = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
    if is_string:
        return strings[row_id % 10]
    else:
        return numbers[row_id % 10]


def generate_example_1(faker, row_id):
    return [  #
        constant(13700525),  # 0) CONSTANT INT ---  COL WITH VALUE 13700525
        constant("THIS IS CONSTANT"),  # 1) CONSTANT STR COL WITH VALUE THIS IS CONSTANT
        constant(row_id),  # 2) EQUAL_GROUP_0_COL_0
        range_x_to_y(0, 1000),  # 3) RANGE_0_1000
        faker.number_as_string(),  # 4) NUMBER_AS_STRING
        constant(row_id),  # 5) EQUAL_GROUP_0_COL_1
        constant(row_id),  # 6) EQUAL_GROUP_0_COL_2
        map(row_id, True),  # 7) MAP1T1_GROUP_0_COL_0
        map(row_id, False),  # 8) MAP1T1_GROUP_0_COL_1
        #
    ]


def generate_example_2(faker, row_id):
    return [  #
        constant(row_id),  # 0) CONSTANT INT ---  COL WITH VALUE 13700525
        #
    ]


faker = Faker()
faker.add_provider(LanguageProvider)
faker.add_provider(NumberStrings)


def write_file(file_path, generate_func):
    file_path = file_path

    with open(file_path, 'w', newline='\n') as csvfile:
        writer = csv.writer(csvfile, delimiter='|')
        for row_id in range(0, 64 * 1024):
            writer.writerow(generate_func(faker, row_id))


def example_1():
    file = os.path.join(os.getcwd(), '../data/generated/example_1/generated.csv')
    write_file(file, generate_example_1)


def example_2():
    file = os.path.join(os.getcwd(), '../data/generated/example_2/generated.csv')
    write_file(file, generate_example_2)


def main():
    example_1()
    example_2()


if __name__ == "__main__":
    main()
