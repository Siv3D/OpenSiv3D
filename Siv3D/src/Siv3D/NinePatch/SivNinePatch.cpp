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

# include <Siv3D/NinePatch.hpp>
# include "NinePatchDetail.hpp"

namespace s3d
{
	NinePatch::NinePatch(const Texture& texture, const int32 cornerSize, const Style& style)
		: NinePatch{ texture, cornerSize, cornerSize, cornerSize, cornerSize, style } {}

	NinePatch::NinePatch(const Texture& texture, const int32 cornerWidth, const int32 cornerHeight, const Style& style)
		: NinePatch{ texture, cornerWidth, cornerHeight, cornerWidth, cornerHeight, style } {}

	NinePatch::NinePatch(const Texture& texture, const int32 leftWidth, const int32 topHeight, const int32 rightWidth, const int32 bottomHeight, const Style& style)
		: pImpl{ std::make_shared<NinePatchDetail>(texture, leftWidth, topHeight, rightWidth, bottomHeight, style) } {}

	void NinePatch::draw(const RectF& rect, const ColorF& color) const
	{
		draw(rect, 1.0, TextureFilter::Linear, color);
	}

	void NinePatch::draw(const RectF& rect, const double textureScale, const TextureFilter textureFilter, const ColorF& color) const
	{
		pImpl->draw(rect, textureScale, textureFilter, color);
	}

	void NinePatch::release()
	{
		pImpl->release();
	}
}
