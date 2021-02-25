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

	Texture::IDType CTexture_Null::createUnmipped(const Image&, TextureDesc)
	{
		return Texture::IDType::NullAsset();
	}

	Texture::IDType CTexture_Null::createMipped(const Image&, const Array<Image>&, TextureDesc)
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
}
