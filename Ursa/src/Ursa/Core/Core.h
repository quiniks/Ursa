#pragma once
#include <memory>

#ifdef _WIN32
	/* Windows x64/x86 */
	#ifdef _WIN64
		/* Windows x64  */
		#define URSA_PLATFORM_WINDOWS
	#else
		/* Windows x86 */
		#error "x86 Builds are not supported!"
	#endif
#else
	/* Unknown compiler/platform */
	#error "Unknown platform!"
#endif

#ifdef URSA_DEBUG
	#define URSA_ENABLE_ASSERTS
#endif

#ifdef URSA_ENABLE_ASSERTS
	#define URSA_ASSERT(x, ...) {if(!(x)) {URSA_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
	#define URSA_CORE_ASSERT(x, ...) {if(!(x)) {URSA_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
#else
	#define URSA_ASSERT(x, ...)
	#define URSA_CORE_ASSERT(x, ...)
#endif


#define BIT(x) (1 << x)
#define URSA_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Ursa {
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args) {
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args) {
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}