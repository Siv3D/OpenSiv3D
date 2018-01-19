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

# include <Siv3D/Mat3x2.hpp>
# include <Siv3D/Format.hpp>

namespace s3d
{
	void Formatter(FormatData& formatData, const Mat3x2& value)
	{
		formatData.string.push_back(L'(');
		Formatter(formatData, Float2(value._11, value._12));
		formatData.string.push_back(L',');
		Formatter(formatData, Float2(value._21, value._22));
		formatData.string.push_back(L',');
		Formatter(formatData, Float2(value._31, value._32));
		formatData.string.push_back(L')');
	}
}
