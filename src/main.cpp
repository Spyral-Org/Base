#include "common.hpp"
#include "FileMgr/FileMgr.hpp"

namespace Spyral
{
	DWORD __stdcall main(void*)
	{
		std::filesystem::path root_directory = std::getenv("APPDATA");
		root_directory /= "Spyral";

		FileMgr::Init(root_directory);

		const auto testFile = FileMgr::GetProjectFile("./cout.log");
		auto test = std::fstream(testFile.Path(), std::ios::out);
		test << "example output\n" << std::flush;

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
