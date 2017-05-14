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
# include <d3d11.h>
# include <Siv3D/Fwd.hpp>
# include <Siv3D/Array.hpp>
# include <Siv3D/Byte.hpp>
# include <Siv3D/BlendState.hpp>
# include <Siv3D/RasterizerState.hpp>
# include <Siv3D/SamplerState.hpp>
# include <Siv3D/Rectangle.hpp>
# include <Siv3D/Texture.hpp>
# include <Siv3D/RenderTexture.hpp>
# include <Siv3D/HashMap.hpp>
# include <Siv3D/PixelShader.hpp>
# include "../../Siv3DEngine.hpp"
# include "../../Graphics/IGraphics.hpp"
# include "../../Shader/IShader.hpp"

namespace s3d
{
	enum class D3D11Render2DInstruction : uint16
	{
		Nop,

		Draw,

		NextBatch,

		BlendState,

		RasterizerState,

		PSSamplerState,

		ScissorRect,

		Viewport,

		PixelShader,

		PSTexture,

		RenderTarget,
	};

	enum class D3D11Render2DPixelShaderType
	{
		Shape,

		Sprite,
	};

	struct D3D11Render2DCommandHeader
	{
		D3D11Render2DInstruction instruction;

		uint16 commandSize;
	};

	template <D3D11Render2DInstruction instruction>
	struct D3D11Render2DCommand;

	template <>
	struct D3D11Render2DCommand<D3D11Render2DInstruction::Draw>
	{
		D3D11Render2DCommandHeader header =
		{
			D3D11Render2DInstruction::Draw,

			sizeof(D3D11Render2DCommand<D3D11Render2DInstruction::Draw>)
		};

		uint32 indexSize;
	};

	template <>
	struct D3D11Render2DCommand<D3D11Render2DInstruction::NextBatch>
	{
		D3D11Render2DCommandHeader header =
		{
			D3D11Render2DInstruction::NextBatch,

			sizeof(D3D11Render2DCommand<D3D11Render2DInstruction::NextBatch>)
		};
	};

	template <>
	struct D3D11Render2DCommand<D3D11Render2DInstruction::BlendState>
	{
		D3D11Render2DCommandHeader header =
		{
			D3D11Render2DInstruction::BlendState,

			sizeof(D3D11Render2DCommand<D3D11Render2DInstruction::BlendState>)
		};

		BlendState blendState;
	};

	template <>
	struct D3D11Render2DCommand<D3D11Render2DInstruction::RasterizerState>
	{
		D3D11Render2DCommandHeader header =
		{
			D3D11Render2DInstruction::RasterizerState,

			sizeof(D3D11Render2DCommand<D3D11Render2DInstruction::RasterizerState>)
		};

		RasterizerState rasterizerState;
	};

	template <>
	struct D3D11Render2DCommand<D3D11Render2DInstruction::PSSamplerState>
	{
		D3D11Render2DCommandHeader header =
		{
			D3D11Render2DInstruction::PSSamplerState,

			sizeof(D3D11Render2DCommand<D3D11Render2DInstruction::PSSamplerState>)
		};

		SamplerState samplerState;

		uint32 slot;
	};

	template <>
	struct D3D11Render2DCommand<D3D11Render2DInstruction::ScissorRect>
	{
		D3D11Render2DCommandHeader header =
		{
			D3D11Render2DInstruction::ScissorRect,

			sizeof(D3D11Render2DCommand<D3D11Render2DInstruction::ScissorRect>)
		};

		Rect scissorRect;
	};

	template <>
	struct D3D11Render2DCommand<D3D11Render2DInstruction::Viewport>
	{
		D3D11Render2DCommandHeader header =
		{
			D3D11Render2DInstruction::Viewport,

			sizeof(D3D11Render2DCommand<D3D11Render2DInstruction::Viewport>)
		};

		Optional<Rect> viewport;
	};

	template <>
	struct D3D11Render2DCommand<D3D11Render2DInstruction::PixelShader>
	{
		D3D11Render2DCommandHeader header =
		{
			D3D11Render2DInstruction::PixelShader,

			sizeof(D3D11Render2DCommand<D3D11Render2DInstruction::PixelShader>)
		};

