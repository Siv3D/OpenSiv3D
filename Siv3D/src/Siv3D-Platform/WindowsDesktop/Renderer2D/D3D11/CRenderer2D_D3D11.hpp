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
# include <Siv3D/RenderTexture.hpp>
# include "D3D11SpriteBatch.hpp"
# include "D3D11Renderer2DCommand.hpp"
# include <Renderer2D/Vertex2DBuilder.hpp>

namespace s3d
{
	struct SpriteCB0
	{
		static constexpr uint32 BindingPoint()
		{
			return 0;
		}

		Float4 transform[2];

		Float4 colorMul;
	};

	struct SpriteCB1
	{
		static constexpr uint32 BindingPoint()
		{
			return 1;
		}

		Float4 colorAdd;

		Float4 sdfParam;
	};

	struct FullscreenTriangleCB0
	{
		static constexpr uint32 BindingPoint()
		{
			return 0;
		}

		Float4 texScale;
	};

	struct D3D11StandardVS2D
	{
		VertexShader sprite;
		VertexShader fullscreen_triangle_resolve;
		VertexShader fullscreen_triangle_draw;

		bool ok() const
		{
			return sprite
				&& fullscreen_triangle_resolve
				&& fullscreen_triangle_draw;
		}
	};

	struct D3D11StandardPS2D
	{
		// PS
		PixelShader shape;
		PixelShader texture;
		PixelShader square_dot;
		PixelShader round_dot;
		PixelShader sdf;
		PixelShader fullscreen_triangle_resolve;
		PixelShader fullscreen_triangle_draw;

		// PixelShaderID キャッシュ
		PixelShaderID shapeID;
		PixelShaderID textureID;
		PixelShaderID square_dotID;
		PixelShaderID round_dotID;
		PixelShaderID sdfID;
		PixelShaderID fullscreen_triangle_resolveID;
		PixelShaderID fullscreen_triangle_drawID;

		bool setup()
		{
			const bool initialized = 
				shape
				&& texture
				&& square_dot
				&& round_dot
				&& sdf
				&& fullscreen_triangle_resolve
				&& fullscreen_triangle_draw;

			shapeID							= shape.id();
			textureID						= texture.id();
			square_dotID					= square_dot.id();
			round_dotID						= round_dot.id();
			sdfID							= sdf.id();
			fullscreen_triangle_resolveID	= fullscreen_triangle_resolve.id();
			fullscreen_triangle_drawID		= fullscreen_triangle_draw.id();

			return initialized;
		}
	};

	class CRenderer2D_D3D11 : public ISiv3DRenderer2D
	{
	private:

		ID3D11Device* m_device = nullptr;
		ID3D11DeviceContext* m_context = nullptr;

		std::unique_ptr<D3D11StandardVS2D> m_standardVS;
		std::unique_ptr<D3D11StandardPS2D> m_standardPS;

		ConstantBuffer<SpriteCB0> m_cbSprite0;
		ConstantBuffer<SpriteCB1> m_cbSprite1;
		ConstantBuffer<FullscreenTriangleCB0> m_cbFullscreenTriangle0;

		ComPtr<ID3D11InputLayout> m_inputLayout;

		D3D11SpriteBatch m_batches;
		D3D11Renderer2DCommand m_commands;
		BufferCreatorFunc m_bufferCreator;

		std::unique_ptr<Texture> m_boxShadowTexture;

		Optional<PixelShader> m_currentCustomPS;

	public:

		CRenderer2D_D3D11();

		~CRenderer2D_D3D11() override;

		void init(ID3D11Device* device, ID3D11DeviceContext* context);

		void flush() override;

		std::pair<float, FloatRect> getLetterboxingTransform() const override;

		void drawFullscreen(bool multisample) override;

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

		void setPSTexture(uint32 slot, const Optional<Texture>& texture) override;

		void setCustomPS(const Optional<PixelShader>& ps) override;

		Optional<PixelShader> getCustomPS() const override;

		void setConstant(ShaderStage stage, uint32 slot, const s3d::detail::ConstantBufferBase& buffer, const float* data, uint32 num_vectors) override;

		void setRT(const Optional<RenderTexture>& rt) override;

		Optional<RenderTexture> getRT() const override;

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

		void addSprite(const Texture& texture, const Sprite& sprite, uint16 startIndex, uint16 indexCount);

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
