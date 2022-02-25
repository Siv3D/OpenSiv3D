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

namespace s3d
{
	inline DiscreteDistribution::DiscreteDistribution(std::initializer_list<double> ilist)
		: m_distribution(ilist) {}

	inline DiscreteDistribution::DiscreteDistribution(const Array<double>& weights)
		: m_distribution(weights.begin(), weights.end()) {}

	template <size_t Size>
	inline DiscreteDistribution::DiscreteDistribution(const std::array<double, Size>& weights)
		: m_distribution(weights.begin(), weights.end()) {}

	template <class Iterator>
	inline DiscreteDistribution::DiscreteDistribution(Iterator begin, Iterator end)
		: m_distribution(begin, end) {}

	inline DiscreteDistribution& DiscreteDistribution::operator =(std::initializer_list<double> ilist)
	{
		m_distribution = distribution_type(ilist);
		return *this;
	}

	template <size_t Size>
	inline DiscreteDistribution& DiscreteDistribution::operator =(const std::array<double, Size>& weights)
	{
		m_distribution = distribution_type(weights.begin(), weights.end());
		return *this;
	}

	inline DiscreteDistribution& DiscreteDistribution::operator =(const Array<double>& weights)
	{
		m_distribution = distribution_type(weights.begin(), weights.end());
		return *this;
	}

	inline Array<double> DiscreteDistribution::probabilities() const
	{
		return Array<double>(m_distribution.probabilities().begin(), m_distribution.probabilities().end());
	}

	template <class URBG>
	inline DiscreteDistribution::result_type DiscreteDistribution::operator()(URBG& rbg)
	{
		return m_distribution(rbg);
	}

	inline size_t DiscreteDistribution::min() const
	{
		return m_distribution.min();
	}

	inline size_t DiscreteDistribution::max() const
	{
		return m_distribution.max();
	}

	inline size_t DiscreteDistribution::size() const
	{
		return m_distribution.probabilities().size();
	}

	template <class Iterator, class URBG>
	inline auto DiscreteSample(Iterator begin, [[maybe_unused]] Iterator end, DiscreteDistribution& weight, URBG&& urbg)
	{
		assert(begin != end);
		assert(std::distance(begin, end) == static_cast<int64>(weight.size()));

		std::advance(begin, weight(std::forward<URBG>(urbg)));
		return *begin;
	}

	template <class Iterator>
	inline auto DiscreteSample(Iterator begin, Iterator end, DiscreteDistribution& weight)
	{
		return DiscreteSample(begin, end, weight, GetDefaultRNG());
	}

	template <class Container, class URBG>
	inline auto DiscreteSample(const Container& c, DiscreteDistribution& weight, URBG&& urbg)
	{
		assert(std::size(c) != 0);
		assert(std::size(c) == weight.size());

		auto it = std::begin(c);
		std::advance(it, weight(std::forward<URBG>(urbg)));
		return *it;
	}

	template <class Container>
	inline auto DiscreteSample(const Container& c, DiscreteDistribution& weight)
	{
		return DiscreteSample(c, weight, GetDefaultRNG());
	}

	template <class Type, class URBG>
	inline auto DiscreteSample(std::initializer_list<Type> ilist, DiscreteDistribution& weight, URBG&& urbg)
	{
		assert(ilist.size() != 0);
		return *(ilist.begin() + weight(std::forward<URBG>(urbg)));
	}

	template <class Type>
	inline auto DiscreteSample(std::initializer_list<Type> ilist, DiscreteDistribution& weight)
	{
		return DiscreteSample(ilist, weight, GetDefaultRNG());
	}
}