		PixelShader::IDType psID;
	};

	template <>
	struct D3D11Render2DCommand<D3D11Render2DInstruction::PSTexture>
	{
		D3D11Render2DCommandHeader header =
		{
			D3D11Render2DInstruction::PSTexture,

			sizeof(D3D11Render2DCommand<D3D11Render2DInstruction::PSTexture>)
		};

		uint32 slot;

		Texture::IDType textureID;
	};

	template <>
	struct D3D11Render2DCommand<D3D11Render2DInstruction::RenderTarget>
	{
		D3D11Render2DCommandHeader header =
		{
			D3D11Render2DInstruction::RenderTarget,

			sizeof(D3D11Render2DCommand<D3D11Render2DInstruction::RenderTarget>)
		};

		Texture::IDType textureID;
	};

	class D3D11Render2DCommandManager
	{
	private:

		static constexpr uint32 MaxSamplerCount = SamplerState::MaxSamplerCount;

		Array<Byte> m_commands;

		size_t m_commandCount = 0;

		Byte* m_lastCommandPointer = nullptr;

		D3D11Render2DInstruction m_lastCommand = D3D11Render2DInstruction::Nop;

		BlendState m_currentBlendState = BlendState::Default;

		RasterizerState m_currentRasterizerState = RasterizerState::Default2D;

		std::array<SamplerState, SamplerState::MaxSamplerCount> m_currentVSSamplers;

		std::array<SamplerState, SamplerState::MaxSamplerCount> m_currentPSSamplers;

		Rect m_currentScissorRect = { 0, 0, 0, 0 };

		Optional<Rect> m_currentViewport;

		Optional<D3D11Render2DPixelShaderType> m_currentPSType;

		HashMap<Texture::IDType, Texture> m_reservedTextures;

		std::array<Texture::IDType, MaxSamplerCount> m_currentPSTextures;

		RenderTexture m_currentRenderTarget;

		template <class Command>
		void writeCommand(const Command& command)
		{
			static_assert(sizeof(Command) % 4 == 0);
			
			const Byte* dataBegin = static_cast<const Byte*>(static_cast<const void*>(&command));

			const Byte* dataEnd = dataBegin + sizeof(Command);

			m_commands.insert(m_commands.end(), dataBegin, dataEnd);

			++m_commandCount;

			m_lastCommandPointer = m_commands.data() + (m_commands.size() - sizeof(Command));

			m_lastCommand = command.header.instruction;
		}

		template <D3D11Render2DInstruction instruction>
		D3D11Render2DCommand<instruction>& getLastCommand()
		{
			return *static_cast<D3D11Render2DCommand<instruction>*>(static_cast<void*>(m_lastCommandPointer));
		}

	public:
		
		D3D11Render2DCommandManager();

		~D3D11Render2DCommandManager();

		size_t getCount() const
		{
			return m_commandCount;
		}

		const Byte* getCommandBuffer() const
		{
			return m_commands.data();
		}

		void reset();

		void pushDraw(const uint32 indexSize, D3D11Render2DPixelShaderType ps);

		void pushNextBatch();

		void pushBlendState(const BlendState& state);

		void pushRasterizerState(const RasterizerState& state);

		void pushPSSamplerState(uint32 slot, const SamplerState& state);

		void pushScissorRect(const Rect& scissorRect);

		void pushViewport(const Optional<Rect>& viewport);

		void pushPSTexture(const uint32 slot, const Texture& texture);

		void pushRenderTarget(const RenderTexture& texture);

		const BlendState& getCurrentBlendState() const
		{
			return m_currentBlendState;
		}

		const RasterizerState& getCurrentRasterizerState() const
		{
			return m_currentRasterizerState;
		}

		const std::array<SamplerState, SamplerState::MaxSamplerCount>& getCurrentVSSamplerStates() const
		{
			return m_currentVSSamplers;
		}

		const std::array<SamplerState, SamplerState::MaxSamplerCount>& getCurrentPSSamplerStates() const
		{
			return m_currentPSSamplers;
		}

		Rect getCurrentScissorRect() const
		{
			return m_currentScissorRect;
		}

		const Optional<Rect>& getCurrentViewport() const
		{
			return m_currentViewport;
		}
	};
}

# endif
