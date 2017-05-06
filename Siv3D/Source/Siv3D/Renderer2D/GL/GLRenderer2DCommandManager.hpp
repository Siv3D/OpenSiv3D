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

namespace s3d
{
	enum class GLRender2DInstruction : uint16
	{
		Nop,

		Draw,

		NextBatch,

		BlendState,
		
		RasterizerState,
		
		Viewport,
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
	struct GLRender2DCommand<GLRender2DInstruction::Viewport>
	{
		GLRender2DCommandHeader header =
		{
			GLRender2DInstruction::Viewport,
			
			sizeof(GLRender2DCommand<GLRender2DInstruction::Viewport>)
		};
		
		Optional<Rect> viewport;
	};

	class GLRender2DCommandManager
	{
	private:

		Array<Byte> m_commands;

		size_t m_commandCount = 0;

		Byte* m_lastCommandPointer = nullptr;

		GLRender2DInstruction m_lastCommand = GLRender2DInstruction::Nop;

		BlendState m_currentBlendState = BlendState::Default;
		
		RasterizerState m_currentRasterizerState = RasterizerState::Default2D;
		
		Optional<Rect> m_currentViewport;

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
				GLRender2DCommand<GLRender2DInstruction::Viewport> command;
				command.viewport = m_currentViewport;
				writeCommand(command);
			}
		}

		void pushDraw(const uint32 indexSize)
		{
			if (m_lastCommand == GLRender2DInstruction::Draw)
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

		const BlendState& getCurrentBlendState() const
		{
			return m_currentBlendState;
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
		
		const RasterizerState& getCurrentRasterizerState() const
		{
			return m_currentRasterizerState;
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
		
		Optional<Rect> getCurrentViewport() const
		{
			return m_currentViewport;
		}
	};
}

# endif
