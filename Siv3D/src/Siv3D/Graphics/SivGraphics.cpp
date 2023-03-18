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

# include <Siv3D/Graphics.hpp>
# include <Siv3D/Renderer/IRenderer.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	namespace Graphics
	{
		void SetVSyncEnabled(const bool enabled)
		{
			return SIV3D_ENGINE(Renderer)->setVSyncEnabled(enabled);
		}

		bool IsVSyncEnabled()
		{
			return SIV3D_ENGINE(Renderer)->isVSyncEnabled();
		}
	}
}
