#pragma once

#ifdef AX_PLATFORM_WINDOWS
	#ifdef AX_BUILD_DLL
		#define AXEL_API _declspec(dllexport)
	#else
		#define AXEL_API _declspec(dllimport)
	#endif
#else
	#error Axel only supports windows for now!
#endif // AX_PLATFORM_WINDOWS

#ifdef AX_ENABLE_ASSERTS
	#define AX_ASSERTS(x, ...) { if (!(x)) { AX_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define AX_CORE_ASSERTS(x, ...) { if (!(x)) { AX_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define AX_ASSERTS(x , ...)
	#define AX_CORE_ASSERTS(x , ...)
#endif // AX_ENABLE_ASSERTS



#define BIT(x) (1 << x)