from re import sub, findall
from math import sqrt, ceil, log
from random import randint
from functools import reduce

def task1() -> str:
    out = "Некорректный формат!"
    try:
        num = str(float(input("Введите число: ").replace(",", ".")))
        out = "{} руб. {} коп.".format(*num.split(".")) if num[0] != "-" else out
    except: pass

    return out

def task2(arr: list) -> str:
    out = "True"
    tmp = type(arr[0]) if len(arr) > 1 else None
    mx = arr[0]

    if tmp is not None:
        for i in range(1, len(arr)):
            if type(arr[i]) == tmp and mx < arr[i]:
                mx = arr[i]
            else: out = "False"
        
    return out

def task3(card: str) -> str:
    return card[0:4] + ('*'*8) + card[-4:]

def task4(words: str) -> None:
    # replace по знакам припинания и пробелам
    words = sub(r"[.,!?:;]", "", words)
    words = words.split(" ")
    # теперь посчитать количество символов в каждом слове и вывести сначала слова от 7 символов, после от 4 до 7, а вконце оставшиеся
    print("Bigger than 7:\n" + " ".join([word for word in words if len(word) >= 7]))
    print("Between 4 and 7:\n" + " ".join([word for word in words if len(word) >= 4 and len(word) < 7]))
    print("Less than 4:\n" + " ".join([word for word in words if len(word) < 4]))

def task5() -> str:
    s = input("Введите текст: ")
    words = s.split(" ")
    res = ""
    for word in words:
        res += word.upper() + " " if len(word) != 0 and word[0].isupper() else word + " "
    return res

def task6() -> None:
    s = input("Введите текст: ")
    words = sub(r"[.,!?:;]", "", s)
    words = words.split(" ")
    print([ word for word in words if len(word) == 1 ])

def task7(arr: list[str]) -> None:
    res = [ ("https://" if i[0:3] == "www" else "") + i + (".com" if i[-3:] != "com" else "") for i in arr ]
    print("Changed List:")
    for i in range(len(res)):
        print(f"{ i } -> { res[i] }")
        
def task8() -> list[int]:
    n = randint(1, 100)
    d = 2**n.bit_length()
    return [ randint(1, n) if i < n else 0 for i in range(d) ]

def task9(money: int=13_146) -> None: # проверка на корректность
    out = []
    
    honor = 5000, 2000, 1000, 500, 200, 100, 50, 10, 5, 2, 1
    for i in honor:
        if (money // i) != 0: out.append(f"{money // i}*{i}")
        money %= i
    return " + ".join(out)

def task10() -> None:
    value = 0
    counts = 0
    pattern = {
        r"[ -\/\:-@\][-`}{-~\"]": 33,
        r"[A-Z]": 26,
        r"[a-z]": 26,
        r"[0-9]": 10
    }
    
    pas = input("Введите пароль: ")
    if 1 <= len(pas) <= 10:
        print("Пароль не надежен!")
        return
        
    for i in pattern.keys():
        if value := value + len(findall(i, pas)):
            counts += pattern[i]

    sl = pow(counts, value)
    entropy = log(sl, 2)
    entropy = round(entropy, 2)
    if entropy < 55:
        print(f"Ваш пароль не достаточно надежен. Ваша энтропия равна {entropy}")
    elif 55 < entropy < 100:
        print(f"Ваш пароль достаточно надежен. Ваша энтропия равна {entropy}")
    else:
        print(f"Ваш пароль очень надежен. Ваша энтропия равна {entropy}")

def task11(start: float=1, end: float=5, step: float=.4) -> list[float]:
    data = int(start*10), int(end*10), int(step*10)
    out = [ i/10 for i in range(*data) ]
    return out

def extra_enumerate(iterable, start=0):
    if len(iterable) > 1:
        m = sum(iterable)
        out, last, index = [], 0, 0
        for i in iterable:
            out.append((index, i, last + i, round((last+i)/m, 1)))
            last += i
            index += 1
        return out

def task13() -> None:
    for i, elem, sam, frac in extra_enumerate([ 7, 4, 1 ]):
        print(elem, sam, frac)

# task14
def non_empty(func):
    def wrapper():
        return list(filter(None, func()))
    return wrapper

@non_empty
def get_pages():
    return ["chapter1", "", "content", "", "line1"]

if __name__ == "__main__":
    print(task13())