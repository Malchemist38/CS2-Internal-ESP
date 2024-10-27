#pragma once
#include <windows.h>

struct Vec2 {
    constexpr Vec2(float x = 0.f, float y = 0.f) noexcept : x(x), y(y) {}
    float x, y;
};

struct Vec3 {
    constexpr Vec3(float x = 0.f, float y = 0.f, float z = 0.f) noexcept : x(x), y(y), z(z) {}
    const bool WorldToScreen(Vec2& out, float(*ViewMatrix)[4][4]);
    float x, y, z;
};
