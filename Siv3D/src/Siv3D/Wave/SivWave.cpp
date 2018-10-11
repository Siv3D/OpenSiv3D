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
# include "../SoundFont/ISoundFont.hpp"
# include <Siv3D/Wave.hpp>
# include <Siv3D/BinaryWriter.hpp>

namespace s3d
{
	namespace detail
	{
		static size_t CalculateSamples(const Duration& duration, const Arg::samplingRate_<uint32> samplingRate)
		{
			return static_cast<size_t>(duration.count() * (*samplingRate));
		}
	}

	Wave::Wave(const Duration& duration, const Arg::samplingRate_<uint32> samplingRate)
		: Wave(detail::CalculateSamples(duration, samplingRate), samplingRate)
	{

	}

	Wave::Wave(const Duration& duration, const WaveSample& sample, const Arg::samplingRate_<uint32> samplingRate)
		: Wave(detail::CalculateSamples(duration, samplingRate), sample, samplingRate)
	{

	}

	Wave::Wave(const size_t num_samples, Arg::generator_<std::function<double(double)>> generator, const Arg::samplingRate_<uint32> samplingRate)
		: base_type(num_samples)
		, m_samplingRate(*samplingRate)
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

	Wave::Wave(const Duration& duration, Arg::generator_<std::function<double(double)>> generator, const Arg::samplingRate_<uint32> samplingRate)
		: Wave(detail::CalculateSamples(duration, samplingRate), generator, samplingRate)
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

	Wave::Wave(const GMInstrument instrumrnt, const uint8 key, const Duration& duration, const double velocity, const Arg::samplingRate_<uint32> samplingRate)
		: Wave(detail::CalculateSamples(duration + SecondsF(0.5), samplingRate), samplingRate)
	{
		Siv3DEngine::GetSoundFont()->render(*this, detail::CalculateSamples(duration, samplingRate), *samplingRate, static_cast<uint8>(instrumrnt), key, velocity);
	}

	bool Wave::save(const FilePath& path, AudioFormat format)
	{
		if (isEmpty())
		{
			return false;
		}

		if (format == AudioFormat::Unspecified)
		{
			format = Siv3DEngine::GetAudioFormat()->getFormatFromFilePath(path);
		}

		// [Siv3D ToDo]
		if (format != AudioFormat::WAVE)
		{
			return false;
		}

		return saveWAVE(path);
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
