#pragma once

#ifdef URSA_PLATFORM_WINDOWS

extern Ursa::Application* Ursa::CreateApplication();

int main(int argc, char** argv) {
	Ursa::Log::Init();

	URSA_PROFILE_BEGIN_SESSION("Startup", "UrsaProfile-Startup.json");
	auto app = Ursa::CreateApplication();
	URSA_PROFILE_END_SESSION();

	URSA_PROFILE_BEGIN_SESSION("Runtime", "UrsaProfile-Runtime.json");
	app->Run();
	URSA_PROFILE_END_SESSION();

	URSA_PROFILE_BEGIN_SESSION("Shutdown", "UrsaProfile-Shutdown.json");
	delete app;
	URSA_PROFILE_END_SESSION();
}

#endif // URSA_PLATFORM_WINDOWS
