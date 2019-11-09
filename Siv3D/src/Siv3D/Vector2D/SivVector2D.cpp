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

# include <Siv3D/Vector2D.hpp>
# include <Siv3D/Rectangle.hpp>

namespace s3d
{
	template <class Type>
	Vector2D<Type> Vector2D<Type>::clamped(const RectF& rect) const noexcept
	{
		return{
			Clamp(x, static_cast<value_type>(rect.x), static_cast<value_type>(rect.x + rect.w)),
			Clamp(y, static_cast<value_type>(rect.y), static_cast<value_type>(rect.y + rect.h)) };
	}

	template <class Type>
	Vector2D<Type>& Vector2D<Type>::clamp(const RectF& rect) noexcept
	{
		x = Clamp(x, static_cast<value_type>(rect.x), static_cast<value_type>(rect.x + rect.w));
		y = Clamp(y, static_cast<value_type>(rect.y), static_cast<value_type>(rect.y + rect.h));
		return *this;
	}

	void Formatter(FormatData& formatData, const Float2& value)
	{
		Formatter(formatData, Vec2(value));
	}

	void Formatter(FormatData& formatData, const Vec2& value)
	{
		formatData.string.push_back(U'(');
		formatData.string.append(ToString(value.x, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(value.y, formatData.decimalPlaces.value));
		formatData.string.push_back(U')');
	}
	
	template struct Vector2D<float>;
	template struct Vector2D<double>;
}
