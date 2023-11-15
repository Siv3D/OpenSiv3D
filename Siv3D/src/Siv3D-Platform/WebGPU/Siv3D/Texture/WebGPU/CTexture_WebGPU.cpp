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

# include "CTexture_WebGPU.hpp"
# include <Siv3D/Error.hpp>
# include <Siv3D/ImageProcessing.hpp>
# include <Siv3D/System.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Texture/TextureCommon.hpp>

namespace s3d
{
	CTexture_WebGPU::CTexture_WebGPU()
	{
		// do nothing
	}

	CTexture_WebGPU::~CTexture_WebGPU()
	{
		LOG_SCOPED_TRACE(U"CTexture_WebGPU::~CTexture_WebGPU()");

		m_textures.destroy();
	}

	void CTexture_WebGPU::init()
	{
		auto pRenderer = static_cast<CRenderer_WebGPU*>(SIV3D_ENGINE(Renderer)); assert(pRenderer);
		m_device = pRenderer->getDevice();

		// null Texture を管理に登録
		{
			const Image image{ 16, Palette::Yellow };
			const Array<Image> mips = {
				Image{ 8, Palette::Yellow }, Image{ 4, Palette::Yellow },
				Image{ 2, Palette::Yellow }, Image{ 1, Palette::Yellow }
			};

			// null Texture を作成
			auto nullTexture = std::make_unique<WebGPUTexture>(m_device, image, mips, TextureDesc::Mipped);

			if (not nullTexture->isInitialized()) // もし作成に失敗していたら
			{
				throw EngineError(U"Null Texture initialization failed");
			}

			// 管理に登録
			m_textures.setNullData(std::move(nullTexture));
		}
	}

	void CTexture_WebGPU::updateAsyncTextureLoad(const size_t maxUpdate)
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

	size_t CTexture_WebGPU::getTextureCount() const
	{
		return m_textures.size();
	}

	Texture::IDType CTexture_WebGPU::create(const Image& image, const TextureDesc desc)
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

		auto texture = std::make_unique<WebGPUTexture>(m_device, image, desc);

		if (not texture->isInitialized())
		{
			return Texture::IDType::NullAsset();
		}

