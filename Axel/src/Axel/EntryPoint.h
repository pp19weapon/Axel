#pragma once


#ifdef AX_PLATFORM_WINDOWS

extern Axel::Application* Axel::createApplication();

int main(int argc, char** argv) {
	Axel::Log::init();
	AX_CORE_WARN("Initialized log!");
	int a = 8;
	AX_INFO("HEllo var={0}", a);

	auto app = Axel::createApplication();
	app->run();
	delete app;
}
#endif // AX_PLATFORM_WINDOWS
