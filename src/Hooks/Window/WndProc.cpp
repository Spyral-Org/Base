#include "../Hooks.hpp"
#include "../../Renderer/Renderer.hpp"

namespace Spyral
{
    LRESULT Window::WndProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
    {
        if (gRunning)
            Renderer::WndProc(hwnd, umsg, wparam, lparam);

        if (umsg == WM_KEYUP && wparam == VK_DELETE) // fallback to unload
            gRunning = false;

        return Hooking::GetHook<DetourHook>("WndProc")->Original<WNDPROC>()(hwnd, umsg, wparam, lparam);
    }
}