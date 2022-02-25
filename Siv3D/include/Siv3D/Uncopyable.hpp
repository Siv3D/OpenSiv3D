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
	/// @brief コピー禁止 Mixin | Non-copyable mixin
	/// @remark このクラスを private 継承して使います。
	/// @remark Intended to be used as a private base class.
	class Uncopyable
	{
	protected:

		Uncopyable() = default;

		~Uncopyable() = default;

		Uncopyable(const Uncopyable&) = delete;

		Uncopyable& operator =(const Uncopyable&) = delete;
	};
}
