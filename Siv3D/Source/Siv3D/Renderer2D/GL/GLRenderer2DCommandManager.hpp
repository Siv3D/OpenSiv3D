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
# if defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

# include <Siv3D/Fwd.hpp>
# include <Siv3D/Array.hpp>
# include <Siv3D/Byte.hpp>
# include <Siv3D/BlendState.hpp>
# include <Siv3D/RasterizerState.hpp>
# include <Siv3D/SamplerState.hpp>
# include <Siv3D/PixelShader.hpp>
# include <Siv3D/Texture.hpp>
# include <Siv3D/HashMap.hpp>
# include "../../Siv3DEngine.hpp"
# include "../../Shader/IShader.hpp"

namespace s3d
{
	enum class GLRender2DInstruction : uint16
	{
		Nop,

		Draw,

		NextBatch,

		BlendState,
		
		RasterizerState,
		
		SamplerState,

		ScissorRect,
		
		Viewport,
		
		PixelShader,
		
		PSTexture,
	};
	
	enum class GLRender2DPixelShaderType
	{
		Shape,
		
		Sprite,
	};

	struct GLRender2DCommandHeader
	{
		GLRender2DInstruction instruction;

		uint16 commandSize;
	};

	template <GLRender2DInstruction instruction>
	struct GLRender2DCommand;

	template <>
	struct GLRender2DCommand<GLRender2DInstruction::Draw>
	{
		GLRender2DCommandHeader header =
		{
			GLRender2DInstruction::Draw,

			sizeof(GLRender2DCommand<GLRender2DInstruction::Draw>)
		};

		uint32 indexSize;
	};

	template <>
	struct GLRender2DCommand<GLRender2DInstruction::NextBatch>
	{
		GLRender2DCommandHeader header =
		{
			GLRender2DInstruction::NextBatch,

			sizeof(GLRender2DCommand<GLRender2DInstruction::NextBatch>)
		};
	};

	template <>
	struct GLRender2DCommand<GLRender2DInstruction::BlendState>
	{
		GLRender2DCommandHeader header =
		{
			GLRender2DInstruction::BlendState,

			sizeof(GLRender2DCommand<GLRender2DInstruction::BlendState>)
		};

		BlendState blendState;
	};
	
	template <>
	struct GLRender2DCommand<GLRender2DInstruction::RasterizerState>
	{
		GLRender2DCommandHeader header =
		{
			GLRender2DInstruction::RasterizerState,
			
			sizeof(GLRender2DCommand<GLRender2DInstruction::RasterizerState>)
		};
		
		RasterizerState rasterizerState;
	};
	
	template <>
	struct GLRender2DCommand<GLRender2DInstruction::SamplerState>
	{
		GLRender2DCommandHeader header =
		{
			GLRender2DInstruction::SamplerState,
			
			sizeof(GLRender2DCommand<GLRender2DInstruction::SamplerState>)
		};
		
		SamplerState samplerState;
		
		uint32 slot;
	};
	
	template <>
	struct GLRender2DCommand<GLRender2DInstruction::ScissorRect>
	{
		GLRender2DCommandHeader header =
		{
			GLRender2DInstruction::ScissorRect,

			sizeof(GLRender2DCommand<GLRender2DInstruction::ScissorRect>)
		};

		Rect scissorRect;
	};
	
	template <>
	struct GLRender2DCommand<GLRender2DInstruction::Viewport>
	{
		GLRender2DCommandHeader header =
		{
			GLRender2DInstruction::Viewport,
			
			sizeof(GLRender2DCommand<GLRender2DInstruction::Viewport>)
		};
		
		Optional<Rect> viewport;
	};
	
	template <>
	struct GLRender2DCommand<GLRender2DInstruction::PixelShader>
	{
		GLRender2DCommandHeader header =
		{
			GLRender2DInstruction::PixelShader,
			
			sizeof(GLRender2DCommand<GLRender2DInstruction::PixelShader>)
		};

		PixelShader::IDType psID;
	};
	
	template <>
	struct GLRender2DCommand<GLRender2DInstruction::PSTexture>
	{
		GLRender2DCommandHeader header =
		{
			GLRender2DInstruction::PSTexture,
			
			sizeof(GLRender2DCommand<GLRender2DInstruction::PSTexture>)
		};
		
		uint32 slot;
		
		Texture::IDType textureID;
	};

	class GLRender2DCommandManager
	{
	private:

		static constexpr uint32 MaxSamplerCount = SamplerState::MaxSamplerCount;
		
		Array<Byte> m_commands;

		size_t m_commandCount = 0;

		Byte* m_lastCommandPointer = nullptr;

		GLRender2DInstruction m_lastCommand = GLRender2DInstruction::Nop;

		BlendState m_currentBlendState = BlendState::Default;
		
		RasterizerState m_currentRasterizerState = RasterizerState::Default2D;
		
		std::array<SamplerState, SamplerState::MaxSamplerCount> m_currentSamplerStates;
		
		Rect m_currentScissorRect = { 0, 0, 0, 0 };

		Optional<Rect> m_currentViewport;
		
		Optional<GLRender2DPixelShaderType> m_currentPSType;

