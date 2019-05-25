//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/PointVector.hpp>
# include <Siv3D/Scene.hpp>
# include <Siv3D/Image.hpp>
# include <Siv3D/TextReader.hpp>
# include <Siv3D/Unicode.hpp>
# include <Siv3D/Resource.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3DEngine.hpp>
# include <Renderer2D/IRenderer2D.hpp>
# include <Profiler/IProfiler.hpp>
# include <GL/glew.h>
# include <GLFW/glfw3.h>

# define SIV3D_USE_MULTISAMPLE

namespace s3d
{	
	class SceneTexture
	{
	private:

	# if defined(SIV3D_USE_MULTISAMPLE)
		
		GLuint m_msFrameBuffer = 0;
		GLuint m_msTexture = 0;
		
		GLuint m_resolvedFrameBuffer;
		GLuint m_resolvedTexture = 0;

	# else
		
		GLuint m_frameBuffer = 0;
		GLuint m_texture = 0;
		
	# endif
		
		Size m_size = Scene::DefaultSceneSize;
		
		GLuint m_copyProgram = 0;
		
		GLuint m_locationTexture = 0;
	
		GLuint m_vertexArray = 0;
		
		GLuint m_sampler = 0;
		
		
		Image m_image;
		
		bool m_screenCaptureRequested = false;

	public:
		
		SceneTexture();
		
		~SceneTexture();
		
		bool init();
		
		void clear(const ColorF& color);
		
		const Size& getSize() const noexcept;
		
		void resize(const Size& size, const ColorF& clearColor);
		
		void bindSceneFrameBuffer();
		
		void resolve(bool linearFilter);
		
		
		
		void requestCapture();
		
		bool hasCaptureRequest() const noexcept;
		
		void capture();
		
		const Image& getImage() const;
	};
}
