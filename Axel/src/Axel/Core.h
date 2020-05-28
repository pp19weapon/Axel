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

#ifdef AX_DEBUG
	#define AX_ENABLE_ASSERTS
	#define AX_ENABLE_DEBUG_LOG
#endif

#ifdef AX_ENABLE_ASSERTS
	#define AX_ASSERT(x, ...) { if (!(x)) { AX_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define AX_CORE_ASSERT(x, ...) { if (!(x)) { AX_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define AX_ASSERT(x , ...)
	#define AX_CORE_ASSERT(x , ...)
#endif // AX_ENABLE_ASSERTS



#define BIT(x) (1 << x)

#define AX_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)