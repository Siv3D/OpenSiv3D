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

# include "CTexture_D3D11.hpp"
# include <Siv3D/Error.hpp>
# include <Siv3D/Byte.hpp>
# include <Siv3D/ImageProcessing.hpp>
# include <Siv3D/HalfFloat.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/Texture/TextureCommon.hpp>

namespace s3d
{
	CTexture_D3D11::CTexture_D3D11()
	{
		// do nothing
	}

	CTexture_D3D11::~CTexture_D3D11()
	{
		LOG_SCOPED_TRACE(U"CTexture_D3D11::~CTexture_D3D11()");

		m_textures.destroy();
	}

	void CTexture_D3D11::init()
	{
		LOG_SCOPED_TRACE(U"CTexture_D3D11::init()");

		pRenderer	= static_cast<CRenderer_D3D11*>(SIV3D_ENGINE(Renderer));
		m_device	= pRenderer->getDevice();
		m_context	= pRenderer->getContext();

		// 4x MSAA サポート状況を取得
		{
			constexpr std::array<TextureFormat, 10> formats =
			{
				TextureFormat::Unknown,
				TextureFormat::R8G8B8A8_Unorm,
				TextureFormat::R8G8B8A8_Unorm_SRGB,
				TextureFormat::R16G16_Float,
				TextureFormat::R32_Float,
				TextureFormat::R10G10B10A2_Unorm,
				TextureFormat::R11G11B10_UFloat,
				TextureFormat::R16G16B16A16_Float,
				TextureFormat::R32G32_Float,
				TextureFormat::R32G32B32A32_Float,
			};

			String logText = U"4x MSAA support:\n";

			for (size_t i = 1; i < formats.size(); ++i)
			{
				const String name(formats[i].name());
				const int32 dxgiFormat = formats[i].DXGIFormat();

				if (UINT quality = 0; SUCCEEDED(m_device->CheckMultisampleQualityLevels(
					DXGI_FORMAT(dxgiFormat), 4, &quality)) && (0 < quality))
				{
					m_multiSampleAvailable[i] = true;
					logText += (U"{} ✔\n"_fmt(name));
				}
				else
				{
					logText += (U"{} ✘\n"_fmt(name));
				}
			}

			logText.pop_back();
			LOG_INFO(logText);
		}

		// null Texture を管理に登録
		{
			const Image image{ 16, Palette::Yellow };
			const Array<Image> mips = {
				Image{ 8, Palette::Yellow }, Image{ 4, Palette::Yellow },
				Image{ 2, Palette::Yellow }, Image{ 1, Palette::Yellow }
			};

			// null Texture を作成
			auto nullTexture = std::make_unique<D3D11Texture>(m_device, image, mips, TextureDesc::Mipped);

			if (not nullTexture->isInitialized()) // もし作成に失敗していたら
			{
				throw EngineError(U"Null Texture initialization failed");
			}

			// 管理に登録
			m_textures.setNullData(std::move(nullTexture));
		}
	}

	void CTexture_D3D11::updateAsyncTextureLoad(const size_t)
	{
		// do nothing
	}

	size_t CTexture_D3D11::getTextureCount() const
	{
		return m_textures.size();
	}

	Texture::IDType CTexture_D3D11::create(const Image& image, const TextureDesc desc)
	{
		if (not image)
		{
			return Texture::IDType::NullAsset();
		}

		auto texture = std::make_unique<D3D11Texture>(m_device, image, desc);

		if (not texture->isInitialized())
		{
			return Texture::IDType::NullAsset();
		}

		if (detail::HasMipMap(desc))
		{
			texture->generateMips(m_context);
		}

		const String info = U"(type: Default, size:{0}x{1}, format: {2})"_fmt(image.width(), image.height(), texture->getDesc().format.name());
		return m_textures.add(std::move(texture), info);
	}

	Texture::IDType CTexture_D3D11::create(const Image& image, const Array<Image>& mips, const TextureDesc desc)
	{
		if (not image)
		{
			return Texture::IDType::NullAsset();
		}

		auto texture = std::make_unique<D3D11Texture>(m_device, image, mips, desc);

		if (not texture->isInitialized())
		{
			return Texture::IDType::NullAsset();
		}

		const String info = U"(type: Default, size: {0}x{1}, format: {2})"_fmt(image.width(), image.height(), texture->getDesc().format.name());
		return m_textures.add(std::move(texture), info);
	}

	Texture::IDType CTexture_D3D11::createDynamic(const Size& size, const void* pData, uint32 stride, const TextureFormat& format, const TextureDesc desc)
	{
		if ((size.x <= 0) || (size.y <= 0))
		{
			return Texture::IDType::NullAsset();
		}

		auto texture = std::make_unique<D3D11Texture>(D3D11Texture::Dynamic{}, m_device, size, pData, stride, format, desc);

		if (not texture->isInitialized())
		{
			return Texture::IDType::NullAsset();
		}

		const String info = U"(type: Dynamic, size: {0}x{1}, format: {2})"_fmt(size.x, size.y, texture->getDesc().format.name());
		return m_textures.add(std::move(texture), info);
	}

