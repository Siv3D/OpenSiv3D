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

# pragma once
# include "Array.hpp"
# include "WaveSample.hpp"
# include "AudioFormat.hpp"
# include "Duration.hpp"

namespace s3d
{
	class Wave : protected Array<WaveSample>
	{
	private:

		using base_type = Array<WaveSample>;

		uint32 m_samplingRate = DefaultSamplingRate;

		void remove_silence_tail(float value);

	public:

		using typename base_type::value_type;
		using typename base_type::pointer;
		using typename base_type::const_pointer;
		using typename base_type::reference;
		using typename base_type::const_reference;
		using typename base_type::iterator;
		using typename base_type::const_iterator;
		using typename base_type::reverse_iterator;
		using typename base_type::const_reverse_iterator;
		using typename base_type::size_type;
		using typename base_type::difference_type;
		using typename base_type::allocator_type;

		using base_type::Array;
		using base_type::assign;
		using base_type::get_allocator;
		using base_type::at;
		using base_type::operator[];
		using base_type::front;
		using base_type::back;
		using base_type::data;
		using base_type::begin;
		using base_type::cbegin;
		using base_type::end;
		using base_type::cend;
		using base_type::rbegin;
		using base_type::crbegin;
		using base_type::rend;
		using base_type::crend;
		using base_type::empty;
		using base_type::size;
		using base_type::max_size;
		using base_type::reserve;
		using base_type::capacity;
		using base_type::shrink_to_fit;
		using base_type::clear;
		using base_type::insert;
		using base_type::emplace;
		using base_type::erase;
		using base_type::push_back;
		using base_type::emplace_back;
		using base_type::pop_back;
		using base_type::resize;

		using base_type::count;
		using base_type::count_if;
		using base_type::isEmpty;
		using base_type::operator bool;
		using base_type::release;
		using base_type::size_bytes;
		using base_type::push_front;
		using base_type::pop_front;
		using base_type::fill;
		using base_type::join;
		using base_type::remove;

		/// <summary>
		/// 
		/// </summary>
		static constexpr uint32 MinSamplingRate = 4000;

		/// <summary>
		/// 
		/// </summary>
		static constexpr uint32 DefaultSamplingRate = 44100;

		/// <summary>
		/// 
		/// </summary>
		static constexpr uint32 MaxSamplingRate = 192000;

		Wave();

		Wave(const Wave& wave) = default;

		Wave(Wave&& wave) = default;

		explicit Wave(size_t num_samples, Arg::samplingRate_<uint32> samplingRate);

		explicit Wave(const Duration& duration, Arg::samplingRate_<uint32> samplingRate = DefaultSamplingRate);

		Wave(size_t num_samples, const WaveSample& sample, Arg::samplingRate_<uint32> samplingRate);

		Wave(const Duration& duration, const WaveSample& sample, Arg::samplingRate_<uint32> samplingRate = DefaultSamplingRate);

		Wave(size_t num_samples, Arg::generator_<std::function<double(double)>> generator, Arg::samplingRate_<uint32> samplingRate = DefaultSamplingRate);

		Wave(const Duration& duration, Arg::generator_<std::function<double(double)>> generator, Arg::samplingRate_<uint32> samplingRate = DefaultSamplingRate);

		explicit Wave(const FilePath& path);

		explicit Wave(IReader&& reader, AudioFormat format = AudioFormat::Unspecified);

		template <class InputIt>
		Wave(InputIt first, InputIt last, Arg::samplingRate_<uint32> samplingRate = DefaultSamplingRate)
			: base_type(first, last)
			, m_samplingRate(*samplingRate) {}

		explicit Wave(const Array<WaveSample>& samples, Arg::samplingRate_<uint32> samplingRate = DefaultSamplingRate);

		explicit Wave(Array<WaveSample>&& samples, Arg::samplingRate_<uint32> samplingRate = DefaultSamplingRate);

		Wave(GMInstrument instrumrnt, uint8 key, const Duration& duration, double velocity = 1.0, Arg::samplingRate_<uint32> samplingRate = DefaultSamplingRate, float silenceValue = 0.01f);

		[[nodiscard]] uint32 samplingRate() const noexcept
		{
			return m_samplingRate;
		}

		void setSamplingRate(uint32 samplingRate) noexcept
		{
			m_samplingRate = samplingRate;
		}
		
		[[nodiscard]] size_t samples() const noexcept
		{
			return size();
		}

		[[nodiscard]] size_t lengthSample() const noexcept
		{
			return size();
		}

		[[nodiscard]] double lengthSec() const noexcept
		{
			return static_cast<double>(size()) / m_samplingRate;
		}

		void fillZero();

		Wave& operator =(const Array<WaveSample>& other);

		Wave& operator =(Array<WaveSample>&& other) noexcept;

		Wave& operator =(const Wave& other);

		Wave& operator =(Wave&& other) noexcept;

		void assign(const Wave& other);

		void assign(Wave&& other) noexcept;
		
		Wave& operator <<(const WaveSample& sample);

		void swap(Wave& other);

		Wave& append(const Array<WaveSample>& other);

		Wave& append(const Wave& other);

		Wave& remove_at(const size_t index);

		Wave& reverse();

		Wave& rotate(std::ptrdiff_t count = 1);

		Wave slice(size_t index) const;

		Wave slice(size_t index, size_t length) const;

		bool save(const FilePath& path, AudioFormat format = AudioFormat::WAVE);

		bool saveWAVE(const FilePath& path, WAVEFormat format = WAVEFormat::Default);

		//[[nodiscard]] MemoryWriter encode(AudioFormat format = AudioFormat::WAVE) const;
	};
}

namespace std
{
	inline void swap(s3d::Wave& a, s3d::Wave& b)
	{
		a.swap(b);
	}
}
