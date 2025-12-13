#pragma once

#include <imgui.h>
#include "Walnut/Layer.h"

namespace example {

class DefaultLayer : public Walnut::Layer
{
    void OnUIRender() override;
};

}
