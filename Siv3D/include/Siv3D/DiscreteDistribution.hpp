﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <array>
# include "Common.hpp"
# include "Array.hpp"

SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4127)
SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4244)
# include <ThirdParty/absl/random/discrete_distribution.h>
SIV3D_DISABLE_MSVC_WARNINGS_POP()
SIV3D_DISABLE_MSVC_WARNINGS_POP()

namespace s3d
{
	class DiscreteDistribution
	{
	private:

		using distribution_type = absl::discrete_distribution<size_t>;

		distribution_type m_distribution;

	public:

		using result_type = size_t;

		DiscreteDistribution() = default;

		SIV3D_NODISCARD_CXX20
		explicit DiscreteDistribution(std::initializer_list<double> ilist);

		SIV3D_NODISCARD_CXX20
		explicit DiscreteDistribution(const Array<double>& weights);

		template <size_t Size>
		SIV3D_NODISCARD_CXX20
		explicit DiscreteDistribution(const std::array<double, Size>& weights);

		template <class Iterator>
		SIV3D_NODISCARD_CXX20
		explicit DiscreteDistribution(Iterator begin, Iterator end);

		DiscreteDistribution& operator =(std::initializer_list<double> ilist);

		template <size_t Size>
		DiscreteDistribution& operator =(const std::array<double, Size>& weights);

		DiscreteDistribution& operator =(const Array<double>& weights);

		[[nodiscard]]
		Array<double> probabilities() const;

		template <class URBG>
		result_type operator()(URBG& rbg);

		[[nodiscard]]
		size_t min() const;

		[[nodiscard]]
		size_t max() const;

		[[nodiscard]]
		size_t size() const;
	};
}

# include "detail/DiscreteDistribution.ipp"
