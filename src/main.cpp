#include "common.hpp"
#include "FileMgr/FileMgr.hpp"
#include "GUI/GUI.hpp"
#include "Memory/ModuleMgr.hpp"
#include "Hooking.hpp"
#include "Pointers.hpp"
#include "Renderer/Renderer.hpp"

namespace Spyral
{
	DWORD __stdcall main(void*)
	{
		const auto root_directory = std::filesystem::path(std::getenv("APPDATA")) / "Spyral";
		FileMgr::Init(root_directory);

		Logger::Init("SpyralMenu", FileMgr::GetProjectFile("./cout.log").Path());
		LOG(INFO) << "Logger Initialized.";

		ModuleMgr::CacheModule("GTA5.exe");
		ModuleMgr::Init();

		Pointers::Init();

		Renderer::Init();
		GUI::Init();

		Hooking::Init();

		while (gRunning)
		{
			std::this_thread::sleep_for(500ms);
		}
		
		Hooking::Destroy();
		Renderer::Destroy();
		Pointers::Destroy();

		LOG(INFO) << "Destroying logger and doing final cleanup.";
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
