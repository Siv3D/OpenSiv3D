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
