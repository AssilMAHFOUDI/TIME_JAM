#include "minunit.h"
#include "math_ops.h"

MU_TEST(test_add_2_numbers_int) {
    mu_assert(add_2_numbers_int(2, 3) == 5, "2 + 3 should be 5");
    mu_assert(add_2_numbers_int(-1, 1) == 0, "-1 + 1 should be 0");
    mu_assert(add_2_numbers_int(0, 0) == 0, "0 + 0 should be 0");
    mu_assert(add_2_numbers_int(-5, -7) == -12, "-5 + -7 should be -12");
}

MU_TEST_SUITE(test_suite) {
    MU_RUN_TEST(test_add_2_numbers_int);
}

int main(int argc, char *argv[]) {
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return MU_EXIT_CODE;
}
