#pragma once
#include <memory>

namespace Walnut {

	class Layer
	{
	public:
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}

		virtual void OnUpdate(float ts) {}
		virtual void OnRender() {}
		virtual void OnUIRender() {}

		template<std::derived_from<Layer> T, typename... Args>
		void TransitionTo(Args&&... args)
		{
			QueueTransition(std::move(std::make_shared<T>(std::forward<Args>(args)...)));
		}

	private:
		void QueueTransition(std::shared_ptr<Layer> toLayer);
	};

}
