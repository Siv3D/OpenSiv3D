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

# include <Siv3D/Vector3D.hpp>

namespace s3d
{
	template Float3;
	template Vec3;

	void Formatter(FormatData& formatData, const Float3& value)
	{
		Formatter(formatData, Vec3(value));
	}

	void Formatter(FormatData& formatData, const Vec3& value)
	{
		formatData.string.push_back(L'(');
		formatData.string.append(ToString(value.x, formatData.decimalPlace.value));
		formatData.string.push_back(L',');
		formatData.string.append(ToString(value.y, formatData.decimalPlace.value));
		formatData.string.push_back(L',');
		formatData.string.append(ToString(value.z, formatData.decimalPlace.value));
		formatData.string.push_back(L')');
	}
}
