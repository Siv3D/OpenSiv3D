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
	NinePatch::NinePatch(const FilePathView path, const int32 patchSize, const Style& style)
		: NinePatch{ Image{ path }, patchSize, patchSize, patchSize, patchSize, style } {}

	NinePatch::NinePatch(const FilePathView path, const int32 patchWidth, const int32 patchHeight, const Style& style)
		: NinePatch{ Image{ path }, patchWidth, patchHeight, patchWidth, patchHeight, style } {}

	NinePatch::NinePatch(const FilePathView path, const int32 leftWidth, const int32 topHeight, const int32 rightWidth, const int32 bottomHeight, const Style& style)
		: NinePatch{ Image{ path }, leftWidth, topHeight, rightWidth, bottomHeight, style } {}

	NinePatch::NinePatch(const Image& image, const int32 patchSize, const Style& style)
		: NinePatch{ image, patchSize, patchSize, patchSize, patchSize, style } {}

	NinePatch::NinePatch(const Image& image, const int32 patchWidth, const int32 patchHeight, const Style& style)
		: NinePatch{ image, patchWidth, patchHeight, patchWidth, patchHeight, style } {}

	NinePatch::NinePatch(const Image& image, const int32 leftWidth, const int32 topHeight, const int32 rightWidth, const int32 bottomHeight, const Style& style)
		: pImpl{ std::make_shared<NinePatchDetail>(image, leftWidth, topHeight, rightWidth, bottomHeight, style) } {}

	NinePatch::NinePatch(const Texture& texture, const int32 patchSize, const Style& style)
		: NinePatch{ texture, patchSize, patchSize, patchSize, patchSize, style } {}

	NinePatch::NinePatch(const Texture& texture, const int32 patchWidth, const int32 patchHeight, const Style& style)
		: NinePatch{ texture, patchWidth, patchHeight, patchWidth, patchHeight, style } {}

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

	const Texture& NinePatch::getTexture() const noexcept
	{
		return pImpl->getTexture();
	}

	const NinePatch::RepeatableTexture& NinePatch::getRepeatableTexture() const noexcept
	{
		return pImpl->getRepeatableTexture();
	}

	const NinePatch::PatchSize& NinePatch::getPatchSize() const noexcept
	{
		return pImpl->getPatchSize();
	}
}
