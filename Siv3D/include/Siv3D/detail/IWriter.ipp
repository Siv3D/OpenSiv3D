﻿//-----------------------------------------------
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

namespace s3d
{
	SIV3D_CONCEPT_TRIVIALLY_COPYABLE_
	bool IWriter::write(const TriviallyCopyable& src)
	{
		return (write(std::addressof(src), sizeof(TriviallyCopyable)) == sizeof(TriviallyCopyable));
	}
}
