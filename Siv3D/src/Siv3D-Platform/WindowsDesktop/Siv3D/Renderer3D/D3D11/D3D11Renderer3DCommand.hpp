//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Common.hpp>
# include <Siv3D/Array.hpp>
# include <Siv3D/Optional.hpp>
# include <Siv3D/HashTable.hpp>
# include <Siv3D/BlendState.hpp>
# include <Siv3D/RasterizerState.hpp>
# include <Siv3D/SamplerState.hpp>
# include <Siv3D/DepthStencilState.hpp>
# include <Siv3D/RenderTexture.hpp>
# include <Siv3D/ShaderStage.hpp>
# include <Siv3D/ConstantBuffer.hpp>
# include <Siv3D/VertexShader.hpp>
# include <Siv3D/PixelShader.hpp>
# include <Siv3D/2DShapes.hpp>
# include <Siv3D/Mesh.hpp>
# include <Siv3D/Renderer2D/CurrentBatchStateChanges.hpp>

namespace s3d
{
	enum class D3D11Renderer3DCommandType : uint32
	{
		Null,

		Draw,

		BlendState,

		RasterizerState,

		DepthStencilState,

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

		ScissorRect,

		Viewport,

		SetRT,

		SetVS,

		SetPS,

		CameraTransform,

		SetConstantBuffer,

		VSTexture0,

		VSTexture1,

		VSTexture2,

		VSTexture3,

		VSTexture4,

		VSTexture5,

		VSTexture6,

		VSTexture7,

		PSTexture0,

		PSTexture1,

		PSTexture2,

		PSTexture3,

		PSTexture4,

		PSTexture5,

		PSTexture6,

		PSTexture7,

		SetMesh,

		SIZE_,
	};
	static_assert(FromEnum(D3D11Renderer3DCommandType::SIZE_) < 64);

	struct D3D11Renderer3DCommand
	{
		D3D11Renderer3DCommandType type = D3D11Renderer3DCommandType::Null;

		uint32 index = 0;
	};

	struct D3D11Draw3DCommand
	{
		uint32 startIndex = 0;
		
		uint32 indexCount = 0;

		uint32 instanceCount = 0;
	};

	struct D3D11ConstantBuffer3DCommand
	{
		ShaderStage stage = ShaderStage::Vertex;
		uint32 slot = 0;
		uint32 offset = 0;
		uint32 num_vectors = 0;
		uint32 cbBaseIndex = 0;
		ConstantBufferBase cbBase;
	};

	class D3D11Renderer3DCommandManager
	{
	private:

		// commands
		Array<D3D11Renderer3DCommand> m_commands;
		CurrentBatchStateChanges<D3D11Renderer3DCommandType> m_changes;

		// buffer
		Array<D3D11Draw3DCommand> m_draws;
		//Array<uint32> m_nullDraws;
		Array<Mat4x4> m_drawLocalToWorlds;
		Array<Float4> m_drawDiffuses;
		Array<BlendState> m_blendStates				= { BlendState::Default };
		Array<RasterizerState> m_rasterizerStates	= { RasterizerState::Default3D };
		Array<DepthStencilState> m_depthStencilStates	= { DepthStencilState::Default3D };
		std::array<Array<SamplerState>, SamplerState::MaxSamplerCount> m_vsSamplerStates;
		std::array<Array<SamplerState>, SamplerState::MaxSamplerCount> m_psSamplerStates;
		Array<Rect> m_scissorRects					= { Rect{0} };
		Array<Optional<Rect>> m_viewports			= { none };
		//Array<std::array<Float4, 3>> m_sdfParams	= { { Float4{ 0.5f, 0.5f, 0.0f, 0.0f }, Float4{ 0.0f, 0.0f, 0.0f, 1.0f }, Float4{ 0.0f, 0.0f, 0.0f, 0.5f } } };
		Array<Optional<RenderTexture>> m_RTs		= { none };
		Array<VertexShader::IDType> m_VSs;	
		Array<PixelShader::IDType> m_PSs;
		Array<Mat4x4> m_cameraTransforms			= { Mat4x4::Identity() };
		Array<__m128> m_constants;
		Array<D3D11ConstantBuffer3DCommand> m_constantBufferCommands;
		std::array<Array<Texture::IDType>, SamplerState::MaxSamplerCount> m_vsTextures;
		std::array<Array<Texture::IDType>, SamplerState::MaxSamplerCount> m_psTextures;
		Array<Mesh::IDType> m_meshes;

