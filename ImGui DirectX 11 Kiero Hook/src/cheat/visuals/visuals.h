#pragma once
#include "../../math/math.h"
#include <cstddef>
#include <cstdint>
#include "../../../ext/imgui/imgui.h"

namespace O {
    // offsets - used with client.dll
    constexpr std::ptrdiff_t dwEntityList = 0x19CFC48;
    constexpr std::ptrdiff_t dwLocalPlayerPawn = 0x1834B18;
    constexpr std::ptrdiff_t dwViewMatrix = 0x1A31D30;

    // server.dll
    constexpr std::ptrdiff_t m_hPlayerPawn = 0x894;
    constexpr std::ptrdiff_t m_iHealth = 0x2C8;
    constexpr std::ptrdiff_t m_iTeamNum = 0x334;

    // client.dll
    constexpr std::ptrdiff_t m_vOldOrigin = 0x1324;
}

namespace V {
    extern uintptr_t client;
    extern uintptr_t server;
    void PlayerESP();
}
