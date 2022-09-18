#pragma once
#include "common.hpp"

namespace Spyral::Pointers
{
    extern void Destroy();
    extern void Init();

    inline IDXGISwapChain** SwapChain;
    inline WNDPROC WndProc;
    inline HWND hwnd;
}