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

# include <Siv3D/EngineError.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/ScopeGuard.hpp>
# include <Siv3D/Mat3x2.hpp>
# include <Siv3D/FloatRect.hpp>
# include <Siv3D/FloatQuad.hpp>
# include <Siv3D/Line.hpp>
# include <Siv3D/Resource.hpp>
# include <Siv3D/Math.hpp>
//# include <ConstantBuffer/D3D11/D3D11ConstantBuffer.hpp>
//# include <Graphics/GL/CGraphics_GL.hpp>
# include <Texture/GL/CTexture_GL.hpp>
# include <Shader/IShader.hpp>
# include <Profiler/IProfiler.hpp>
# include <Siv3DEngine.hpp>
# include <Renderer2D/Vertex2DBuilder.hpp>
# include "CRenderer2D_GL.hpp"
//# include "D3D11SpriteBatch.hpp"
# include <Siv3D/BlendState.hpp>
# include <Siv3D/RasterizerState.hpp>
# include <Siv3D/SamplerState.hpp>

/*
#	define LOG_COMMAND(...) LOG_TRACE(__VA_ARGS__)
/*/
#	define LOG_COMMAND(...) ((void)0)
//*/

namespace s3d
{
	namespace detail
	{
		static constexpr IndexType RectIndexTable[6] = { 0, 1, 2, 2, 1, 3 };
	}

	CRenderer2D_GL::CRenderer2D_GL()
	{

	}

	CRenderer2D_GL::~CRenderer2D_GL()
	{
		LOG_TRACE(U"CRenderer2D_GL::~CRenderer2D_GL()");
	}

	void CRenderer2D_GL::init()
	{
		LOG_TRACE(U"CRenderer2D_GL::init()");

	

		LOG_INFO(U"ℹ️ CRenderer2D_GL initialized");
	}

	void CRenderer2D_GL::flush()
	{


	}

	std::pair<float, FloatRect> CRenderer2D_GL::getLetterboxingTransform() const
	{
		// [Siv3D ToDo]
		return{ 1.0, FloatRect(0,0, 800, 600) };
	}

	void CRenderer2D_GL::drawResolved()
	{
		// [Siv3D ToDo]
	}

	void CRenderer2D_GL::setColorMul(const Float4& color)
	{
		// [Siv3D ToDo]
	}

	ColorF CRenderer2D_GL::getColorMul() const
	{
		// [Siv3D ToDo]
		return ColorF(0.0);
	}

	void CRenderer2D_GL::setColorAdd(const Float4& color)
	{

	}

	ColorF CRenderer2D_GL::getColorAdd() const
	{
		// [Siv3D ToDo]
		return ColorF(0.0);
	}

	void CRenderer2D_GL::setBlendState(const BlendState& state)
	{
		// [Siv3D ToDo]
	}

	BlendState CRenderer2D_GL::getBlendState() const
	{
		// [Siv3D ToDo]
		return BlendState();
	}

	void CRenderer2D_GL::setRasterizerState(const RasterizerState& state)
	{
		// [Siv3D ToDo]
	}

	RasterizerState CRenderer2D_GL::getRasterizerState() const
	{
		// [Siv3D ToDo]
		return RasterizerState();
	}

	void CRenderer2D_GL::setPSSamplerState(const uint32 slot, const SamplerState& state)
	{
		// [Siv3D ToDo]
	}

	SamplerState CRenderer2D_GL::getPSSamplerState(const uint32 slot) const
	{
		// [Siv3D ToDo]
		return SamplerState();
	}

	void CRenderer2D_GL::setLocalTransform(const Mat3x2& matrix)
	{
		// [Siv3D ToDo]
	}

	const Mat3x2& CRenderer2D_GL::getLocalTransform() const
	{
		// [Siv3D ToDo]
		static Mat3x2 dummy;
		return dummy;
	}

	void CRenderer2D_GL::setCameraTransform(const Mat3x2& matrix)
	{
		// [Siv3D ToDo]
	}

	const Mat3x2& CRenderer2D_GL::getCameraTransform() const
	{
		// [Siv3D ToDo]
		static Mat3x2 dummy;
		return dummy;
	}

	float CRenderer2D_GL::getMaxScaling() const
	{
		// [Siv3D ToDo]
		return 1.0f;
	}

	void CRenderer2D_GL::setScissorRect(const Rect& rect)
	{
		// [Siv3D ToDo]
	}

	Rect CRenderer2D_GL::getScissorRect() const
	{
		// [Siv3D ToDo]
		return Rect(0, 0, 0, 0);
	}

	void CRenderer2D_GL::setViewport(const Optional<Rect>& viewport)
	{
		// [Siv3D ToDo]
	}

	Optional<Rect> CRenderer2D_GL::getViewport() const
	{
		// [Siv3D ToDo]
		return none;
	}

	void CRenderer2D_GL::setSDFParameters(const Float4& parameters)
	{
		// [Siv3D ToDo]
	}

	Float4 CRenderer2D_GL::getSDFParameters() const
	{
		// [Siv3D ToDo]
		return Float4(0, 0, 0, 0);
	}

