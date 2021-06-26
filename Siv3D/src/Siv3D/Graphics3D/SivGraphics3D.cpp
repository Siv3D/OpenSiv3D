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

# include <Siv3D/Graphics3D.hpp>
# include <Siv3D/Renderer3D/IRenderer3D.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	namespace Graphics3D
	{
		void SetCameraTransform(const Mat4x4& matrix)
		{
			SIV3D_ENGINE(Renderer3D)->setCameraTransform(matrix);
		}

		void Flush()
		{
			SIV3D_ENGINE(Renderer3D)->flush();
		}

		namespace Internal
		{
			void SetRenderTarget(const Optional<RenderTexture>& rt)
			{
				SIV3D_ENGINE(Renderer3D)->setRenderTarget(rt);
			}
		}
	}
}
