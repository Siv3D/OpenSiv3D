//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include <ThirdParty/scope-guard/unique_resource.h>

namespace s3d
{
	/// @brief オブジェクトの破棄時に、指定したデリータを呼ぶ RAII ラッパー
	using sr::unique_resource;
}
