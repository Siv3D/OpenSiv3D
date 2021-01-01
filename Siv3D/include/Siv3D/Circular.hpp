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
# include "FastMath.hpp"
# include "PredefinedNamedParameter.hpp"

namespace s3d
{
	/// @brief 円座標
	template <class Float, int32 Oclock = 0>
	struct CircularBase
	{
		using value_type = Float;

		/// @brief 半径
		value_type r;

		/// @brief 角度（ラジアン）
		value_type theta;

		SIV3D_NODISCARD_CXX20
		CircularBase() = default;

		SIV3D_NODISCARD_CXX20
		constexpr CircularBase(value_type _r, value_type _theta) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr CircularBase(Arg::r_<value_type> _r, Arg::theta_<value_type> _theta) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr CircularBase(Arg::theta_<value_type> _theta, Arg::r_<value_type> _r) noexcept;

		SIV3D_NODISCARD_CXX20
		CircularBase(Vector2D<value_type> v) noexcept;

		[[nodiscard]]
		constexpr CircularBase operator +() const noexcept;

		[[nodiscard]]
		constexpr CircularBase operator -() const noexcept;

		[[nodiscard]]
		Vector2D<value_type> operator +(Vector2D<value_type> v) const noexcept;

		[[nodiscard]]
		Vector2D<value_type> operator -(Vector2D<value_type> v) const noexcept;

		[[nodiscard]]
		constexpr CircularBase rotated(value_type angle) const noexcept;

		constexpr CircularBase& rotate(value_type angle) noexcept;

		[[nodiscard]]
		Float2 toFloat2() const noexcept;

		[[nodiscard]]
		Vec2 toVec2() const noexcept;

		[[nodiscard]]
		Float2 fastToFloat2() const noexcept;

		[[nodiscard]]
		Vec2 fastToVec2() const noexcept;

		[[nodiscard]]
		operator Vector2D<value_type>() const noexcept;

	private:

		[[nodiscard]]
		static constexpr value_type ClampAngle(value_type theta) noexcept;

		[[nodiscard]]
		static constexpr value_type Clock() noexcept;

		[[nodiscard]]
		static constexpr value_type Offset(value_type theta) noexcept;
	};

	using Circular	= CircularBase<double, 0>;
	using Circular0	= CircularBase<double, 0>;
	using Circular3	= CircularBase<double, 3>;
	using Circular6	= CircularBase<double, 6>;
	using Circular9	= CircularBase<double, 9>;

	using CircularF		= CircularBase<float, 0>;
	using Circular0F	= CircularBase<float, 0>;
	using Circular3F	= CircularBase<float, 3>;
	using Circular6F	= CircularBase<float, 6>;
	using Circular9F	= CircularBase<float, 9>;
}

# include "detail/Circular.ipp"
