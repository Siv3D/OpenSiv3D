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
# include <Siv3D/Vertex2D.hpp>
# include <Siv3D/Renderer2D/CurrentBatchStateChanges.hpp>

namespace s3d
{
	enum class GL4Renderer2DCommandType : uint32
	{
		Null,

		SetBuffers,

		UpdateBuffers,

		Draw,
	};

	struct GL4Renderer2DCommand
	{
		GL4Renderer2DCommandType type = GL4Renderer2DCommandType::Null;

		uint32 index = 0;
		
		GL4Renderer2DCommand() = default;
		
		constexpr GL4Renderer2DCommand(GL4Renderer2DCommandType _type, uint32 _index) noexcept
			: type(_type)
			, index(_index) {}
	};

	struct GL4DrawCommand
	{
		uint32 indexCount = 0;
	};

	class GL4Renderer2DCommandManager
	{
	private:

		Array<GL4Renderer2DCommand> m_commands;

		CurrentBatchStateChanges<GL4Renderer2DCommandType> m_changes;

		Array<GL4DrawCommand> m_draws;

		GL4DrawCommand m_currentDraw;

	public:

		GL4Renderer2DCommandManager();

		void reset();

		void flush();

		const Array<GL4Renderer2DCommand>& getCommands() const noexcept;

		void pushUpdateBuffers(uint32 batchIndex);

		void pushDraw(Vertex2D::IndexType indexCount);
		const GL4DrawCommand& getDraw(uint32 index) const noexcept;
	};
}
