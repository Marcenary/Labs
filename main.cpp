#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

// Шаблонный класс Cache<T>
template <typename T>
class Cache {
private:
    std::vector<T> data;

public:
    // Метод добавления элемента в кеш
    void put(T elem) {
        data.push_back(elem);
    }

    // Оператор += для добавления элемента
    Cache& operator+=(T elem) {
        put(elem);
        return *this;
    }

    // Метод проверки наличия элемента в кеше
    bool contains(T elem) const {
        return std::find(data.begin(), data.end(), elem) != data.end();
    }
};

// Специализация шаблона для типа std::string
template <>
class Cache<std::string> {
private:
    std::vector<std::string> data;
    static const size_t MAX_SIZE = 100;

public:
    // Метод добавления строки в кеш
    void put(std::string elem) {
        if (data.size() >= MAX_SIZE) {
            throw std::overflow_error("Cache is full: cannot add more than 100 strings.");
        }
        data.push_back(elem);
    }

    // Оператор += для добавления строки
    Cache& operator+=(std::string elem) {
        put(elem);
        return *this;
    }

    // Метод проверки наличия строки в кеше (по первому символу)
    bool contains(std::string elem) const {
        if (elem.empty()) {
            return false;
        }
        char firstChar = elem[0];
        for (const auto& str : data) {
            if (!str.empty() && str[0] == firstChar) {
                return true;
            }
        }
        return false;
    }
};

int main() {
    try {
        Cache<int> cache;
        cache.put(1); // так должно работать
        cache.put(2);
        cache.put(3);
        cache += 5; // так тоже должно работать

        std::cout << "Cache<int> contains 5: " << cache.contains(5) << std::endl; // 1

        Cache<std::string> voc;
        voc.put("OK");
        voc.put("Hello");
        voc.put("World");

        std::cout << "Cache<std::string> contains 'Only': " << voc.contains("Only") << std::endl; // 1 (совпадение по 'O')
        std::cout << "Cache<std::string> contains 'Bye': " << voc.contains("Bye") << std::endl;  // 0 (нет совпадения)

    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }

    return 0;
}
