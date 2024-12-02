#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int process_array(int *v, int size_of_list);
void process_unsafe(int *v, int size_of_list, int *res);

int main() {
    int res = 0;
    int *v = (int *)malloc(1 * sizeof(int));
    int item = 0;
    int size_of_list = 1;
    int count = 0; 
    int ch;
    int is_digit = 0;
    int is_safe;

    if (v == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    while ((ch = getchar()) != EOF) {
        if (isdigit(ch)) {
            item = item * 10 + (ch - '0');
            is_digit = 1;
        } else if (ch == '\n') {
            if (is_digit) {
                if (count >= size_of_list) {
                    size_of_list++;
                    v = (int *)realloc(v, size_of_list * sizeof(int));
                    if (v == NULL) {
                        fprintf(stderr, "Memory reallocation failed\n");
                        return 1;
                    }
                }
                v[count++] = item;
                item = 0;
                is_digit = 0;
            }
            if (ch == '\n' && count > 0) {
                is_safe = process_array(v, count);
                if (!is_safe) {
                    process_unsafe(v, count, &res);
                } else {
                    res++;
                }
                free(v);
                v = (int *)malloc(1 * sizeof(int));
                if (v == NULL) {
                    fprintf(stderr, "Memory allocation failed\n");
                    return 1;
                }
                size_of_list = 1;
                count = 0;
            }
        }
    }
    if (count > 0) {
        is_safe = process_array(v, count);
        if (!is_safe) {
            process_unsafe(v, count, &res);
        } else {
            res++;
        }
    }
    free(v);
    printf("Total safe rows: %d\n", res);
    return 0;
}

int process_array(int *v, int size_of_list) {
    if (size_of_list == 1) {
        return 1;
    }

    int is_safe = 1;
    int is_asc = (v[0] < v[1]) ? 1 : 0;

    for (int i = 1; i < size_of_list && is_safe; i++) {
        if (abs(v[i - 1] - v[i]) > 3 || (is_asc && v[i - 1] >= v[i]) || (!is_asc && v[i - 1] <= v[i])) {
            is_safe = 0;
        }
    }

    return is_safe;
}

void process_unsafe(int *v, int size_of_list, int *res) {
    for (int i = 0; i < size_of_list; i++) {
        int *temp = (int *)malloc((size_of_list - 1) * sizeof(int));
        if (temp == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }

        for (int j = 0, k = 0; j < size_of_list; j++) {
            if (j != i) {
                temp[k++] = v[j];
            }
        }

        if (process_array(temp, size_of_list - 1)) {
            (*res)++;
            free(temp);
            return;
        }

        free(temp);
    }
}