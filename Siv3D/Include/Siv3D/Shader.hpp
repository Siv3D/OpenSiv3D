//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"
# include "String.hpp"

namespace s3d
{
	enum class ShaderStage
	{
		Vertex,

		Pixel,
	};

	struct BindingPoint
	{
		String bufferName;
		
		uint32 index;
	};
}
