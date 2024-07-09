#include "ShaderPackageStream.h"

#if !__has_include("ShaderPackageBinaryBlob.inl")
#error "ShaderPackageBinaryBlob.inl not found. Run /resources/GenerateHeaderFromBinary.ps1 at least once."
#else
#include "ShaderPackageBinaryBlob.inl"
#endif

ShaderPackageStream::ShaderPackageStream()
{
	m_FileSize = sizeof(ShaderPackageBinaryBlob);
	m_Buffer = ShaderPackageBinaryBlob;
}

ShaderPackageStream::ErrorCode ShaderPackageStream::DoOpen()
{
	return ErrorCode::kNone;
}

void ShaderPackageStream::DoClose()
{
}

std::uint64_t ShaderPackageStream::DoGetKey() const
{
	__debugbreak();
	__assume(0);
}

ShaderPackageStream::ErrorCode ShaderPackageStream::DoGetInfo(RE::BSResource::Info&)
{
	__debugbreak();
	__assume(0);
}

void ShaderPackageStream::DoClone(RE::BSTSmartPointer<Stream>&) const
{
	__debugbreak();
	__assume(0);
}

ShaderPackageStream::ErrorCode ShaderPackageStream::DoRead(void *Buffer, std::uint64_t Bytes, std::uint64_t& Read) const
{
	const auto copySize = (std::min)(Bytes, m_FileSize - m_FilePosition);

	if (copySize > 0) {
		memcpy(Buffer, m_Buffer + m_FilePosition, copySize);
		m_FilePosition += copySize;

		// Redistributing game assets is generally frowned upon. Pretend it's not the original shader package by XORing
		// the data with a key. Maybe a bit too paranoid...
		for (size_t i = 0; i < copySize; i++)
			reinterpret_cast<uint8_t *>(Buffer)[i] ^= ShaderPackageBinaryBlobXorKey;
	}

	Read = copySize;
	return ErrorCode::kNone;
}

ShaderPackageStream::ErrorCode ShaderPackageStream::DoReadAt(void *, std::uint64_t, std::uint64_t, std::uint64_t&) const
{
	__debugbreak();
	__assume(0);
}

ShaderPackageStream::ErrorCode ShaderPackageStream::DoWrite(const void *, std::uint64_t, std::uint64_t&) const
{
	__debugbreak();
	__assume(0);
}

ShaderPackageStream::ErrorCode ShaderPackageStream::DoSeek(std::int64_t, RE::BSResource::SeekMode, std::uint64_t&) const
{
	__debugbreak();
	__assume(0);
}

ShaderPackageStream::ErrorCode ShaderPackageStream::DoSetEndOfStream()
{
	m_FilePosition = m_FileSize;
	return ErrorCode::kNone;
}

ShaderPackageStream::ErrorCode ShaderPackageStream::DoPrefetchAt(std::uint64_t, std::uint64_t, std::uint32_t) const
{
	return ErrorCode::kNone;
}

ShaderPackageStream::ErrorCode ShaderPackageStream::DoStartTaggedPrioritizedRead(
	void *,
	std::uint64_t,
	std::uint64_t,
	std::uint32_t,
	volatile std::uint32_t *,
	std::uint32_t&,
	RE::BSEventFlag *) const
{
	__debugbreak();
	__assume(0);
}

ShaderPackageStream::ErrorCode ShaderPackageStream::DoWaitTags(volatile std::uint32_t *, std::uint32_t, RE::BSEventFlag *) const
{
	__debugbreak();
	__assume(0);
}

ShaderPackageStream::ErrorCode ShaderPackageStream::DoPrefetchAll(std::uint32_t) const
{
	return ErrorCode::kNone;
}

bool ShaderPackageStream::DoGetName(RE::BSFixedString&) const
{
	__debugbreak();
	__assume(0);
}

ShaderPackageStream::ErrorCode ShaderPackageStream::DoCreateAsync(RE::BSTSmartPointer<RE::BSResource::AsyncStream>&) const
{
	__debugbreak();
	__assume(0);
}

bool ShaderPackageStream::DoQTaggedPrioritizedReadSupported() const
{
	return false;
}

ShaderPackageStream::ErrorCode ShaderPackageStream::DoCreateOp(RE::BSTSmartPointer<RE::BSResource::ICacheDriveOp>&, const char *) const
{
	__debugbreak();
	__assume(0);
}

bool ShaderPackageStream::DoGetIsFromArchive() const
{
	return true;
}

ShaderPackageStream* ShaderPackageStream::Create()
{
	return new ShaderPackageStream();
}
