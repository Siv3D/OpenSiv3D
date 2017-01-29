//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2017 Ryo Suzuki
//	Copyright (C) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Console.hpp>
# include "../Siv3DEngine.hpp"
# include "IConsole.hpp"

namespace s3d
{
	namespace detail
	{
		void Console_impl::open() const
		{
			Siv3DEngine::GetConsole()->open();
		}
	}
}
