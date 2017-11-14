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

# pragma once
# include "Platform.hpp"
# include "Types.hpp"

namespace s3d
{
	//////////////////////////////////////////////////////
	//
	//	Uncopyable.hpp
	//
	class Uncopyable;

	//////////////////////////////////////////////////////
	//
	//	Byte.hpp
	//
	enum class Byte : unsigned char;

	//////////////////////////////////////////////////////
	//
	//	ByteArrayView.hpp
	//
	class ByteArrayView;

	//////////////////////////////////////////////////////
	//
	//	ConcurrentTask.hpp
	//
	template <class Type> class ConcurrentTask;

	//////////////////////////////////////////////////////
	//
	//	AlignedAllocator.hpp
	//
	template <class Type, size_t Alignment> class AlignedAllocator;
	template <class Type> struct DefaultAllocator;

	//////////////////////////////////////////////////////
	//
	//	Array.hpp
	//
	template <class Type, class Allocator> class Array;

	//////////////////////////////////////////////////////
	//
	//	StringView.hpp
	//
	class StringView;

	//////////////////////////////////////////////////////
	//
	//	String.hpp
	//
	class String;
	using FilePath = String;
	
	
	
	class BigInt;
	class BigFloat;


	struct Date;
	struct DateTime;


	//////////////////////////////////////////////////////
	//
	//	MemoryMapping.hpp
	//
	class MemoryMapping;

	//////////////////////////////////////////////////////
	//
	//	WritableMemoryMapping.hpp
	//
	class WritableMemoryMapping;
	enum class MMFOpenMode_if_Exists;
	enum class MMFOpenMode_if_NotFound;


	//////////////////////////////////////////////////////
	//
	//	ByteArray.hpp
	//
	class ByteArray;

	//////////////////////////////////////////////////////
	//
	//	LicenseManager.hpp
	//
	struct LicenseInfo;


	//////////////////////////////////////////////////////
	//
	//	Logger.hpp
	//
	enum class OutputLevel;
	enum class LogDescription;


	//////////////////////////////////////////////////////
	//
	//	Color.hpp
	//
	struct Color;
	struct ColorF;

	//////////////////////////////////////////////////////
	//
	//	HSV.hpp
	//
	struct HSV;

	//////////////////////////////////////////////////////
	//
	//	PointVector.hpp
	//
	struct Point;
	using Size = Point;
	template <class Type> struct Vector2D;
	template <class Type> struct Vector3D;
	template <class Type> struct Vector4D;
	using Float2	= Vector2D<float>;
	using Vec2		= Vector2D<double>;
	using Float3	= Vector3D<float>;
	using Vec3		= Vector3D<double>;
	using Float4	= Vector4D<float>;
	using Vec4		= Vector4D<double>;




	//////////////////////////////////////////////////////
	//
	//	Rectangle.hpp
	//
	template <class SizeType> struct Rectangle;
	using Rect = Rectangle<Point>;
	using RectF = Rectangle<Vec2>;
}
