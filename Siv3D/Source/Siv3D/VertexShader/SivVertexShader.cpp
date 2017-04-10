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

# include "../Siv3DEngine.hpp"
# include "../Shader/IShader.hpp"
# include <Siv3D/VertexShader.hpp>
# include <Siv3D/BinaryReader.hpp>

namespace s3d
{
	template <>
	AssetHandle<VertexShader::Handle>::~AssetHandle()
	{
		if (!Siv3DEngine::isActive())
		{
			return;
		}

		if (auto p = Siv3DEngine::GetShader())
		{
			p->releaseVS(m_id);
		}
	}

	VertexShader::VertexShader()
		: m_handle(std::make_shared<VertexShaderHandle>())
	{

	}

	VertexShader::VertexShader(const FilePath& path)
		: VertexShader()
	{
	# if defined(SIV3D_TARGET_WINDOWS)

		BinaryReader reader(path);

		if (!reader.isOpened() || reader.size() == 0 || !reader.supportsLookahead())
		{
			return;
		}

		static constexpr uint8 dxbc[4] = { 'D', 'X', 'B', 'C' };
		uint8 fourcc[4];

		if (!reader.lookahead(fourcc))
		{
			return;
		}

		const bool isBinary = (::memcmp(dxbc, fourcc, 4) == 0);

		ByteArray memory;

		if (isBinary)
		{
			memory = reader.readAll();
		}
		else if (!Siv3DEngine::GetShader()->compileHLSL(reader, memory, reader.path().narrow().c_str(), "VS", "vs_4_0"))
		{
			return;
		}

		m_handle = std::make_shared<VertexShaderHandle>(Siv3DEngine::GetShader()->createVS(std::move(memory)));

	# endif
	}

	VertexShader::~VertexShader()
	{

	}

	void VertexShader::release()
	{
		m_handle = std::make_shared<VertexShaderHandle>();
	}

	bool VertexShader::isEmpty() const
	{
		return m_handle->getID() == VertexShaderHandle::NullID;
	}

	VertexShader::IDType VertexShader::id() const
	{
		return m_handle->getID();
	}

	bool VertexShader::operator ==(const VertexShader& shader) const
	{
		return m_handle->getID() == shader.m_handle->getID();
	}

	bool VertexShader::operator !=(const VertexShader& shader) const
	{
		return m_handle->getID() != shader.m_handle->getID();
	}
}
