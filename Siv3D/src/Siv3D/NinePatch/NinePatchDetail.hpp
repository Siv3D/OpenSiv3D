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

# pragma once
# include <Siv3D/NinePatch.hpp>
# include <Siv3D/RenderTexture.hpp>

namespace s3d
{
	class NinePatch::NinePatchDetail
	{
	public:

		NinePatchDetail() = default;

		NinePatchDetail(const Image& image, int32 leftWidth, int32 topHeight, int32 rightWidth, int32 bottomHeight, const Style& style);

		NinePatchDetail(const Texture& texture, int32 leftWidth, int32 topHeight, int32 rightWidth, int32 bottomHeight, const Style& style);

		void draw(const RectF& rect, double textureScale, TextureFilter textureFilter, const ColorF& color) const;

		void release();

		[[nodiscard]]
		const Texture& getTexture() const noexcept;

		[[nodiscard]]
		const RepeatableTexture& getRepeatableTexture() const noexcept;

		[[nodiscard]]
		const PatchSize& getPatchSize() const noexcept;

	private:

		Style m_style = Style::Default();

		Texture m_texture;

		RepeatableTexture m_repeatableTexture;

		PatchSize m_patchSize;
	};
}