	Texture::IDType CTexture_D3D11::createDynamic(const Size& size, const ColorF& color, const TextureFormat& format, const TextureDesc desc)
	{
		const Array<Byte> initialData = GenerateInitialColorBuffer(size, color, format);

		if (not initialData)
		{
			return Texture::IDType::NullAsset();
		}

		return createDynamic(size, initialData.data(), static_cast<uint32>(initialData.size() / size.y), format, desc);
	}

	Texture::IDType CTexture_D3D11::createRT(const Size& size, const TextureFormat& format, const HasDepth hasDepth, const HasMipMap hasMipMap)
	{
		if ((size.x <= 0) || (size.y <= 0))
		{
			return Texture::IDType::NullAsset();
		}

		const TextureDesc desc = detail::MakeTextureDesc(hasMipMap.getBool(), format.isSRGB());
		auto texture = std::make_unique<D3D11Texture>(D3D11Texture::Render{}, m_device, size, format, desc, hasDepth);

		if (not texture->isInitialized())
		{
			return Texture::IDType::NullAsset();
		}

		const String info = U"(type: Render, size:{0}x{1}, format: {2})"_fmt(size.x, size.y, texture->getDesc().format.name());
		return m_textures.add(std::move(texture), info);
	}

	Texture::IDType CTexture_D3D11::createRT(const Image& image, const HasDepth hasDepth, const HasMipMap hasMipMap)
	{
		if (not image)
		{
			return Texture::IDType::NullAsset();
		}

		const TextureDesc desc = detail::MakeTextureDesc(hasMipMap.getBool(), false);
		const TextureFormat format = TextureFormat::R8G8B8A8_Unorm;
		auto texture = std::make_unique<D3D11Texture>(D3D11Texture::Render{}, m_device, image, format, desc, hasDepth);

		if (not texture->isInitialized())
		{
			return Texture::IDType::NullAsset();
		}

		if (hasMipMap)
		{
			texture->generateMips(m_context);
		}

		const String info = U"(type: Render, size:{0}x{1}, format: {2})"_fmt(image.width(), image.height(), texture->getDesc().format.name());
		return m_textures.add(std::move(texture), info);
	}

	Texture::IDType CTexture_D3D11::createRT(const Grid<float>& image, const HasDepth hasDepth, const HasMipMap hasMipMap)
	{
		if (not image)
		{
			return Texture::IDType::NullAsset();
		}

		const TextureDesc desc = detail::MakeTextureDesc(hasMipMap.getBool(), false);
		const TextureFormat format = TextureFormat::R32_Float;
		auto texture = std::make_unique<D3D11Texture>(D3D11Texture::Render{}, m_device, image, format, desc, hasDepth);

		if (not texture->isInitialized())
		{
			return Texture::IDType::NullAsset();
		}

		if (hasMipMap)
		{
			texture->generateMips(m_context);
		}

		const String info = U"(type: Render, size:{0}x{1}, format: {2})"_fmt(image.width(), image.height(), texture->getDesc().format.name());
		return m_textures.add(std::move(texture), info);
	}

	Texture::IDType CTexture_D3D11::createRT(const Grid<Float2>& image, const HasDepth hasDepth, const HasMipMap hasMipMap)
	{
		if (not image)
		{
			return Texture::IDType::NullAsset();
		}

		const TextureDesc desc = detail::MakeTextureDesc(hasMipMap.getBool(), false);
		const TextureFormat format = TextureFormat::R32G32_Float;
		auto texture = std::make_unique<D3D11Texture>(D3D11Texture::Render{}, m_device, image, format, desc, hasDepth);

		if (not texture->isInitialized())
		{
			return Texture::IDType::NullAsset();
		}

		if (hasMipMap)
		{
			texture->generateMips(m_context);
		}

		const String info = U"(type: Render, size:{0}x{1}, format: {2})"_fmt(image.width(), image.height(), texture->getDesc().format.name());
		return m_textures.add(std::move(texture), info);
	}

	Texture::IDType CTexture_D3D11::createRT(const Grid<Float4>& image, const HasDepth hasDepth, const HasMipMap hasMipMap)
	{
		if (not image)
		{
			return Texture::IDType::NullAsset();
		}

		const TextureDesc desc = detail::MakeTextureDesc(hasMipMap.getBool(), false);
		const TextureFormat format = TextureFormat::R32G32B32A32_Float;
		auto texture = std::make_unique<D3D11Texture>(D3D11Texture::Render{}, m_device, image, format, desc, hasDepth);

		if (not texture->isInitialized())
		{
			return Texture::IDType::NullAsset();
		}

		if (hasMipMap)
		{
			texture->generateMips(m_context);
		}

		const String info = U"(type: Render, size:{0}x{1}, format: {2})"_fmt(image.width(), image.height(), texture->getDesc().format.name());
		return m_textures.add(std::move(texture), info);
	}

