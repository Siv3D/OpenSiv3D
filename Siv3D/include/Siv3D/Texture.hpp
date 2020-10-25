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
# include <memory>
# include "Common.hpp"
# include "Image.hpp"
# include "AssetHandle.hpp"

namespace s3d
{
	class Texture : public AssetHandle<Texture>
	{
	public:

		Texture();

		explicit Texture(FilePathView path);

		explicit Texture(const Image& image);

		//virtual ~Texture();
	};
}
