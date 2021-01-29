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

# include <Siv3D/Texture.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/2DShapes.hpp>
# include <Siv3D/FreestandingMessageBox/FreestandingMessageBox.hpp>
# include <Siv3D/Texture/ITexture.hpp>
# include <Siv3D/ImageProcessing.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	template <>
	AssetIDWrapper<AssetHandle<Texture>>::AssetIDWrapper()
	{
		if (not Siv3DEngine::isActive())
		{
			FreestandingMessageBox::ShowError(U"`Texture` must be initialized after engine-setup. Please fix the C++ code.");
			std::abort();
		}
	}

	template <>
	AssetIDWrapper<AssetHandle<Texture>>::~AssetIDWrapper()
	{
		LOG_INFO(U"pTexture->release({})"_fmt(m_id.value()));
	}

	Texture::Texture()
	{

	}

	Texture::Texture(const Image& image, const TextureDesc desc)
		: AssetHandle{ std::make_shared<AssetIDWrapperType>(
			detail::IsMipped(desc) ?
				SIV3D_ENGINE(Texture)->createMipped(image, ImageProcessing::GenerateMips(image), desc) :
				SIV3D_ENGINE(Texture)->createUnmipped(image, desc)) }
	{
		//ReportAssetCreation();
	}

	Texture::Texture(const Image& image, const Array<Image>& mipmaps, const TextureDesc desc)
		: AssetHandle{ std::make_shared<AssetIDWrapperType>(SIV3D_ENGINE(Texture)->createMipped(image, mipmaps, desc)) }
	{
		//ReportAssetCreation();
	}

	Texture::Texture(const FilePathView path, const TextureDesc desc)
		: Texture{ Image{ path }, desc }
	{

	}

	Texture::Texture(IReader&& reader, const TextureDesc desc)
		: Texture{ Image{ std::move(reader) }, desc }
	{

	}

	Texture::Texture(const FilePathView rgb, const FilePathView alpha, const TextureDesc desc)
		: Texture{ Image{ rgb, alpha }, desc }
	{

	}

	Texture::Texture(const Color& rgb, const FilePathView alpha, const TextureDesc desc)
		: Texture{ Image{ rgb, alpha }, desc }
	{

	}

	Texture::~Texture()
	{

	}

	int32 Texture::width() const
	{
		return SIV3D_ENGINE(Texture)->getSize(m_handle->id()).x;
	}

	int32 Texture::height() const
	{
		return SIV3D_ENGINE(Texture)->getSize(m_handle->id()).y;
	}

	Size Texture::size() const
	{
		return SIV3D_ENGINE(Texture)->getSize(m_handle->id());
	}

	TextureDesc Texture::getDesc() const
	{
		return SIV3D_ENGINE(Texture)->getDesc(m_handle->id());
	}

	TextureFormat Texture::getFormat() const
	{
		return SIV3D_ENGINE(Texture)->getFormat(m_handle->id());
	}

	bool Texture::isMipped() const
	{
		return detail::IsMipped(SIV3D_ENGINE(Texture)->getDesc(m_handle->id()));
	}

	bool Texture::isSDF() const
	{
		return detail::IsSDF(SIV3D_ENGINE(Texture)->getDesc(m_handle->id()));
	}

	Rect Texture::region(const int32 x, const int32 y) const
	{
		return{ x, y, size() };
	}

	Rect Texture::region(const Point pos) const
	{
		return region(pos.x, pos.y);
	}

	RectF Texture::region(const double x, const double y) const
	{
		return{ x, y, size() };
	}

	RectF Texture::region(const Vec2 pos) const
	{
		return region(pos.x, pos.y);
	}

	RectF Texture::regionAt(const double x, const double y) const
	{
		const Size s = size();
		return{ x - s.x * 0.5, y - s.y * 0.5, s };
	}

	RectF Texture::regionAt(const Vec2 pos) const
	{
		return regionAt(pos.x, pos.y);
	}
}
