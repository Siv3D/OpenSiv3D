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
# include "String.hpp"
# include "Optional.hpp"

namespace s3d
{
	inline bool ParseBool(const String& str)
	{
		return str.trimmed().lowercase().compare(S3DSTR("true")) == 0;
	}

	inline Optional<bool> ParseBoolOpt(const String& str)
	{
		const String t = str.trimmed().lowercase();

		if (t.compare(S3DSTR("true")) == 0)
		{
			return true;
		}
		else if (t.compare(S3DSTR("false")) == 0)
		{
			return false;
		}
		else
		{
			return none;
		}
	}
}
