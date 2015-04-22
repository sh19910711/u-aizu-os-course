#include <gtest/gtest.h>

namespace {

#include "./hello.c"

  TEST(HelloTest, CallFunction) {
    ASSERT_STREQ("hello, world", get_hello());
  }

}
