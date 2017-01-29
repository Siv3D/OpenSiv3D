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

namespace s3d
{
	/// <summary>
	/// コピー禁止クラス
	/// </summary>
	/// <remarks>
	/// このクラスを private 継承すると、コピー禁止のクラスを定義できます。
	/// </remarks>
	class Uncopyable
	{
	protected:

		Uncopyable() = default;

		Uncopyable(const Uncopyable&) = delete;

		Uncopyable& operator =(const Uncopyable&) = delete;
	};
}
