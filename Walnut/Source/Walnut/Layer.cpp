#include "Layer.h"
#include "Application.h"

namespace Walnut {

    void Layer::QueueTransition(std::shared_ptr<Layer> toLayer)
    {
        // Adapted from https://github.com/TheCherno/Architecture/blob/main/Core/Source/Core/Layer.cpp
        // NOTE: THIS MIGHT BE BAD. TODO: "dont do this" - The Cherno
        auto& application = Application::Get();
        for (auto& layer : application.GetLayerStack()) {
            if (layer.get() == this) {
                application.PopLayer(layer);
                application.PushLayer(toLayer);
            }
        }
    }


}