		const String info = U"(type: Default, size:{0}x{1}, format: {2})"_fmt(image.width(), image.height(), texture->getFormat().name());
		return m_textures.add(std::move(texture), info);
	}

	Texture::IDType CTexture_WebGPU::create(const Image& image, const Array<Image>& mips, const TextureDesc desc)
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

		auto texture = std::make_unique<WebGPUTexture>(m_device, image, mips, desc);

		if (not texture->isInitialized())
		{
			return Texture::IDType::NullAsset();
		}

		const String info = U"(type: Default, size: {0}x{1}, format: {2})"_fmt(image.width(), image.height(), texture->getFormat().name());
		return m_textures.add(std::move(texture), info);
	}

	Texture::IDType CTexture_WebGPU::createDynamic(const Size& size, const void* pData, uint32 stride, const TextureFormat& format, const TextureDesc desc)
	{
		if ((size.x <= 0) || (size.y <= 0))
		{
			return Texture::IDType::NullAsset();
		}

		auto texture = std::make_unique<WebGPUTexture>(WebGPUTexture::Dynamic{}, m_device, size, pData, stride, format, desc);

		if (not texture->isInitialized())
		{
			return Texture::IDType::NullAsset();
		}

		const String info = U"(type: Dynamic, size: {0}x{1}, format: {2})"_fmt(size.x, size.y, texture->getFormat().name());
		return m_textures.add(std::move(texture), info);
	}

	Texture::IDType CTexture_WebGPU::createDynamic(const Size& size, const ColorF& color, const TextureFormat& format, const TextureDesc desc)
	{
		const Array<Byte> initialData = GenerateInitialColorBuffer(size, color, format);

		if (not initialData)
		{
			return Texture::IDType::NullAsset();
		}

		return createDynamic(size, initialData.data(), static_cast<uint32>(initialData.size() / size.y), format, desc);
	}

	Texture::IDType CTexture_WebGPU::createRT(const Size& size, const TextureFormat& format, const HasDepth hasDepth, const HasMipMap hasMipMap)
	{
		if ((size.x <= 0) || (size.y <= 0))
		{
			return Texture::IDType::NullAsset();
		}

		const TextureDesc desc = (format.isSRGB() ? TextureDesc::UnmippedSRGB : TextureDesc::Unmipped);
		auto texture = std::make_unique<WebGPUTexture>(WebGPUTexture::Render{}, m_device, size, format, desc, hasDepth);

		if (not texture->isInitialized())
		{
			return Texture::IDType::NullAsset();
		}

		const String info = U"(type: Render, size:{0}x{1}, format: {2})"_fmt(size.x, size.y, texture->getFormat().name());
		return m_textures.add(std::move(texture), info);
	}

	Texture::IDType CTexture_WebGPU::createRT(const Image& image, const HasDepth hasDepth, const HasMipMap hasMipMap)
	{
		if (not image)
		{
			return Texture::IDType::NullAsset();
		}

		const TextureDesc desc = TextureDesc::Unmipped;
		const TextureFormat format = TextureFormat::R8G8B8A8_Unorm;
		auto texture = std::make_unique<WebGPUTexture>(WebGPUTexture::Render{}, m_device, image, format, desc, hasDepth);

		if (not texture->isInitialized())
		{
			return Texture::IDType::NullAsset();
		}

		const String info = U"(type: Render, size:{0}x{1}, format: {2})"_fmt(image.width(), image.height(), texture->getFormat().name());
		return m_textures.add(std::move(texture), info);
	}

	Texture::IDType CTexture_WebGPU::createRT(const Grid<float>& image, const HasDepth hasDepth, const HasMipMap hasMipMap)
	{
		if (not image)
		{
			return Texture::IDType::NullAsset();
		}

		const TextureDesc desc = TextureDesc::Unmipped;
		const TextureFormat format = TextureFormat::R32_Float;
		auto texture = std::make_unique<WebGPUTexture>(WebGPUTexture::Render{}, m_device, image, format, desc, hasDepth);

		if (not texture->isInitialized())
		{
			return Texture::IDType::NullAsset();
		}

		const String info = U"(type: Render, size:{0}x{1}, format: {2})"_fmt(image.width(), image.height(), texture->getFormat().name());
		return m_textures.add(std::move(texture), info);
	}

	Texture::IDType CTexture_WebGPU::createRT(const Grid<Float2>& image, const HasDepth hasDepth, const HasMipMap hasMipMap)
	{
		if (not image)
		{
			return Texture::IDType::NullAsset();
		}

		const TextureDesc desc = TextureDesc::Unmipped;
		const TextureFormat format = TextureFormat::R32G32_Float;
		auto texture = std::make_unique<WebGPUTexture>(WebGPUTexture::Render{}, m_device, image, format, desc, hasDepth);

		if (not texture->isInitialized())
		{
			return Texture::IDType::NullAsset();
		}

		const String info = U"(type: Render, size:{0}x{1}, format: {2})"_fmt(image.width(), image.height(), texture->getFormat().name());
		return m_textures.add(std::move(texture), info);
	}

	Texture::IDType CTexture_WebGPU::createRT(const Grid<Float4>& image, const HasDepth hasDepth, const HasMipMap hasMipMap)
	{
		if (not image)
		{
			return Texture::IDType::NullAsset();
		}

		const TextureDesc desc = TextureDesc::Unmipped;
		const TextureFormat format = TextureFormat::R32G32B32A32_Float;
		auto texture = std::make_unique<WebGPUTexture>(WebGPUTexture::Render{}, m_device, image, format, desc, hasDepth);

		if (not texture->isInitialized())
		{
			return Texture::IDType::NullAsset();
		}

		const String info = U"(type: Render, size:{0}x{1}, format: {2})"_fmt(image.width(), image.height(), texture->getFormat().name());
		return m_textures.add(std::move(texture), info);
	}

	Texture::IDType CTexture_WebGPU::createMSRT(const Size& size, const TextureFormat& format, const HasDepth hasDepth, const HasMipMap hasMipMap)
	{
		if ((size.x <= 0) || (size.y <= 0))
		{
			return Texture::IDType::NullAsset();
		}

		const TextureDesc desc = (format.isSRGB() ? TextureDesc::UnmippedSRGB : TextureDesc::Unmipped);
		auto texture = std::make_unique<WebGPUTexture>(WebGPUTexture::MSRender{}, m_device, size, format, desc, hasDepth);

		if (not texture->isInitialized())
		{
			return Texture::IDType::NullAsset();
		}

		const String info = U"(type: MSRender, size:{0}x{1}, format: {2})"_fmt(size.x, size.y, texture->getFormat().name());
		return m_textures.add(std::move(texture), info);
	}

	void CTexture_WebGPU::release(const Texture::IDType handleID)
	{
		m_textures.erase(handleID);
	}

	Size CTexture_WebGPU::getSize(const Texture::IDType handleID)
	{
		return m_textures[handleID]->getSize();
	}

	TextureDesc CTexture_WebGPU::getDesc(const Texture::IDType handleID)
	{
		return m_textures[handleID]->getDesc();
	}

	TextureFormat CTexture_WebGPU::getFormat(const Texture::IDType handleID)
	{
		return m_textures[handleID]->getFormat();
	}

	bool CTexture_WebGPU::hasDepth(const Texture::IDType handleID)
	{
		return m_textures[handleID]->hasDepth();
	}

	bool CTexture_WebGPU::fill(const Texture::IDType handleID, const ColorF& color, const bool wait)
	{
		return m_textures[handleID]->fill(m_device, color, wait);
	}

	bool CTexture_WebGPU::fillRegion(const Texture::IDType handleID, const ColorF& color, const Rect& rect)
	{
		return m_textures[handleID]->fillRegion(m_device, color, rect);
	}

	bool CTexture_WebGPU::fill(const Texture::IDType handleID, const void* src, uint32 stride, const bool wait)
	{
		return m_textures[handleID]->fill(m_device, src, stride, wait);
	}

	bool CTexture_WebGPU::fillRegion(const Texture::IDType handleID, const void* src, const uint32 stride, const Rect& rect, const bool wait)
	{
		return m_textures[handleID]->fillRegion(m_device, src, stride, rect, wait);
	}

	void CTexture_WebGPU::clearRT(const Texture::IDType handleID, const ColorF& color)
	{
		m_textures[handleID]->clearRT(m_device, color);
	}

	void CTexture_WebGPU::generateMips(const Texture::IDType handleID)
	{

	}

	void CTexture_WebGPU::readRT(const Texture::IDType handleID, Image& image)
	{
		m_textures[handleID]->readRT(image);
	}

	void CTexture_WebGPU::readRT(const Texture::IDType handleID, Grid<float>& image)
	{
		m_textures[handleID]->readRT(image);
	}

	void CTexture_WebGPU::readRT(const Texture::IDType handleID, Grid<Float2>& image)
	{
		m_textures[handleID]->readRT(image);
	}

	void CTexture_WebGPU::readRT(const Texture::IDType handleID, Grid<Float4>& image)
	{
		m_textures[handleID]->readRT(image);
	}

	void CTexture_WebGPU::resolveMSRT(const Texture::IDType handleID)
	{
		m_textures[handleID]->resolveMSRT(m_device);
	}

	wgpu::Texture CTexture_WebGPU::getTexture(const Texture::IDType handleID)
	{
		return m_textures[handleID]->getTexture();
	}

	wgpu::TextureView CTexture_WebGPU::getTextureView(const Texture::IDType handleID)
	{
		return m_textures[handleID]->getTextureView();
	}

	wgpu::RenderPassEncoder CTexture_WebGPU::begin(Texture::IDType handleID, const wgpu::CommandEncoder& encoder)
	{
		return m_textures[handleID]->begin(encoder);
	}

	WebGPURenderTargetState CTexture_WebGPU::getRenderTargetState(Texture::IDType handleID)
	{
		return m_textures[handleID]->getRenderTargetState();
	}

	bool CTexture_WebGPU::isMainThread() const noexcept
	{
		return (std::this_thread::get_id() == m_mainThreadID);
	}

	Texture::IDType CTexture_WebGPU::pushRequest(const Image& image, const Array<Image>& mipmaps, const TextureDesc desc)
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
