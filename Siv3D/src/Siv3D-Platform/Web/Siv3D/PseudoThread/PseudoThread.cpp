//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2020-2021 Kamenoko-Nyokonyoko
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "PseudoThread.hpp"

namespace s3d
{
	namespace detail
	{
		void clearInterval(long intervalID)
		{
			// Generating function pointer of function defined in JavaScript is often problematic, wrapping this function...
			::emscripten_clear_interval(intervalID);
		}
	}
}
