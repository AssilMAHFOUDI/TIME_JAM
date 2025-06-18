#include "minunit.h"
#include "player_action.h"
#include <string.h>
 
MU_TEST(test_move_valid) {
    char buffer[50];
    int code = move(buffer, 1, 2, 1000);
    mu_assert(code == 0, "Expected success code 0");
    mu_assert_string_eq("MOVE 1 2 1000", buffer);
}
 
MU_TEST(test_move_invalid_id) {
    char buffer[50];
    int code = move(buffer, 0, 2, 1000);
    mu_assert(code == 1, "Expected error code 1 for invalid ship ID");
}
 
MU_TEST(test_move_invalid_angle) {
    char buffer[50];
    int code = move(buffer, 1, 360, 1000);
    mu_assert(code == 2, "Expected error code 2 for invalid angle");
}
 
MU_TEST(test_move_invalid_speed) {
    char buffer[50];
    int code = move(buffer, 1, 2, 4000);
    mu_assert(code == 3, "Expected error code 3 for invalid speed");
}
 
MU_TEST(test_fire_valid) {
    char buffer[50];
    int code = fire(buffer, 3, 270);
    mu_assert(code == 0, "Expected success code 0");
    mu_assert_string_eq("FIRE 3 270", buffer);
}
 
MU_TEST(test_fire_invalid_id_not_attacker) {
    char buffer[50];
    int code = fire(buffer, 6, 90);
    mu_assert(code == 1, "Expected error code 1 for non-attacker ship_id");
}
 
MU_TEST(test_fire_invalid_angle) {
    char buffer[50];
    int code = fire(buffer, 5, 400);
    mu_assert(code == 2, "Expected error code 2 for invalid angle");
}
 
MU_TEST(test_radar_valid) {
    char buffer[50];
    int code = radar(buffer, 6);
    mu_assert(code == 0, "Expected success code 0");
    mu_assert_string_eq("RADAR 6", buffer);
}
 
MU_TEST(test_radar_invalid_id) {
    char buffer[50];
    int code = radar(buffer, 3);
    mu_assert(code == 1, "Expected error code 1 for non-explorer ship_id");
}
 
MU_TEST_SUITE(test_suite) {
    MU_RUN_TEST(test_move_valid);
    MU_RUN_TEST(test_move_invalid_id);
    MU_RUN_TEST(test_move_invalid_angle);
    MU_RUN_TEST(test_move_invalid_speed);
    MU_RUN_TEST(test_fire_valid);
    MU_RUN_TEST(test_fire_invalid_id_not_attacker);
    MU_RUN_TEST(test_fire_invalid_angle);
    MU_RUN_TEST(test_radar_valid);
    MU_RUN_TEST(test_radar_invalid_id);
}
 
int main(int argc, char *argv[]) {
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return MU_EXIT_CODE;
}
 