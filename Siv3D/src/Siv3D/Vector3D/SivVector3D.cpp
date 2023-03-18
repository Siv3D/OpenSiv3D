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

# include <Siv3D/PointVector.hpp>
# include <Siv3D/Box.hpp>
# include <Siv3D/FormatFloat.hpp>

namespace s3d
{
	template <>
	Vector3D<double> Vector3D<double>::clamped(const Box& box) const noexcept
	{
		return{
			Clamp(x, (box.center.x - box.size.x * 0.5), (box.center.x + box.size.x * 0.5)),
			Clamp(y, (box.center.y - box.size.y * 0.5), (box.center.y + box.size.y * 0.5)),
			Clamp(z, (box.center.z - box.size.z * 0.5), (box.center.z + box.size.z * 0.5)),
		};
	}

	template <>
	Vector3D<double>& Vector3D<double>::clamp(const Box& box) noexcept
	{
		x = Clamp(x, (box.center.x - box.size.x * 0.5), (box.center.x + box.size.x * 0.5));
		y = Clamp(y, (box.center.y - box.size.y * 0.5), (box.center.y + box.size.y * 0.5));
		z = Clamp(z, (box.center.z - box.size.z * 0.5), (box.center.z + box.size.z * 0.5));
		return *this;
	}

	template <>
	Vector3D<float> Vector3D<float>::clamped(const Box& box) const noexcept
	{
		return{
			Clamp(x, static_cast<float>(box.center.x - box.size.x * 0.5), static_cast<float>(box.center.x + box.size.x * 0.5)),
			Clamp(y, static_cast<float>(box.center.y - box.size.y * 0.5), static_cast<float>(box.center.y + box.size.y * 0.5)),
			Clamp(z, static_cast<float>(box.center.z - box.size.z * 0.5), static_cast<float>(box.center.z + box.size.z * 0.5)),
		};
	}

	template <>
	Vector3D<float>& Vector3D<float>::clamp(const Box& box) noexcept
	{
		x = Clamp(x, static_cast<float>(box.center.x - box.size.x * 0.5), static_cast<float>(box.center.x + box.size.x * 0.5));
		y = Clamp(y, static_cast<float>(box.center.y - box.size.y * 0.5), static_cast<float>(box.center.y + box.size.y * 0.5));
		z = Clamp(z, static_cast<float>(box.center.z - box.size.z * 0.5), static_cast<float>(box.center.z + box.size.z * 0.5));
		return *this;
	}

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
