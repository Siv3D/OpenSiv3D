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
# include "Common.hpp"
# include "Mat4x4.hpp"
# include "RenderTexture.hpp"

namespace s3d
{
	namespace Graphics3D
	{
		void SetCameraTransform(const Mat4x4& matrix);

		namespace Internal
		{
			void SetRenderTarget(const Optional<RenderTexture>& rt);
		}
	}
}
