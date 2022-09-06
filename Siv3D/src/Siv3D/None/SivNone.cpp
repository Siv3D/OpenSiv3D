//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/None.hpp>
# include <Siv3D/FormatData.hpp>

namespace s3d
{
	void Formatter(FormatData& formatData, None_t)
	{
		formatData.string.append(U"none"_sv);
	}
}
