#ifndef lcthw_array_algos_h
#define lcthw_array_algos_h

typedef int (*compare_cb) (int a, int b);

int sorted_order(int a, int b);
int reverse_order(int a, int b);

int *Bubble_sort(int *numbers, int count, compare_cb cmp);
void mergeSort(int arr[], int l, int r);
void print_array(int *array, int count);

#endif
