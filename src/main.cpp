#include "common.hpp"
#include "FileMgr/FileMgr.hpp"
#include "Memory/ModuleMgr.hpp"
#include "Hooking.hpp"
#include "Pointers.hpp"

namespace Spyral
{
	DWORD __stdcall main(void*)
	{
		const auto root_directory = std::filesystem::path(std::getenv("APPDATA")) / "Spyral";
		FileMgr::Init(root_directory);

		Logger::Init("SpyralMenu", FileMgr::GetProjectFile("./cout.log").Path());
		LOG(INFO) << "Logger Initialized.";

		ModuleMgr::CacheModule("t6zm.exe");
		ModuleMgr::CacheModule("kernel32.dll");
		ModuleMgr::Init();

		Pointers::Init();
		Hooking::Init();

		while (gRunning)
		{
			std::this_thread::sleep_for(500ms);
		}
		
		Hooking::Destroy();
		Pointers::Destroy();

		Logger::Destroy();

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
