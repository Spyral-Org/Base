#include "../Hooks.hpp"
#include "../../Hooking.hpp"

namespace Spyral
{
    LRESULT Window::WndProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
    {
        if (umsg == WM_KEYUP)
        {
            switch (wparam)
            {
            case VK_DELETE:
                gRunning = false;
                break;
            default:
                break;
            }
        }

        return Hooking::GetHook<DetourHook>("WndProc")->Original<WNDPROC>()(hwnd, umsg, wparam, lparam);
    }
}