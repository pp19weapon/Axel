#pragma once


#ifdef AX_PLATFORM_WINDOWS

extern Axel::Application* Axel::CreateApplication();

int main(int argc, char** argv) {
	auto app = Axel::CreateApplication();
	app->run();
	delete app;
}
#endif // AX_PLATFORM_WINDOWS
