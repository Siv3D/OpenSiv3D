//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/PointVector.hpp>
# include <Siv3D/FormatFloat.hpp>

namespace s3d
{
	template <>
	void Vector3D<double>::_Formatter(FormatData& formatData, const Vector3D<double>& value)
	{
		formatData.string.push_back(U'(');
		formatData.string.append(ToString(value.x, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(value.y, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(value.z, formatData.decimalPlaces.value));
		formatData.string.push_back(U')');
	}

	template <>
	void Vector3D<float>::_Formatter(FormatData& formatData, const Vector3D<float>& value)
	{
		Vector3D<double>::_Formatter(formatData, value);
	}

	template struct Vector3D<float>;
	template struct Vector3D<double>;
}
