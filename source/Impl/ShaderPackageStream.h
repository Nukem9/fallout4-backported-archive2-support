#pragma once

#include "../RE/Shims.h"

using namespace F4SE;

class ShaderPackageStream : public RE::BSResource::Stream
{
	using ErrorCode = RE::BSResource::ErrorCode;

private:
	mutable size_t m_FilePosition = 0; // CommonLib incorrectly declares several functions as const
	size_t m_FileSize = 0;

	const uint8_t *m_Buffer = nullptr;

public:
	F4_HEAP_REDEFINE_NEW(ShaderPackageStream);

	ShaderPackageStream();
	~ShaderPackageStream() override = default;

	ErrorCode DoOpen() override;
	void DoClose() override;
	std::uint64_t DoGetKey() const override;
	ErrorCode DoGetInfo(RE::BSResource::Info&) override;
	void DoClone(RE::BSTSmartPointer<Stream>&) const override;
	ErrorCode DoRead(void *Buffer, std::uint64_t Bytes, std::uint64_t& Read) const override;
	ErrorCode DoReadAt(void *, std::uint64_t, std::uint64_t, std::uint64_t&) const override;
	ErrorCode DoWrite(const void *, std::uint64_t, std::uint64_t&) const override;
	ErrorCode DoSeek(std::int64_t, RE::BSResource::SeekMode, std::uint64_t&) const override;
	ErrorCode DoSetEndOfStream() override;
	ErrorCode DoPrefetchAt(uint64_t, uint64_t, uint32_t) const override;
	ErrorCode DoStartTaggedPrioritizedRead(
		void *,
		std::uint64_t,
		std::uint64_t,
		std::uint32_t,
		volatile std::uint32_t *,
		std::uint32_t&,
		RE::BSEventFlag *) const override;
	ErrorCode DoWaitTags(volatile std::uint32_t *, std::uint32_t, RE::BSEventFlag *) const override;
	ErrorCode DoPrefetchAll(std::uint32_t) const override;
	bool DoGetName(RE::BSFixedString&) const override;
	ErrorCode DoCreateAsync(RE::BSTSmartPointer<RE::BSResource::AsyncStream>&) const override;
	bool DoQTaggedPrioritizedReadSupported() const override;
	ErrorCode DoCreateOp(RE::BSTSmartPointer<RE::BSResource::ICacheDriveOp>&, const char *) const override;
	bool DoGetIsFromArchive() const override;

	static ShaderPackageStream *Create();
};

struct ShaderPackageStreamHook
{
	static RE::BSIStream *Thunk(RE::BSIStream *Thisptr, void *a1, void *a2, void *a3)
	{
		auto bsStream = Func(Thisptr, a1, a2, a3);
		bsStream->spStream.reset(ShaderPackageStream::Create());

		return bsStream;
	}

	static auto GetTarget()
	{
		return REL::Relocation<uintptr_t>(REL::ID(545406), 0x86).address();
	}

	static inline REL::Relocation<decltype(&Thunk)> Func;
};
