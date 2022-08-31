#include "common.hpp"
#include "FileMgr/FileMgr.hpp"

namespace Spyral
{
	void main()
	{
		std::filesystem::path root_directory = std::getenv("USERPROFILE");
		root_directory /= "Spyral";

		const auto fileManager = FileMgr(root_directory);

		while (gRunning)
			std::this_thread::sleep_for(100ms);
	}
}

bool __stdcall DllMain(HINSTANCE hinstance, std::uint32_t reason, void** reserved)
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
	{
		DisableThreadLibraryCalls(hinstance);

		Spyral::gMainThread = std::thread(Spyral::main);
		Spyral::gInstance   = hinstance;

		break;
	}
	}

	return true;
}