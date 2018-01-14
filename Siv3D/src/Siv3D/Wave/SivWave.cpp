//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "../Siv3DEngine.hpp"
# include "../AudioFormat/IAudioFormat.hpp"
# include <Siv3D/Wave.hpp>
# include <Siv3D/BinaryWriter.hpp>

namespace s3d
{
	Wave::Wave(const SecondsF& length, const uint32 samplingRate)
		: Wave(static_cast<size_t>(length.count() * samplingRate), samplingRate)
	{

	}

	Wave::Wave(const SecondsF& length, const WaveSample& sample, const uint32 samplingRate)
		: Wave(static_cast<size_t>(length.count() * samplingRate), sample, samplingRate)
	{

	}

	Wave::Wave(const size_t num_samples, Arg::generator_<std::function<double(double)>> generator, const uint32 samplingRate)
		: base_type(num_samples)
		, m_samplingRate(samplingRate)
	{
		if (!num_samples)
		{
			return;
		}

		const double ir = 1.0 / m_samplingRate;

		WaveSample* pDst = data();

		for (size_t i = 0; i < num_samples; ++i)
		{
			*pDst++ = static_cast<float>((*generator)(i * ir));
		}
	}

	Wave::Wave(const SecondsF& length, Arg::generator_<std::function<double(double)>> generator, const uint32 samplingRate)
		: Wave(static_cast<size_t>(length.count() * samplingRate), generator, samplingRate)
	{

	}

	Wave::Wave(const FilePath& path)
		: Wave(Siv3DEngine::GetAudioFormat()->load(path))
	{

	}

	Wave::Wave(IReader&& reader, const AudioFormat format)
		: Wave(Siv3DEngine::GetAudioFormat()->decode(std::move(reader), format))
	{

	}

	bool Wave::saveWAVE(const FilePath& path, const WAVEFormat format)
	{
		if (isEmpty())
		{
			return false;
		}

		BinaryWriter writer(path);

		if (!writer)
		{
			return false;
		}

		return Siv3DEngine::GetAudioFormat()->encodeWAVE(writer, *this, format);
	}
}
