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
# include "String.hpp"
# include "Unicode.hpp"

namespace s3d
{
	/// @brief 名前をデマングルします。
	/// @param name 名前
	/// @return デマングルされた名前
	[[nodiscard]]
	inline String Demangle(const char* name);
}

# include "detail/Demangle.ipp"
