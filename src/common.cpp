#include "common.hpp"

namespace Spyral
{
    std::thread gMainThread { };
    HINSTANCE gInstance { nullptr };

    bool gRunning { false };
}