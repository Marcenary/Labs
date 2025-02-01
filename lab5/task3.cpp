#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <locale>

class Book {
private:
    std::string name;
    std::string author;
    int year;

public:
    Book(const std::string& name, const std::string& author, int year)
        : name(name), author(author), year(year) {}

    std::string getName() const { return name; }
    std::string getAuthor() const { return author; }
    int getYear() const { return year; }
};

class BookSorter {
public:
    bool operator()(const Book* book1, const Book* book2) const {
        if (book1->getAuthor() == book2->getAuthor())
            return book1->getName() < book2->getName();
        return book1->getAuthor() < book2->getAuthor();
    }
};

class BookFinder {
private:
    int startYear;
    int endYear;

public:
    BookFinder(int startYear, int endYear) : startYear(startYear), endYear(endYear) {}

    bool operator()(const Book* book) const {
        return book->getYear() >= startYear && book->getYear() <= endYear;
    }
};

int main() {
    system("chcp 65001");

    std::vector<Book*> books;
    books.push_back(new Book("Война и мир", "Толстой Л.Н.", 2010));
    books.push_back(new Book("Подросток", "Достоевский Ф.М.", 2004));
    books.push_back(new Book("Обрыв", "Гончаров И.А.", 2010));
    books.push_back(new Book("Анна Каренина", "Толстой Л.Н.", 1999));
    books.push_back(new Book("Обыкновенная история", "Гончаров И.А.", 2011));
    books.push_back(new Book("Утраченные иллюзии", "Бальзак О.", 2009));
    books.push_back(new Book("Оливер Твист", "Диккенс Ч.", 2001));
    books.push_back(new Book("Фауст", "Гёте И.В.", 2010));
    books.push_back(new Book("Лилия долины", "Бальзак О.", 1998));

    std::cout << "\nКниги в алфавитном порядке:\n\n";
    BookSorter book_sorter;
    std::sort(books.begin(), books.end(), book_sorter);

    for (const auto& book : books)
        std::cout << book->getAuthor() << " \"" << book->getName() << "\"" << std::endl;

    BookFinder book_finder(2005, 2014);
    auto finder = std::find_if(books.begin(), books.end(), book_finder);

    std::cout << "\nКниги в диапазоне года издания 2005 - 2014:\n\n";
    while (finder != books.end()) {
        std::cout << (*finder)->getAuthor() << " \"" << (*finder)->getName() << "\"" << std::endl;
        finder = std::find_if(++finder, books.end(), book_finder);
    }

    for (auto& book : books)
        delete book;

    return 0;
}