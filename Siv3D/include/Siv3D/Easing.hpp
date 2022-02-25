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
# include "Common.hpp"
# include "MathConstants.hpp"
# include "Interpolation.hpp"

namespace s3d
{
	namespace Easing
	{
		[[nodiscard]]
		inline constexpr double Linear(double t) noexcept;

		[[nodiscard]]
		inline double Sine(double t) noexcept;

		[[nodiscard]]
		inline constexpr double Quad(double t) noexcept;

		[[nodiscard]]
		inline constexpr double Cubic(double t) noexcept;

		[[nodiscard]]
		inline constexpr double Quart(double t) noexcept;

		[[nodiscard]]
		inline constexpr double Quint(double t) noexcept;

		[[nodiscard]]
		inline double Expo(double t) noexcept;

		[[nodiscard]]
		inline double Circ(double t) noexcept;

		[[nodiscard]]
		inline constexpr double Back(double t) noexcept;

		[[nodiscard]]
		inline double Elastic(double t) noexcept;

		[[nodiscard]]
		inline constexpr double Bounce(double t) noexcept;
	}

	[[nodiscard]]
	inline constexpr double EaseIn(double f(double), double t) noexcept;

	template <class Type>
	[[nodiscard]]
	inline constexpr auto EaseIn(double f(double), const Type& start, const Type& end, double t);

	[[nodiscard]]
	inline constexpr double EaseOut(double f(double), double t) noexcept;

	template <class Type>
	[[nodiscard]]
	inline constexpr auto EaseOut(double f(double), const Type& start, const Type& end, double t);

	[[nodiscard]]
	inline constexpr double EaseInOut(double f(double), double t) noexcept;

	template <class Type>
	[[nodiscard]]
	inline constexpr auto EaseInOut(double f(double), const Type& start, const Type& end, double t);


	[[nodiscard]]
	inline constexpr double EaseInLinear(double t) noexcept;

	[[nodiscard]]
	inline constexpr double EaseOutLinear(double t) noexcept;

	[[nodiscard]]
	inline constexpr double EaseInOutLinear(double t) noexcept;


	[[nodiscard]]
	inline double EaseInSine(double t) noexcept;

	[[nodiscard]]
	inline double EaseOutSine(double t) noexcept;

	[[nodiscard]]
	inline double EaseInOutSine(double t) noexcept;


	[[nodiscard]]
	inline constexpr double EaseInQuad(double t) noexcept;

	[[nodiscard]]
	inline constexpr double EaseOutQuad(double t) noexcept;

	[[nodiscard]]
	inline constexpr double EaseInOutQuad(double t) noexcept;


	[[nodiscard]]
	inline constexpr double EaseInCubic(double t) noexcept;

	[[nodiscard]]
	inline constexpr double EaseOutCubic(double t) noexcept;

	[[nodiscard]]
	inline constexpr double EaseInOutCubic(double t) noexcept;


	[[nodiscard]]
	inline constexpr double EaseInQuart(double t) noexcept;

	[[nodiscard]]
	inline constexpr double EaseOutQuart(double t) noexcept;

	[[nodiscard]]
	inline constexpr double EaseInOutQuart(double t) noexcept;


	[[nodiscard]]
	inline constexpr double EaseInQuint(double t) noexcept;

	[[nodiscard]]
	inline constexpr double EaseOutQuint(double t) noexcept;

	[[nodiscard]]
	inline constexpr double EaseInOutQuint(double t) noexcept;


	[[nodiscard]]
	inline double EaseInExpo(double t) noexcept;

	[[nodiscard]]
	inline double EaseOutExpo(double t) noexcept;

	[[nodiscard]]
	inline double EaseInOutExpo(double t) noexcept;


	[[nodiscard]]
	inline double EaseInCirc(double t) noexcept;

	[[nodiscard]]
	inline double EaseOutCirc(double t) noexcept;

	[[nodiscard]]
	inline double EaseInOutCirc(double t) noexcept;


	[[nodiscard]]
	inline constexpr double EaseInBack(double t) noexcept;

	[[nodiscard]]
	inline constexpr double EaseOutBack(double t) noexcept;

	[[nodiscard]]
	inline constexpr double EaseInOutBack(double t) noexcept;


	[[nodiscard]]
	inline double EaseInElastic(double t) noexcept;

	[[nodiscard]]
	inline double EaseOutElastic(double t) noexcept;

	[[nodiscard]]
	inline double EaseInOutElastic(double t) noexcept;


	[[nodiscard]]
	inline constexpr double EaseInBounce(double t) noexcept;

	[[nodiscard]]
	inline constexpr double EaseOutBounce(double t) noexcept;

	[[nodiscard]]
	inline constexpr double EaseInOutBounce(double t) noexcept;
}

# include "detail/Easing.ipp"
