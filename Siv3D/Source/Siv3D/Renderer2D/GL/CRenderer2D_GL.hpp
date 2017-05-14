//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

# include <GL/glew.h>
# include "../../../ThirdParty/GLFW/include/GLFW/glfw3.h"
# include <Siv3D/Optional.hpp>
# include <Siv3D/Rectangle.hpp>
# include <Siv3D/ConstantBuffer.hpp>
# include "../IRenderer2D.hpp"
# include "GLSpriteBatch.hpp"
# include "GLRenderer2DCommandManager.hpp"

namespace s3d
{
	class ShaderPipeline
	{
	private:
		
		GLuint m_pipeline = 0;
		
	public:
		
		~ShaderPipeline()
		{
			if (m_pipeline)
			{
				::glDeleteProgramPipelines(1, &m_pipeline);
			}
		}
		
		bool init()
		{
			::glGenProgramPipelines(1, &m_pipeline);
			
			return m_pipeline != 0;
		}
		
		void setVS(GLuint vsProgramHandle)
		{
			::glUseProgramStages(m_pipeline, GL_VERTEX_SHADER_BIT, vsProgramHandle);
		}
		
		void setPS(GLuint psProgramHandle)
		{
			::glUseProgramStages(m_pipeline, GL_FRAGMENT_SHADER_BIT, psProgramHandle);
		}
		
		void use()
		{
			::glUseProgram(0);
			::glBindProgramPipeline(m_pipeline);
		}
	};
					
	struct SpriteCB
	{
		static const char* Name()
		{
			return "SpriteCB";
		}
		
		static constexpr uint32 BindingPoint()
		{
			return 0;
		}
		
		Float4 transform[2];
	};

	class CRenderer2D_GL : public ISiv3DRenderer2D
	{
	private:

		ShaderPipeline m_pipeline;

		ConstantBuffer<SpriteCB> m_cbSprite;
		
		GLSpriteBatch m_spriteBatch;
		
		GLRender2DCommandManager m_commandManager;
		
	public:

		CRenderer2D_GL();

		~CRenderer2D_GL() override;

		bool init();

		void flush() override;

		void setBlendState(const BlendState& state) override;

		BlendState getBlendState() const override;

		void setRasterizerState(const RasterizerState& state) override;

		RasterizerState getRasterizerState() const override;

		void setSamplerState(ShaderStage stage, uint32 slot, const SamplerState& state) override;

		const std::array<SamplerState, SamplerState::MaxSamplerCount>& getSamplerStates(ShaderStage stage) const override;

		void setScissorRect(const Rect& rect) override;

		Rect getScissorRect() const override;

		void setViewport(const Optional<Rect>& viewport) override;

		Optional<Rect> getViewport() const override;

		void addLine(LineStyle style, const Float2& begin, const Float2& end, float thickness, const Float4(&colors)[2]) override;
		
		void addTriangle(const Float2(&pts)[3], const Float4& color) override;

		void addTriangle(const Float2(&pts)[3], const Float4(&colors)[3]) override;

		void addRect(const FloatRect& rect, const Float4& color) override;
		
		void addRect(const FloatRect& rect, const Float4(&colors)[4]) override;

		void addRectFrame(const FloatRect& rect, float thickness, const Float4& color) override;

		void addCircle(const Float2& center, float r, const Float4& color) override;

		void addCircleFrame(const Float2& center, float r, float thickness, const Float4& color) override;

		void addCircleFrame(const Float2& center, float r, float thickness, const Float4& innerColor, const Float4& outerColor) override;

		void addCirclePie(const Float2& center, float r, float startAngle, float angle, const Float4& color) override;
		
		void addCircleArc(const Float2& center, float r, float startAngle, float angle, float thickness, const Float4& color) override;	
		
		void addEllipse(const Float2& center, float a, float b, const Float4& color) override;

		void addEllipseFrame(const Float2& center, float a, float b, float thickness, const Float4& color) override;

		void addQuad(const FloatQuad& quad, const Float4& color) override;
		
		void addQuad(const FloatQuad& quad, const Float4(&colors)[4]) override;
		
		void addLineString(const Vec2* pts, uint32 size, const Optional<Float2>& offset, float thickness, bool inner, const Float4& color, bool isClosed) override;
		
		void addShape2D(const Array<Float2>& vertices, const Array<uint32>& indices, const Float4& color) override;
		
		void addShape2DFrame(const Float2* pts, uint32 size, float thickness, const Float4& color) override;



		void addTextureRegion(const Texture& texture, const FloatRect& rect, const FloatRect& uv, const Float4& color) override;
		
		void addTexturedQuad(const Texture& texture, const FloatQuad& quad, const FloatRect& uv, const Float4& color) override;
	};
}

# endif
