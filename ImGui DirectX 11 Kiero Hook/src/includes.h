#pragma once
#include <Windows.h>
#include <d3d11.h>
#include <dxgi.h>
#include "../ext/imgui/imgui.h"
#include "../ext/imgui/imgui_impl_dx11.h"
#include "../ext/imgui/imgui_impl_win32.h"
#include "cheat/visuals/visuals.h"
#include "math/math.h"
#include "../ext/kiero/kiero.h"
#include "../ext/kiero/minhook/include/MinHook.h"


typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef LRESULT(CALLBACK* WNDPROC) (HWND, UINT, WPARAM, LPARAM);
typedef uintptr_t PTR;