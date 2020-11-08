//-----------------------------------------------
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
# include "Common.hpp"
# include "FastMath.hpp"
# include "PredefinedNamedParameter.hpp"

namespace s3d
{
	/// @brief 円座標
	template <int32 Oclock, class Float>
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

	using Circular	= CircularBase<0, double>;
	using Circular0	= CircularBase<0, double>;
	using Circular3	= CircularBase<3, double>;
	using Circular6	= CircularBase<6, double>;
	using Circular9	= CircularBase<9, double>;

	using CircularF = CircularBase<0, float>;
	using Circular0F = CircularBase<0, float>;
	using Circular3F = CircularBase<3, float>;
	using Circular6F = CircularBase<6, float>;
	using Circular9F = CircularBase<9, float>;
}

# include "detail/Circular.ipp"
