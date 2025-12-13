#include <imgui.h>

#include "AppLayer.h"
#include "Walnut/Layer.h"

#include "DefaultLayer.h"

namespace example
{
     void AppLayer::OnUIRender() {
        ImGui::Begin("App Layer");
        if (ImGui::Button("Button")) {
            TransitionTo<DefaultLayer>();
        }

        ImGui::End();
    }
};
