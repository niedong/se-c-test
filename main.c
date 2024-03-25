#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

int maxSubssequenceSum_ver0(const int *input, int n)
{
    int ans = 0, sum;

    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            sum = 0;

            for (int k = i; k <= j; ++k) {
                sum += input[k];
            }

            ans = max(ans, sum);
        }
    }

    return ans;
}

int maxSubssequenceSum_ver1(const int *input, int n)
{
    int ans = 0, sum;

    for (int i = 0; i < n; ++i) {
        sum = 0;

        for (int j = i; j < n; ++j) {
            sum += input[j];

            ans = max(ans, sum);
        }
    }

    return ans;
}

int maxSubssequenceSum_ver2(const int *input, int begin, int end)
{
    if (begin == end) {
        if (input[begin] > 0) {
            return input[begin];
        }
        else {
            return 0;
        }
    }

    int mid = (begin + end) / 2;

    int l = maxSubssequenceSum_ver2(input, begin, mid);
    int r = maxSubssequenceSum_ver2(input, mid + 1, end);

    int suml = 0, sumr = 0, temp = 0;

    for (int i = mid; i >= begin; --i) {
        temp += input[i];

        suml = max(suml, temp);
    }

    temp = 0;

    for (int i = mid + 1; i <= end; ++i) {
        temp += input[i];

        sumr = max(sumr, temp);
    }

    return max(suml + sumr, max(l, r));
}

int maxSubssequenceSum_ver3(const int *input, int n)
{
    int ans = 0, sum = 0;

    for (int i = 0; i < n; ++i) {
        sum += input[i];

        if (sum > ans) {
            ans = sum;
        }
        else if (sum < 0) {
            sum = 0;
        }
    }

    return ans;
}

int binarySearch(const int *input, int n, int target)
{
    int l = 0, r = n - 1;

    while (l <= r) {
        int mid = (l + r) / 2;

        if (input[mid] < target) {
            l = mid + 1;
        }
        else if (input[mid] > target) {
            r = mid - 1;
        }
        else {
            return mid;
        }
    }

    return -1;
}

int gcd(unsigned int m, unsigned int n)
{
    while (n > 0) {
        unsigned int mod = m % n;

        // printf("mod: %d\n", mod);

        m = n;
        n = mod;
    }

    return m;
}

typedef unsigned long long ull;

ull myPow(ull a, ull b)
{
    if (b == 0) {
        return 1;
    }

    if (b == 1) {
        return a;
    }

    if (b % 2 == 0) {
        return myPow(a * a, b / 2);
    }
    else {
        return myPow(a * a, b / 2) * a;
    }
}

void printArray(int *array, int N)
{
    for (int i = 0; i < N; i++) {
        if (i != N - 1) {
            printf("%d ", array[i]);
        }
        else {
            printf("%d\n", array[i]);
        }
    }
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void permute(int *array, int i, int length)
{
    if (i == length) {
        printArray(array, length);

        return;
    }

    for (int j = i; j < length; j++) {
        swap(array + i, array + j);

        permute(array, i + 1, length);

        swap(array + i, array + j);
    }
}

int bubbleSort(int *input, int n)
{
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (input[j] > input[j + 1]) {
                int temp = input[j];
                input[j] = input[j + 1];
                input[j + 1] = temp;
            }
        }
    }

    return n;
}

int insertionSort(int *input, int n)
{
    for (int i = 1; i < n; ++i) {
        int temp = input[i];
        int j;

        for (j = i; j > 0 && input[j - 1] > temp; --j) {
            input[j] = input[j - 1];
        }

        input[j] = temp;
    }

    return n;
}

int selectionSort(int *input, int n)
{
    int minValue, minIndex;

    for (int i = 0; i < n; ++i) {
        minValue = input[i];
        minIndex = i;

        for (int j = i; j < n; j++) {
            if (input[j] < minValue) {
                minValue = input[j];
                minIndex = j;
            }
        }

        swap(&input[i], &input[minIndex]);
    }

    return n;
}

void quickSort(int *input, int start, int end)
{
    if (start >= end)
        return;

    int key = input[start];
    int i = start;
    int j = end;

    while (i < j) {
        while (i < j && input[j] >= key) {
            --j;
        }

        while (i < j && input[i] <= key) {
            ++i;
        }

        if (i < j) {
            swap(&input[i], &input[j]);
        }
    }

    assert(i == j);

    swap(&input[i], &input[start]);

    quickSort(input, start, i - 1);
    quickSort(input, j + 1, end);
}

