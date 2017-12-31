//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

namespace s3d
{
	struct PlaceHolder_t
	{
		struct init_t {};

		explicit constexpr PlaceHolder_t(init_t) {}
	};

	namespace Lambda
	{
		/// <summary>
		/// Place holder
		/// </summary>
		inline constexpr PlaceHolder_t _{ PlaceHolder_t::init_t{} };
	}
}
