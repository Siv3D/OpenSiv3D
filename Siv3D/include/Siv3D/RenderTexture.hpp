//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Texture.hpp"

namespace s3d
{
	class RenderTexture : public Texture
	{
	protected:

		explicit RenderTexture(BackBuffer);

	public:

		RenderTexture();

		RenderTexture(const Size& size, uint32 multisampleCount = 1);

		void clear(const ColorF& color);

		void beginResize();

		bool endResize(const Size& size, const uint32 multisampleCount);
	};
}
