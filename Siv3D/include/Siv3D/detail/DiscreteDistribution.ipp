//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
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
}
