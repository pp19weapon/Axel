#pragma once


#ifdef AX_PLATFORM_WINDOWS

extern Axel::Application* Axel::createApplication();

int main(int argc, char** argv) {
	Axel::Log::init();
	AX_CORE_INFO("Initialized log!");

	auto app = Axel::createApplication();
	app->run();
	delete app;
}
#endif // AX_PLATFORM_WINDOWS
