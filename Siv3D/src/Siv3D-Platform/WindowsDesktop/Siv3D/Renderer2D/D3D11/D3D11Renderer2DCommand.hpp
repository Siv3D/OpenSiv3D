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

		Array<D3D11Renderer2DCommand> m_commands;

		CurrentBatchStateChanges<D3D11Renderer2DCommandType> m_changes;

		Array<D3D11DrawCommand> m_draws;

		D3D11DrawCommand m_currentDraw;

	public:

		D3D11Renderer2DCommandManager();

		void reset();

		void flush();

		const Array<D3D11Renderer2DCommand>& getCommands() const noexcept;

		void pushUpdateBuffers(uint32 batchIndex);

		void pushDraw(Vertex2D::IndexType indexCount);
		const D3D11DrawCommand& getDraw(uint32 index) const noexcept;
	};
}
