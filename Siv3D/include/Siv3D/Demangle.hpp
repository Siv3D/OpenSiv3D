//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

namespace s3d
{
	class String;

	/// @brief 名前をデマングルします。
	/// @param name 名前
	/// @return デマングルされた名前
	[[nodiscard]]
	String Demangle(const char* name);
}
