#include <iostream>

using namespace std;

template<class T1>
class Vector {
    T1 *arr;
    int length;
public:
    Vector() {
        length = 2;
        arr = new T1[2]{0, 0};
    }

    Vector(int len) {
        length = len;
        arr = new T1[len];
    }

    Vector(T1 *arr) {
        this->arr = arr;
    }
    
    Vector(T1 **arr) { // конвертировать двумерную матрицу в вектор
        // int n=5, m=5;
        // T1 *narray = new T1[n * m];
        // int count = 0;
        // for (int i = n-1; i >= 0; --i) {
        //     for (int j = 0; j < m; ++j) {
        //         narray[count] = array[i][j];
        //         count++;
        //     }
        // }
        // return narray;
    }

    T1& operator[] (const int id) const { return this->arr[id]; }
    void operator ++() { // pre ++a
        for (int i = 0; i < this->length; ++i)
            ++this->arr[i];
    }
    void operator --() {
        for (int i = 0; i < this->length; ++i)
            --this->arr[i];
    }
    void operator ++(T1 obj) { // post a++
        for (int i = 0; i < this->length; ++i)
            ++this->arr[i];
    }
    void operator --(T1 obj) {
        for (int i = 0; i < this->length; ++i)
            --this->arr[i];
    }

    friend ostream& operator<<(ostream& os, const Vector<T1>& out) {
        if (out.arr != NULL) {
            os << "(";
            for (int i = 0; i < out.length; ++i)
                os << out[i] << ", ";
            os << ")\n";
        }
        return os;
    }

    ~Vector() {
        if (arr != NULL)
            delete arr;
    }
};

// template<class T2>
// class Matrix {
//     T2 **arr;
// public:
//     Vector() arr(NULL) {  }
    
//     Vector(int m, int n) {
//         arr = new T2*[m];
//         for (int i=0; i<n; ++i)
//             arr[i] = new T2[n] { };
//     }
    
//     Vector(T2 **arr) {
//         this->arr = arr;
//     }
    
//     Vector(Vector arr) {
//         arr = NULL;
//     }
//     /*=====================*/
//     T2 at(int i, int j) const {

//     }

//     void setAt(int i, int j, T2 val) {

//     }
//     /*=====================*/
//     // T2& operator ++() { // pre

//     // }
//     // T2& operator --() {

//     // }
//     // T2 operator ++(T2) { // post

//     // }
//     // T2 operator --(T2) {

//     // }
//     friend ostream& operator<<(ostream& os, const T2 out) {
//         os << "[\n";
//         os << out << endl; // ?
//         os << "\n]";
//     }
// };

int main() {
    Vector<int> a;
    a[0] = 2;
    a[1] = 1;
    ++a;
    a++;
    cout << "" << a;
    --a;
    a--;
    cout << "" << a;
    return 0;
}