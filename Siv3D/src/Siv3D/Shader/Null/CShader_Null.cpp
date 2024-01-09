//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "CShader_Null.hpp"
# include <Siv3D/Error.hpp>
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	CShader_Null::CShader_Null()
	{
		// do nothing
	}

	CShader_Null::~CShader_Null()
	{
		LOG_SCOPED_TRACE(U"CShader_Null::~CShader_Null()");

		m_emptyPS.reset();
		m_emptyVS.reset();
	}

	void CShader_Null::init()
	{
		m_emptyVS = std::make_unique<VertexShader>();
		m_emptyPS = std::make_unique<PixelShader>();
	}

	VertexShader::IDType CShader_Null::createVSFromFile(FilePathView, StringView, const Array<ConstantBufferBinding>&)
	{
		return VertexShader::IDType::NullAsset();
	}

	VertexShader::IDType CShader_Null::createVSFromSource(StringView, StringView, const Array<ConstantBufferBinding>&)
	{
		return VertexShader::IDType::NullAsset();
	}

	PixelShader::IDType CShader_Null::createPSFromFile(FilePathView, StringView, const Array<ConstantBufferBinding>&)
	{
		return PixelShader::IDType::NullAsset();
	}

	PixelShader::IDType CShader_Null::createPSFromSource(StringView, StringView, const Array<ConstantBufferBinding>&)
	{
		return PixelShader::IDType::NullAsset();
	}

	void CShader_Null::releaseVS(const VertexShader::IDType)
	{
		// do nothing
	}

	void CShader_Null::releasePS(const PixelShader::IDType)
	{
		// do nothing
	}

	void CShader_Null::setVS(const VertexShader::IDType)
	{
		// do nothing
	}

	void CShader_Null::setPS(const PixelShader::IDType)
	{
		// do nothing
	}

	const Blob& CShader_Null::getBinaryVS(const VertexShader::IDType)
	{
		return m_emptyBinary;
	}

	const Blob& CShader_Null::getBinaryPS(const PixelShader::IDType)
	{
		return m_emptyBinary;
	}

	void CShader_Null::setConstantBufferVS(const uint32, const ConstantBufferBase&)
	{
		// do nothing
	}

	void CShader_Null::setConstantBufferPS(const uint32, const ConstantBufferBase&)
	{
		// do nothing
	}

	const VertexShader& CShader_Null::getEngineVS(const EngineVS) const
	{
		return *m_emptyVS;
	}

	const PixelShader& CShader_Null::getEnginePS(const EnginePS) const
	{
		return *m_emptyPS;
	}

	void CShader_Null::setQuadWarpCB(const VS2DQuadWarp&, const PS2DQuadWarp&)
	{
		// do nothing
	}
}
