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

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_WINDOWS)

# include "D3D11Renderer2DCommandManager.hpp"

namespace s3d
{
	D3D11Render2DCommandManager::D3D11Render2DCommandManager()
	{
		m_currentVSSamplers.fill(SamplerState::Default2D);
		m_currentPSSamplers.fill(SamplerState::Default2D);
	}
	
	D3D11Render2DCommandManager::~D3D11Render2DCommandManager()
	{
		m_currentPSSamplers.fill(SamplerState::Default2D);
	}

	void D3D11Render2DCommandManager::reset()
	{
		m_commands.clear();

		m_commandCount = 0;

		m_reservedTextures.clear();

		pushNextBatch();

		{
			D3D11Render2DCommand<D3D11Render2DInstruction::BlendState> command;
			command.blendState = m_currentBlendState;
			writeCommand(command);
		}

		{
			D3D11Render2DCommand<D3D11Render2DInstruction::RasterizerState> command;
			command.rasterizerState = m_currentRasterizerState;
			writeCommand(command);
		}

		for (uint32 slot = 0; slot < m_currentPSSamplers.size(); ++slot)
		{
			D3D11Render2DCommand<D3D11Render2DInstruction::PSSamplerState> command;
			command.samplerState = m_currentPSSamplers[slot];
			command.slot = slot;
			writeCommand(command);
		}

		for (uint32 slot = 0; slot < m_currentVSSamplers.size(); ++slot)
		{
			//m_commands.emplace_back(slot, m_currentVSSamplers[slot], InstructionTag<D3D11Render2DInstruction::VSSampler>{});
		}

		{
			const RenderTexture& backBuffer2D = Siv3DEngine::GetGraphics()->getBackBuffer2D();
			m_currentRenderTarget = backBuffer2D;
			m_reservedTextures.emplace(backBuffer2D.id(), backBuffer2D);

			D3D11Render2DCommand<D3D11Render2DInstruction::RenderTarget> command;
			command.textureID = backBuffer2D.id();
			writeCommand(command);
		}

		{
			D3D11Render2DCommand<D3D11Render2DInstruction::ScissorRect> command;
			command.scissorRect = m_currentScissorRect;
			writeCommand(command);
		}

		{
			D3D11Render2DCommand<D3D11Render2DInstruction::Viewport> command;
			command.viewport = m_currentViewport;
			writeCommand(command);
		}

		m_currentPSType.reset();

		for (uint32 slot = 0; slot < m_currentPSTextures.size(); ++slot)
		{
			m_currentPSTextures[slot] = Texture::NullHandleID;
			D3D11Render2DCommand<D3D11Render2DInstruction::PSTexture> command;
			command.slot = slot;
			command.textureID = Texture::NullHandleID;
			writeCommand(command);
		}
	}

	void D3D11Render2DCommandManager::pushDraw(const uint32 indexSize, const D3D11Render2DPixelShaderType ps)
	{
		bool shaderChanged = false;

		if (ps != m_currentPSType)
		{
			D3D11Render2DCommand<D3D11Render2DInstruction::PixelShader> command;
			command.psID = Siv3DEngine::GetShader()->getStandardPS(static_cast<size_t>(ps)).id();
			writeCommand(command);

			m_currentPSType = ps;
			shaderChanged = true;
		}

		if (!shaderChanged && m_lastCommand == D3D11Render2DInstruction::Draw)
		{
			getLastCommand<D3D11Render2DInstruction::Draw>().indexSize += indexSize;

			return;
		}

		D3D11Render2DCommand<D3D11Render2DInstruction::Draw> command;
		command.indexSize = indexSize;
		writeCommand(command);
	}

	void D3D11Render2DCommandManager::pushNextBatch()
	{
		writeCommand(D3D11Render2DCommand<D3D11Render2DInstruction::NextBatch>());
	}

	void D3D11Render2DCommandManager::pushBlendState(const BlendState& state)
	{
		if (state == m_currentBlendState)
		{
			return;
		}

		D3D11Render2DCommand<D3D11Render2DInstruction::BlendState> command;
		command.blendState = state;
		writeCommand(command);

		m_currentBlendState = state;
	}

	void D3D11Render2DCommandManager::pushRasterizerState(const RasterizerState& state)
	{
		if (state == m_currentRasterizerState)
		{
			return;
		}

		D3D11Render2DCommand<D3D11Render2DInstruction::RasterizerState> command;
		command.rasterizerState = state;
		writeCommand(command);

		m_currentRasterizerState = state;
	}

	void D3D11Render2DCommandManager::pushPSSamplerState(const uint32 slot, const SamplerState& state)
	{
		assert(slot < MaxSamplerCount);

		if (state == m_currentPSSamplers[slot])
		{
			return;
		}

		D3D11Render2DCommand<D3D11Render2DInstruction::PSSamplerState> command;
		command.samplerState = state;
		command.slot = slot;
		writeCommand(command);

		m_currentPSSamplers[slot] = state;
	}

	void D3D11Render2DCommandManager::pushScissorRect(const Rect& scissorRect)
	{
		if (scissorRect == m_currentScissorRect)
		{
			return;
		}

		D3D11Render2DCommand<D3D11Render2DInstruction::ScissorRect> command;
		command.scissorRect = scissorRect;
		writeCommand(command);

		m_currentScissorRect = scissorRect;
	}

	void D3D11Render2DCommandManager::pushViewport(const Optional<Rect>& viewport)
	{
		if (viewport == m_currentViewport)
		{
			return;
		}

		D3D11Render2DCommand<D3D11Render2DInstruction::Viewport> command;
		command.viewport = viewport;
		writeCommand(command);

		m_currentViewport = viewport;
	}

	void D3D11Render2DCommandManager::pushPSTexture(const uint32 slot, const Texture& texture)
	{
		assert(slot < MaxSamplerCount);

		const auto id = texture.id();

		if (id == m_currentPSTextures[slot])
		{
			return;
		}

		if (m_reservedTextures.find(id) == m_reservedTextures.end())
		{
			m_reservedTextures.emplace(id, texture);
		}

		D3D11Render2DCommand<D3D11Render2DInstruction::PSTexture> command;
		command.slot = slot;
		command.textureID = id;
		writeCommand(command);

		m_currentPSTextures[slot] = id;
	}

	void D3D11Render2DCommandManager::pushRenderTarget(const RenderTexture& texture)
	{
		const auto id = texture.id();

		if (id == m_currentRenderTarget.id())
		{
			return;
		}

		if (m_reservedTextures.find(id) == m_reservedTextures.end())
		{
			m_reservedTextures.emplace(id, texture);
		}

		D3D11Render2DCommand<D3D11Render2DInstruction::RenderTarget> command;
		command.textureID = id;
		writeCommand(command);

		m_currentRenderTarget = texture;
	}
}

# endif
