import re

from os.path import exists
from sys import argv

if __name__ == "__main__":
    if len(argv) > 1:
        if argv[1] in ["-h", "--help"]:
            print("File name: ./lab2.py 'file name.txt'")
        else:
            if argv[1].endswith(".txt"):
                if exists(argv[1]):
                    with open(argv[1], "r") as f:
                        txt = f.read().lower()
                        orig = set(txt)
                        for i, c in enumerate(set(txt)):
                            print(i, " ", c, " ", re.findall(r"\d", txt))
                else: print("Error: File not found")
            else: print("Error: File name must be end with .txt")
    else: print("Error: File name not found")