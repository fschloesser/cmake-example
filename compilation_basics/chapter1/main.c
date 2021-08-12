#include <stdio.h>
void helper () {
  puts("helper");
}
int main () {
  puts("main");
  helper();
}

