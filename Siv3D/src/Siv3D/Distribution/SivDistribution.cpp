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

# include <Siv3D/Distribution.hpp>

namespace s3d
{
	DiscreteDistribution::DiscreteDistribution(std::initializer_list<double> ilist)
		: m_distribution(ilist)
	{
	
	}

	DiscreteDistribution::DiscreteDistribution(const Array<double>& weights)
		: m_distribution(weights.begin(), weights.end())
	{
	
	}

	DiscreteDistribution& DiscreteDistribution::operator =(std::initializer_list<double> ilist)
	{
		m_distribution = ilist;
		return *this;
	}

	DiscreteDistribution& DiscreteDistribution::operator =(const Array<double>& weights)
	{
		m_distribution = distribution_type(weights.begin(), weights.end());
		return *this;
	}

	Array<double> DiscreteDistribution::probabilities() const
	{
		const std::vector<double> results = m_distribution.probabilities();
		return Array<double>(results.begin(), results.end());
	}

	size_t DiscreteDistribution::min() const
	{
		return m_distribution.min();
	}

	size_t DiscreteDistribution::max() const
	{
		return m_distribution.max();
	}

	size_t DiscreteDistribution::size() const
	{
		return m_distribution.probabilities().size();
	}
}
