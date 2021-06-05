//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Common.hpp>
# include <Siv3D/PointVector.hpp>

namespace s3d
{
	struct VSConstants2D
	{
		Float4 transform[2] = { { 0.0f, 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f, 0.0f } };

		Float4 colorMul{ 1.0f, 1.0f, 1.0f, 1.0f };
	};

	struct PSConstants2D
	{
		Float4 colorAdd{ 0.0f, 0.0f, 0.0f, 0.0f };

		Float4 sdfParam{ 0.5f, 0.5f, 0.0f, 0.0f };

		Float4 sdfOuterColor{ 0.0f, 0.0f, 0.0f, 1.0f };

		Float4 sdfShadowColor{ 0.0f, 0.0f, 0.0f, 0.5f };
	};

	struct BatchInfo2D
	{
		uint32 indexCount = 0;

		uint32 startIndexLocation = 0;

		uint32 baseVertexLocation = 0;
	};
}
