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

# pragma once
# include "TypeTraits.hpp"
# include "Point.hpp"
# include "Vector2D.hpp"
# include "Point.inl"
# include "Vector3D.hpp"
# include "Vector4D.hpp"

namespace s3d
{
	template <class T, class U, bool isScalar = std::is_arithmetic<T>::value && std::is_arithmetic<U>::value>
	struct CommonVector {};

	template <class T, class U>
	struct CommonVector<T, U, true>
	{
		using type = CommonFloat_t<T, U>;
	};

	template <>
	struct CommonVector<Point, Point, false>
	{
		using type = Vec2;
	};

	template <>
	struct CommonVector<Point, Float2, false>
	{
		using type = Float2;
	};

	template <>
	struct CommonVector<Point, Vec2, false>
	{
		using type = Vec2;
	};

	template <>
	struct CommonVector<Float2, Point, false>
	{
		using type = Float2;
	};

	template <>
	struct CommonVector<Float2, Float2, false>
	{
		using type = Float2;
	};

	template <>
	struct CommonVector<Float2, Vec2, false>
	{
		using type = Vec2;
	};

	template <>
	struct CommonVector<Vec2, Point, false>
	{
		using type = Vec2;
	};

	template <>
	struct CommonVector<Vec2, Float2, false>
	{
		using type = Vec2;
	};

	template <>
	struct CommonVector<Vec2, Vec2, false>
	{
		using type = Vec2;
	};

	template <class T, class U, bool isScalar = std::is_arithmetic<T>::value && std::is_arithmetic<U>::value>
	using CommonVector_t = typename CommonVector<T, U, isScalar>::type;
}