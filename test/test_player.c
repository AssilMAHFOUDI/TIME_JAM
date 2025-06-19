#include "minunit.h"
#include "player_action.h"
#include <string.h>
#include <math.h>

MU_TEST(test_parse_radar_response_simple) {
    const char *input = "P 101 1000 2000 -1 0,S 0 3 1020 2020 0,B 500 500,S 0 2 100 2050 0";
    RadarInfo radar;

    parse_radar_response(input, &radar);

    mu_assert_int_eq(1, radar.planet_count);
    mu_assert_int_eq(2, radar.ship_count);
    mu_assert_int_eq(500, radar.base.x);
    mu_assert_int_eq(500, radar.base.y);

    mu_assert_int_eq(101, radar.planets[0].planet_id);
    mu_assert_int_eq(1000, radar.planets[0].x);
    mu_assert_int_eq(2000, radar.planets[0].y);
    mu_assert_int_eq(-1, radar.planets[0].collected_by);
    mu_assert_int_eq(0, radar.planets[0].at_base);

    mu_assert_int_eq(0, radar.ships[0].team);
    mu_assert_int_eq(3, radar.ships[0].ship_id);
    mu_assert_int_eq(1020, radar.ships[0].x);
    mu_assert_int_eq(2020, radar.ships[0].y);
    mu_assert_int_eq(0, radar.ships[0].broken);

    mu_assert_int_eq(2, radar.ships[1].ship_id);
    mu_assert_int_eq(0, radar.ships[1].team);
}

MU_TEST(test_move_toward_planet) {
    RadarInfo radar;
    const char *input = "P 101 1000 1000 -1 0,S 0 2 500 500 0,B 0 0";
    parse_radar_response(input, &radar);

    Ship ship = radar.ships[0];
    Planet planet = radar.planets[0];

    int dx = planet.x - ship.x;
    int dy = planet.y - ship.y;

    double angle_rad = atan2(dy, dx);
    int angle_deg = (int)(angle_rad * 180.0 / M_PI);
    if (angle_deg < 0) angle_deg += 360;

    char buffer[50];
    int code = move(buffer, ship.ship_id, angle_deg, 1000);
    mu_assert_int_eq(0, code);
}
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
    MU_RUN_TEST(test_parse_radar_response_simple);
    MU_RUN_TEST(test_move_toward_planet);
}
 
int main(int argc, char *argv[]) {
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return MU_EXIT_CODE;
}
 