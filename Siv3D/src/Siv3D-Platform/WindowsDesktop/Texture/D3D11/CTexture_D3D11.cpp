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
# include "CTexture_D3D11.hpp"

namespace s3d
{
	namespace detail
	{
		Array<Byte> GenerateInitialColorBuffer(const Size& size, const ColorF& color, const TextureFormat& format)
		{
			const size_t num_pixels = size.x * size.y;

			if (format == TextureFormat::R8G8B8A8_Unorm)
			{
				Array<Byte> bytes(num_pixels * sizeof(uint32));

				const uint32 value = Color(color).asUint32();

				uint32* pDst = static_cast<uint32*>(static_cast<void*>(bytes.data()));

				for (size_t i = 0; i < num_pixels; ++i)
				{
					*pDst++ = value;
				}

				return bytes;
			}

			return Array<Byte>();
		}
	}

	CTexture_D3D11::~CTexture_D3D11()
	{
		LOG_TRACE(U"CTexture_D3D11::~CTexture_D3D11()");

		m_textures.destroy();
	}

	void CTexture_D3D11::init(ID3D11Device* const device, ID3D11DeviceContext* const context)
	{
		LOG_TRACE(U"CTexture_D3D11::init()");

		// device と context をコピー
		m_device = device;
		m_context = context;

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

			LOG_INFO(U"4x MSAA support:");

			for (size_t i = 1; i < formats.size(); ++i)
			{
				const String name(formats[i].name());
				const int32 dxgiFormat = formats[i].DXGIFormat();

				if (UINT quality = 0; SUCCEEDED(m_device->CheckMultisampleQualityLevels(
					DXGI_FORMAT(dxgiFormat), 4, &quality)) && (0 < quality))
				{
					m_multiSampleAvailable[i] = true;
					LOG_DEBUG(U"{} ✔"_fmt(name));
				}
				else
				{
					LOG_DEBUG(U"{} ✘"_fmt(name));
				}
			}
		}

		// null テクスチャを作成し、管理に登録
		{
			const Image image(16, Palette::Yellow);
			const Array<Image> mips = {
				Image(8, Palette::Yellow), Image(4, Palette::Yellow),
				Image(2, Palette::Yellow), Image(1, Palette::Yellow)
			};

			auto nullTexture = std::make_unique<Texture_D3D11>(device, image, mips, TextureDesc::Mipped);

			if (!nullTexture->isInitialized())
			{
				throw EngineError(U"Null Texture initialization failed");
			}

			m_textures.setNullData(std::move(nullTexture));
		}

