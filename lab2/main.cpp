#include <iostream>
#include <stdexcept>

using namespace std;

template<class T1>
class Vector {
    T1 *arr;
    int length;
public:
    Vector() {
        this->length = 2;
        this->arr = new T1[2]{0, 0};
    }

    Vector(int len) {
        this->length = len;
        this->arr = new T1[len]{0};
    }

    Vector(T1* arr) {
        int i;
        for (i = 0; 1; ++i)
            if (arr[i] == NULL) break;
        this->length = ++i;
        this->arr = arr;
    }
    
    // Matrix<T1> arr
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

    // getter
    int Length() { return this->length; }

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
        if (this->arr != NULL)
            delete [] this->arr; // maybe error, test -> delete arr;
    }
};

template<class T2>
class Matrix {
    T2 **arr;
    int rows, cols;
public:
    Matrix() {
        cout << "Data created" << endl;
        rows = 2; cols = 2;
        this->arr = new T2*[rows];
        for (int i = 0; i < rows; ++i)
            this->arr[i] = new T2[cols]{ 0, 1 };
    }
    
    Matrix(int m, int n) {
        rows = m; cols = n;
        this->arr = new T2*[rows];
        for (int i = 0; i < rows; ++i)
            this->arr[i] = new T2[cols] { 0, 1 };
    }
    
    Matrix(T2 **arr) { this->arr = arr; }
    
    Matrix(Vector<T2>& arr): arr(nullptr) {
        int test_size = arr.Length() / 5; // 5 3
        if (test_size == 3) {
            this->rows = 5;
            this->cols = 3;
            this->arr = new int*[5];

            for (int i = 0; i < this->rows; ++i) {
                this->arr[i] = new int[3];
                for (int j = 0; j < this->cols; ++j) {
                    this->arr[i][j] = arr[i * cols + j];
                }
            }
        }
    }
    //=====================//
    T2& at(int i, int j) const {
        if (i >= 0 && j >= 0)
            return this->arr[i][j];
        else throw std::invalid_argument( "received negative value" );
    }

    void setAt(int i, int j, T2 val) {
        if (i >= 0 && j >= 0)
            this->arr[i][j] = val;
    }

    int getRows() const { return this->rows; }

    int getCols() const { return this->cols; }

    //=====================//
    void operator ++() { // pre
        for (int i = 0; i < this->rows; ++i) {
            for (int j = 0; j < this->cols; ++j)
                ++this->arr[i][j];
        }
    }
    void operator --() {
        for (int i = 0; i < this->rows; ++i) {
            for (int j = 0; j < this->cols; ++j)
                --this->arr[i][j];
        }
    }
    void operator ++(T2 obj) { // post
        for (int i = 0; i < this->rows; ++i) {
            for (int j = 0; j < this->cols; ++j)
                ++this->arr[i][j];
        }
    }
    void operator --(T2 obj) {
        for (int i = 0; i < this->rows; ++i) {
            for (int j = 0; j < this->cols; ++j)
                --this->arr[i][j];
        }
    }

    friend ostream& operator<<(ostream& os, const Matrix<T2>& out) {
        os << "[";
        for (int i = 0; i < out.getRows(); ++i) {
            os << endl;
            os << "\t";
            for (int j = 0; j < out.getCols(); ++j)
                os << out.at(i, j) << ", ";
        }
        os << "\n]\n";
        return os;
    }

    ~Matrix() {
        if (arr != NULL) {
            for (int i = 0; i < rows; ++i)
                if (this->arr[i] != NULL)
                    delete [] this->arr[i];
            delete [] this->arr;
        }
    }
};

int main() {
    // int** array = new int*[3];
    // for (int i = 0; i < 3; ++i) {
    //     array[i] = new int[3];
    //     for (int j = 0; j < 3; ++j)
    //         array[i][j] = j+1;

    // for (int i = 0; i < 3; ++i)
    //     delete [] array[i];
    // delete [] array;

    int* c {new int[15]{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15}};
    Vector<int> a{c};
    Matrix<int> b{a};
    ++b;
    b++;
    b--;
    --b;
    cout << b;
    
    return 0;
}