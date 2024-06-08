#pragma once
#include "Core.h"
#include "Layer.h"
#include <vector>

namespace Hazel {
	class HAZEL_API LayerStack {
	public:
		LayerStack();
		virtual ~LayerStack();
		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);

		std::vector<Layer*>::iterator Begin();
		std::vector<Layer*>::iterator End();

	private:
		std::vector<Layer*> mLayers;
	};
	
}
