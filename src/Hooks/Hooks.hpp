#pragma once
#include "../common.hpp"

namespace Spyral
{
    namespace Kernel32
    {
        extern BOOL IsDebuggerPresent();
    }

    namespace Window
    {
        extern LRESULT WndProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam);
    }
}