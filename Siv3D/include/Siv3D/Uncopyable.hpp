//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

namespace s3d
{
	class Uncopyable
	{
	protected:

		constexpr Uncopyable() = default;

		~Uncopyable() = default;

		Uncopyable(const Uncopyable&) = delete;

		Uncopyable& operator =(const Uncopyable&) = delete;
	};
}
