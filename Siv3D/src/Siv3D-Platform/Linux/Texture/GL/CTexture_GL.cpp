//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Image.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/EngineError.hpp>
# include <Siv3D/TextureFormat.hpp>
# include "CTexture_GL.hpp"

namespace s3d
{
	CTexture_GL::~CTexture_GL()
	{
		LOG_TRACE(U"CTexture_D3D11::~CTexture_D3D11()");

		m_textures.destroy();
	}

	void CTexture_GL::init()
	{
		LOG_TRACE(U"CTexture_GL::init()");

		/*

		const Image image(16, Palette::Yellow);
		const Array<Image> mips = {
			Image(8, Palette::Yellow), Image(4, Palette::Yellow),
			Image(2, Palette::Yellow), Image(1, Palette::Yellow)
		};

		auto nullTexture = std::make_unique<Texture_GL>(device, image, mips, TextureDesc::Mipped);

		if (!nullTexture->isInitialized())
		{
			throw EngineError(U"Null Texture initialization failed");
		}

		m_textures.setNullData(std::move(nullTexture));
		 
		 */

		LOG_INFO(U"ℹ️ CTexture_GL initialized");
	}

	void CTexture_GL::updateAsync(size_t)
	{
		// do nothing
	}

	TextureID CTexture_GL::createUnmipped(const Image& image, const TextureDesc desc)
	{
		// [Siv3D ToDo]
		return TextureID::NullAsset();
	}

	TextureID CTexture_GL::create(const Image& image, const Array<Image>& mips, TextureDesc desc)
	{
		// [Siv3D ToDo]
		return TextureID::NullAsset();
	}

	TextureID CTexture_GL::createDynamic(const Size& size, const void* pData, const uint32 stride, const TextureFormat format, const TextureDesc desc)
	{
		// [Siv3D ToDo]
		return TextureID::NullAsset();
	}

	TextureID CTexture_GL::createDynamic(const Size& size, const ColorF& color, const TextureFormat format, const TextureDesc desc)
	{
		// [Siv3D ToDo]
		return TextureID::NullAsset();
	}

	void CTexture_GL::release(const TextureID handleID)
	{
		m_textures.erase(handleID);
	}

	Size CTexture_GL::getSize(const TextureID handleID)
	{
		return m_textures[handleID]->getSize();
	}

	TextureDesc CTexture_GL::getDesc(const TextureID handleID)
	{
		return m_textures[handleID]->getDesc();
	}

	bool CTexture_GL::fill(const TextureID handleID, const ColorF& color, const bool wait)
	{
		return m_textures[handleID]->fill(color, wait);
	}

	bool CTexture_GL::fillRegion(TextureID handleID, const ColorF& color, const Rect& rect)
	{
		// [Siv3D ToDo]
		return (false);
		//return m_textures[handleID]->fillRegion(m_context, color, rect);
	}

	bool CTexture_GL::fill(const TextureID handleID, const void* const src, const uint32 stride, const bool wait)
	{
		return m_textures[handleID]->fill(src, stride, wait);
	}

	bool CTexture_GL::fillRegion(TextureID handleID, const void* src, uint32 stride, const Rect& rect, const bool wait)
	{
		// [Siv3D ToDo]
		return (false);
		//return m_textures[handleID]->fillRegion(src, stride, rect, wait);
	}
}
