//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/HalfFloat.hpp>

namespace s3d
{
	void Formatter(FormatData& formatData, const HalfFloat& value)
	{
		return Formatter(formatData, static_cast<float>(value));
	}
}
