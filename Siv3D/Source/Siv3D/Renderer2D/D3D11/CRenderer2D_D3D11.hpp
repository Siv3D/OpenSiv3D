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
# if defined(SIV3D_TARGET_WINDOWS)

# define  NOMINMAX
# define  STRICT
# define  WIN32_LEAN_AND_MEAN
# define  _WIN32_WINNT _WIN32_WINNT_WIN7
# define  NTDDI_VERSION NTDDI_WIN7
# include <Windows.h>
# include <wrl.h>
# include <d3d11.h>
# include <Siv3D/ConstantBuffer.hpp>
# include "../IRenderer2D.hpp"
# include "D3D11SpriteBatch.hpp"
# include "D3D11Renderer2DCommandManager.hpp"

using namespace Microsoft::WRL;

namespace s3d
{
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

	class CRenderer2D_D3D11 : public ISiv3DRenderer2D
	{
	private:

		ID3D11Device* m_device = nullptr;

		ID3D11DeviceContext* m_context = nullptr;

		ComPtr<ID3D11InputLayout> m_inputLayout;

		D3D11SpriteBatch m_spriteBatch;

		ConstantBuffer<SpriteCB> m_cbSprite;

		D3D11Render2DCommandManager m_commandManager;

	public:

		CRenderer2D_D3D11();

		~CRenderer2D_D3D11() override;

		bool init(ID3D11Device* device, ID3D11DeviceContext* context);

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

		void addLine(const Float2& begin, const Float2& end, float thickness, const Float4(&colors)[2]) override;

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
	};
}

# endif
