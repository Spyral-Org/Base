#pragma once
#include "common.hpp"

namespace Spyral::Pointers
{
    extern void Destroy();
    extern void Init();

    inline void*** SwapChain;
    inline WNDPROC WndProc;
    inline HWND hwnd;
}