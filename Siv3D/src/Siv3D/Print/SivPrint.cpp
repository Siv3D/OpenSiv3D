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

# include "../Siv3DEngine.hpp"
# include "IPrint.hpp"
# include <Siv3D/Print.hpp>

namespace s3d
{
	namespace detail
	{
		void Print_impl::writeln(const String& text) const
		{
			Siv3DEngine::GetPrint()->add(text);
		}
	}

	void ClearPrint()
	{
		Siv3DEngine::GetPrint()->clear();
	}
}
