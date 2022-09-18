#pragma once
#include "../common.hpp"
#include "../Hooking.hpp"

namespace Spyral
{
    namespace Kernel32
    {
        extern BOOL IsDebuggerPresent();
    }

    namespace SwapChain
    {
        constexpr auto VMTPresentIdx = 8;
        constexpr auto VMTResizeBuffersIdx = 13;
        extern HRESULT Present(IDXGISwapChain* that, UINT syncInterval, UINT flags);
        extern HRESULT ResizeBuffers(IDXGISwapChain* that, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags);
    }

    namespace Window
    {
        extern LRESULT WndProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam);
    }
}