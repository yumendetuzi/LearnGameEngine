#include "LayerStack.h"
namespace Hazel {

	Hazel::LayerStack::LayerStack()
	{

	}

	Hazel::LayerStack::~LayerStack()
	{
		for each (Layer * var in mLayers)
		{
			delete var;
			var = NULL;
		}
		mLayers.clear();
	}
	void LayerStack::PushLayer(Layer* layer)
	{
		mLayers.push_back(layer);
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		std::vector<Layer*>::iterator it = End();
		for (it = Begin(); it != End(); it++)
		{
			if ((*it) == layer)
			{
				break;
			}
		}
		if (it != End())
		{
			mLayers.erase(it);
			delete (*it);
		}
	}

	std::vector<Layer*>::iterator LayerStack::Begin()
	{
		return mLayers.begin();
	}

	std::vector<Layer*>::iterator LayerStack::End()
	{
		return mLayers.end();
	}

}