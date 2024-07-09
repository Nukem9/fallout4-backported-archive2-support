#include "Impl/ShaderPackageStream.h"
#include "Impl/BSImagespaceShaderCopyShadowMapToArray.h"

extern "C" DLLEXPORT bool F4SEAPI F4SEPlugin_Query(const F4SE::QueryInterface *F4SE, F4SE::PluginInfo *Info)
{
#ifndef NDEBUG
	auto sink = std::make_shared<spdlog::sinks::msvc_sink_mt>();
#else
	auto path = logger::log_directory();

	if (!path)
		return false;

	*path /= fmt::format(FMT_STRING("{}.log"), BUILD_PROJECT_NAME);
	auto sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(path->string(), true);
#endif

	auto log = std::make_shared<spdlog::logger>("global log"s, std::move(sink));

#ifndef NDEBUG
	log->set_level(spdlog::level::trace);
#else
	log->set_level(spdlog::level::info);
	log->flush_on(spdlog::level::info);
#endif

	spdlog::set_default_logger(std::move(log));
	spdlog::set_pattern("[%H:%M:%S:%e TID %5t] %v"s);

	spdlog::info("{} v{}.{}.0", BUILD_PROJECT_NAME, BUILD_VERSION_MAJOR, BUILD_VERSION_MINOR);

	Info->infoVersion = F4SE::PluginInfo::kVersion;
	Info->name = BUILD_PROJECT_NAME;
	Info->version = BUILD_VERSION_MAJOR;

	if (F4SE->IsEditor())
	{
		spdlog::error("Loaded in editor");
		return false;
	}

	const auto ver = F4SE->RuntimeVersion();

	if (ver < F4SE::RUNTIME_1_10_162)
	{
		spdlog::error("Unsupported runtime v{}", ver.string());
		return false;
	}

	return true;
}

extern "C" DLLEXPORT bool F4SEAPI F4SEPlugin_Load(const F4SE::LoadInterface *F4SE)
{
	F4SE::Init(F4SE);

	// Alloc trampoline space and set up hooks
	auto& trampoline = F4SE::GetTrampoline();
	F4SE::AllocTrampoline(32);

	REL::Relocation<uint8_t> versionPatch1 { REL::ID(1566228), 0x3DF };
	REL::safe_fill(versionPatch1.address(), 8, 1);

	REL::Relocation<uint8_t> versionPatch2 { REL::ID(624471), 0xBA };
	REL::safe_fill(versionPatch2.address(), 8, 1);

	ShaderPackageStreamHook::Func = trampoline.write_call<5>(ShaderPackageStreamHook::GetTarget(), ShaderPackageStreamHook::Thunk);

#if 0
	// Bump shader package version to avoid conflicts. Still doesn't work correctly as a loose file.
	REL::Relocation<uint8_t> shadersFxVersionPatch{ REL::ID(730737) };
	REL::safe_fill(shadersFxVersionPatch.address(), 163, 1);

	HookBSImagespaceShaderCopyShadowMapToArray::Func = trampoline.write_call<5>(
		HookBSImagespaceShaderCopyShadowMapToArray::GetTarget(),
		HookBSImagespaceShaderCopyShadowMapToArray::Thunk);
#endif

	return true;
}