		LOG_INFO(U"ℹ️ CTexture_D3D11 initialized");
	}

	void CTexture_D3D11::updateAsync(size_t)
	{
		// do nothing
	}

	TextureID CTexture_D3D11::createUnmipped(const Image& image, const TextureDesc desc)
	{
		if (!image)
		{
			return TextureID::NullAsset();
		}

		auto texture = std::make_unique<Texture_D3D11>(m_device, image, desc);

		if (!texture->isInitialized())
		{
			return TextureID::NullAsset();
		}

		const String info = U"(type: Normal, size:{0}x{1}, format: {2})"_fmt(image.width(), image.height(), texture->getDesc().format.name());
		return m_textures.add(std::move(texture), info);
	}

	TextureID CTexture_D3D11::create(const Image& image, const Array<Image>& mips, TextureDesc desc)
	{
		if (!image)
		{
			return TextureID::NullAsset();
		}

		auto texture = std::make_unique<Texture_D3D11>(m_device, image, mips, desc);

		if (!texture->isInitialized())
		{
			return TextureID::NullAsset();
		}

		const String info = U"(type: Normal, size: {0}x{1}, format: {2})"_fmt(image.width(), image.height(), texture->getDesc().format.name());
		return m_textures.add(std::move(texture), info);
	}

	TextureID CTexture_D3D11::createDynamic(const Size& size, const void* pData, const uint32 stride, const TextureFormat& format, const TextureDesc desc)
	{
		auto texture = std::make_unique<Texture_D3D11>(Texture_D3D11::Dynamic(), m_device, size, pData, stride, format, desc);

		if (!texture->isInitialized())
		{
			return TextureID::NullAsset();
		}

		const String info = U"(type: Dynamic, size: {0}x{1}, format: {2})"_fmt(size.x, size.y, texture->getDesc().format.name());
		return m_textures.add(std::move(texture), info);
	}

	TextureID CTexture_D3D11::createDynamic(const Size& size, const ColorF& color, const TextureFormat& format, const TextureDesc desc)
	{
		const Array<Byte> initialData = detail::GenerateInitialColorBuffer(size, color, format);

		return createDynamic(size, initialData.data(), static_cast<uint32>(initialData.size() / size.y), format, desc);
	}

	TextureID CTexture_D3D11::createRT(const Size& size, const TextureFormat& format)
	{
		const TextureDesc desc = format.isSRGB() ? TextureDesc::UnmippedSRGB : TextureDesc::Unmipped;

		auto texture = std::make_unique<Texture_D3D11>(Texture_D3D11::Render(), m_device, size, format, desc);

		if (!texture->isInitialized())
		{
			return TextureID::NullAsset();
		}

		const String info = U"(type: Render, size: {0}x{1}, format: {2})"_fmt(size.x, size.y, texture->getDesc().format.name());
		return m_textures.add(std::move(texture), info);
	}

	TextureID CTexture_D3D11::createRT(const Image& image)
	{
		const TextureDesc desc = TextureDesc::Unmipped;
		const TextureFormat format = TextureFormat::R8G8B8A8_Unorm;

		auto texture = std::make_unique<Texture_D3D11>(Texture_D3D11::Render(), m_device, image, format, desc);

		if (!texture->isInitialized())
		{
			return TextureID::NullAsset();
		}

		const String info = U"(type: Render, size: {0}x{1}, format: {2})"_fmt(image.width(), image.height(), texture->getDesc().format.name());
		return m_textures.add(std::move(texture), info);
	}

	TextureID CTexture_D3D11::createRT(const Grid<float>& image)
	{
		const TextureDesc desc = TextureDesc::Unmipped;
		const TextureFormat format = TextureFormat::R32_Float;

		auto texture = std::make_unique<Texture_D3D11>(Texture_D3D11::Render(), m_device, image, format, desc);

		if (!texture->isInitialized())
		{
			return TextureID::NullAsset();
		}

		const String info = U"(type: Render, size: {0}x{1}, format: {2})"_fmt(image.width(), image.height(), texture->getDesc().format.name());
		return m_textures.add(std::move(texture), info);
	}

	TextureID CTexture_D3D11::createRT(const Grid<Float2>& image)
	{
		const TextureDesc desc = TextureDesc::Unmipped;
		const TextureFormat format = TextureFormat::R32G32_Float;

		auto texture = std::make_unique<Texture_D3D11>(Texture_D3D11::Render(), m_device, image, format, desc);

		if (!texture->isInitialized())
		{
			return TextureID::NullAsset();
		}

		const String info = U"(type: Render, size: {0}x{1}, format: {2})"_fmt(image.width(), image.height(), texture->getDesc().format.name());
		return m_textures.add(std::move(texture), info);
	}

	TextureID CTexture_D3D11::createRT(const Grid<Float4>& image)
	{
		const TextureDesc desc = TextureDesc::Unmipped;
		const TextureFormat format = TextureFormat::R32G32B32A32_Float;

		auto texture = std::make_unique<Texture_D3D11>(Texture_D3D11::Render(), m_device, image, format, desc);

		if (!texture->isInitialized())
		{
			return TextureID::NullAsset();
		}

		const String info = U"(type: Render, size: {0}x{1}, format: {2})"_fmt(image.width(), image.height(), texture->getDesc().format.name());
		return m_textures.add(std::move(texture), info);
	}

	TextureID CTexture_D3D11::createMSRT(const Size& size, const TextureFormat& format)
	{
		if (!m_multiSampleAvailable[FromEnum(format.value())]) // もし 4x MSAA がサポートされていなければ
		{
			LOG_FAIL(U"TextureFormat {} does not support 4x MSAA on this hardware");
			return TextureID::NullAsset();
		}

		const TextureDesc desc = format.isSRGB() ? TextureDesc::UnmippedSRGB : TextureDesc::Unmipped;

		auto texture = std::make_unique<Texture_D3D11>(Texture_D3D11::MSRender(), m_device, size, format, desc);

		if (!texture->isInitialized())
		{
			return TextureID::NullAsset();
		}

		const String info = U"(type: MSRender, size: {0}x{1}, format: {2})"_fmt(size.x, size.y, texture->getDesc().format.name());
		return m_textures.add(std::move(texture), info);
	}

	void CTexture_D3D11::release(const TextureID handleID)
	{
		m_textures.erase(handleID);
	}

	Size CTexture_D3D11::getSize(const TextureID handleID)
	{
		return m_textures[handleID]->getDesc().size;
	}

	TextureDesc CTexture_D3D11::getDesc(const TextureID handleID)
	{
		return m_textures[handleID]->getDesc().desc;
	}

	TextureFormat CTexture_D3D11::getFormat(const TextureID handleID)
	{
		return m_textures[handleID]->getDesc().format;
	}

	ID3D11ShaderResourceView** CTexture_D3D11::getSRVPtr(const TextureID handleID)
	{
		return m_textures[handleID]->getSRVPtr();
	}

	ID3D11RenderTargetView* CTexture_D3D11::getRTV(const TextureID handleID)
	{
		return m_textures[handleID]->getRTV();
	}

	void CTexture_D3D11::clearRT(const TextureID handleID, const ColorF& color)
	{
		m_textures[handleID]->clearRT(m_context, color);
	}

	void CTexture_D3D11::readRT(const TextureID handleID, Image& image)
	{
		m_textures[handleID]->readRT(m_device, m_context, image);
	}

	void CTexture_D3D11::readRT(const TextureID handleID, Grid<float>& image)
	{
		m_textures[handleID]->readRT(m_device, m_context, image);
	}

	void CTexture_D3D11::readRT(const TextureID handleID, Grid<Float2>& image)
	{
		m_textures[handleID]->readRT(m_device, m_context, image);
	}

	void CTexture_D3D11::readRT(const TextureID handleID, Grid<Float4>& image)
	{
		m_textures[handleID]->readRT(m_device, m_context, image);
	}

	void CTexture_D3D11::resolveMSRT(const TextureID handleID)
	{
		m_textures[handleID]->resolveMSRT(m_context);
	}

	bool CTexture_D3D11::fill(const TextureID handleID, const ColorF& color, const bool wait)
	{
		return m_textures[handleID]->fill(m_context, color, wait);
	}

	bool CTexture_D3D11::fillRegion(TextureID handleID, const ColorF& color, const Rect& rect)
	{
		return m_textures[handleID]->fillRegion(m_context, color, rect);
	}

	bool CTexture_D3D11::fill(const TextureID handleID, const void* const src, const uint32 stride, const bool wait)
	{
		return m_textures[handleID]->fill(m_context, src, stride, wait);
	}

	bool CTexture_D3D11::fillRegion(TextureID handleID, const void* src, uint32 stride, const Rect& rect, const bool wait)
	{
		return m_textures[handleID]->fillRegion(m_context, src, stride, rect, wait);
	}
}
