#pragma once
#include QMK_KEYBOARD_H // needed

#define ___ 0, 0, 0
#define YELLOW 50, 255, 255
#define ORANGE 29, 255, 255
#define PINK 238, 255, 255
#define PURPLE 196, 255, 255
#define BLUE 162, 255, 255
#define CYAN 137, 255, 255
#define RED 255, 255, 225
#define GREEN 94, 255, 225

#define TXT CYAN
#define SYM PURPLE
#define NUM PINK
#define MOD ORANGE
#define MOV GREEN
#define NAV BLUE
#define SYS RED
#define STN YELLOW

// clang-format off
#define LEDS(k0B, k0C, k0D, k0E, k0F, k0G, k6A, k6B, k6C, k6D, k6E, k6F, k1B, k1C, k1D, k1E, k1F, k1G, k7A, k7B, k7C, k7D, k7E, k7F, k2B, k2C, k2D, k2E, k2F, k2G, k8A, k8B, k8C, k8D, k8E, k8F, k3B, k3C, k3D, k3E, k3F, k4E, kAC, k9B, k9C, k9D, k9E, k9F, k5A, k5B, kBF, kBG) \
{ \
    {k0B}, {k0C}, {k0D}, {k0E}, {k0F}, {k0G}, \
    {k1B}, {k1C}, {k1D}, {k1E}, {k1F}, {k1G}, \
    {k2B}, {k2C}, {k2D}, {k2E}, {k2F}, {k2G}, \
    {k3B}, {k3C}, {k3D}, {k3E}, {k3F}, {k4E}, \
    {k5A}, {k5B}, \
    {k6A}, {k6B}, {k6C}, {k6D}, {k6E}, {k6F}, \
    {k7A}, {k7B}, {k7C}, {k7D}, {k7E}, {k7F}, \
    {k8A}, {k8B}, {k8C}, {k8D}, {k8E}, {k8F}, \
    {kAC}, {k9B}, {k9C}, {k9D}, {k9E}, {k9F}, \
    {kBF}, {kBG} \
}
// clang-format on

void toggle_leds(void);
void enable_leds(void);

extern rgb_config_t rgb_matrix_config;

RGB  hsv_to_rgb_with_value(HSV hsv);
void set_layer_color(int layer);
bool rgb_matrix_indicators_user(void);
