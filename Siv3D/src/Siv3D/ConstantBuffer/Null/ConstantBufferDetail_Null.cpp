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

# include "ConstantBufferDetail_Null.hpp"

namespace s3d
{
	ConstantBufferDetail_Null::ConstantBufferDetail_Null(const size_t)
	{

	}

	bool ConstantBufferDetail_Null::update(const void*, const size_t)
	{
		return true;
	}
}
