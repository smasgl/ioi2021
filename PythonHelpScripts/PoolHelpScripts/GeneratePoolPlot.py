import argparse
import os
import json
import matplotlib.pyplot as plt


class ArgParser:
    def __init__(self):
        self.arg_parser = argparse.ArgumentParser(prog="(GeneratePoolPlot)", add_help=True)

        # Mandatory args
        self.arg_parser.add_argument("file_path", metavar='-FilePath', type=str, action="store",
                                     help="path of the file where the list of pool elements is saved")

    def extract_args(self):
        try:
            return self.arg_parser.parse_args()
        except argparse.ArgumentError:
            self.arg_parser.print_help()
            sys.exit(2)


def main():
    args = ArgParser().extract_args()

    file_path = args.file_path

    if not os.path.exists(file_path):
        print("File doesn't exist, please check the file and try again!")
        sys.exit(-1)

    rand_list = list()

    with open(file_path, 'r') as f:
        rand_list = json.loads(f.read())
    print(rand_list)
    s = [str(i) for i in rand_list]
    plt.bar(s, rand_list)
    plt.show()


if __name__ == "__main__":
    main()
