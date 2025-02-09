import re

def task1():
    out = "Некорректный формат!"
    try:
        num = str(float(input("Введите число: ").replace(",", ".")))
        out = "{} руб. {} коп.".format(*num.split(".")) if num[0] != "-" else out
    except: pass

    return out

def task2(arr: list):
    out = "True"
    tmp = type(arr[0]) if len(arr) > 1 else None
    mx = arr[0]

    if tmp is not None:
        for i in range(1, len(arr)):
            if type(arr[i]) == tmp and mx < arr[i]:
                mx = arr[i]
            else: out = "False"
        
    return out

def task3(card: str):
    return card[0:4] + ('*'*8) + card[-4:]

def task4(words: str):
    # replace по знакам припинания и пробелам
    words = re.sub(r"[.,!?:;]", "", words)
    words = words.split(" ")
    # теперь посчитать количество символов в каждом слове и вывести сначала слова от 7 символов, после от 4 до 7, а вконце оставшиеся
    print("Bigger than 7:\n" + " ".join([word for word in words if len(word) >= 7]))
    print("Between 4 and 7:\n" + " ".join([word for word in words if len(word) >= 4 and len(word) < 7]))
    print("Less than 4:\n" + " ".join([word for word in words if len(word) < 4]))

def task5():
    s = input("Введите текст: ")
    words = s.split(" ")
    res = ""
    for word in words:
        res += word.upper() + " " if len(word) != 0 and word[0].isupper() else word + " "
    return res

def task6():
    s = input("Введите текст: ")
    res = set(s)
    print(res)

def task7(arr: list[str]):
    res = [ ("https://" if i[0:3] == "www" else "") + i + (".com" if i[-3:] != "com" else "") for i in arr ]
    print("Changed List:")
    for i in range(len(res)):
        print(f"{ i } -> { res[i] }")
        

if __name__ == "__main__":
    print(task7(["iorgoierhg", "ropegjier", "www.iorgoierhg", "www.ropegjier"]))