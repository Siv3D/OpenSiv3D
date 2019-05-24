//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3DEngine.hpp>
# include <AudioFormat/IAudioFormat.hpp>
# include <SoundFont/ISoundFont.hpp>
# include <Siv3D/Wave.hpp>
# include <Siv3D/BinaryWriter.hpp>
# include <Siv3D/Math.hpp>

namespace s3d
{
	namespace detail
	{
		static size_t CalculateSamples(const Duration& duration, const Arg::samplingRate_<uint32> samplingRate)
		{
			if (duration.count() <= 0.0)
			{
				return 0;
			}

			return static_cast<size_t>(duration.count() * (*samplingRate));
		}
	}

	Wave::Wave()
	{

	}

	Wave::Wave(const size_t num_samples, Arg::samplingRate_<uint32> samplingRate)
		: base_type(num_samples)
		, m_samplingRate(*samplingRate)
	{
	
	}

	Wave::Wave(const size_t num_samples, const WaveSample& sample, Arg::samplingRate_<uint32> samplingRate)
		: base_type(num_samples, sample)
		, m_samplingRate(*samplingRate)
	{
	
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
		: Wave(Siv3DEngine::Get<ISiv3DAudioFormat>()->load(path))
	{

	}

	Wave::Wave(IReader&& reader, const AudioFormat format)
		: Wave(Siv3DEngine::Get<ISiv3DAudioFormat>()->decode(std::move(reader), format))
	{

	}

	Wave::Wave(const Array<WaveSample>& samples, Arg::samplingRate_<uint32> samplingRate)
		: base_type(samples)
		, m_samplingRate(*samplingRate)
	{
	
	}

	Wave::Wave(Array<WaveSample>&& samples, Arg::samplingRate_<uint32> samplingRate)
		: base_type(std::move(samples))
		, m_samplingRate(*samplingRate)
	{
	
	}

	Wave::Wave(const GMInstrument instrumrnt, const uint8 key, const Duration& duration, const double velocity, const Arg::samplingRate_<uint32> samplingRate, const float silenceValue)
		: Wave(detail::CalculateSamples(duration + SecondsF(1.0), samplingRate), samplingRate)
	{
		Siv3DEngine::Get<ISiv3DSoundFont>()->render(*this, detail::CalculateSamples(duration, samplingRate), *samplingRate, static_cast<uint8>(instrumrnt), key, velocity);

		remove_silence_tail(silenceValue);
	}

	void Wave::fillZero()
	{
		fill(WaveSample::Zero());
	}

	Wave& Wave::operator =(const Array<WaveSample>& other)
	{
		base_type::operator=(other);

		return *this;
	}

	Wave& Wave::operator =(Array<WaveSample>&& other) noexcept
	{
		base_type::operator=(std::move(other));

		return *this;
	}

	Wave& Wave::operator =(const Wave& other)
	{
		base_type::operator=(other);

		return *this;
	}

	Wave& Wave::operator =(Wave&& other) noexcept
	{
		base_type::operator=(std::move(other));

		return *this;
	}

	void Wave::assign(const Wave& other)
	{
		base_type::operator=(other);
	}

	void Wave::assign(Wave&& other) noexcept
	{
		base_type::operator=(std::move(other));
	}

	Wave& Wave::operator <<(const WaveSample& sample)
	{
		base_type::push_back(sample);

		return *this;
	}

	void Wave::swap(Wave& other)
	{
		base_type::swap(other);
	}

	Wave& Wave::append(const Array<WaveSample>& other)
	{
		base_type::insert(end(), other.begin(), other.end());

		return *this;
	}

	Wave& Wave::append(const Wave& other)
	{
		base_type::insert(end(), other.begin(), other.end());

		return *this;
	}

	Wave& Wave::remove_at(const size_t index)
	{
		base_type::remove_at(index);

		return *this;
	}

	Wave& Wave::reverse()
	{
		base_type::reverse();

		return *this;
	}

	Wave& Wave::rotate(const std::ptrdiff_t count)
	{
		base_type::rotate(count);

		return *this;
	}

	Wave Wave::slice(const size_t index) const
	{
		return Wave(base_type::slice(index), Arg::samplingRate = m_samplingRate);
	}

	Wave Wave::slice(const size_t index, const size_t length) const
	{
		return Wave(base_type::slice(index, length), Arg::samplingRate = m_samplingRate);
	}

	bool Wave::save(const FilePath& path, AudioFormat format)
	{
		if (isEmpty())
		{
			return false;
		}

		if (format == AudioFormat::Unspecified)
		{
			format = Siv3DEngine::Get<ISiv3DAudioFormat>()->getFormatFromFilePath(path);
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

		return Siv3DEngine::Get<ISiv3DAudioFormat>()->encodeWAVE(writer, *this, format);
	}

	void Wave::remove_silence_tail(const float value)
	{
		if (size() < 2)
		{
			return;
		}

		size_t removeCount = 0;

		const WaveSample* const pSrcTop = data();
		const WaveSample* pSrc = pSrcTop + (size() - 1);

		while (pSrc > (pSrcTop + 1))
		{
			if (Math::Abs(pSrc->left) <= value && (Math::Abs(pSrc->right) <= value))
			{
				++removeCount;
				--pSrc;
			}
			else
			{
				break;
			}
		}

		if (removeCount > 1)
		{
			erase(end() - (removeCount - 1), end());
			shrink_to_fit();
			back() = WaveSample(0.0f, 0.0f);
		}
	}
}
