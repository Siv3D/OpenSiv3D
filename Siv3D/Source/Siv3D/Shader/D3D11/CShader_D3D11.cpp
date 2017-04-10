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

# include "CShader_D3D11.hpp"
# include <Siv3D/IReader.hpp>
# include <Siv3D/ByteArray.hpp>

namespace s3d
{
	CShader_D3D11::CShader_D3D11()
	{

	}

	CShader_D3D11::~CShader_D3D11()
	{

	}

	bool CShader_D3D11::init(ID3D11Device* const device, ID3D11DeviceContext* const context)
	{
		m_device = device;
		m_context = context;

		const auto nullVertexShader = std::make_shared<VertexShader_D3D11>(VertexShader_D3D11::Null{});

		if (!nullVertexShader->isInitialized())
		{
			return false;
		}

		m_vertexShaders.setNullData(nullVertexShader);

		return true;
	}

	VertexShader::IDType CShader_D3D11::createVS(IReader&& reader)
	{
		if (!reader.isOpened() || reader.size() == 0 || !reader.supportsLookahead())
		{
			return VertexShader::IDType(0);
		}

		static constexpr uint8 dxbc[4] = { 'D', 'X', 'B', 'C' };
		uint8 fourcc[4];

		if (!reader.lookahead(fourcc))
		{
			return VertexShader::IDType(0);
		}

		const bool isBinary = (::memcmp(dxbc, fourcc, 4) == 0);

		ByteArray binary;

		if (isBinary)
		{
			Array<Byte> data(static_cast<size_t>(reader.size()));

			reader.read(data.data(), data.size());

			binary.create(std::move(data));
		}
		else if (!compileHLSL(reader, binary))
		{
			return VertexShader::IDType(0);
		}

		const auto vertexShader = std::make_shared<VertexShader_D3D11>(std::move(binary), m_device);

		if (!vertexShader->isInitialized())
		{
			return VertexShader::IDType(0);
		}

		return m_vertexShaders.add(vertexShader);
	}

	bool CShader_D3D11::compileHLSL(IReader& reader, ByteArray& to)
	{
		return false;
	}
}

# endif
