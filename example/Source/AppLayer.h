#pragma once

#include <imgui.h>
#include "Walnut/Layer.h"

namespace example {

class AppLayer : public Walnut::Layer
{
    void OnUIRender() override;
};

}
