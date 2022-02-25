//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

namespace s3d
{
	inline Ray::Ray(const Float3 _origin, const Float3 normalizedDirection) noexcept
		: origin{ _origin, 0.0f, }
		, direction{ normalizedDirection, 0.0f } {}

	template <class X, class Y, class Z>
	inline Ray::Ray(const X ox, const Y oy, const Z oz, const Float3 normalizedDirection) noexcept
		: origin{ static_cast<float>(ox), static_cast<float>(oy), static_cast<float>(oz), 0.0f, }
		, direction{ normalizedDirection, 0.0f } {}

	template <class X, class Y, class Z>
	inline Ray::Ray(const Float3 _origin, const X ndx, const Y ndy, const Z ndz) noexcept
		: origin{ _origin, 0.0f, }
		, direction{ static_cast<float>(ndx), static_cast<float>(ndy), static_cast<float>(ndz), 0.0f, } {}

	inline Float3 Ray::getOrigin() const noexcept
	{
		return origin.xyz();
	}

	inline Ray& Ray::setOrigin(const Float3 _origin) noexcept
	{
		origin.set(_origin.x, _origin.y, _origin.z, 0.0f);

		return *this;
	}

	inline Float3 Ray::getDirection() const noexcept
	{
		return direction.xyz();
	}

	inline Ray& Ray::setDirection(const Float3 _direction) noexcept
	{
		direction.set(_direction.x, _direction.y, _direction.z, 0.0f);
		
		return *this;
	}

	inline Float3 Ray::point_at(const float distance) const noexcept
	{
		return ((direction * distance) + origin).xyz();
	}

	SIV3D_CONCEPT_ARITHMETIC_
	inline Vec3 Ray::point_at(const Arithmetic distance) const noexcept
	{
		return ((distance * direction.xyz()) + origin.xyz());
	}
}
