#include "common.hpp"
#include "FileMgr/FileMgr.hpp"
#include "Memory/ModuleMgr.hpp"
#include "Memory/PatternScanner.hpp"
#include "Hooking.hpp"
#include <fstream>

namespace Spyral
{
	DWORD __stdcall main(void*)
	{
		AllocConsole();

		const auto root_directory = std::filesystem::path(std::getenv("APPDATA")) / "Spyral";
		FileMgr::Init(root_directory);

		auto cout = std::fstream("CONOUT$", std::ios::out | std::ios::app);
		cout << "Starting SpyralBase...\n" << std::flush;

		ModuleMgr::CacheModule("GTA5.exe");
		ModuleMgr::Init();
		cout << "ModuleMgr initialized!\n" << std::flush;

		const auto module = ModuleMgr::GetModule("GTA5.exe");
		cout << "Found Module: [GTA5.exe] => 0x" << std::hex << std::uppercase << module->Base() << " : sizeof(" << module->Size() << ")\n" << std::flush;

		PatternScanner scanner(module);
		scanner.Add("66 0F 6E 0D ? ? ? ? 0F B7 3D", [&cout](AddressHelper addr)
		{
			const auto x = addr.Sub(4).Relative().As<int*>();
			const auto y = addr.Add(4).Relative().As<int*>();

			cout << "Game is running at " << std::dec << *x << "x" << *y << "\n" << std::flush;

			return true;
		});
		scanner.Scan();

		Hooking::Init();

		// do menu stuff (infinite while or smth)

		Hooking::Destroy();

		cout << "Finished...\n" << std::flush;
		cout.close();
		std::this_thread::sleep_for(5s);

		FreeConsole();
		CloseHandle(gMainThread);
		FreeLibraryAndExitThread(gInstance, 0);

		return 0;
	}
}

bool __stdcall DllMain(HINSTANCE hinstance, std::uint32_t reason, void** reserved)
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
	{
		DisableThreadLibraryCalls(hinstance);

		Spyral::gMainThread = CreateThread(nullptr, 0, Spyral::main, nullptr, 0, nullptr);
		Spyral::gInstance   = hinstance;

		break;
	}
	}

	return true;
}
