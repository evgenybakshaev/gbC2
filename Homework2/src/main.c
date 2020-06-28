#include <stdio.h>
#include <math.h>
#include <stdbool.h>

bool isPrime(int n) {
    int last = (int)sqrt(n);
    for (int i = 2; i <= last; ++i) {
        if (n % i == 0)
            return false;
    }
    return true;
}

int main() {
    int num;
    scanf("%d", &num);
    printf("Number %d is%s simple\n", num, (isPrime(num)) ? "" : " not");
    return 0;
}
