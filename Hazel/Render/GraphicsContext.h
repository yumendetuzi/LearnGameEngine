#pragma once
#include "Core.h"
#include <vector>

namespace Hazel {
	class HAZEL_API GraphicsContext {
	public:
		GraphicsContext() {};
		virtual ~GraphicsContext() {};
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};
	
}
