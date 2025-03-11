import os
import os.path as path

from re import findall, match, search
from hashlib import md5
from sys import argv

FLAGS = {
    "-h": "lab2\n\nOptional arguments:\n\t-h, --help - Помощь\n\t-t, --task [number task] [...optionals] - Задание",
    "-f": "Название файла",
}

def task1(name: str, out: str = "") -> str:
    if name.endswith(".txt"):
        if path.exists(name):
            with open(name, "r") as f:
                txt  = findall(r"[a-zA-Zа-яА-Я]", f.read().lower())
                dest = { i: txt.count(i) for i in sorted(set(txt)) }
                return str(dict(sorted(dest.items(), key=lambda x: x[1])))
        else: out = "Error: File not found or use local path"
    else: out = "Error: File name must be end with .txt"
    return out

def task2(out: list = []) -> list[str]:
    dr = "./"
    cmp  = {}

    for (root, dirs, files) in os.walk(dr):
        for file in files:
            name = path.join(root, file)
            with open(name, "rb") as f:
                hsum = md5(f.read()).hexdigest()
            
                if hsum in cmp.values():
                    out.append(name)
                    continue
                cmp[name] = hsum
    return out

def task3() -> str:
    return "Error: Not implemented"

def task4(out: str="") -> str:
    name = input("Enter name of file: ")
    # name = "task4.txt"
    if path.exists(name):
        with open(name, "r") as f:
            lines =  f.readlines()
            for i in range(len(lines)):
                searched = search(r"(int|short|byte) [a-zA-Z]* = \d*", lines[i])
                if searched != None:
                    index = searched.start() if searched != None else None
                    out += f"Строка {i+1:3}, позиция {index:3} : найдено '{ searched.group() }'\n"
    else:
        return "File error: File not exsists!"
    return out

def task5(out: str="") -> str:
    txt = input("Enter text: ")
    out += ", ".join(findall(r"[A-Z]{1}[A-Za-z]+\d{2,4}", txt))
    return out

if __name__ == "__main__":
    if len(argv) > 1:
        if argv[1] in ["-h", "--help"]:
            print(FLAGS["-h"])
        if argv[1] in ["-t", "--task"] and len(argv) >= 2:
            try: 
                if argv[2] == "1" and len(argv) > 3:
                    print(task1(argv[3]))
                elif argv[2] == "2":
                    print(task2())
                elif argv[2] == "3":
                    print(task3())
                elif argv[2] == "4":
                    print(task4())
                elif argv[2] == "5":
                    print(task5())
                else: print("Error: Не известное задание")
            except Exception as e: print(repr(e))
        else: print("Error: Не известная команда")