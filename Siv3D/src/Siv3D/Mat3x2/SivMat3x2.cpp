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

# include <Siv3D/Mat3x2.hpp>

namespace s3d
{
	void Formatter(FormatData& formatData, const Mat3x2& value)
	{
		formatData.string.push_back(U'(');
		Formatter(formatData, Float2{ value._11, value._12 });
		formatData.string.push_back(U',');
		Formatter(formatData, Float2{ value._21, value._22 });
		formatData.string.push_back(U',');
		Formatter(formatData, Float2{ value._31, value._32 });
		formatData.string.push_back(U')');
	}
}