		HashMap<Texture::IDType, Texture> m_reservedTextures;
		
		std::array<Texture::IDType, MaxSamplerCount> m_currentPSTextures;
		
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

		template <GLRender2DInstruction instruction>
		GLRender2DCommand<instruction>& getLastCommand()
		{
			return *static_cast<GLRender2DCommand<instruction>*>(static_cast<void*>(m_lastCommandPointer));
		}

	public:
		
		GLRender2DCommandManager()
		{
			m_currentSamplerStates.fill(SamplerState::Default2D);
		}

		size_t getCount() const
		{
			return m_commandCount;
		}

		const Byte* getCommandBuffer() const
		{
			return m_commands.data();
		}

		void reset()
		{
			m_commands.clear();

			m_commandCount = 0;
			
			m_reservedTextures.clear();

			pushNextBatch();

			{
				GLRender2DCommand<GLRender2DInstruction::BlendState> command;
				command.blendState = m_currentBlendState;
				writeCommand(command);
			}
			
			{
				GLRender2DCommand<GLRender2DInstruction::RasterizerState> command;
				command.rasterizerState = m_currentRasterizerState;
				writeCommand(command);
			}

			{
				GLRender2DCommand<GLRender2DInstruction::ScissorRect> command;
				command.scissorRect = m_currentScissorRect;
				writeCommand(command);
			}
			
			{
				GLRender2DCommand<GLRender2DInstruction::Viewport> command;
				command.viewport = m_currentViewport;
				writeCommand(command);
			}
			
			m_currentPSType.reset();
			
			for (uint32 slot = 0; slot < m_currentPSTextures.size(); ++slot)
			{
				m_currentPSTextures[slot] = Texture::NullHandleID;
				GLRender2DCommand<GLRender2DInstruction::PSTexture> command;
				command.slot = slot;
				command.textureID = Texture::NullHandleID;
				writeCommand(command);
			}
		}

		void pushDraw(const uint32 indexSize, GLRender2DPixelShaderType ps)
		{
			bool shaderChanged = false;
			
			if (ps != m_currentPSType)
			{
				GLRender2DCommand<GLRender2DInstruction::PixelShader> command;
				command.psID = Siv3DEngine::GetShader()->getStandardPS(static_cast<size_t>(ps)).id();
				writeCommand(command);
				
				m_currentPSType = ps;
				shaderChanged = true;
			}
			
			if (!shaderChanged && m_lastCommand == GLRender2DInstruction::Draw)
			{
				getLastCommand<GLRender2DInstruction::Draw>().indexSize += indexSize;
				
				return;
			}

			GLRender2DCommand<GLRender2DInstruction::Draw> command;
			command.indexSize = indexSize;
			writeCommand(command);
		}

		void pushNextBatch()
		{
			writeCommand(GLRender2DCommand<GLRender2DInstruction::NextBatch>());
		}

		void pushBlendState(const BlendState& state)
		{
			if (state == m_currentBlendState)
			{
				return;
			}

			GLRender2DCommand<GLRender2DInstruction::BlendState> command;
			command.blendState = state;
			writeCommand(command);

			m_currentBlendState = state;
		}
		
		void pushRasterizerState(const RasterizerState& state)
		{
			if (state == m_currentRasterizerState)
			{
				return;
			}
			
			GLRender2DCommand<GLRender2DInstruction::RasterizerState> command;
			command.rasterizerState = state;
			writeCommand(command);
			
			m_currentRasterizerState = state;
		}
		
		void pushSamplerState(const uint32 slot, const SamplerState& state)
		{
			assert(slot < MaxSamplerCount);
			
			if (state == m_currentSamplerStates[slot])
			{
				return;
			}
			
			GLRender2DCommand<GLRender2DInstruction::SamplerState> command;
			command.samplerState = state;
			command.slot = slot;
			writeCommand(command);
			
			m_currentSamplerStates[slot] = state;
		}

		void pushScissorRect(const Rect& scissorRect)
		{
			if (scissorRect == m_currentScissorRect)
			{
				return;
			}

			GLRender2DCommand<GLRender2DInstruction::ScissorRect> command;
			command.scissorRect = scissorRect;
			writeCommand(command);

			m_currentScissorRect = scissorRect;
		}
		
		void pushViewport(const Optional<Rect>& viewport)
		{
			if (viewport == m_currentViewport)
			{
				return;
			}
			
			GLRender2DCommand<GLRender2DInstruction::Viewport> command;
			command.viewport = viewport;
			writeCommand(command);
			
			m_currentViewport = viewport;
		}
		
		void pushPSTexture(const uint32 slot, const Texture& texture)
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
			
			GLRender2DCommand<GLRender2DInstruction::PSTexture> command;
			command.slot = slot;
			command.textureID = id;
			writeCommand(command);
			
			m_currentPSTextures[slot] = id;
		}

		const BlendState& getCurrentBlendState() const
		{
			return m_currentBlendState;
		}
		
		const RasterizerState& getCurrentRasterizerState() const
		{
			return m_currentRasterizerState;
		}
		
		const std::array<SamplerState, SamplerState::MaxSamplerCount>& getSamplerStates() const
		{
			return m_currentSamplerStates;
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
