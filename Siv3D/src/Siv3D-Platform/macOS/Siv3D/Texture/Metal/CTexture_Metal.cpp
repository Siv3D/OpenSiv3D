//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
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

	Texture::IDType CTexture_Metal::createUnmipped(const Image& image, TextureDesc desc)
	{
		return(Texture::IDType::NullAsset());
	}

	Texture::IDType CTexture_Metal::createMipped(const Image& image, const Array<Image>& mips, TextureDesc desc)
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
}
