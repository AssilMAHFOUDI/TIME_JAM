#include "minunit.h"
#include "player_action.h"
#include <string.h>

MU_TEST(test_move) {
    mu_assert(strcmp(move(1, 2, 1000), "MOVE 1 2 1000") == 0, "Wrong move output");
}

MU_TEST_SUITE(test_suite) {
    MU_RUN_TEST(test_move);
}

int main(int argc, char *argv[]) {
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return MU_EXIT_CODE;
}
