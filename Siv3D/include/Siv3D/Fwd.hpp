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

	enum class LogLevel : uint8;
	enum class LogType : uint8;

	struct Point;

	/// @brief 2 次元のサイズベクトル（成分が int32 型）
	/// @remark Point 型と同じです。
	using Size = Point;

	/// @brief 2 次元のベクトル
	/// @tparam Type ベクトルの要素の型
	template <class Type> struct Vector2D;

	/// @brief 2 次元のベクトルを、float 型の要素 x, y で表現するクラスです。
	using Float2 = Vector2D<float>;

	/// @brief 2 次元のベクトルを、double 型の要素 x, y で表現するクラスです。
	using Vec2 = Vector2D<double>;

	class Image;


	enum class WindowStyle : uint8;
	struct WindowState;
}
