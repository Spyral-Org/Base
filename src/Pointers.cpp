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
        const auto module = ModuleMgr::GetModule("t6zm.exe");
        PatternScanner scanner(module);

		scanner.Add("A1 ?? ?? ?? ?? 81 EC 90 00 00 00", [](AddressHelper addr)
		{
			SwapChain = addr.Add(1).Absolute().As<void***>();

			return true;
		});

        scanner.Add("83 EC 40 A1 ?? ?? ?? ?? 53 55 56 50 E8 ?? ?? ?? ?? 8B", [](AddressHelper addr)
        {
            WndProc = addr.As<WNDPROC>();

            return true;
        });

		scanner.Scan();
    }
}
