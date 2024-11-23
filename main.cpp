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
        
    }

    T1& operator[] (const int id) const {
        return this->arr[id];
    }

    void show() {
        cout << "(";
        for (int i = 0; i < this->length; ++i) {
            cout << " " << this->arr[i] << ", ";
        }
        cout << ")\n";
    }
    // T1& operator ++() { // pre

    // }
    // T1& operator --() {

    // }
    // T1 operator ++(T1) { // post

    // }
    // T1 operator --(T1) {

    // }
    friend ostream& operator<<(ostream& os, const T1& out) {
        if (out.arr != NULL) {
            os << "(\n";
            for (int i = 0; i < out.length; ++i) {
                os << out[i] << endl;
            }
            os << "\n)";
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
    cout << a;
    a[0] = 2;
    a[1] = 1;
    cout << a << endl;
    // a.show();
    return 0;
}