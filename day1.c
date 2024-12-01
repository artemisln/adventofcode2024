#include <stdio.h>
#include <stdlib.h>

int compare(const void* a, const void* b) {
   return (*(int*)a - *(int*)b);
}

int main(){
    int *left_list = malloc(sizeof(int)), *right_list = malloc(sizeof(int));
    int left_index = 0, right_index = 0, item, current_list = 1, left_size = 1, right_size = 1;
    while(scanf("%d", &item) == 1){
        if (current_list == 1){
            if (left_index >= left_size) {
                left_list = (int *)realloc(left_list, ++left_size * sizeof(int));
            }
            left_list[left_index++] = item;
            current_list = 2;
        } else {
            if (right_index >= right_size) {
                right_list = (int *)realloc(right_list, ++right_size * sizeof(int));
            }
            right_list[right_index++] = item;
            current_list = 1;
        }
    }

    qsort(left_list, left_index, sizeof(int), compare);
    qsort(right_list, right_index, sizeof(int), compare);

    // Part 1
    int res = 0;
    for (int i = 0; i < right_index; i++) {
        res += abs(right_list[i]-left_list[i]);
    }
    printf("Result is %d\n", res);

    // Part 2
    int similarity = 0;
    for (int i = 0; i<left_index; i++){
        int times_occured = 0;
        for(int j=0; j<right_index; j++){
            if (left_list[i]==right_list[j]){
                times_occured++;
            }
        }
        similarity += left_list[i]*times_occured;
    }
    printf("similarity is %d\n", similarity);
    return 0;
}