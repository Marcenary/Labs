#include <iostream>

using namespace std;

template<class T1>
class Vector {
    T1 *arr;
    int length;
public:
    Vector() {
        arr = NULL;
    }

    Vector(int len) {
        length = len;
        arr = new T1[len];
    }

    Vector(T1 *arr) {
        this->arr = arr;
    }
    
    Vector(T1 **arr) { // конвертировать двумерную матрицу в вектор
        return;
    }

    T1 operator[] (const int id) { return arr[id]; }
    // T1& operator ++() { // pre

    // }
    // T1& operator --() {

    // }
    // T1 operator ++(T1) { // post

    // }
    // T1 operator --(T1) {

    // }
    friend ostream& operator<<(ostream& os, const T1 out) {
        os << "[\n";
        os << out << endl; // ?
        os << "\n]";
    }

    ~Vector() {
        if (arr != NULL)
            delete arr;
    }
};

template<class T2>
class Matrix {
    T2 **arr;
public:
    Vector() arr(NULL) {  }
    
    Vector(int m, int n) {
        arr = new T2*[m];
        for (int i=0; i<n; ++i)
            arr[i] = new T2[n] { };
    }
    
    Vector(T2 **arr) {
        this->arr = arr;
    }
    
    Vector(Vector arr) {
        arr = NULL;
    }
    /*=====================*/
    T2 at(int i, int j) const {

    }

    void setAt(int i, int j, T2 val) {

    }
    /*=====================*/
    // T2& operator ++() { // pre

    // }
    // T2& operator --() {

    // }
    // T2 operator ++(T2) { // post

    // }
    // T2 operator --(T2) {

    // }
    friend ostream& operator<<(ostream& os, const T2 out) {
        os << "[\n";
        os << out << endl; // ?
        os << "\n]";
    }
};

int main() {

    return 0;
}