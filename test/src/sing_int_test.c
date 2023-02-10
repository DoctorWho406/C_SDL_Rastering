#define CLOVE_SUITE_NAME SignIntTest
#include "clove-unit.h"

CLOVE_TEST(TestAllPositiveNumber) {
   int a = 3;
   int b = 6;
   int c = 9;

   CLOVE_IS_TRUE((a ^ b) >= 0);
   CLOVE_IS_TRUE((b ^ c) >= 0);
   CLOVE_IS_TRUE((a ^ b) >= 0 && (b ^ c) >= 0);
}

CLOVE_TEST(TestAllNegativeNumber) {
   int a = -3;
   int b = -6;
   int c = -9;

   CLOVE_IS_TRUE((a ^ b) >= 0);
   CLOVE_IS_TRUE((b ^ c) >= 0);
   CLOVE_IS_TRUE((a ^ b) >= 0 && (b ^ c) >= 0);
}

CLOVE_TEST(TestOnePositiveTwoNegativeNumber) {
   int a = 3;
   int b = -6;
   int c = -9;

   CLOVE_IS_FALSE((a ^ b) >= 0);
   CLOVE_IS_TRUE((b ^ c) >= 0);
   CLOVE_IS_FALSE((a ^ b) >= 0 && (b ^ c) >= 0);
}

CLOVE_TEST(TestTwoPositiveOneNegativeNumber) {
   int a = 3;
   int b = 6;
   int c = -9;

   CLOVE_IS_TRUE((a ^ b) >= 0);
   CLOVE_IS_FALSE((b ^ c) >= 0);
   CLOVE_IS_FALSE((a ^ b) >= 0 && (b ^ c) >= 0);
}
