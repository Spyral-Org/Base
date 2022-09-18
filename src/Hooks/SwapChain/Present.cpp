#include "../Hooks.hpp"
#include "../../Renderer/Renderer.hpp"

namespace Spyral
{
    HRESULT SwapChain::Present(IDXGISwapChain* that, UINT syncInterval, UINT flags)
    {
        if (gRunning)
            Renderer::OnPresent();
        return Hooking::GetHook<VMTHook>("IDXGISwapChain")->Original<decltype(&Present)>(SwapChain::VMTPresentIdx)(that, syncInterval, flags);
    }
}