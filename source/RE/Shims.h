#pragma once

namespace RE
{
	class BSImageSpaceShader;

	class BSIStream
	{
	public:
		virtual ~BSIStream() = 0;
		BSTSmartPointer<BSResource::Stream, BSTSmartPointerAutoPtr> spStream;
	};
}
