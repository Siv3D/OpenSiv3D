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

# include "CTexture_GLES3.hpp"
# include <Siv3D/Error.hpp>
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	CTexture_GLES3::CTexture_GLES3()
	{
		// do nothing
	}

	CTexture_GLES3::~CTexture_GLES3()
	{
		LOG_SCOPED_TRACE(U"CTexture_GLES3::~CTexture_GLES3()");

		m_textures.destroy();
	}

	void CTexture_GLES3::init()
	{
		// null Texture を管理に登録
		{
			const Image image{ 16, Palette::Yellow };
			const Array<Image> mips = {
				Image{ 8, Palette::Yellow }, Image{ 4, Palette::Yellow },
				Image{ 2, Palette::Yellow }, Image{ 1, Palette::Yellow }
			};

			// null Texture を作成
			auto nullTexture = std::make_unique<GLES3Texture>(image, mips, TextureDesc::Mipped);

			if (not nullTexture->isInitialized()) // もし作成に失敗していたら
			{
				throw EngineError(U"Null Texture initialization failed");
			}

			// 管理に登録
			m_textures.setNullData(std::move(nullTexture));
		}
	}

	void CTexture_GLES3::updateAsyncTextureLoad(const size_t)
	{
		// [Siv3D ToDo]
	}

	Texture::IDType CTexture_GLES3::createUnmipped(const Image& image, const TextureDesc desc)
	{
		if (not image)
		{
			return Texture::IDType::NullAsset();
		}

		//if (not isMainThread())
		//{
		//	return pushRequest(image, Array<Image>(), desc);
		//}

		auto texture = std::make_unique<GLES3Texture>(image, desc);

		if (not texture->isInitialized())
		{
			return Texture::IDType::NullAsset();
		}

		const String info = U"(type: Default, size:{0}x{1}, format: {2})"_fmt(image.width(), image.height(), texture->getFormat().name());
		return m_textures.add(std::move(texture), info);
	}

	Texture::IDType CTexture_GLES3::createMipped(const Image& image, const Array<Image>& mips, const TextureDesc desc)
	{
		if (not image)
		{
			return Texture::IDType::NullAsset();
		}

		//if (not isMainThread())
		//{
		//	return pushRequest(image, mips, desc);
		//}

		auto texture = std::make_unique<GLES3Texture>(image, mips, desc);

		if (not texture->isInitialized())
		{
			return Texture::IDType::NullAsset();
		}

		const String info = U"(type: Default, size: {0}x{1}, format: {2})"_fmt(image.width(), image.height(), texture->getFormat().name());
		return m_textures.add(std::move(texture), info);
	}

	void CTexture_GLES3::release(const Texture::IDType handleID)
	{
		m_textures.erase(handleID);
	}

	Size CTexture_GLES3::getSize(const Texture::IDType handleID)
	{
		return m_textures[handleID]->getSize();
	}

	TextureDesc CTexture_GLES3::getDesc(const Texture::IDType handleID)
	{
		return m_textures[handleID]->getDesc();
	}

	TextureFormat CTexture_GLES3::getFormat(const Texture::IDType handleID)
	{
		return m_textures[handleID]->getFormat();
	}

	GLuint CTexture_GLES3::getTexture(const Texture::IDType handleID)
	{
		return m_textures[handleID]->getTexture();
	}

	GLuint CTexture_GLES3::getFrameBuffer(const Texture::IDType handleID)
	{
		return m_textures[handleID]->getFrameBuffer();
	}
}
