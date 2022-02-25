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
	namespace Math
	{
		/// @brief 数が素数であるかを返します。
		/// @param n 判定する数
		/// @remark Forišek, Michal, and Jakub Jancina., "Fast Primality Testing for Integers That Fit into a Machine Word⋆." (2015). による実装です。
		/// @return 素数である場合 true, それ以外の場合は false
		[[nodiscard]]
		bool IsPrime(uint64 n);
	}
}
