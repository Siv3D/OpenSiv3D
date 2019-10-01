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

# include <Siv3D/Mat4x4.hpp>

namespace s3d
{
	void Formatter(FormatData& formatData, const Mat4x4& value)
	{
		formatData.string.push_back(U'(');
		Formatter(formatData, value.r[0]);
		formatData.string.append(U",\n "_sv);
		Formatter(formatData, value.r[1]);
		formatData.string.append(U",\n "_sv);
		Formatter(formatData, value.r[2]);
		formatData.string.append(U",\n "_sv);
		Formatter(formatData, value.r[3]);
		formatData.string.push_back(L')');
	}
}
