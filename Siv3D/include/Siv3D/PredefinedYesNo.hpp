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
# include "YesNo.hpp"

namespace s3d
{
	using CheckValidity = YesNo<struct CheckValidity_tag>;
	using StartImmediately = YesNo<struct StartImmediately_tag>;
}
