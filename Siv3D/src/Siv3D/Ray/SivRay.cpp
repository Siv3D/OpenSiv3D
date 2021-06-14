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

# include <Siv3D/Ray.hpp>
# include <Siv3D/FormatFloat.hpp>

namespace s3d
{
	void Ray::_Formatter(FormatData& formatData, const Ray& value)
	{
		const Float4 o = value.origin.toFloat4();
		const Float4 d = value.direction.toFloat4();

		formatData.string.append(U"(("_sv);

		formatData.string.append(ToString(o.x, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(o.y, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(o.z, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(o.w, formatData.decimalPlaces.value));
		formatData.string.append(U"), ("_sv);

		formatData.string.append(ToString(d.x, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(d.y, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(d.z, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(d.w, formatData.decimalPlaces.value));

		formatData.string.append(U"))"_sv);
	}
}
