//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "YesNo.hpp"

namespace s3d
{
	using SkipValidation	= YesNo<struct SkipValidation_tag>;
	using StartImmediately	= YesNo<struct StartImmediately_tag>;
	using CloseRing			= YesNo<struct CloseRing_tag>;
	using SortByDistance	= YesNo<struct SortByDistance_tag>;
}