	Texture::IDType CTexture_D3D11::createMSRT(const Size& size, const TextureFormat& format, const HasDepth hasDepth, const HasMipMap hasMipMap)
	{
		if (not m_multiSampleAvailable[FromEnum(format.value())]) // もし 4x MSAA がサポートされていなければ
		{
			LOG_FAIL(U"TextureFormat {} does not support 4x MSAA on this hardware");
			return Texture::IDType::NullAsset();
		}

		if ((size.x <= 0) || (size.y <= 0))
		{
			return Texture::IDType::NullAsset();
		}

		const TextureDesc desc = detail::MakeTextureDesc(hasMipMap.getBool(), format.isSRGB());
		auto texture = std::make_unique<D3D11Texture>(D3D11Texture::MSRender{}, m_device, size, format, desc, hasDepth);

		if (not texture->isInitialized())
		{
			return Texture::IDType::NullAsset();
		}

		const String info = U"(type: MSRender, size:{0}x{1}, format: {2})"_fmt(size.x, size.y, texture->getDesc().format.name());
		return m_textures.add(std::move(texture), info);
	}

	void CTexture_D3D11::release(const Texture::IDType handleID)
	{
		m_textures.erase(handleID);
	}

	Size CTexture_D3D11::getSize(const Texture::IDType handleID)
	{
		return m_textures[handleID]->getDesc().size;
	}

	TextureDesc CTexture_D3D11::getDesc(const Texture::IDType handleID)
	{
		return m_textures[handleID]->getDesc().desc;
	}

	TextureFormat CTexture_D3D11::getFormat(const Texture::IDType handleID)
	{
		return m_textures[handleID]->getDesc().format;
	}

	bool CTexture_D3D11::hasDepth(const Texture::IDType handleID)
	{
		return m_textures[handleID]->hasDepth();
	}

	bool CTexture_D3D11::fill(const Texture::IDType handleID, const ColorF& color, const bool wait)
	{
		return m_textures[handleID]->fill(m_context, color, wait);
	}

	bool CTexture_D3D11::fillRegion(const Texture::IDType handleID, const ColorF& color, const Rect& rect)
	{
		return m_textures[handleID]->fillRegion(m_context, color, rect);
	}

	bool CTexture_D3D11::fill(const Texture::IDType handleID, const void* src, uint32 stride, const bool wait)
	{
		return m_textures[handleID]->fill(m_context, src, stride, wait);
	}

	bool CTexture_D3D11::fillRegion(const Texture::IDType handleID, const void* src, const uint32 stride, const Rect& rect, const bool wait)
	{
		return m_textures[handleID]->fillRegion(m_context, src, stride, rect, wait);
	}

	void CTexture_D3D11::clearRT(const Texture::IDType handleID, const ColorF& color)
	{
		m_textures[handleID]->clearRT(m_context, color);
	}

	void CTexture_D3D11::generateMips(const Texture::IDType handleID)
	{
		m_textures[handleID]->generateMips(m_context);
	}

	void CTexture_D3D11::readRT(const Texture::IDType handleID, Image& image)
	{
		m_textures[handleID]->readRT(m_device, m_context, image);
	}

	void CTexture_D3D11::readRT(const Texture::IDType handleID, Grid<float>& image)
	{
		m_textures[handleID]->readRT(m_device, m_context, image);
	}

	void CTexture_D3D11::readRT(const Texture::IDType handleID, Grid<Float2>& image)
	{
		m_textures[handleID]->readRT(m_device, m_context, image);
	}

	void CTexture_D3D11::readRT(const Texture::IDType handleID, Grid<Float4>& image)
	{
		m_textures[handleID]->readRT(m_device, m_context, image);
	}

	void CTexture_D3D11::resolveMSRT(const Texture::IDType handleID)
	{
		m_textures[handleID]->resolveMSRT(m_context);
	}

	ID3D11Texture2D* CTexture_D3D11::getTexture(const Texture::IDType handleID)
	{
		return m_textures[handleID]->getTexture();
	}

	ID3D11ShaderResourceView** CTexture_D3D11::getSRVPtr(const Texture::IDType handleID)
	{
		return m_textures[handleID]->getSRVPtr();
	}

	ID3D11RenderTargetView* CTexture_D3D11::getRTV(const Texture::IDType handleID)
	{
		return m_textures[handleID]->getRTV();
	}

	ID3D11DepthStencilView* CTexture_D3D11::getDSV(const Texture::IDType handleID)
	{
		return m_textures[handleID]->getDSV();
	}
}
