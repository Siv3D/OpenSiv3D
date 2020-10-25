﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
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

	}

	CShader_Null::~CShader_Null()
	{
		LOG_SCOPED_TRACE(U"CShader_Null::~CShader_Null()");
	}

	void CShader_Null::init()
	{

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

	}

	void CShader_Null::releasePS(const PixelShader::IDType)
	{

	}

	void CShader_Null::setVS(const VertexShader::IDType)
	{

	}

	void CShader_Null::setPS(const PixelShader::IDType)
	{

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

	}

	void CShader_Null::setConstantBufferPS(const uint32, const ConstantBufferBase&)
	{

	}
}
