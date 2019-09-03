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
# include <Renderer2D/IRenderer2D.hpp>
# include <Siv3D/PointVector.hpp>
# include <Siv3D/ByteArray.hpp>
# include <Siv3D/VertexShader.hpp>
# include <Siv3D/PixelShader.hpp>
# include <Siv3D/ConstantBuffer.hpp>
# include <Renderer2D/Vertex2DBuilder.hpp>
# include <GL/glew.h>
# include <GLFW/glfw3.h>
# include "GLSpriteBatch.hpp"
# include "GLRenderer2DCommand.hpp"


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
				m_pipeline = 0;
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
	
	struct VscbSprite
	{
		static constexpr const char* Name()
		{
			return "vscbSprite";
		}
		
		static constexpr uint32 BindingPoint()
		{
			return 0;
		}
		
		Float4 transform[2];
		
		Float4 colorMul;
	};
	
	struct PscbSprite
	{
		static constexpr const char* Name()
		{
			return "pscbSprite";
		}
		
		static constexpr uint32 BindingPoint()
		{
			return 1;
		}
		
		Float4 colorAdd;
		
		Float4 sdfParam;
	};
	
	struct GLStandardVS2D
	{
		VertexShader sprite;
		
		bool ok() const
		{
			return !!sprite;
		}
	};
	
	struct GLStandardPS2D
	{
		PixelShader shape;
		PixelShader texture;
		PixelShader square_dot;
		PixelShader round_dot;
		PixelShader sdf;
		
		// PixelShaderID キャッシュ
		PixelShaderID shapeID;
		PixelShaderID textureID;
		PixelShaderID square_dotID;
		PixelShaderID round_dotID;
		PixelShaderID sdfID;
		
		bool setup()
		{
			const bool initialized =
			shape
			&& texture
			&& square_dot
			&& round_dot
			&& sdf;
			
			shapeID			= shape.id();
			textureID		= texture.id();
			square_dotID	= square_dot.id();
			round_dotID		= round_dot.id();
			sdfID			= sdf.id();
			
			return initialized;
		}
	};
	
	class CRenderer2D_GL : public ISiv3DRenderer2D
	{
	private:
		
		std::unique_ptr<GLStandardVS2D> m_standardVS;
		std::unique_ptr<GLStandardPS2D> m_standardPS;
		
		BufferCreatorFunc m_bufferCreator;
		
		ShaderPipeline m_pipeline;
		
		ConstantBuffer<VscbSprite> m_vscbSprite;
		ConstantBuffer<PscbSprite> m_pscbSprite;
		
		GLSpriteBatch m_batches;
		
		GLRenderer2DCommand m_commands;
		
		std::unique_ptr<Texture> m_boxShadowTexture;

	public:

		CRenderer2D_GL();

		~CRenderer2D_GL() override;

		void init();

		void flush() override;

		std::pair<float, FloatRect> getLetterboxingTransform() const override;

		void drawFullscreen(bool) override {} // do nothing for OpenGL

		void setColorMul(const Float4& color) override;

		ColorF getColorMul() const override;

		void setColorAdd(const Float4& color) override;

		ColorF getColorAdd() const override;

		void setBlendState(const BlendState& state) override;

		BlendState getBlendState() const override;

		void setRasterizerState(const RasterizerState& state) override;

		RasterizerState getRasterizerState() const override;

		void setPSSamplerState(uint32 slot, const SamplerState& state) override;

		SamplerState getPSSamplerState(uint32 slot) const override;

		void setLocalTransform(const Mat3x2& matrix) override;

		const Mat3x2& getLocalTransform() const override;

		void setCameraTransform(const Mat3x2& matrix) override;

		const Mat3x2& getCameraTransform() const override;

		void setScissorRect(const Rect& rect) override;

		float getMaxScaling() const override;

		Rect getScissorRect() const override;

		void setViewport(const Optional<Rect>& viewport) override;

		Optional<Rect> getViewport() const override;

		void setSDFParameters(const Float4& parameters) override;

		Float4 getSDFParameters() const override;
		
		void setCustomPS(const Optional<PixelShader>& ps) override;
		
		Optional<PixelShader> getCustomPS() const override;

		void addLine(const LineStyle& style, const Float2& begin, const Float2& end, float thickness, const Float4(&colors)[2]) override;

		void addTriangle(const Float2(&pts)[3], const Float4& color) override;

		void addTriangle(const Float2(&pts)[3], const Float4(&colors)[3]) override;

		void addRect(const FloatRect& rect, const Float4& color) override;

		void addRect(const FloatRect& rect, const Float4(&colors)[4]) override;

		void addRectFrame(const FloatRect& rect, float thickness, const Float4& color) override;

		void addCircle(const Float2& center, float r, const Float4& color) override;

		void addCircleFrame(const Float2& center, float rInner, float thickness, const Float4& innerColor, const Float4& outerColor) override;

		void addCirclePie(const Float2& center, float r, float startAngle, float angle, const Float4& color) override;

		void addCircleArc(const Float2& center, float rInner, float startAngle, float angle, float thickness, const Float4& color) override;

		void addEllipse(const Float2& center, float a, float b, const Float4& color) override;

		void addEllipseFrame(const Float2& center, float aInner, float bInner, float thickness, const Float4& innerColor, const Float4& outerColor) override;

		void addQuad(const FloatQuad& quad, const Float4& color) override;

		void addQuad(const FloatQuad& quad, const Float4(&colors)[4]) override;

		void addRoundRect(const FloatRect& rect, float w, float h, float r, const Float4& color) override;

		void addLineString(const LineStyle& style, const Vec2* pts, uint16 size, const Optional<Float2>& offset, float thickness, bool inner, const Float4& color, bool isClosed) override;

		void addShape2D(const Array<Float2>& vertices, const Array<uint16>& indices, const Optional<Float2>& offset, const Float4& color) override;

		void addShape2DTransformed(const Array<Float2>& vertices, const Array<uint16>& indices, float s, float c, const Float2& offset, const Float4& color) override;

		void addShape2DFrame(const Float2* pts, uint16 size, float thickness, const Float4& color) override;

		void addSprite(const Sprite& sprite, uint16 startIndex, uint16 indexCount) override;

		void addSprite(const Texture& texture, const Sprite& sprite, uint16 startIndex, uint16 indexCount) override;

		void addTextureRegion(const Texture& texture, const FloatRect& rect, const FloatRect& uv, const Float4& color) override;

		void addTextureRegion(const Texture& texture, const FloatRect& rect, const FloatRect& uv, const Float4(&colors)[4]) override;

		void addTexturedCircle(const Texture& texture, const Circle& circle, const FloatRect& uv, const Float4& color) override;

		void addTexturedQuad(const Texture& texture, const FloatQuad& quad, const FloatRect& uv, const Float4& color) override;
	
		void addTexturedParticles(const Texture& texture, const Array<Particle2D>& particles,
			ParticleSystem2DParameters::SizeOverLifeTimeFunc sizeOverLifeTimeFunc,
			ParticleSystem2DParameters::ColorOverLifeTimeFunc colorOverLifeTimeFunc) override;

		const Texture& getBoxShadowTexture() const override;
	};
}
