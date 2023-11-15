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

# include "CTexture_GLES3.hpp"
# include <Siv3D/Error.hpp>
# include <Siv3D/ImageProcessing.hpp>
# include <Siv3D/System.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Texture/TextureCommon.hpp>

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

	void CTexture_GLES3::updateAsyncTextureLoad(const size_t maxUpdate)
	{
		if (not isMainThread())
		{
			return;
		}

		// 終了時は即座に全消去
		if (maxUpdate == Largest<size_t>)
		{
			std::lock_guard lock{ m_requestsMutex };

			for (auto& request : m_requests)
			{
				request.waiting.get() = false;
			}

			m_requests.clear();

			return;
		}

		std::lock_guard lock{ m_requestsMutex };

		const size_t loadCount = Min(maxUpdate, m_requests.size());

		for (size_t i = 0; i < loadCount; ++i)
		{
			auto& request = m_requests[i];

			if (*request.pMipmaps)
			{
				request.idResult.get() = create(*request.pImage, *request.pMipmaps, *request.pDesc);
			}
			else
			{
				request.idResult.get() = create(*request.pImage, *request.pDesc);
			}

			request.waiting.get() = false;
		}

		m_requests.pop_front_N(loadCount);
	}

	size_t CTexture_GLES3::getTextureCount() const
	{
		return m_textures.size();
	}

	Texture::IDType CTexture_GLES3::create(const Image& image, const TextureDesc desc)
	{
		// [Siv3D ToDo] GPU でミップマップを生成する
		if (detail::HasMipMap(desc))
		{
			return create(image, ImageProcessing::GenerateMips(image), desc);
		}

		if (not image)
		{
			return Texture::IDType::NullAsset();
		}

		// OpenGL は異なるスレッドで Texture を作成できないので、実際の作成は updateAsyncTextureLoad() にさせる 
		if (not isMainThread())
		{
			return pushRequest(image, {}, desc);
		}

		auto texture = std::make_unique<GLES3Texture>(image, desc);

		if (not texture->isInitialized())
		{
			return Texture::IDType::NullAsset();
		}

		const String info = U"(type: Default, size:{0}x{1}, format: {2})"_fmt(image.width(), image.height(), texture->getFormat().name());
		return m_textures.add(std::move(texture), info);
	}

	Texture::IDType CTexture_GLES3::create(const Image& image, const Array<Image>& mips, const TextureDesc desc)
	{
		if (not image)
		{
			return Texture::IDType::NullAsset();
		}

		// OpenGL は異なるスレッドで Texture を作成できないので、実際の作成は updateAsyncTextureLoad() にさせる 
		if (not isMainThread())
		{
			return pushRequest(image, mips, desc);
		}

		auto texture = std::make_unique<GLES3Texture>(image, mips, desc);

		if (not texture->isInitialized())
		{
			return Texture::IDType::NullAsset();
		}

		const String info = U"(type: Default, size: {0}x{1}, format: {2})"_fmt(image.width(), image.height(), texture->getFormat().name());
		return m_textures.add(std::move(texture), info);
	}

	Texture::IDType CTexture_GLES3::createDynamic(const Size& size, const void* pData, uint32 stride, const TextureFormat& format, const TextureDesc desc)
	{
		if ((size.x <= 0) || (size.y <= 0))
		{
			return Texture::IDType::NullAsset();
		}

		auto texture = std::make_unique<GLES3Texture>(GLES3Texture::Dynamic{}, size, pData, stride, format, desc);

		if (not texture->isInitialized())
		{
			return Texture::IDType::NullAsset();
		}

		const String info = U"(type: Dynamic, size: {0}x{1}, format: {2})"_fmt(size.x, size.y, texture->getFormat().name());
		return m_textures.add(std::move(texture), info);
	}

	Texture::IDType CTexture_GLES3::createDynamic(const Size& size, const ColorF& color, const TextureFormat& format, const TextureDesc desc)
	{
		const Array<Byte> initialData = GenerateInitialColorBuffer(size, color, format);

		if (not initialData)
		{
			return Texture::IDType::NullAsset();
		}

		return createDynamic(size, initialData.data(), static_cast<uint32>(initialData.size() / size.y), format, desc);
	}

	Texture::IDType CTexture_GLES3::createRT(const Size& size, const TextureFormat& format, const HasDepth hasDepth, const HasMipMap hasMipMap)
	{
		if ((size.x <= 0) || (size.y <= 0))
		{
			return Texture::IDType::NullAsset();
		}

		const TextureDesc desc = (format.isSRGB() ? TextureDesc::UnmippedSRGB : TextureDesc::Unmipped);
		auto texture = std::make_unique<GLES3Texture>(GLES3Texture::Render{}, size, format, desc, hasDepth);

		if (not texture->isInitialized())
		{
			return Texture::IDType::NullAsset();
		}

		const String info = U"(type: Render, size:{0}x{1}, format: {2})"_fmt(size.x, size.y, texture->getFormat().name());
		return m_textures.add(std::move(texture), info);
	}

	Texture::IDType CTexture_GLES3::createRT(const Image& image, const HasDepth hasDepth, const HasMipMap hasMipMap)
	{
		if (not image)
		{
			return Texture::IDType::NullAsset();
		}

		const TextureDesc desc = TextureDesc::Unmipped;
		const TextureFormat format = TextureFormat::R8G8B8A8_Unorm;
		auto texture = std::make_unique<GLES3Texture>(GLES3Texture::Render{}, image, format, desc, hasDepth);

		if (not texture->isInitialized())
		{
			return Texture::IDType::NullAsset();
		}

		const String info = U"(type: Render, size:{0}x{1}, format: {2})"_fmt(image.width(), image.height(), texture->getFormat().name());
		return m_textures.add(std::move(texture), info);
	}

	Texture::IDType CTexture_GLES3::createRT(const Grid<float>& image, const HasDepth hasDepth, const HasMipMap hasMipMap)
	{
		if (not image)
		{
			return Texture::IDType::NullAsset();
		}

		const TextureDesc desc = TextureDesc::Unmipped;
		const TextureFormat format = TextureFormat::R32_Float;
		auto texture = std::make_unique<GLES3Texture>(GLES3Texture::Render{}, image, format, desc, hasDepth);

		if (not texture->isInitialized())
		{
			return Texture::IDType::NullAsset();
		}

		const String info = U"(type: Render, size:{0}x{1}, format: {2})"_fmt(image.width(), image.height(), texture->getFormat().name());
		return m_textures.add(std::move(texture), info);
	}

	Texture::IDType CTexture_GLES3::createRT(const Grid<Float2>& image, const HasDepth hasDepth, const HasMipMap hasMipMap)
	{
		if (not image)
		{
			return Texture::IDType::NullAsset();
		}

		const TextureDesc desc = TextureDesc::Unmipped;
		const TextureFormat format = TextureFormat::R32G32_Float;
		auto texture = std::make_unique<GLES3Texture>(GLES3Texture::Render{}, image, format, desc, hasDepth);

		if (not texture->isInitialized())
		{
			return Texture::IDType::NullAsset();
		}

		const String info = U"(type: Render, size:{0}x{1}, format: {2})"_fmt(image.width(), image.height(), texture->getFormat().name());
		return m_textures.add(std::move(texture), info);
	}

	Texture::IDType CTexture_GLES3::createRT(const Grid<Float4>& image, const HasDepth hasDepth, const HasMipMap hasMipMap)
	{
		if (not image)
		{
			return Texture::IDType::NullAsset();
		}

		const TextureDesc desc = TextureDesc::Unmipped;
		const TextureFormat format = TextureFormat::R32G32B32A32_Float;
		auto texture = std::make_unique<GLES3Texture>(GLES3Texture::Render{}, image, format, desc, hasDepth);

		if (not texture->isInitialized())
		{
			return Texture::IDType::NullAsset();
		}

		const String info = U"(type: Render, size:{0}x{1}, format: {2})"_fmt(image.width(), image.height(), texture->getFormat().name());
		return m_textures.add(std::move(texture), info);
	}

	Texture::IDType CTexture_GLES3::createMSRT(const Size& size, const TextureFormat& format, const HasDepth hasDepth, const HasMipMap hasMipMap)
	{
		if ((size.x <= 0) || (size.y <= 0))
		{
			return Texture::IDType::NullAsset();
		}

		const TextureDesc desc = (format.isSRGB() ? TextureDesc::UnmippedSRGB : TextureDesc::Unmipped);
		auto texture = std::make_unique<GLES3Texture>(GLES3Texture::MSRender{}, size, format, desc, hasDepth);

		if (not texture->isInitialized())
		{
			return Texture::IDType::NullAsset();
		}

		const String info = U"(type: MSRender, size:{0}x{1}, format: {2})"_fmt(size.x, size.y, texture->getFormat().name());
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

	bool CTexture_GLES3::hasDepth(const Texture::IDType handleID)
	{
		return m_textures[handleID]->hasDepth();
	}

	bool CTexture_GLES3::fill(const Texture::IDType handleID, const ColorF& color, const bool wait)
	{
		return m_textures[handleID]->fill(color, wait);
	}

	bool CTexture_GLES3::fillRegion(const Texture::IDType handleID, const ColorF& color, const Rect& rect)
	{
		return m_textures[handleID]->fillRegion(color, rect);
	}

	bool CTexture_GLES3::fill(const Texture::IDType handleID, const void* src, uint32 stride, const bool wait)
	{
		return m_textures[handleID]->fill(src, stride, wait);
	}

	bool CTexture_GLES3::fillRegion(const Texture::IDType handleID, const void* src, const uint32 stride, const Rect& rect, const bool wait)
	{
		return m_textures[handleID]->fillRegion(src, stride, rect, wait);
	}

	void CTexture_GLES3::clearRT(const Texture::IDType handleID, const ColorF& color)
	{
		m_textures[handleID]->clearRT(color);
	}

	void CTexture_GLES3::generateMips(const Texture::IDType handleID)
	{

	}

	void CTexture_GLES3::readRT(const Texture::IDType handleID, Image& image)
	{
		m_textures[handleID]->readRT(image);
	}

	void CTexture_GLES3::readRT(const Texture::IDType handleID, Grid<float>& image)
	{
		m_textures[handleID]->readRT(image);
	}

	void CTexture_GLES3::readRT(const Texture::IDType handleID, Grid<Float2>& image)
	{
		m_textures[handleID]->readRT(image);
	}

	void CTexture_GLES3::readRT(const Texture::IDType handleID, Grid<Float4>& image)
	{
		m_textures[handleID]->readRT(image);
	}

	void CTexture_GLES3::resolveMSRT(const Texture::IDType handleID)
	{
		m_textures[handleID]->resolveMSRT();
	}

	GLuint CTexture_GLES3::getTexture(const Texture::IDType handleID)
	{
		return m_textures[handleID]->getTexture();
	}

	GLuint CTexture_GLES3::getFrameBuffer(const Texture::IDType handleID)
	{
		return m_textures[handleID]->getFrameBuffer();
	}

	bool CTexture_GLES3::isMainThread() const noexcept
	{
		return (std::this_thread::get_id() == m_mainThreadID);
	}

	Texture::IDType CTexture_GLES3::pushRequest(const Image& image, const Array<Image>& mipmaps, const TextureDesc desc)
	{
		std::atomic<bool> waiting = true;

		Texture::IDType result = Texture::IDType::NullAsset();
		{
			std::lock_guard lock{ m_requestsMutex };

			m_requests.push_back(Request{ &image, &mipmaps, &desc, std::ref(result), std::ref(waiting) });
		}

		// [Siv3D ToDo] conditional_variable を使う
		while (waiting)
		{
			System::Sleep(3);
		}

		return result;
	}
}
