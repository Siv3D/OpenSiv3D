﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Error.hpp>

namespace s3d
{
	void Formatter(FormatData& formatData, const Error& value)
	{
		const String s = (U"["_s + value.type() + U"] " + value.what());

		formatData.string.append(s);
	}
}
