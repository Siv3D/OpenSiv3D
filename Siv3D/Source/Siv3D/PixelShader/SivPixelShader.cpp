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
# include <Siv3D/PixelShader.hpp>
# include <Siv3D/BinaryReader.hpp>

namespace s3d
{
	template <>
	AssetHandle<PixelShader::Handle>::~AssetHandle()
	{
		if (!Siv3DEngine::isActive())
		{
			return;
		}

		if (auto p = Siv3DEngine::GetShader())
		{
			p->releasePS(m_id);
		}
	}

	PixelShader::PixelShader()
		: m_handle(std::make_shared<PixelShaderHandle>())
	{

	}

	PixelShader::PixelShader(const FilePath& path)
		: PixelShader()
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
		else if (!Siv3DEngine::GetShader()->compileHLSL(reader, memory, reader.path().narrow().c_str(), "PS", "ps_4_0"))
		{
			return;
		}

		m_handle = std::make_shared<PixelShaderHandle>(Siv3DEngine::GetShader()->createPS(std::move(memory)));

	# endif
	}

	PixelShader::~PixelShader()
	{

	}

	void PixelShader::release()
	{
		m_handle = std::make_shared<PixelShaderHandle>();
	}

	bool PixelShader::isEmpty() const
	{
		return m_handle->getID() == PixelShaderHandle::NullID;
	}

	PixelShader::IDType PixelShader::id() const
	{
		return m_handle->getID();
	}

	bool PixelShader::operator ==(const PixelShader& shader) const
	{
		return m_handle->getID() == shader.m_handle->getID();
	}

	bool PixelShader::operator !=(const PixelShader& shader) const
	{
		return m_handle->getID() != shader.m_handle->getID();
	}
}
