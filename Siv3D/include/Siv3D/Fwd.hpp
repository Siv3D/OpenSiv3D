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

# pragma once
# include "Common.hpp"

namespace s3d
{
	struct PlaceHolder_t;
	class StringView;
	class String;

	class BigInt;
	class BigFloat;

	class IReader;
	class IWriter;

	struct FormatData;

	enum class LogLevel;
	enum class LogType;

	struct Point;
	using Size = Point;
	template <class Type> struct Vector2D;
	using Float2 = Vector2D<float>;
	using Vec2 = Vector2D<double>;


	//////////////////////////////////////////////////////
	//
	//	Rectangle.hpp
	//
	template <class SizeType> struct Rectangle;
	using Rect = Rectangle<Point>;
	using RectF = Rectangle<Vec2>;

	class Image;


	enum class WindowStyle : uint32;
	struct WindowState;
}
