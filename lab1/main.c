#include <stdio.h>
#include <string.h>
#include <time.h>
#define SIZE 20
 
void process_array(int a[]);
void find_max_elements(int arr[]);
char *m_strncat(char*, const char*, size_t);
 
int main() {
    srand(time(0));
 
    int n[SIZE];
    memset(n, 0, SIZE * sizeof(int));
    printf("Задание 1");
    process_array(n);

    // 2
    puts("Задание 3");
    char out[100] = "";
    char *dest = "Hello, ";
    char *src = "World!";
 
    fprintf(stdout, "%s\n", out);
    fprintf(stdout, "%s\n", strncat(out, dest, 8));
    fprintf(stdout, "%s\n", m_strncat(out, src, 6));
 
    return 0;
}
 
// 1
void process_array(int a[]) {
    int tmp[11];
    memset(tmp, 0, 11 * sizeof(int));

    printf("Исходный массив:\n");
    for (int i = 0; i < SIZE; ++i) {
        a[i] = (rand() % 10) + 1;
        tmp[a[i]] += 1;
        fprintf(stdout, "%-3d ", a[i]);
    }
    printf("\n\n");
    for (int i = 1; i < 11; ++i) {
        fprintf(stdout, "%d = %d\n", i, tmp[i]);
    }
    printf("\n");
    find_max_elements(tmp);
}
 
void find_max_elements(int arr[]) {
    int max = arr[1];
    // Т.к. в массиве присутствует индекс 0, его игнорируем и начинаем с 2 элемента
    for (int i = 1; i < 11; ++i) //max = arr[i] > max ? arr[i] : max;
        if (arr[i] > max)
            max = arr[i];
 
    for (int i = 2; i < 11; i++)
        if (arr[i] == max)
            fprintf(stdout, "Max int %d -> %d\n", i, max);
}
 
// 3
char *m_strncat(char *dest, const char *src, size_t maxlen) {
    size_t dest_len = strlen(dest);
    size_t i;
 
    for (i = 0; i < maxlen && src[i] != '\0'; i++)
        dest[dest_len + i] = src[i];
    dest[dest_len + i] = '\0';
 
    return dest;
}