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
# include <Siv3D/Array.hpp>
# include <Siv3D/HashTable.hpp>
# include <Siv3D/Vertex2D.hpp>
# include <Siv3D/BlendState.hpp>
# include <Siv3D/RasterizerState.hpp>
# include <Siv3D/SamplerState.hpp>
# include <Siv3D/VertexShader.hpp>
# include <Siv3D/PixelShader.hpp>
# include <Siv3D/Common/D3D11.hpp>
# include <Siv3D/Renderer2D/CurrentBatchStateChanges.hpp>

namespace s3d
{
	enum class D3D11Renderer2DCommandType : uint32
	{
		Null,

		SetBuffers,

		UpdateBuffers,

		Draw,

		DrawNull,

		BlendState,

		RasterizerState,

		VSSamplerState0,

		VSSamplerState1,

		VSSamplerState2,

		VSSamplerState3,

		VSSamplerState4,

		VSSamplerState5,

		VSSamplerState6,

		VSSamplerState7,

		PSSamplerState0,

		PSSamplerState1,

		PSSamplerState2,

		PSSamplerState3,

		PSSamplerState4,

		PSSamplerState5,

		PSSamplerState6,

		PSSamplerState7,

		SetVS,

		SetPS,
	};

	struct D3D11Renderer2DCommand
	{
		D3D11Renderer2DCommandType type = D3D11Renderer2DCommandType::Null;

		uint32 index = 0;
	};

	struct D3D11DrawCommand
	{
		uint32 indexCount = 0;
	};

	class D3D11Renderer2DCommandManager
	{
	private:

		// commands
		Array<D3D11Renderer2DCommand> m_commands;
		CurrentBatchStateChanges<D3D11Renderer2DCommandType> m_changes;

		// buffer
		Array<D3D11DrawCommand> m_draws;
		Array<uint32> m_nullDraws;
		Array<BlendState> m_blendStates				= { BlendState::Default };
		Array<RasterizerState> m_rasterizerStates	= { RasterizerState::Default2D };
		std::array<Array<SamplerState>, SamplerState::MaxSamplerCount> m_vsSamplerStates;
		std::array<Array<SamplerState>, SamplerState::MaxSamplerCount> m_psSamplerStates;
		Array<VertexShader::IDType> m_VSs;
		Array<PixelShader::IDType> m_PSs;

		// current
		D3D11DrawCommand m_currentDraw;
		BlendState m_currentBlendState				= m_blendStates.back();
		RasterizerState m_currentRasterizerState	= m_rasterizerStates.back();
		std::array<SamplerState, SamplerState::MaxSamplerCount> m_currentVSSamplerStates;
		std::array<SamplerState, SamplerState::MaxSamplerCount> m_currentPSSamplerStates;
		VertexShader::IDType m_currentVS			= VertexShader::IDType::InvalidValue();
		PixelShader::IDType m_currentPS				= PixelShader::IDType::InvalidValue();

		// reserved
		HashTable<VertexShader::IDType, VertexShader> m_reservedVSs;
		HashTable<PixelShader::IDType, PixelShader> m_reservedPSs;

	public:

		D3D11Renderer2DCommandManager();

		void reset();

		void flush();

		const Array<D3D11Renderer2DCommand>& getCommands() const noexcept;

		void pushUpdateBuffers(uint32 batchIndex);

		void pushDraw(Vertex2D::IndexType indexCount);
		const D3D11DrawCommand& getDraw(uint32 index) const noexcept;

		void pushNullVertices(uint32 count);
		uint32 getNullDraw(uint32 index) const noexcept;

		void pushBlendState(const BlendState& state);
		const BlendState& getBlendState(uint32 index) const;
		const BlendState& getCurrentBlendState() const;

		void pushRasterizerState(const RasterizerState& state);
		const RasterizerState& getRasterizerState(uint32 index) const;
		const RasterizerState& getCurrentRasterizerState() const;

		void pushVSSamplerState(const SamplerState& state, uint32 slot);
		const SamplerState& getVSSamplerState(uint32 slot, uint32 index) const;
		const SamplerState& getVSCurrentSamplerState(uint32 slot) const;

		void pushPSSamplerState(const SamplerState& state, uint32 slot);
		const SamplerState& getPSSamplerState(uint32 slot, uint32 index) const;
		const SamplerState& getPSCurrentSamplerState(uint32 slot) const;

		void pushStandardVS(const VertexShader::IDType& id);
		void pushCustomVS(const VertexShader& vs);
		const VertexShader::IDType& getVS(uint32 index) const;

		void pushStandardPS(const PixelShader::IDType& id);
		void pushCustomPS(const PixelShader& ps);
		const PixelShader::IDType& getPS(uint32 index) const;
	};
}
