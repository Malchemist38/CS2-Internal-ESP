#include "visuals.h"
#include <cstdint>
#include <vector>
#include <iostream>  // for debugging

uintptr_t V::client = (uintptr_t)GetModuleHandle("client.dll");
uintptr_t V::server = (uintptr_t)GetModuleHandle("server.dll");

void V::PlayerESP() {
    float(*ViewMatrix)[4][4] = (float(*)[4][4])(client + O::dwViewMatrix);
    if (!ViewMatrix) {
        std::cerr << "ViewMatrix is null." << std::endl;
        return;
    }

    auto localPawn = *(uintptr_t*)(client + O::dwLocalPlayerPawn);
    if (!localPawn) {
        std::cerr << "LocalPawn is null." << std::endl;
        return;
    }

    auto localTeam = *(UINT8*)(server + O::m_iTeamNum);
    auto entityList = *(uintptr_t*)(client + O::dwEntityList);
    if (!entityList) {
        std::cerr << "EntityList is null." << std::endl;
        return;
    }

    for (int i = 1; i < 64; i++) {
        uintptr_t list_entry1 = *(uintptr_t*)(entityList + (8 * (i & 0x7FFF) >> 9) + 16);
        if (!list_entry1) continue;

        uintptr_t playerController = *(uintptr_t*)(list_entry1 + 120 * (i & 0x1FF));
        if (!playerController) continue;

        uint32_t playerPawn = *(uint32_t*)(playerController + O::m_hPlayerPawn);
        if (!playerPawn) continue;

        uintptr_t list_entry2 = *(uintptr_t*)(entityList + 0x8 * ((playerPawn & 0x7FFF) >> 9) + 16);
        if (!list_entry2) continue;

        uintptr_t pCSPlayerPawnPtr = *(uintptr_t*)(list_entry2 + 120 * (playerPawn & 0x1FF));
        if (!pCSPlayerPawnPtr) continue;

        int health = *(INT32*)(pCSPlayerPawnPtr + O::m_iHealth);
        if (health <= 0) continue;

        int team = *(UINT8*)(pCSPlayerPawnPtr + O::m_iTeamNum);
        if (team == localTeam) continue;

        Vec3 feetPos = *(Vec3*)(pCSPlayerPawnPtr + O::m_vOldOrigin);
        Vec3 headPos = { feetPos.x, feetPos.y, feetPos.z + 65.0f };

        // convert world position to screen position
        Vec2 feet, head;
        if (feetPos.WorldToScreen(feet, ViewMatrix) && headPos.WorldToScreen(head, ViewMatrix)) {
            // calculate bounding box dimensions
            float height = (feet.y - head.y) * 1.5f;
            float width = height / 1.5f;
            float x = feet.x - width / 2;
            float y = head.y;

            // draw a box around the enemy
            ImGui::GetBackgroundDrawList()->AddRect({ x, y }, { x + width, y + height }, ImColor(255, 0, 0));
            std::cout << "Drawing box for enemy at index " << i << " with health " << health << std::endl;  // Debugging
        }
    }
}