		// current
		BlendState m_currentBlendState				= m_blendStates.back();
		RasterizerState m_currentRasterizerState	= m_rasterizerStates.back();
		DepthStencilState m_currentDepthStencilState	= m_depthStencilStates.back();
		std::array<SamplerState, SamplerState::MaxSamplerCount> m_currentVSSamplerStates;
		std::array<SamplerState, SamplerState::MaxSamplerCount> m_currentPSSamplerStates;
		Rect m_currentScissorRect					= m_scissorRects.front();
		Optional<Rect> m_currentViewport			= m_viewports.front();
		//std::array<Float4, 3> m_currentSDFParams	= m_sdfParams.front();
		Optional<RenderTexture> m_currentRT			= m_RTs.front();
		VertexShader::IDType m_currentVS			= VertexShader::IDType::InvalidValue();
		PixelShader::IDType m_currentPS				= PixelShader::IDType::InvalidValue();
		Mat4x4 m_currentCameraTransform				= Mat4x4::Identity();
		std::array<Texture::IDType, SamplerState::MaxSamplerCount> m_currentVSTextures;
		std::array<Texture::IDType, SamplerState::MaxSamplerCount> m_currentPSTextures;
		Mesh::IDType m_currentMesh;

		// reserved
		HashTable<VertexShader::IDType, VertexShader> m_reservedVSs;
		HashTable<PixelShader::IDType, PixelShader> m_reservedPSs;
		HashTable<Texture::IDType, Texture> m_reservedTextures;
		HashTable<Mesh::IDType, Mesh> m_reservedMeshes;

	public:

		D3D11Renderer3DCommandManager();

		void reset();

		void flush();

		bool hasDraw() const noexcept;

		const Array<D3D11Renderer3DCommand>& getCommands() const noexcept;

		void pushDraw(uint32 startIndex, uint32 indexCount, const Mat4x4* mat, const Float4* color, uint32 instanceCount);
		const D3D11Draw3DCommand& getDraw(uint32 index) const noexcept;
		const Mat4x4& getDrawLocalToWorld(uint32 index) const noexcept;
		const Float4& getDrawDiffuse(uint32 index) const noexcept;

		//void pushNullVertices(uint32 count);
		//uint32 getNullDraw(uint32 index) const noexcept;

		void pushBlendState(const BlendState& state);
		const BlendState& getBlendState(uint32 index) const;
		const BlendState& getCurrentBlendState() const;

		void pushRasterizerState(const RasterizerState& state);
		const RasterizerState& getRasterizerState(uint32 index) const;
		const RasterizerState& getCurrentRasterizerState() const;

		void pushDepthStencilState(const DepthStencilState& state);
		const DepthStencilState& getDepthStencilState(uint32 index) const;
		const DepthStencilState& getCurrentDepthStencilState() const;

		void pushVSSamplerState(const SamplerState& state, uint32 slot);
		const SamplerState& getVSSamplerState(uint32 slot, uint32 index) const;
		const SamplerState& getVSCurrentSamplerState(uint32 slot) const;

		void pushPSSamplerState(const SamplerState& state, uint32 slot);
		const SamplerState& getPSSamplerState(uint32 slot, uint32 index) const;
		const SamplerState& getPSCurrentSamplerState(uint32 slot) const;

		void pushScissorRect(const Rect& state);
		const Rect& getScissorRect(uint32 index) const;
		const Rect& getCurrentScissorRect() const;

		void pushViewport(const Optional<Rect>& state);
		const Optional<Rect>& getViewport(uint32 index) const;
		const Optional<Rect>& getCurrentViewport() const;

		//void pushSDFParameters(const std::array<Float4, 3>& state);
		//const std::array<Float4, 3>& getSDFParameters(uint32 index) const;
		//const std::array<Float4, 3>& getCurrentSDFParameters() const;

		void pushStandardVS(const VertexShader::IDType& id);
		void pushCustomVS(const VertexShader& vs);
		const VertexShader::IDType& getVS(uint32 index) const;

		void pushStandardPS(const PixelShader::IDType& id);
		void pushCustomPS(const PixelShader& ps);
		const PixelShader::IDType& getPS(uint32 index) const;

		void pushCameraTransform(const Mat4x4& state);
		const Mat4x4& getCurrentCameraTransform() const;
		const Mat4x4& getCameraTransform(uint32 index) const;

		void pushConstantBuffer(ShaderStage stage, uint32 slot, const ConstantBufferBase& buffer, const float* data, uint32 num_vectors);
		D3D11ConstantBuffer3DCommand& getConstantBuffer(uint32 index);
		const __m128* getConstantBufferPtr(uint32 offset) const;

		void pushVSTextureUnbind(uint32 slot);
		void pushVSTexture(uint32 slot, const Texture& texture);
		const Texture::IDType& getVSTexture(uint32 slot, uint32 index) const;
		const std::array<Texture::IDType, SamplerState::MaxSamplerCount>& getCurrentVSTextures() const;

		void pushPSTextureUnbind(uint32 slot);
		void pushPSTexture(uint32 slot, const Texture& texture);
		const Texture::IDType& getPSTexture(uint32 slot, uint32 index) const;
		const std::array<Texture::IDType, SamplerState::MaxSamplerCount>& getCurrentPSTextures() const;

		void pushRT(const Optional<RenderTexture>& rt);
		const Optional<RenderTexture>& getRT(uint32 index) const;
		const Optional<RenderTexture>& getCurrentRT() const;

		void pushMesh(const Mesh& mesh);
		const Mesh::IDType& getMesh(uint32 index) const;
		const Mesh::IDType& getCurrentMesh() const;
	};
}
