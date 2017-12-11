//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Vector2D.hpp>
# include <Siv3D/Rectangle.hpp>

namespace s3d
{
	template <class Type>
	Vector2D<Type>& Vector2D<Type>::clamp(const RectF& rect) noexcept
	{
		x = Clamp(x, static_cast<value_type>(rect.x), static_cast<value_type>(rect.x + rect.w));
		y = Clamp(y, static_cast<value_type>(rect.y), static_cast<value_type>(rect.y + rect.h));
		return *this;
	}

	template <class Type>
	Vector2D<Type> Vector2D<Type>::clamped(const RectF& rect) noexcept
	{
		return{ 
			Clamp(x, static_cast<value_type>(rect.x), static_cast<value_type>(rect.x + rect.w)),
			Clamp(y, static_cast<value_type>(rect.y), static_cast<value_type>(rect.y + rect.h)) };
	}

	void Formatter(FormatData& formatData, const Float2& value)
	{
		Formatter(formatData, Vec2(value));
	}

	void Formatter(FormatData& formatData, const Vec2& value)
	{
		formatData.string.push_back(U'(');
		formatData.string.append(ToString(value.x, formatData.decimalPlace.value));
		formatData.string.push_back(U',');
		formatData.string.append(ToString(value.y, formatData.decimalPlace.value));
		formatData.string.push_back(U')');
	}
	
	template struct Vector2D<float>;
	template struct Vector2D<double>;
}
