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

		using base_type::operator=;
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

		Wave() = default;

		explicit Wave(size_t num_samples, uint32 samplingRate = DefaultSamplingRate)
			: base_type(num_samples)
			, m_samplingRate(samplingRate) {}

		explicit Wave(const SecondsF& length, uint32 samplingRate = DefaultSamplingRate);

		Wave(size_t num_samples, const WaveSample& sample, uint32 samplingRate = DefaultSamplingRate)
			: base_type(num_samples, sample)
			, m_samplingRate(samplingRate) {}

		Wave(const SecondsF& length, const WaveSample& sample, uint32 samplingRate = DefaultSamplingRate);

		Wave(size_t num_samples, Arg::generator_<std::function<double(double)>> generator, uint32 samplingRate = Wave::DefaultSamplingRate);

		Wave(const SecondsF& length, Arg::generator_<std::function<double(double)>> generator, uint32 samplingRate = Wave::DefaultSamplingRate);

		explicit Wave(const FilePath& path);

		explicit Wave(IReader&& reader, AudioFormat format = AudioFormat::Unspecified);

		Wave(const Wave& wave) = default;

		Wave(Wave&& wave) noexcept;

		template <class InputIt>
		Wave(InputIt first, InputIt last, uint32 samplingRate = Wave::DefaultSamplingRate)
			: base_type(first, last)
			, m_samplingRate(samplingRate) {}

		explicit Wave(const Array<WaveSample>& samples, uint32 samplingRate = Wave::DefaultSamplingRate)
			: base_type(samples)
			, m_samplingRate(samplingRate) {}

		explicit Wave(Array<WaveSample>&& samples, uint32 samplingRate = Wave::DefaultSamplingRate)
			: base_type(std::move(samples))
			, m_samplingRate(samplingRate) {}

		uint32 samplingRate() const noexcept
		{
			return m_samplingRate;
		}

		void setSamplingRate(uint32 samplingRate) noexcept
		{
			m_samplingRate = samplingRate;
		}

		size_t lengthSample() const noexcept
		{
			return size();
		}

		double lengthSec() const noexcept
		{
			return static_cast<double>(size()) / m_samplingRate;
		}

		Wave& operator <<(const WaveSample& sample)
		{
			base_type::push_back(sample);

			return *this;
		}

		void swap(Wave& other)
		{
			base_type::swap(other);
		}

		Wave& append(const Array<WaveSample>& other)
		{
			base_type::insert(end(), other.begin(), other.end());

			return *this;
		}

		Wave& append(const Wave& other)
		{
			base_type::insert(end(), other.begin(), other.end());

			return *this;
		}

		Wave& remove_at(const size_t index)
		{
			base_type::remove_at(index);

			return *this;
		}

		Wave& reverse()
		{
			base_type::reverse();

			return *this;
		}

		Wave& rotate(std::ptrdiff_t count = 1)
		{
			base_type::rotate(count);

			return *this;
		}

		Wave slice(const size_t index) const
		{
			return Wave(base_type::slice(index), m_samplingRate);
		}

		Wave slice(const size_t index, const size_t length) const
		{
			return Wave(base_type::slice(index, length), m_samplingRate);
		}

		bool saveWAVE(const FilePath& path, WAVEFormat format = WAVEFormat::Default);
	};
}

namespace std
{
	inline void swap(s3d::Wave& a, s3d::Wave& b)
	{
		a.swap(b);
	}
}
