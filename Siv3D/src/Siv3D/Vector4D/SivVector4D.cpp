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
	void Formatter(FormatData& formatData, const Vector4D<double>& value)
	{
		formatData.string.push_back(U'(');
		formatData.string.append(ToString(value.x, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(value.y, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(value.z, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(value.w, formatData.decimalPlaces.value));
		formatData.string.push_back(U')');
	}

	void Formatter(FormatData& formatData, const Vector4D<float>& value)
	{
		Formatter(formatData, Vector4D<double>{ value });
	}

	template struct Vector4D<float>;
	template struct Vector4D<double>;
}
