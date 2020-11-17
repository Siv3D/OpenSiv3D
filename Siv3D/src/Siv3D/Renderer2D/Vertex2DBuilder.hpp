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
# include <Siv3D/Common.hpp>
# include <Siv3D/Vertex2D.hpp>
# include <Siv3D/FloatRect.hpp>
# include "Vertex2DBufferPointer.hpp"

namespace s3d
{
	using BufferCreatorFunc = std::function<Vertex2DBufferPointer(Vertex2D::IndexType, Vertex2D::IndexType)>;

	namespace Vertex2DBuilder
	{
		[[nodiscard]]
		Vertex2D::IndexType BuildRect(const BufferCreatorFunc& bufferCreator, const FloatRect& rect, const Float4& color);
	}
}
