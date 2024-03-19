#include <stdio.h>

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

        if (temp > suml) {
            suml = temp;
        }
    }

    temp = 0;

    for (int i = mid + 1; i <= end; ++i) {
        temp += input[i];

        if (temp > sumr) {
            sumr = temp;
        }
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

    return 0;
}
