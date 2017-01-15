//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"
# include "Format.hpp"

namespace s3d
{
	namespace Window
	{
		void SetTitle(const String& title);

		template <class... Args>
		inline void SetTitle(const Args&... args)
		{
			SetTitle(Format(args...));
		}
	}
}
