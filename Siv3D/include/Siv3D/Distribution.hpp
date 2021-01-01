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
# include "Common.hpp"
# include "Concepts.hpp"
# include "detail/Distribution.ipp"

namespace s3d
{
	/// @brief 
	/// @tparam IntType 
# if __cpp_lib_concepts
	template <Concept::Integral IntType = int32>
# else
	template <class IntType = int32>
# endif
	using UniformIntDistribution = absl::uniform_int_distribution<IntType>;

	/// @brief 
	/// @tparam RealType 
# if __cpp_lib_concepts
	template <Concept::FloatingPoint RealType = double>
# else
	template <class RealType = double>
# endif
	using UniformRealDistribution = absl::uniform_real_distribution<RealType>;

	/// @brief 
	/// @tparam RealType 
# if __cpp_lib_concepts
	template <Concept::FloatingPoint RealType = double>
# else
	template <class RealType = double>
# endif
	using NormalDistribution = absl::gaussian_distribution<RealType>;

	/// @brief 
	using BernoulliDistribution = absl::bernoulli_distribution;
}
