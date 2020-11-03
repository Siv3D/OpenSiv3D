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
# include <Siv3D/Common/OpenGL.hpp>
# include <Siv3D/Renderer/IRenderer.hpp>
# include <Siv3D/PointVector.hpp>

namespace s3d
{
	class CRenderer_GLES3 final : public ISiv3DRenderer
	{
	private:
		
		GLFWwindow* m_window = nullptr;

		Size m_frameBufferSize = Size(0, 0);

		Size m_sceneSize = Size(800, 600);

	public:

		CRenderer_GLES3();

		~CRenderer_GLES3() override;

		void init() override;

		StringView getName() const override;

		void clear() override;

		void flush() override;

		bool present() override;

		Size getFrameBufferSize() const override;

		Size getSceneSize() const override;	
	};
}
