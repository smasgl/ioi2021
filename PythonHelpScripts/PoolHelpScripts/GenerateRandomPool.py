import random
import json


def generate_random_list(elements_count):
    rand_list = list(range(1, elements_count + 1))
    random.shuffle(rand_list)
    return rand_list


def generate_random_file_name():
    code = ''
    for i in range(6):
        code += str(random.randint(0, 9))
    return code


def save_list_to_file(rand_list):
    with open(f'{generate_random_file_name()}.txt', 'w') as f:
        f.write(json.dumps(rand_list))


def main():
    while True:
        try:
            elements = int(input("enter number of elements: "))

            if elements < 3:
                print("enter a number bigger than 2!")
            else:
                break

        except:
            print("couldn't convert input to int!")

    rand_list = generate_random_list(elements)
    print(rand_list)
    save_list_to_file(rand_list)


if __name__ == "__main__":
    main()
