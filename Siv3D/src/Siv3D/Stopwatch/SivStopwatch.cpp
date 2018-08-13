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

# include <Siv3D/Stopwatch.hpp>
# include <Siv3D/String.hpp>

namespace s3d
{
	String Stopwatch::format(const String& format) const
	{
		return FormatTime(elapsedF(), format);
	}
}
