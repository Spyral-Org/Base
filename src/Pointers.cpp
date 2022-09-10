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

		scanner.Add("48 8B 01 41 8B D6 0F 44 15", [](AddressHelper addr)
		{
			SwapChain = addr.Sub(20).As<void***>();

			return true;
		});
		scanner.Scan();
    }
}
