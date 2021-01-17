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
# include "PointVector.hpp"
# include "FastMath.hpp"
# include "PredefinedNamedParameter.hpp"

namespace s3d
{
	template <class Float, int32 Oclock = 0>
	struct OffsetCircularBase
	{
		using value_type = Float;
		using position_type = Vector2D<value_type>;

		position_type center;

		/// @brief 半径
		value_type r;

		/// @brief 角度（ラジアン）
		value_type theta;

		SIV3D_NODISCARD_CXX20
		OffsetCircularBase() = default;

		SIV3D_NODISCARD_CXX20
		constexpr OffsetCircularBase(const position_type& _center, value_type _r = 0, value_type _theta = 0) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr OffsetCircularBase(const position_type& _center, Arg::r_<value_type> _r, Arg::theta_<value_type> _theta) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr OffsetCircularBase(const position_type& _center, Arg::theta_<value_type> _theta, Arg::r_<value_type> _r) noexcept;

		SIV3D_NODISCARD_CXX20
		OffsetCircularBase(const position_type& _center, const position_type& target) noexcept;

		[[nodiscard]]
		constexpr OffsetCircularBase operator +() const noexcept;

		[[nodiscard]]
		constexpr OffsetCircularBase operator -() const noexcept;

		[[nodiscard]]
		position_type operator +(position_type v) const noexcept;

		[[nodiscard]]
		position_type operator -(position_type v) const noexcept;

		[[nodiscard]]
		constexpr OffsetCircularBase rotated(value_type angle) const noexcept;

		constexpr OffsetCircularBase& rotate(value_type angle) noexcept;

		[[nodiscard]]
		Float2 toFloat2() const noexcept;

		[[nodiscard]]
		Vec2 toVec2() const noexcept;

		[[nodiscard]]
		Float2 fastToFloat2() const noexcept;

		[[nodiscard]]
		Vec2 fastToVec2() const noexcept;

		[[nodiscard]]
		operator position_type() const noexcept;

		[[nodiscard]]
		size_t hash() const noexcept;

	private:

		[[nodiscard]]
		static constexpr value_type ClampAngle(value_type theta) noexcept;

		[[nodiscard]]
		static constexpr value_type Clock() noexcept;

		[[nodiscard]]
		static constexpr value_type Offset(value_type theta) noexcept;
	};

	using OffsetCircular	= OffsetCircularBase<double, 0>;
	using OffsetCircular0	= OffsetCircularBase<double, 0>;
	using OffsetCircular3	= OffsetCircularBase<double, 3>;
	using OffsetCircular6	= OffsetCircularBase<double, 6>;
	using OffsetCircular9	= OffsetCircularBase<double, 9>;

	using OffsetCircularF	= OffsetCircularBase<float, 0>;
	using OffsetCircular0F	= OffsetCircularBase<float, 0>;
	using OffsetCircular3F	= OffsetCircularBase<float, 3>;
	using OffsetCircular6F	= OffsetCircularBase<float, 6>;
	using OffsetCircular9F	= OffsetCircularBase<float, 9>;
}

# include "detail/OffsetCircular.ipp"

template <class Float, s3d::int32 Oclock>
struct std::hash<s3d::OffsetCircularBase<Float, Oclock>>
{
	[[nodiscard]]
	size_t operator()(const s3d::OffsetCircularBase<Float, Oclock>& value) const noexcept
	{
		return value.hash();
	}
};
