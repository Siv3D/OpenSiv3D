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
# include "PointVector.hpp"
# include "ColorHSV.hpp"
# include "NamedParameter.hpp"
# include "PredefinedNamedParameter.hpp"

namespace s3d
{
	/// @brief 角丸長方形
	struct RoundRect
	{
		using position_type	= RectF::position_type;

		using size_type		= RectF::size_type;

		using value_type	= position_type::value_type;

		SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4201)

		union
		{
			RectF rect;

			struct
			{
				value_type x, y, w, h;
			};
		};

		value_type r;

		SIV3D_DISABLE_MSVC_WARNINGS_POP()

		SIV3D_NODISCARD_CXX20
		RoundRect() = default;

		/// @brief 
		/// @param _x 
		/// @param _y 
		/// @param _w 
		/// @param _h 
		/// @param _r 
		SIV3D_NODISCARD_CXX20
		constexpr RoundRect(value_type _x, value_type _y, value_type _w, value_type _h, value_type _r) noexcept;

		/// @brief 
		/// @param pos 
		/// @param _w 
		/// @param _h 
		/// @param _r 
		SIV3D_NODISCARD_CXX20
		constexpr RoundRect(position_type pos, value_type _w, value_type _h, value_type _r) noexcept;

		/// @brief 
		/// @param _x 
		/// @param _y 
		/// @param size 
		/// @param _r 
		SIV3D_NODISCARD_CXX20
		constexpr RoundRect(value_type _x, value_type _y, size_type size, value_type _r) noexcept;

		/// @brief 
		/// @param pos 
		/// @param size 
		/// @param _r 
		SIV3D_NODISCARD_CXX20
		constexpr RoundRect(position_type pos, value_type size, value_type _r) noexcept;

		/// @brief 
		/// @param pos 
		/// @param size 
		/// @param _r 
		SIV3D_NODISCARD_CXX20
		constexpr RoundRect(position_type pos, size_type size, value_type _r) noexcept;

		/// @brief 
		/// @param _center 
		/// @param _w 
		/// @param _h 
		/// @param _r 
		SIV3D_NODISCARD_CXX20
		constexpr RoundRect(Arg::center_<position_type> _center, value_type _w, value_type _h, value_type _r) noexcept;

		/// @brief 
		/// @param _center 
		/// @param size 
		/// @param _r 
		SIV3D_NODISCARD_CXX20
		constexpr RoundRect(Arg::center_<position_type> _center, size_type size, value_type _r) noexcept;

		/// @brief 
		/// @param _rect 
		/// @param _r 
		SIV3D_NODISCARD_CXX20
		constexpr RoundRect(const RectF& _rect, value_type _r) noexcept;
	};
}

# include "detail/RoundRect.ipp"
