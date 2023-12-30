#pragma once

#ifdef HAZEL_BUILD
#define HAZEL_API _declspec(dllexport)
	
#else
#define HAZEL_API _declspec(dllimport)
#endif

#define BIT(x) (1 << x)
