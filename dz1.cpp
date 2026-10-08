#include <stdio.h>
#include <stddef.h>

void swap(int *a, int *b) {
    if (a == NULL || b == NULL) {
        return;
    }

    int t = *a;
    *a = *b;
    *b = t;
}

void print_array(const int *arr, int n) {
    if (arr == NULL || n <= 0) {
        printf("[]\n");
        return;
    }

    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d%s", arr[i], i + 1 < n ? ", " : "");
    }
    printf("]\n");
}

// 1
long long sum_all(long long n) {
    if (n <= 0) {
        return 0;
    }

    return n * (n + 1) / 2;
}

// 2
int two_sum(const int *nums, int n, int target, int *out) {
    if (nums == NULL || out == NULL || n < 2) {
        return 0;
    }

    int left = 0;
    int right = n - 1;

    while (left < right) {
        long long s = (long long)nums[left] + nums[right];

        if (s == target) {
            out[0] = left;
            out[1] = right;
            return 1;
        } else if (s < target) {
            left++;
        } else {
            right--;
        }
    }

    return 0;
}

// 3
void reverse_part(int *arr, int left, int right) {
    if (arr == NULL || left < 0 || right < 0 || left >= right) {
        return;
    }

    while (left < right) {
        swap(&arr[left], &arr[right]);
        left++;
        right--;
    }
}

void reverse_array(int *arr, int n) {
    if (arr == NULL || n <= 0) {
        return;
    }

    reverse_part(arr, 0, n - 1);
}

// 4
void rotate_array(int *arr, int n, int k) {
    if (arr == NULL || n <= 0) {
        return;
    }

    k = k % n;


    if (k < 0) {
        k += n;
    }

    if (k == 0) {
        return;
    }

    reverse_part(arr, 0, n - 1);
    reverse_part(arr, 0, k - 1);
    reverse_part(arr, k, n - 1);
}

// 5
void merge_sorted_arrays(const int *a1, int n1, const int *a2, int n2, int *out) {
    if (out == NULL || n1 < 0 || n2 < 0) {
        return;
    }

    if ((a1 == NULL && n1 > 0) || (a2 == NULL && n2 > 0)) {
        return;
    }

    int i = 0;
    int j = 0;
    int p = 0;

    while (i < n1 && j < n2) {
        if (a1[i] < a2[j]) {
            out[p++] = a1[i++];
        } else {
            out[p++] = a2[j++];
        }
    }

    while (i < n1) {
        out[p++] = a1[i++];
    }

    while (j < n2) {
        out[p++] = a2[j++];
    }
}

// 6
void merge_in_place(int *arr1, int n1, const int *arr2, int n2) {
    if (arr1 == NULL || n1 < 0 || n2 < 0 || n1 < n2) {
        return;
    }

    if (n2 == 0) {
        return;
    }

    if (arr2 == NULL) {
        return;
    }

    int p1 = n1 - n2 - 1;  
    int p2 = n2 - 1;        
    int p3 = n1 - 1;        

    while (p2 >= 0) {
        if (p1 >= 0 && arr1[p1] > arr2[p2]) {
            arr1[p3--] = arr1[p1--];
        } else {
            arr1[p3--] = arr2[p2--];
        }
    }
}

// 7
int min_sub_array(const int *nums, int n, int target) {
    if (nums == NULL || n <= 0) {
        return 0;
    }

    if (target <= 0) {
        return 1;
    }

    int min_len = n + 1;    
    int left = 0;
    long long cur_sum = 0;

    for (int right = 0; right < n; right++) {
        cur_sum += nums[right];

        while (cur_sum >= target) {
            int window = right - left + 1;

            if (window < min_len) {
                min_len = window;
            }

            cur_sum -= nums[left];
            left++;
        }
    }

    return min_len != n + 1 ? min_len : 0;
}

// 8
void sort_binary_array(int *arr, int n) {
    if (arr == NULL || n <= 0) {
        return;
    }

    int left = 0;
    int right = n - 1;

    while (left < right) {
        if (arr[left] == 0) {
            left++;
        } else if (arr[right] == 1) {
            right--;
        } else {
            swap(&arr[left], &arr[right]);
            left++;
            right--;
        }
    }
}

// 9
void sort_colors(int *nums, int n) {
    if (nums == NULL || n <= 0) {
        return;
    }

    int low = 0;
    int mid = 0;
    int high = n - 1;

    while (mid <= high) {
        if (nums[mid] == 0) {
            swap(&nums[low], &nums[mid]);
            low++;
            mid++;
        } else if (nums[mid] == 1) {
            mid++;
        } else {
            swap(&nums[mid], &nums[high]);
            high--;
        }
    }
}

// 10
void even_first(int *arr, int n) {
    if (arr == NULL || n <= 0) {
        return;
    }

    int even_index = 0;

    for (int i = 0; i < n; i++) {
        if (arr[i] % 2 == 0) {
            swap(&arr[i], &arr[even_index]);
            even_index++;
        }
    }
}

// 11
void move_zeroes(int *arr, int n) {
    if (arr == NULL || n <= 0) {
        return;
    }

    int insert_pos = 0;

    for (int i = 0; i < n; i++) {
        if (arr[i] != 0) {
            swap(&arr[i], &arr[insert_pos]);
            insert_pos++;
        }
    }
}


int main(void) {
    printf("1: %lld\n", sum_all(1000000));

    int nums2[] = {2, 7, 11, 15, 20};
    int idx[2];

    if (two_sum(nums2, 5, 18, idx)) {
        printf("2: [%d, %d]\n", idx[0], idx[1]);   /* 7 + 11 */
    } else {
        printf("2: []\n");
    }

    int a3[] = {1, 2, 3, 4, 5};
    reverse_array(a3, 5);
    printf("3: ");
    print_array(a3, 5);

    int a4[] = {1, 2, 3, 4, 5, 6, 7};
    rotate_array(a4, 7, 3);
    printf("4: ");
    print_array(a4, 7);

    int a5[] = {1, 3, 5};
    int b5[] = {2, 4, 6, 8};
    int out5[7];

    merge_sorted_arrays(a5, 3, b5, 4, out5);
    printf("5: ");
    print_array(out5, 7);

    int a6[] = {1, 3, 5, 0, 0, 0};
    int b6[] = {2, 4, 6};

    merge_in_place(a6, 6, b6, 3);
    printf("6: ");
    print_array(a6, 6);

    int a7[] = {2, 3, 1, 2, 4, 3};
    printf("7: %d\n", min_sub_array(a7, 6, 7));

    int a8[] = {1, 0, 1, 0, 1, 1, 0};
    sort_binary_array(a8, 7);
    printf("8: ");
    print_array(a8, 7);

    int a9[] = {2, 0, 2, 1, 1, 0};
    sort_colors(a9, 6);
    printf("9: ");
    print_array(a9, 6);

    int a10[] = {3, 2, 4, 1, 11, 8, 9};
    even_first(a10, 7);
    printf("10: ");
    print_array(a10, 7);

    int a11[] = {0, 0, 1, 0, 3, 12};
    move_zeroes(a11, 6);
    printf("11: ");
    print_array(a11, 6);

    return 0;
}