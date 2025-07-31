#include <stdio.h>

int main() {
    int n;

    scanf("%i", &n);

    int arr[n];
    int a[n];
    int sam = 0;
    int gf = 0;

    for (int i=0; i<n; i++) {
        scanf("%i", arr[i]);
        gf += arr[i];
        for (int j=i; j>0; j++) {
            if (arr[j] < arr[j-1]) {
                arr[j-1] = arr[j];
            } 
        }
    }

    int ans = gf / 2;

    for (int i=0; i<n; i++) {
        if ((ans - arr[i]) > 0) {
            ans -= arr[i];
        }
    }

    printf("%i", gf / 2 - ans);

}