#include "minunit.h"
#include "player_action.h"
#include <string.h>
#include <math.h>
#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

MU_TEST(test_parse_radar_response_simple) {
    const char *input = "P 101 1000 2000 -1 0,S 0 3 1020 2020 0,B 500 500,S 0 2 100 2050 0";
    Radar radar;

    parse_radar_data(&radar,input);

    mu_assert_int_eq(1, radar.planet_count);
    mu_assert_int_eq(2, radar.ship_count);
    mu_assert_int_eq(500, radar.base.abscissa);
    mu_assert_int_eq(500, radar.base.ordinate);

    mu_assert_int_eq(101, radar.planets[0].planet_id);
    mu_assert_int_eq(1000, radar.planets[0].abscissa);
    mu_assert_int_eq(2000, radar.planets[0].ordinate);
    mu_assert_int_eq(-1, radar.planets[0].ship_id);
    mu_assert_int_eq(0, radar.planets[0].saved);

    mu_assert_int_eq(0, radar.ships[0].team);
    mu_assert_int_eq(3, radar.ships[0].ship_id);
    mu_assert_int_eq(1020, radar.ships[0].abscissa);
    mu_assert_int_eq(2020, radar.ships[0].ordinate);
    mu_assert_int_eq(0, radar.ships[0].broken);

    mu_assert_int_eq(2, radar.ships[1].ship_id);
    mu_assert_int_eq(0, radar.ships[1].team);
}

MU_TEST(test_move_toward_planet) {
    Radar radar;
    // const char *input = "P 101 1000 1000 -1 0,S 0 2 500 500 0,B 0 0";
    const char *input = "P 56672 13000 7000 -1 0,P 57321 9000 16000 -1 0,P 14123 7000 15000 -1 0,P 12558 11000 8000 -1 0,P 32241 17000 4000 -1 0,P 61987 11000 10000 -1 0,P 59165 3000 10000 -1 0,P 24933 8000 14000 -1 0,P 50385 17000 7000 -1 0,P 21619 4000 16000 -1 0,P 12390 4000 17000 -1 0,P 14136 10000 6000 -1 0,S 0 1 10000 0 0,S 0 2 11500 0 0,S 0 3 8500 0 0,S 0 4 13000 0 0,S 0 5 7000 0 0,S 0 6 14500 0 0,S 0 7 5500 0 0,S 0 8 16000 0 0,S 0 9 4000 0 0,B 10000 0";
    parse_radar_data(&radar,input);

    Ship ship = radar.ships[0];
    Planet planet = radar.planets[0];

    int dx = planet.abscissa - ship.abscissa;
    int dy = planet.ordinate - ship.ordinate;

    double angle_rad = atan2(dy, dx);
    int angle_deg = (int)(angle_rad * 180.0 / M_PI);
    if (angle_deg < 0) angle_deg += 360;

    char buffer[50];
    int code = move(buffer, ship.ship_id, angle_deg, 1000);
    printf("Move command: %s", buffer);
    mu_assert_int_eq(0, code);
}
MU_TEST(test_move_valid) {
    char buffer[50];
    int code = move(buffer, 1, 2, 1000);
    mu_assert(code == 0, "Expected success code 0");
    mu_assert_string_eq("MOVE 1 2 1000\n", buffer);
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
    mu_assert_string_eq("FIRE 3 270\n", buffer);
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
    mu_assert_string_eq("RADAR 6\n", buffer);
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
    MU_RUN_TEST(test_parse_radar_response_simple);
    MU_RUN_TEST(test_move_toward_planet);
}
 
int main(int argc, char *argv[]) {
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return MU_EXIT_CODE;
}
 