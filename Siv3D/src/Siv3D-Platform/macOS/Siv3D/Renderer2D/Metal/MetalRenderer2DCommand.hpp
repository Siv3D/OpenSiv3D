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
	enum class MetalRenderer2DCommandType : uint32
	{
		Null,

		SetBuffers,

		UpdateBuffers,

		Draw,
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

	class MetalRenderer2DCommandManager
	{
	private:

		Array<MetalRenderer2DCommand> m_commands;

		CurrentBatchStateChanges<MetalRenderer2DCommandType> m_changes;

		Array<MetalDrawCommand> m_draws;

		MetalDrawCommand m_currentDraw;

	public:

		MetalRenderer2DCommandManager();

		void reset();

		void flush();

		const Array<MetalRenderer2DCommand>& getCommands() const noexcept;

		void pushUpdateBuffers(uint32 batchIndex);

		void pushDraw(Vertex2D::IndexType indexCount);
		const MetalDrawCommand& getDraw(uint32 index) const noexcept;
	};
}
