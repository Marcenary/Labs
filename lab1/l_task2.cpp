#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdio>
#include <cstring>

using namespace std;

int n, m;

float** init();
float* transform(float**);
void display(float**);
void free(float**);

int main(int argc, char *argv[]) {
    n = 5, m = 3;
    float** a = init();
    display(a);
 
    float* b = transform(a);
    cout << "=>\n[";
    for (int i = 0; i < 15; ++i)
        cout << b[i] << " ";
    cout << "]\n";
 
    delete[] b;
    free(a);
}

float** init() {
    float** array = new float*[n];
    for (int i = 0; i < n; ++i) {
        array[i] = new float[m]{};
    
        for (int j = 0; j < m; ++j) {
            array[i][j] = sin(i-j) + cos(i+j);
        }
    }
    return array;
}

float* transform(float** array) {
    float* narray = new float[n * m];
    int count = 0;
    for (int i = n-1; i >= 0; --i) {
        for (int j = 0; j < m; ++j) {
            narray[count] = array[i][j];
            count++;
        }
    }
    return narray;
}

void display(float** array) {
    char* str;
    int len = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 3; j++)
            len += snprintf(nullptr, 0, "%14.4f ", array[i][j]);
        len += 1;
    }
    str = new char[len+1];
    char* p = str;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 3; j++) {
            p += sprintf(p, "%14.4f ", array[i][j]);
        }
        *p++ = '\n';
    }
    cout << "[" << str << "]\n";
    free(str);
}

void free(float** array) {
    for (unsigned i{}; i < n; ++i)
        delete[] array[i];
    delete[] array;
}