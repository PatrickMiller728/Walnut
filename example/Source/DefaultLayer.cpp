#include <imgui.h>

#include "DefaultLayer.h"
#include "AppLayer.h"
#include "Walnut/Layer.h"

namespace example
{
     void DefaultLayer::OnUIRender() {
        ImGui::Begin("Default Layer");
        if (ImGui::Button("Button")) {
            TransitionTo<AppLayer>();
        }

        ImGui::End();
    }
};
