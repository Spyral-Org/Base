#include "common.hpp"
#include "FileMgr/FileMgr.hpp"
#include "Memory/ModuleMgr.hpp"
#include "Hooking.hpp"
#include "Pointers.hpp"
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

		Pointers::Init();

		Hooking::Init();

		// do menu stuff (infinite while or smth)

		Hooking::Destroy();

		Pointers::Destroy();

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
