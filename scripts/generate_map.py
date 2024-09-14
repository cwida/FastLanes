def print_offset_map():
    for i in range(0, 256):
        print(bin(i).count("1"), end=",")


# FROM CHATGPT
def indices_of_bits_set_to_1(n):
    indices = []
    binary_representation = bin(n)[2:]  # Get binary representation of the number and strip the '0b' prefix
    length = len(binary_representation)

    for i, bit in enumerate(binary_representation):
        if bit == '1':
            indices.append(length - 1 - i)

    return indices


def print_index_arr():
    lane_index_arr = [0, 128, 256, 384, 512, 640, 768, 896]
    for n in range(0, 256):
        #
        array = indices_of_bits_set_to_1(n)
        reversed_array = list(reversed(array))
        array_length = len(array)
        gap = 8 - len(array)

        for index in reversed_array:
            print(lane_index_arr[index], end=',')
        for i in range(0, gap):
            print(0, end=',')
        print(f"// index = {n} , binary {bin(n)}")


def main():
    print_offset_map()
    # print_index_arr()


if __name__ == "__main__":
    main()
