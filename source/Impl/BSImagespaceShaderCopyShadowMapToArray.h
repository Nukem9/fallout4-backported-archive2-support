#pragma once

#if 0 // Attempt to load newer shader package version
#include "../RE/Shims.h"

struct HookBSImagespaceShaderCopyShadowMapToArray
{
	static void Thunk(RE::BSImageSpaceShader* Thisptr)
	{
		Func(Thisptr);

		auto loadStream = GetLoadStream();
		uint64_t currentPosition = 0;

		// Fallout 4 1.10.163: Stream position is expected to be 12358684 after the above call returns.
		// Fallout 4 1.10.980: Stream position is expected to be 12408244 after the above call returns. However,
		// Bethesda added a new pass (ISCopyNormals) that doesn't exist in 1.10.163, so we have to skip that chunk.
		loadStream->spStream->DoSeek(0, RE::BSResource::SeekMode::kCur, currentPosition);

		if (currentPosition == 12408244)
		{
			currentPosition = 12409024;
			loadStream->spStream->DoSeek(currentPosition, RE::BSResource::SeekMode::kSet, currentPosition);
		}
	}

	static RE::BSIStream* GetLoadStream()
	{
		static REL::Relocation<RE::BSIStream**> loadStream{ REL::ID(1160120) };
		return *loadStream.get();
	}

	static auto GetTarget()
	{
		return REL::Relocation<uintptr_t>(REL::ID(362866), 0x10C).address();
	}

	static inline REL::Relocation<decltype(&Thunk)> Func;
};
#endif
