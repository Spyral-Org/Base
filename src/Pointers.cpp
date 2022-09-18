#include "Pointers.hpp"
#include "Memory/ModuleMgr.hpp"
#include "Memory/PatternScanner.hpp"

namespace Spyral
{
    void Pointers::Destroy()
    {
        
    }

    void Pointers::Init()
    {
        const auto module = ModuleMgr::GetModule("GTA5.exe");
        PatternScanner scanner(module);

		scanner.Add("48 8B 0D ? ? ? ? 48 85 C9 0F 84 02 02 00 00", [](AddressHelper addr)
		{
            SwapChain = addr.Add(3).Relative().As<IDXGISwapChain**>();

            return true;
		});

        scanner.Add("48 8B C4 48 89 58 08 4C 89 48 20 55 56 57 41 54 41 55 41 56 41 57 48 8D 68 A1 48 81 EC F0", [](AddressHelper addr)
        {
            WndProc = addr.As<WNDPROC>();

            return true;
        });

		scanner.Scan();

        if (hwnd = FindWindowA("grcWindow", nullptr); !hwnd)
            LOG(WARNING) << "Failed to find game window.";

        LOG(INFO) << "Finished module address lookups.";
    }
}
