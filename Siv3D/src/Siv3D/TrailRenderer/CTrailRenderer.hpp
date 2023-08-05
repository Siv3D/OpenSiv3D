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
# include "ITrailRenderer.hpp"
# include <Siv3D/Buffer2D.hpp>

namespace s3d
{
	class CTrailRenderer final : public ISiv3DTrailRenderer
	{
	public:

		void draw(const Trail& trail) override;

		void draw(const Trail& trail, const Texture& texture) override;

	private:

		void drawImpl(const Trail& trail, const Texture* pTexture);

		void setBuffer(const Trail& trail);

		void resizeBuffer(size_t num_vertices);

		static constexpr size_t MinVertexCount = 512;

		Buffer2D m_buffer;
	};
}
