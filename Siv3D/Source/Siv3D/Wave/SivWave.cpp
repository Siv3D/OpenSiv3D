//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "../Siv3DEngine.hpp"
# include "../AudioFormat/IAudioFormat.hpp"
# include <Siv3D/Wave.hpp>

namespace s3d
{
	Wave::Wave(const FilePath& path)
		: Wave(Siv3DEngine::GetAudioFormat()->load(path))
	{

	}

	Wave::Wave(IReader&& reader, const AudioFormat format)
		: Wave(Siv3DEngine::GetAudioFormat()->decode(std::move(reader), format))
	{

	}

	Wave::Wave(Wave&& wave) noexcept
		: base_type(std::move(wave))
		, m_samplingRate(wave.m_samplingRate)
	{

	}
}
