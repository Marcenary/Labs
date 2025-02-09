#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

template <typename T>
class Cache {
private:
    std::vector<T> data;

public:
    void put(const T& elem) {
        data.push_back(elem);
    }

    Cache<T>& operator+=(const T& elem) {
        put(elem);
        return *this;
    }

    bool contains(const T& elem) const {
        return std::find(data.begin(), data.end(), elem) != data.end();
    }
};

// Специализация для std::string
template <>
class Cache<std::string> {
private:
    std::vector<std::string> data;
    static constexpr size_t MAX_SIZE = 100;

public:
    void put(const std::string& elem) {
        if (data.size() >= MAX_SIZE) {
            throw std::overflow_error("Cache overflow: max size reached");
        }
        data.push_back(elem);
    }

    Cache<std::string>& operator+=(const std::string& elem) {
        put(elem);
        return *this;
    }

    bool contains(const std::string& elem) const {
        return std::any_of(data.begin(), data.end(), [&](const std::string& str) {
            return !str.empty() && str[0] == elem[0];
        });
    }
};

int main() {
    Cache<int> cache;
    cache.put(1);
    cache.put(2);
    cache.put(3);
    cache += 5;

    std::cout << cache.contains(5) << std::endl; // Должно вывести 1 (true)
    std::cout << cache.contains(7) << std::endl; // Должно вывести 0 (false)

    Cache<std::string> voc;
    voc.put("OK");

    std::cout << voc.contains("Only") << std::endl; // Должно вывести 1 (по первой букве)
    std::cout << voc.contains("Test") << std::endl; // Должно вывести 0

    return 0;
}
