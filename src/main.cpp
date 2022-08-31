#include "common.hpp"
#include "FileMgr/FileMgr.hpp"
#include "Memory/ModuleMgr.hpp"
#include "Memory/PatternScanner.hpp"
#include <fstream>

namespace Spyral
{
	DWORD __stdcall main(void*)
	{
		const auto root_directory = std::filesystem::path(std::getenv("APPDATA")) / "Spyral";
		FileMgr::Init(root_directory);

		auto file = std::fstream(FileMgr::GetProjectFile("./cout.log").Path(), std::ios::out);
		file << "Starting SpyralBase...\n";

		ModuleMgr::CacheModule("GTA5.exe");
		ModuleMgr::Init();
		file << "ModuleMgr initialized!\n";

		const auto module = ModuleMgr::GetModule("GTA5.exe");
		file << "Found Module: [GTA5.exe] => 0x" << std::hex << std::uppercase << module->Base() << " : sizeof(" << module->Size() << ")\n";

		PatternScanner scanner(module);
		scanner.Add("66 0F 6E 0D ? ? ? ? 0F B7 3D", [&file](void* addr)
		{
			file << "Found Screen Resolution at Addr[0x" << std::hex << std::uppercase << addr << "]\n";

			return true;
		});
		scanner.Scan();

		file.close();

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