void msort(int *input, int *tempArr, int start, int end)
{
    if (start >= end)
        return;

    int mid = (start + end) / 2;

    msort(input, tempArr, start, mid);
    msort(input, tempArr, mid + 1, end);

    int l = start, r = mid + 1, s = start;

    while (l <= mid && r <= end) {
        if (input[l] < input[r]) {
            tempArr[s++] = input[l++];
        }
        else {
            tempArr[s++] = input[r++];
        }
    }

    while (l <= mid) {
        tempArr[s++] = input[l++];
    }

    while (r <= end) {
        tempArr[s++] = input[r++];
    }

    for (int i = start; i < s; ++i) {
        input[i] = tempArr[i];
    }
}

void mergeSort_ver1(int *input, int start, int end)
{
    if (start >= end)
        return;

    int *tempArr = (int *)malloc(sizeof(int) * (end - start + 1));

    msort(input, tempArr, start, end);

    free(tempArr);
}

void mergeSort_ver0(int *input, int start, int end)
{
    if (start >= end)
        return;

    int mid = (start + end) / 2;

    mergeSort_ver0(input, start, mid);
    mergeSort_ver0(input, mid + 1, end);

    int *temp = (int *)malloc(sizeof(int) * (end - start + 1));

    int l = start, r = mid + 1, s = start;

    while (l <= mid && r <= end) {
        if (input[l] < input[r]) {
            temp[s++] = input[l++];
        }
        else {
            temp[s++] = input[r++];
        }
    }

    while (l <= mid) {
        temp[s++] = input[l++];
    }

    while (r <= end) {
        temp[s++] = input[r++];
    }

    for (int i = start; i <= end; ++i) {
        input[i] = temp[i];
    }

    free(temp);
}

int cmp(const void *a, const void *b)
{
    int l = *(int *)a;
    int r = *(int *)b;

    if (l < r) {
        return -1;
    }
    else if (l > r) {
        return 1;
    }
    else {
        return 0;
    }
}

int main(int argc, char **argv)
{
    int input0[] = {-2, 11, -4, 13, -5, -2};

    printf("ans0: %d\n", maxSubssequenceSum_ver0(input0, 6));
    printf("ans1: %d\n", maxSubssequenceSum_ver1(input0, 6));
    printf("ans2: %d\n", maxSubssequenceSum_ver2(input0, 0, 5));
    printf("ans3: %d\n", maxSubssequenceSum_ver3(input0, 6));

    int input1[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};

    printf("ans0: %d\n", maxSubssequenceSum_ver0(input1, 9));
    printf("ans1: %d\n", maxSubssequenceSum_ver1(input1, 9));
    printf("ans2: %d\n", maxSubssequenceSum_ver2(input1, 0, 8));
    printf("ans3: %d\n", maxSubssequenceSum_ver3(input1, 9));

    int input2[] = {1, 4, 7, 9, 20, 45};

    printf("binarySearch: %d\n", binarySearch(input2, 6, 50));

    printf("gcd(%d, %d): %d\n", 15, 50, gcd(15, 50));

    printf("myPow: %llu, %llu, result = %llu\n", 2ull, 30ull, myPow(2, 30));

//    FILE *file = fopen("../CMakeLists.txt", "r");
//
//    printf("file: %p\n", file);
//
//    int c;
//
//    while ((c = fgetc(file)) != EOF) {
//        putchar(c);
//    }
//
//    if (feof(file)) {
//        printf("eof file\n");
//    }
//
//    if (ferror(file)) {
//        printf("error file\n");
//    }
//
//    printf("Done\n");
//
//    fclose(file);
//
//    printf("EOF value: %d\n\n\n", (int)EOF);
//
//    char arr[8];
//
//    fgets(arr, sizeof(arr), stdin);
//
//    printf("arr: %s\n", arr);
//
//    int a, b;
//
//    scanf("%d %d", &a, &b);
//
//    printf("a: %d b: %d\n", a, b);

    int A[4] = {1, 2, 3, 4};

    permute(A, 0, 4);

    int unordered[] = {9, 6, 4, 34, 56, 3, 9, 1, 23, -9, 101};

//    qsort(unordered, 11, sizeof(int), cmp);
//    selectionSort(unordered, 11);
//    mergeSort_ver0(unordered, 0, 10);
    mergeSort_ver1(unordered, 0, 10);
//    quickSort(unordered, 0, 10);


    for (int i = 0; i < 11; ++i) {
        printf("%d\n", unordered[i]);
    }

    return 0;
}
