//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"

namespace s3d
{
	class IAudioStream
	{
	public:

		virtual ~IAudioStream() = default;

		virtual void getAudio(float* left, float* right, size_t samplesToWrite) = 0;

		virtual bool hasEnded() = 0;

		virtual void rewind() = 0;
	};
}
