//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//	Copyright (C) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Vector4D.hpp>

namespace s3d
{
	template Float4;
	template Vec4;
	
	void Formatter(FormatData& formatData, const Float4& value)
	{
		Formatter(formatData, Vec4(value));
	}

	void Formatter(FormatData& formatData, const Vec4& value)
	{
		formatData.string.push_back(L'(');
		formatData.string.append(ToString(value.x, formatData.decimalPlace.value));
		formatData.string.push_back(L',');
		formatData.string.append(ToString(value.y, formatData.decimalPlace.value));
		formatData.string.push_back(L',');
		formatData.string.append(ToString(value.z, formatData.decimalPlace.value));
		formatData.string.push_back(L',');
		formatData.string.append(ToString(value.w, formatData.decimalPlace.value));
		formatData.string.push_back(L')');
	}
}
