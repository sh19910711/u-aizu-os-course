#include <stdio.h>

char* get_hello() {
  return "hello, world";
}

#ifndef GTEST_INCLUDE_GTEST_GTEST_H_
int main() {
  puts(get_hello());
  return 0;
}
#endif
