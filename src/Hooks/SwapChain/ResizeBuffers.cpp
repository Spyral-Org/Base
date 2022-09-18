#include "../Hooks.hpp"
#include "../../Renderer/Renderer.hpp"

namespace Spyral
{
    HRESULT SwapChain::ResizeBuffers(IDXGISwapChain* that, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags)
    {
        const auto& original = Hooking::GetHook<VMTHook>("IDXGISwapChain")->Original<decltype(&ResizeBuffers)>(SwapChain::VMTResizeBuffersIdx);
        if (gRunning)
        {
            Renderer::PreResize();
            const auto result = original(that, bufferCount, width, height, newFormat, swapChainFlags);
            Renderer::PostResize();

            return result;
        }

        return original(that, bufferCount, width, height, newFormat, swapChainFlags);
    }
}