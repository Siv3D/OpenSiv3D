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
# include <Siv3D/Array.hpp>
# include <Siv3D/PointVector.hpp>
# include <Siv3D/BlendState.hpp>
# include <Siv3D/RasterizerState.hpp>
# include <Siv3D/SamplerState.hpp>
# include <Siv3D/Mat3x2.hpp>
# include <Siv3D/Rectangle.hpp>
# include <Siv3D/Texture.hpp>
# include <Siv3D/PixelShader.hpp>
# include <Siv3D/HashTable.hpp>

namespace s3d
{
	enum class RendererCommand
	{
		Draw,

		SetBuffers,

		UpdateBuffers,

		NextBatch,

		ColorMul,

		ColorAdd,

		BlendState,

		RasterizerState,

		PSSamplerState0,
		
		PSSamplerState1,
		
		PSSamplerState2,
		
		PSSamplerState3,
		
		PSSamplerState4,
		
		PSSamplerState5,
		
		PSSamplerState6,
		
		PSSamplerState7,

		Transform,

		SetPS,

		ScissorRect,

		Viewport,

		PSTexture0,

		PSTexture1,

		PSTexture2,

		PSTexture3,

		PSTexture4,

		PSTexture5,

		PSTexture6,

		PSTexture7,

		SDFParam,
	};

	class CurrentBatchStateChanges
	{
	private:

		uint32 m_states = 0;

	public:

		bool has(RendererCommand command) const noexcept
		{
			return !!(m_states & (0x1 << FromEnum(command)));
		}

		bool hasStateChange() const noexcept
		{
			return m_states > 1;
		}

		void set(RendererCommand command) noexcept
		{
			m_states |= (0x1u << FromEnum(command));
		}

		void clear(RendererCommand command) noexcept
		{
			m_states &= ~(0x1u << FromEnum(command));
		}

		void reset() noexcept
		{
			m_states = 0;
		}
	};

	struct DrawCommand
	{
		uint32 indexCount = 0;
	};

	class D3D11Renderer2DCommand
	{
	private:

		Array<std::pair<RendererCommand, uint32>> m_commands;

		CurrentBatchStateChanges m_changes;

		Array<DrawCommand> m_draws;

		Array<Float4> m_colorMuls = { Float4(1.0f, 1.0f, 1.0f, 1.0f) };
		Array<Float4> m_colorAdds = { Float4(0.0f, 0.0f, 0.0f, 0.0f) };
		Array<BlendState> m_blendStates = { BlendState::Default };
		Array<RasterizerState> m_rasterizerStates = { RasterizerState::Default2D };
		std::array<Array<SamplerState>, SamplerState::MaxSamplerCount> m_psSamplerStates;
		Array<Mat3x2> m_combinedTransforms = { Mat3x2::Identity() };
		float m_currentMaxScaling = 1.0f;
		Array<PixelShaderID> m_PSs;
		Array<Rect> m_scissorRects = { Rect(0) };
		Array<Optional<Rect>> m_viewports = { none };
		std::array<Array<TextureID>, SamplerState::MaxSamplerCount> m_psTextures;
		Array<Float4> m_sdfParams = { Float4(0.0f, 0.0f, 0.0f, 0.0f) };

		DrawCommand m_currentDraw;
		Float4 m_currentColorMul = m_colorMuls.front();
		Float4 m_currentColorAdd = m_colorAdds.front();
		BlendState m_currentBlendState = m_blendStates.front();
		RasterizerState m_currentRasterizerState = m_rasterizerStates.front();
		std::array<SamplerState, SamplerState::MaxSamplerCount> m_currentPSSamplerStates;
		Mat3x2 m_currentLocalTransform = Mat3x2::Identity();
		Mat3x2 m_currentCameraTransform = Mat3x2::Identity();
		Mat3x2 m_currentCombinedTransform = Mat3x2::Identity();
		PixelShaderID m_currentPS = PixelShaderID::InvalidValue();
		Rect m_currentScissorRect = m_scissorRects.front();
		Optional<Rect> m_currentViewport = m_viewports.front();
		std::array<TextureID, SamplerState::MaxSamplerCount> m_currentPSTextures;
		Float4 m_currentSdfParam = m_sdfParams.front();

		HashTable<PixelShaderID, PixelShader> m_reservedPSs;
		HashTable<TextureID, Texture> m_reservedTextures;

	public:

		D3D11Renderer2DCommand();

		void reset();

		void flush();

		const Array<std::pair<RendererCommand, uint32>>& getList() const;

		void pushDraw(uint16 indexCount);
		const DrawCommand& getDraw(uint32 index);

		void pushUpdateBuffers(uint32 batchIndex);
	
		void pushColorMul(const Float4& color);
		const Float4& getColorMul(uint32 index) const;
		const Float4& getCurrentColorMul() const;

		void pushColorAdd(const Float4& color);
		const Float4& getColorAdd(uint32 index) const;
		const Float4& getCurrentColorAdd() const;

		void pushBlendState(const BlendState& state);
		const BlendState& getBlendState(uint32 index) const;
		const BlendState& getCurrentBlendState() const;

		void pushRasterizerState(const RasterizerState& state);
		const RasterizerState& getRasterizerState(uint32 index) const;
		const RasterizerState& getCurrentRasterizerState() const;

		void pushPSSamplerState(const SamplerState& state, uint32 slot);
		const SamplerState& getPSSamplerState(uint32 slot, uint32 index) const;
		const SamplerState& getPSCurrentSamplerState(uint32 slot) const;

		void pushLocalTransform(const Mat3x2& local);
		const Mat3x2& getCurrentLocalTransform() const;

		void pushCameraTransform(const Mat3x2& camera);
		const Mat3x2& getCurrentCameraTransform() const;

		const Mat3x2& getCombinedTransform(uint32 index) const;
		const Mat3x2& getCurrentCombinedTransform() const;
		float getCurrentMaxScaling() const noexcept;

		void pushStandardPS(const PixelShaderID& id);
		void pushCustomPS(const PixelShader& ps);
		const PixelShaderID& getPS(uint32 index) const;

		void pushScissorRect(const Rect& rect);
		const Rect& getScissorRect(uint32 index) const;
		const Rect& getCurrentScissorRect() const;

		void pushViewport(const Optional<Rect>& rect);
		const Optional<Rect>& getViewport(uint32 index) const;
		const Optional<Rect>& getCurrentViewport() const;

		void pushPSTexture(uint32 slot, const Texture& texture);
		const TextureID& getPSTexture(uint32 slot, uint32 index) const;

		void pushSdfParam(const Float4& param);
		const Float4& getSdfParam(uint32 index) const;
		const Float4& getCurrentSdfParam() const;
	};
}
