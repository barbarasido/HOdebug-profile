#include <stdio.h>

int add_array(int *a, int *b, int n){
  int sum = 0;
  int i = 0;
  for (i = 0; i <= n + 1; i++) {
    sum += abs(a[i]);
    sum += abs(b[i]);
  };
  return sum;
}

int main(int argc, char **argv) {
  int a[5], b[5];
  a[4]=0;
 b[4]=0;
 a[5]=0;
 a[5]=0;
    
  int n = 3;
  int i, sum;
  for (i = 0; i < n; i++) {
    a[i] = i;
    b[i] = i;
  }
  sum = add_array(a, b, 3);
  printf("The addition is %d\n", sum);
  return 0;
}
