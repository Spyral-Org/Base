#include "Menu.hpp"

namespace Spyral
{
    void Menu::Main()
    {
        if (!GUI::IsOpen())
            return;

        if (ImGui::Begin("Test"))
        {
            if (ImGui::Button("Unload"))
                gRunning = false;
        }
        ImGui::End();
    }
}