	void CRenderer2D_GL::addLine(const LineStyle& style, const Float2& begin, const Float2& end, const float thickness, const Float4(&colors)[2])
	{
		// [Siv3D ToDo]
	}

	void CRenderer2D_GL::addTriangle(const Float2(&pts)[3], const Float4& color)
	{
		// [Siv3D ToDo]
	}

	void CRenderer2D_GL::addTriangle(const Float2(&pts)[3], const Float4(&colors)[3])
	{
		// [Siv3D ToDo]
	}

	void CRenderer2D_GL::addRect(const FloatRect& rect, const Float4& color)
	{
		// [Siv3D ToDo]
	}

	void CRenderer2D_GL::addRect(const FloatRect& rect, const Float4(&colors)[4])
	{
		// [Siv3D ToDo]
	}

	void CRenderer2D_GL::addRectFrame(const FloatRect& rect, const float thickness, const Float4& color)
	{
		// [Siv3D ToDo]
	}

	void CRenderer2D_GL::addCircle(const Float2& center, const float r, const Float4& color)
	{
		// [Siv3D ToDo]
	}

	void CRenderer2D_GL::addCircleFrame(const Float2& center, const float rInner, const float thickness, const Float4& innerColor, const Float4& outerColor)
	{
		// [Siv3D ToDo]
	}

	void CRenderer2D_GL::addCirclePie(const Float2& center, const float r, const float startAngle, const float angle, const Float4& color)
	{
		// [Siv3D ToDo]
	}

	void CRenderer2D_GL::addCircleArc(const Float2& center, const float rInner, const float startAngle, float angle, const float thickness, const Float4& color)
	{
		// [Siv3D ToDo]
	}

	void CRenderer2D_GL::addEllipse(const Float2& center, const float a, const float b, const Float4& color)
	{
		// [Siv3D ToDo]
	}

	void CRenderer2D_GL::addEllipseFrame(const Float2& center, const float aInner, const float bInner, const float thickness, const Float4& innerColor, const Float4& outerColor)
	{
		// [Siv3D ToDo]
	}

	void CRenderer2D_GL::addQuad(const FloatQuad& quad, const Float4& color)
	{
		// [Siv3D ToDo]
	}

	void CRenderer2D_GL::addQuad(const FloatQuad& quad, const Float4(&colors)[4])
	{
		// [Siv3D ToDo]
	}

	void CRenderer2D_GL::addRoundRect(const FloatRect& rect, const float w, const float h, const float r, const Float4& color)
	{
		// [Siv3D ToDo]
	}

	void CRenderer2D_GL::addLineString(const LineStyle& style, const Vec2* pts, const uint16 size, const Optional<Float2>& offset, const float thickness, const bool inner, const Float4& color, const bool isClosed)
	{
		// [Siv3D ToDo]
	}

	void CRenderer2D_GL::addShape2D(const Array<Float2>& vertices, const Array<uint16>& indices, const Optional<Float2>& offset, const Float4& color)
	{
		// [Siv3D ToDo]
	}

	void CRenderer2D_GL::addShape2DTransformed(const Array<Float2>& vertices, const Array<uint16>& indices, const float s, const float c, const Float2& offset, const Float4& color)
	{
		// [Siv3D ToDo]
	}

	void CRenderer2D_GL::addShape2DFrame(const Float2* pts, const uint16 size, const float thickness, const Float4& color)
	{
		// [Siv3D ToDo]
	}

	void CRenderer2D_GL::addSprite(const Sprite& sprite, const uint16 startIndex, const uint16 indexCount)
	{
		// [Siv3D ToDo]
	}

	void CRenderer2D_GL::addSprite(const Texture& texture, const Sprite& sprite, const uint16 startIndex, const uint16 indexCount)
	{
		// [Siv3D ToDo]
	}

	void CRenderer2D_GL::addTextureRegion(const Texture& texture, const FloatRect& rect, const FloatRect& uv, const Float4& color)
	{
		// [Siv3D ToDo]
	}

	void CRenderer2D_GL::addTextureRegion(const Texture& texture, const FloatRect& rect, const FloatRect& uv, const Float4(&colors)[4])
	{
		// [Siv3D ToDo]
	}

	void CRenderer2D_GL::addTexturedCircle(const Texture& texture, const Circle& circle, const FloatRect& uv, const Float4& color)
	{
		// [Siv3D ToDo]
	}

	void CRenderer2D_GL::addTexturedQuad(const Texture& texture, const FloatQuad& quad, const FloatRect& uv, const Float4& color)
	{
		// [Siv3D ToDo]
	}

	void CRenderer2D_GL::addTexturedParticles(const Texture& texture, const Array<Particle2D>& particles,
		ParticleSystem2DParameters::SizeOverLifeTimeFunc sizeOverLifeTimeFunc,
		ParticleSystem2DParameters::ColorOverLifeTimeFunc colorOverLifeTimeFunc)
	{
		// [Siv3D ToDo]
	}

	const Texture& CRenderer2D_GL::getBoxShadowTexture() const
	{
		return *m_boxShadowTexture;
	}
}
