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
	enum class GLES3Renderer2DCommandType : uint32
	{
		Null,

		SetBuffers,

		UpdateBuffers,

		Draw,
	};

	struct GLES3Renderer2DCommand
	{
		GLES3Renderer2DCommandType type = GLES3Renderer2DCommandType::Null;

		uint32 index = 0;
		
		GLES3Renderer2DCommand() = default;
		
		constexpr GLES3Renderer2DCommand(GLES3Renderer2DCommandType _type, uint32 _index) noexcept
			: type(_type)
			, index(_index) {}
	};

	struct GLES3DrawCommand
	{
		uint32 indexCount = 0;
	};

	class GLES3Renderer2DCommandManager
	{
	private:

		Array<GLES3Renderer2DCommand> m_commands;

		CurrentBatchStateChanges<GLES3Renderer2DCommandType> m_changes;

		Array<GLES3DrawCommand> m_draws;

		GLES3DrawCommand m_currentDraw;

	public:

		GLES3Renderer2DCommandManager();

		void reset();

		void flush();

		const Array<GLES3Renderer2DCommand>& getCommands() const noexcept;

		void pushUpdateBuffers(uint32 batchIndex);

		void pushDraw(Vertex2D::IndexType indexCount);
		const GLES3DrawCommand& getDraw(uint32 index) const noexcept;
	};
}
