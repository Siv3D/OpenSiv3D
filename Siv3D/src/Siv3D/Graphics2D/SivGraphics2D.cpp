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

# include <Siv3D/Graphics2D.hpp>
# include <Siv3D/Renderer2D/IRenderer2D.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	namespace Graphics2D
	{
		Optional<VertexShader> GetCustomVertexShader()
		{
			return SIV3D_ENGINE(Renderer2D)->getCustomVS();
		}

		Optional<PixelShader> GetCustomPixelShader()
		{
			return SIV3D_ENGINE(Renderer2D)->getCustomPS();
		}

		void DrawTriangles(const uint32 count)
		{
			SIV3D_ENGINE(Renderer2D)->addNullVertices(count * 3);
		}

		namespace Internal
		{
			void SetCustomVertexShader(const Optional<VertexShader>& vs)
			{
				SIV3D_ENGINE(Renderer2D)->setCustomVS(vs);
			}

			void SetCustomPixelShader(const Optional<PixelShader>& ps)
			{
				SIV3D_ENGINE(Renderer2D)->setCustomPS(ps);
			}
		}
	}
}
