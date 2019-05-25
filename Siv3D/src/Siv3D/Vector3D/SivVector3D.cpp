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

# include <Siv3D/Vector3D.hpp>

namespace s3d
{
	void Formatter(FormatData& formatData, const Float3& value)
	{
		Formatter(formatData, Vec3(value));
	}

	void Formatter(FormatData& formatData, const Vec3& value)
	{
		formatData.string.push_back(U'(');
		formatData.string.append(ToString(value.x, formatData.decimalPlace.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(value.y, formatData.decimalPlace.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(value.z, formatData.decimalPlace.value));
		formatData.string.push_back(U')');
	}
	
	template struct Vector3D<float>;
	template struct Vector3D<double>;
}
