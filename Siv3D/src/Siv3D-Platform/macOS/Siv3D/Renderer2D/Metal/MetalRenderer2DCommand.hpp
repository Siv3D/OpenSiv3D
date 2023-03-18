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
# include <Siv3D/ShaderStage.hpp>
# include <Siv3D/ConstantBuffer.hpp>
# include <Siv3D/Mat3x2.hpp>
# include <Siv3D/Renderer2D/CurrentBatchStateChanges.hpp>

namespace s3d
{
	enum class MetalRenderer2DCommandType : uint32
	{
		Null,

		SetBuffers,

		UpdateBuffers,

		Draw,

		DrawNull,

		ColorMul,

		ColorAdd,
		
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

		Transform,
		
		SetConstantBuffer,
	};

	struct MetalRenderer2DCommand
	{
		MetalRenderer2DCommandType type = MetalRenderer2DCommandType::Null;

		uint32 index = 0;
		
		MetalRenderer2DCommand() = default;
		
		constexpr MetalRenderer2DCommand(MetalRenderer2DCommandType _type, uint32 _index) noexcept
			: type(_type)
			, index(_index) {}
	};

	struct MetalDrawCommand
	{
		uint32 indexCount = 0;
	};

	struct MetalConstantBufferCommand
	{
		ShaderStage stage	= ShaderStage::Vertex;
		uint32 slot			= 0;
		uint32 offset		= 0;
		uint32 num_vectors	= 0;
		uint32 cbBaseIndex	= 0;
		ConstantBufferBase cbBase;
	};

	class MetalRenderer2DCommandManager
	{
	private:

		// commands
		Array<MetalRenderer2DCommand> m_commands;
		CurrentBatchStateChanges<MetalRenderer2DCommandType> m_changes;

		// buffer
		Array<MetalDrawCommand> m_draws;
		Array<uint32> m_nullDraws;
		Array<Float4> m_colorMuls					= { Float4{ 1.0f, 1.0f, 1.0f, 1.0f } };
		Array<Float4> m_colorAdds					= { Float4{ 0.0f, 0.0f, 0.0f, 0.0f } };
		Array<BlendState> m_blendStates				= { BlendState::Default2D };
		Array<RasterizerState> m_rasterizerStates	= { RasterizerState::Default2D };
		std::array<Array<SamplerState>, SamplerState::MaxSamplerCount> m_vsSamplerStates;
		std::array<Array<SamplerState>, SamplerState::MaxSamplerCount> m_psSamplerStates;
		Array<VertexShader::IDType> m_VSs;
		Array<PixelShader::IDType> m_PSs;
		Array<Mat3x2> m_combinedTransforms = { Mat3x2::Identity() };
		Array<__m128> m_constants;
		Array<MetalConstantBufferCommand> m_constantBufferCommands;

		// current
		MetalDrawCommand m_currentDraw;
		Float4 m_currentColorMul					= m_colorMuls.back();
		Float4 m_currentColorAdd					= m_colorAdds.back();
		BlendState m_currentBlendState				= m_blendStates.back();
		RasterizerState m_currentRasterizerState	= m_rasterizerStates.back();
		std::array<SamplerState, SamplerState::MaxSamplerCount> m_currentVSSamplerStates;
		std::array<SamplerState, SamplerState::MaxSamplerCount> m_currentPSSamplerStates;
		VertexShader::IDType m_currentVS			= VertexShader::IDType::InvalidValue();
		PixelShader::IDType m_currentPS				= PixelShader::IDType::InvalidValue();
		Mat3x2 m_currentLocalTransform				= Mat3x2::Identity();
		Mat3x2 m_currentCameraTransform				= Mat3x2::Identity();
		Mat3x2 m_currentCombinedTransform			= Mat3x2::Identity();
		float m_currentMaxScaling					= 1.0f;

		// reserved
		HashTable<VertexShader::IDType, VertexShader> m_reservedVSs;
		HashTable<PixelShader::IDType, PixelShader> m_reservedPSs;

	public:

		MetalRenderer2DCommandManager();

		void reset();

		void flush();

		const Array<MetalRenderer2DCommand>& getCommands() const noexcept;

		void pushUpdateBuffers(uint32 batchIndex);

		void pushDraw(Vertex2D::IndexType indexCount);
		const MetalDrawCommand& getDraw(uint32 index) const noexcept;

		void pushNullVertices(uint32 count);
		uint32 getNullDraw(uint32 index) const noexcept;

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

		void pushLocalTransform(const Mat3x2& local);
		const Mat3x2& getCurrentLocalTransform() const;

		void pushCameraTransform(const Mat3x2& camera);
		const Mat3x2& getCurrentCameraTransform() const;

		const Mat3x2& getCombinedTransform(uint32 index) const;
		const Mat3x2& getCurrentCombinedTransform() const;
		float getCurrentMaxScaling() const noexcept;
		
		void pushConstantBuffer(ShaderStage stage, uint32 slot, const ConstantBufferBase& buffer, const float* data, uint32 num_vectors);
		MetalConstantBufferCommand& getConstantBuffer(uint32 index);
		const __m128* getConstantBufferPtr(uint32 offset) const;
	};
}
