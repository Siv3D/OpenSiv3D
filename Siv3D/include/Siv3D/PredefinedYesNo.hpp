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
	using SkipValidation	= YesNo<struct SkipValidation_tag>;
	using StartImmediately	= YesNo<struct StartImmediately_tag>;
	using IsClosed			= YesNo<struct IsClosed_tag>;
	using SortByDistance	= YesNo<struct SortByDistance_tag>;
}
