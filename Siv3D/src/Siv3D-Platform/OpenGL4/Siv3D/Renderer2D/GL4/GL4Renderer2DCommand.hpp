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
# include <Siv3D/HashTable.hpp>
# include <Siv3D/Vertex2D.hpp>
# include <Siv3D/VertexShader.hpp>
# include <Siv3D/PixelShader.hpp>
# include <Siv3D/Renderer2D/CurrentBatchStateChanges.hpp>

namespace s3d
{
	enum class GL4Renderer2DCommandType : uint32
	{
		Null,

		SetBuffers,

		UpdateBuffers,

		Draw,

		DrawNull,

		SetVS,

		SetPS,
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

		// commands
		Array<GL4Renderer2DCommand> m_commands;
		CurrentBatchStateChanges<GL4Renderer2DCommandType> m_changes;

		// buffer
		Array<GL4DrawCommand> m_draws;
		Array<uint32> m_nullDraws;
		Array<VertexShader::IDType> m_VSs;
		Array<PixelShader::IDType> m_PSs;

		// current
		GL4DrawCommand m_currentDraw;
		VertexShader::IDType m_currentVS = VertexShader::IDType::InvalidValue();
		PixelShader::IDType m_currentPS = PixelShader::IDType::InvalidValue();

		// reserved
		HashTable<VertexShader::IDType, VertexShader> m_reservedVSs;
		HashTable<PixelShader::IDType, PixelShader> m_reservedPSs;

	public:

		GL4Renderer2DCommandManager();

		void reset();

		void flush();

		const Array<GL4Renderer2DCommand>& getCommands() const noexcept;

		void pushUpdateBuffers(uint32 batchIndex);

		void pushDraw(Vertex2D::IndexType indexCount);
		const GL4DrawCommand& getDraw(uint32 index) const noexcept;

		void pushNullVertices(uint32 count);
		uint32 getNullDraw(uint32 index) const noexcept;

		void pushStandardVS(const VertexShader::IDType& id);
		void pushCustomVS(const VertexShader& vs);
		const VertexShader::IDType& getVS(uint32 index) const;

		void pushStandardPS(const PixelShader::IDType& id);
		void pushCustomPS(const PixelShader& ps);
		const PixelShader::IDType& getPS(uint32 index) const;
	};
}
