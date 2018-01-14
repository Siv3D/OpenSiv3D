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
