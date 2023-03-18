//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Mat4x4.hpp>

namespace s3d
{
	void Formatter(FormatData& formatData, const Mat4x4& value)
	{
		formatData.string.push_back(U'(');
		Formatter(formatData, value.value.r[0]);
		formatData.string.push_back(U',');
		Formatter(formatData, value.value.r[1]);
		formatData.string.push_back(U',');
		Formatter(formatData, value.value.r[2]);
		formatData.string.push_back(U',');
		Formatter(formatData, value.value.r[3]);
		formatData.string.push_back(U')');
	}
}
