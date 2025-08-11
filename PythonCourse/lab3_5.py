import tkinter as tk
from tkinter import messagebox

class StringFormatterApp:
    def __init__(self, root):
        self.root = root
        self.root.title("StringFormatter Demo")

        # Строка ввода
        self.input_label = tk.Label(root, text="Строка:")
        self.input_label.pack()
        self.input_entry = tk.Entry(root, width=50)
        self.input_entry.pack()

        # Чекбоксы
        self.remove_small_words_var = tk.BooleanVar()
        self.remove_small_words_check = tk.Checkbutton(root, text="Удалить слова размером меньше", variable=self.remove_small_words_var)
        self.remove_small_words_check.pack()

        self.remove_small_words_size_entry = tk.Entry(root, width=5)
        self.remove_small_words_size_entry.insert(0, "5")
        self.remove_small_words_size_entry.pack()

        self.replace_all_digits_var = tk.BooleanVar()
        self.replace_all_digits_check = tk.Checkbutton(root, text="Заменить все цифры на *", variable=self.replace_all_digits_var)
        self.replace_all_digits_check.pack()

        self.insert_spaces_var = tk.BooleanVar()
        self.insert_spaces_check = tk.Checkbutton(root, text="Вставлять по пробелу между символами", variable=self.insert_spaces_var)
        self.insert_spaces_check.pack()

        self.sort_words_var = tk.BooleanVar()
        self.sort_words_check = tk.Checkbutton(root, text="Сортировать слова в строке", variable=self.sort_words_var)
        self.sort_words_check.pack()

        # Переключатель для выбора сортировки
        self.sort_option = tk.StringVar(value="lexicographically")
        self.sort_lexicographically_radio = tk.Radiobutton(root, text="Лексикографически", variable=self.sort_option, value="lexicographically")
        self.sort_lexicographically_radio.pack()
        self.sort_by_size_radio = tk.Radiobutton(root, text="По размеру", variable=self.sort_option, value="by_size")
        self.sort_by_size_radio.pack()

        # Кнопка форматирования
        self.format_button = tk.Button(root, text="Форматировать", command=self.format_string)
        self.format_button.pack()

        # Поле результата
        self.result_label = tk.Label(root, text="Результат:")
        self.result_label.pack()
        self.result_entry = tk.Entry(root, width=50)
        self.result_entry.pack()

    def format_string(self):
        input_string = self.input_entry.get()

        if self.remove_small_words_var.get():
            try:
                size = int(self.remove_small_words_size_entry.get())
                input_string = self.remove_small_words(input_string, size)
            except ValueError:
                messagebox.showerror("Ошибка", "Некорректное значение размера слова")

        if self.replace_all_digits_var.get():
            input_string = self.replace_all_digits(input_string)

        if self.insert_spaces_var.get():
            input_string = self.insert_spaces(input_string)

        if self.sort_words_var.get():
            if self.sort_option.get() == "lexicographically":
                input_string = self.sort_lexicographically(input_string)
            elif self.sort_option.get() == "by_size":
                input_string = self.sort_by_size(input_string)

        self.result_entry.delete(0, tk.END)
        self.result_entry.insert(0, input_string)

    def remove_small_words(self, s, size):
        words = s.split()
        filtered_words = [word for word in words if len(word) >= size]
        return ' '.join(filtered_words)

    def replace_all_digits(self, s):
        return ''.join(['*' if c.isdigit() else c for c in s])

    def insert_spaces(self, s):
        return ' '.join(list(s))

    def sort_lexicographically(self, s):
        return ' '.join(sorted(s.split()))

    def sort_by_size(self, s):
        return ' '.join(sorted(s.split(), key=len))

if __name__ == "__main__":
    root = tk.Tk()
    app = StringFormatterApp(root)
    root.mainloop()
