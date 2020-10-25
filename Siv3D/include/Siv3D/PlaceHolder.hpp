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

namespace s3d
{
	/// @brief プレースホルダー型 | Place holder type
	struct PlaceHolder_t
	{
		struct init_t {};

		explicit constexpr PlaceHolder_t(init_t) noexcept {}
	};

	namespace Arg
	{
		/// @brief プレースホルダー | Place holder
		inline constexpr PlaceHolder_t _{ PlaceHolder_t::init_t{} };
	}
}
