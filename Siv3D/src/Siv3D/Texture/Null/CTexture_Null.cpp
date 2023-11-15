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

# include "CTexture_Null.hpp"
# include <Siv3D/Error.hpp>
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	CTexture_Null::CTexture_Null()
	{
		// do nothing
	}

	CTexture_Null::~CTexture_Null()
	{
		LOG_SCOPED_TRACE(U"CTexture_Null::~CTexture_Null()");
	}

	void CTexture_Null::updateAsyncTextureLoad(const size_t)
	{
		// do nothing
	}

	size_t CTexture_Null::getTextureCount() const
	{
		return 0;
	}

	Texture::IDType CTexture_Null::create(const Image&, TextureDesc)
	{
		return Texture::IDType::NullAsset();
	}

	Texture::IDType CTexture_Null::create(const Image&, const Array<Image>&, TextureDesc)
	{
		return Texture::IDType::NullAsset();
	}

	Texture::IDType CTexture_Null::createDynamic(const Size&, const void*, uint32, const TextureFormat&, const TextureDesc)
	{
		return Texture::IDType::NullAsset();
	}

	Texture::IDType CTexture_Null::createDynamic(const Size&, const ColorF&, const TextureFormat&, const TextureDesc)
	{
		return Texture::IDType::NullAsset();
	}

	Texture::IDType CTexture_Null::createRT(const Size&, const TextureFormat&, const HasDepth, const HasMipMap)
	{
		return Texture::IDType::NullAsset();
	}

	Texture::IDType CTexture_Null::createRT(const Image&, const HasDepth, const HasMipMap)
	{
		return Texture::IDType::NullAsset();
	}

	Texture::IDType CTexture_Null::createRT(const Grid<float>&, const HasDepth, const HasMipMap)
	{
		return Texture::IDType::NullAsset();
	}

	Texture::IDType CTexture_Null::createRT(const Grid<Float2>&, const HasDepth, const HasMipMap)
	{
		return Texture::IDType::NullAsset();
	}

	Texture::IDType CTexture_Null::createRT(const Grid<Float4>&, const HasDepth, const HasMipMap)
	{
		return Texture::IDType::NullAsset();
	}

	Texture::IDType CTexture_Null::createMSRT(const Size&, const TextureFormat&, const HasDepth, const HasMipMap)
	{
		return Texture::IDType::NullAsset();
	}

	void CTexture_Null::release(Texture::IDType)
	{
		// do nothing
	}

	Size CTexture_Null::getSize(Texture::IDType)
	{
		return{ 0,0 };
	}

	TextureDesc CTexture_Null::getDesc(Texture::IDType)
	{
		return TextureDesc::Unmipped;
	}

	TextureFormat CTexture_Null::getFormat(Texture::IDType)
	{
		return TextureFormat::Unknown;
	}

	bool CTexture_Null::hasDepth(Texture::IDType)
	{
		return false;
	}

	bool CTexture_Null::fill(Texture::IDType, const ColorF&, bool)
	{
		return false;
	}

	bool CTexture_Null::fillRegion(Texture::IDType, const ColorF&, const Rect&)
	{
		return false;
	}

	bool CTexture_Null::fill(Texture::IDType, const void*, uint32, bool)
	{
		return false;
	}

	bool CTexture_Null::fillRegion(Texture::IDType, const void*, uint32, const Rect&, bool)
	{
		return false;
	}

	void CTexture_Null::clearRT(Texture::IDType, const ColorF&)
	{

	}

	void CTexture_Null::generateMips(const Texture::IDType)
	{

	}

	void CTexture_Null::readRT(Texture::IDType, Image&)
	{

	}

	void CTexture_Null::readRT(Texture::IDType, Grid<float>&)
	{

	}

	void CTexture_Null::readRT(Texture::IDType, Grid<Float2>&)
	{

	}

	void CTexture_Null::readRT(Texture::IDType, Grid<Float4>&)
	{

	}

	void CTexture_Null::resolveMSRT(Texture::IDType)
	{

	}
}
