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

# include "CTexture_Metal.hpp"
# include <Siv3D/Error.hpp>
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	CTexture_Metal::CTexture_Metal()
	{
		// do nothing
	}

	CTexture_Metal::~CTexture_Metal()
	{
		LOG_SCOPED_TRACE(U"CTexture_Metal::~CTexture_Metal()");
	}

	void CTexture_Metal::init()
	{
		
	}

	void CTexture_Metal::updateAsyncTextureLoad(const size_t)
	{
		// [Siv3D ToDo]
	}

	size_t CTexture_Metal::getTextureCount() const
	{
		// [Siv3D ToDo]
		return 0;
	}

	Texture::IDType CTexture_Metal::create(const Image& image, TextureDesc desc)
	{
		return(Texture::IDType::NullAsset());
	}

	Texture::IDType CTexture_Metal::create(const Image& image, const Array<Image>& mips, TextureDesc desc)
	{
		return(Texture::IDType::NullAsset());
	}

	Texture::IDType CTexture_Metal::createDynamic(const Size&, const void*, uint32, const TextureFormat&, const TextureDesc)
	{
		return Texture::IDType::NullAsset();
	}

	Texture::IDType CTexture_Metal::createDynamic(const Size&, const ColorF&, const TextureFormat&, const TextureDesc)
	{
		return Texture::IDType::NullAsset();
	}

	Texture::IDType CTexture_Metal::createRT(const Size& size, const TextureFormat& format, const HasDepth, const HasMipMap)
	{
		return Texture::IDType::NullAsset();
	}

	Texture::IDType CTexture_Metal::createRT(const Image& image, const HasDepth, const HasMipMap)
	{
		return Texture::IDType::NullAsset();
	}

	Texture::IDType CTexture_Metal::createRT(const Grid<float>& image, const HasDepth, const HasMipMap)
	{
		return Texture::IDType::NullAsset();
	}

	Texture::IDType CTexture_Metal::createRT(const Grid<Float2>& image, const HasDepth, const HasMipMap)
	{
		return Texture::IDType::NullAsset();
	}

	Texture::IDType CTexture_Metal::createRT(const Grid<Float4>& image, const HasDepth, const HasMipMap)
	{
		return Texture::IDType::NullAsset();
	}

	Texture::IDType CTexture_Metal::createMSRT(const Size& size, const TextureFormat& format, const HasDepth, const HasMipMap)
	{
		return Texture::IDType::NullAsset();
	}

	void CTexture_Metal::release(Texture::IDType handleID)
	{

	}

	Size CTexture_Metal::getSize(Texture::IDType handleID)
	{
		return(Size{ 0,0 });
	}

	TextureDesc CTexture_Metal::getDesc(Texture::IDType handleID)
	{
		return(TextureDesc::Unmipped);
	}

	TextureFormat CTexture_Metal::getFormat(Texture::IDType handleID)
	{
		return(TextureFormat::Unknown);
	}

	bool CTexture_Metal::hasDepth(Texture::IDType handleID)
	{
		return false;
	}

	bool CTexture_Metal::fill(Texture::IDType, const ColorF&, bool)
	{
		return false;
	}

	bool CTexture_Metal::fillRegion(Texture::IDType, const ColorF&, const Rect&)
	{
		return false;
	}

	bool CTexture_Metal::fill(Texture::IDType, const void*, uint32, bool)
	{
		return false;
	}

	bool CTexture_Metal::fillRegion(Texture::IDType, const void*, uint32, const Rect&, bool)
	{
		return false;
	}



	void CTexture_Metal::clearRT(Texture::IDType handleID, const ColorF& color)
	{

	}

	void CTexture_Metal::generateMips(const Texture::IDType handleID)
	{

	}

	void CTexture_Metal::readRT(Texture::IDType handleID, Image& image)
	{

	}

	void CTexture_Metal::readRT(Texture::IDType handleID, Grid<float>& image)
	{

	}

	void CTexture_Metal::readRT(Texture::IDType handleID, Grid<Float2>& image)
	{

	}

	void CTexture_Metal::readRT(Texture::IDType handleID, Grid<Float4>& image)
	{

	}

	void CTexture_Metal::resolveMSRT(Texture::IDType handleID)
	{

	}
}
