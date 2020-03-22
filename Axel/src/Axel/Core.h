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
