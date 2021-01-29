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
# include <Siv3D/FloatRect.hpp>
# include <Siv3D/FreestandingMessageBox/FreestandingMessageBox.hpp>
# include <Siv3D/Texture/ITexture.hpp>
# include <Siv3D/ImageProcessing.hpp>
# include <Siv3D/Renderer2D/IRenderer2D.hpp>
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

	RectF Texture::draw(const ColorF& diffuse) const
	{
		return draw(0.0, 0.0, diffuse);
	}

	RectF Texture::draw(const ColorF& color0, const ColorF& color1, const ColorF& color2, const ColorF& color3) const
	{
		return draw(0.0, 0.0, color0, color1, color2, color3);
	}

	RectF Texture::draw(Arg::top_<ColorF> topColor, Arg::bottom_<ColorF> bottomColor) const
	{
		return draw(*topColor, *topColor, *bottomColor, *bottomColor);
	}

	RectF Texture::draw(Arg::left_<ColorF> leftColor, Arg::right_<ColorF> rightColor) const
	{
		return draw(*leftColor, *rightColor, *rightColor, *leftColor);
	}

	RectF Texture::draw(const double x, const double y, const ColorF& diffuse) const
	{
		const Size size = SIV3D_ENGINE(Texture)->getSize(m_handle->id());

		SIV3D_ENGINE(Renderer2D)->addTextureRegion(
			*this,
			FloatRect{ x, y, x + size.x, y + size.y },
			FloatRect{ 0.0f, 0.0f, 1.0f, 1.0f },
			diffuse.toFloat4()
		);

		return{ x, y, size };
	}

	RectF Texture::draw(const double x, const double y, const ColorF& color0, const ColorF& color1, const ColorF& color2, const ColorF& color3) const
	{
		const Size size = SIV3D_ENGINE(Texture)->getSize(m_handle->id());

		SIV3D_ENGINE(Renderer2D)->addTextureRegion(
			*this,
			FloatRect{ x, y, x + size.x, y + size.y },
			FloatRect{ 0.0f, 0.0f, 1.0f, 1.0f },
			{ color0.toFloat4(), color1.toFloat4(), color2.toFloat4(), color3.toFloat4() }
		);

		return{ x, y, size };
	}

	RectF Texture::draw(const double x, const double y, Arg::top_<ColorF> topColor, Arg::bottom_<ColorF> bottomColor) const
	{
		return draw(x, y, *topColor, *topColor, *bottomColor, *bottomColor);
	}

	RectF Texture::draw(const double x, const double y, Arg::left_<ColorF> leftColor, Arg::right_<ColorF> rightColor) const
	{
		return draw(x, y, *leftColor, *rightColor, *rightColor, *leftColor);
	}

	RectF Texture::draw(const Vec2& pos, const ColorF& diffuse) const
	{
		return draw(pos.x, pos.y, diffuse);
	}

	RectF Texture::draw(const Vec2& pos, const ColorF& color0, const ColorF& color1, const ColorF& color2, const ColorF& color3) const
	{
		return draw(pos.x, pos.y, color0, color1, color2, color3);
	}

	RectF Texture::draw(const Vec2& pos, Arg::top_<ColorF> topColor, Arg::bottom_<ColorF> bottomColor) const
	{
		return draw(pos.x, pos.y, *topColor, *topColor, *bottomColor, *bottomColor);
	}

	RectF Texture::draw(const Vec2& pos, Arg::left_<ColorF> leftColor, Arg::right_<ColorF> rightColor) const
	{
		return draw(pos.x, pos.y, *leftColor, *rightColor, *rightColor, *leftColor);
	}


	RectF Texture::draw(Arg::topLeft_<Vec2> topLeft, const ColorF& diffuse) const
	{
		return draw(topLeft->x, topLeft->y, diffuse);
	}

	RectF Texture::draw(Arg::topRight_<Vec2> topRight, const ColorF& diffuse) const
	{
		return draw(topRight->x - width(), topRight->y, diffuse);
	}

	RectF Texture::draw(Arg::bottomLeft_<Vec2> bottomLeft, const ColorF& diffuse) const
	{
		return draw(bottomLeft->x, bottomLeft->y - height(), diffuse);
	}

	RectF Texture::draw(Arg::bottomRight_<Vec2> bottomRight, const ColorF& diffuse) const
	{
		return draw(bottomRight->x - width(), bottomRight->y - height(), diffuse);
	}

	RectF Texture::draw(Arg::topCenter_<Vec2> topCenter, const ColorF& diffuse) const
	{
		return draw(topCenter->x - width() * 0.5, topCenter->y, diffuse);
	}

	RectF Texture::draw(Arg::bottomCenter_<Vec2> bottomCenter, const ColorF& diffuse) const
	{
		return draw(bottomCenter->x - width() * 0.5, bottomCenter->y - height(), diffuse);
	}

	RectF Texture::draw(Arg::leftCenter_<Vec2> leftCenter, const ColorF& diffuse) const
	{
		return draw(leftCenter->x, leftCenter->y - height() * 0.5, diffuse);
	}

	RectF Texture::draw(Arg::rightCenter_<Vec2>rightCenter, const ColorF& diffuse) const
	{
		return draw(rightCenter->x - width(), rightCenter->y - height() * 0.5, diffuse);
	}

	RectF Texture::draw(Arg::center_<Vec2> center, const ColorF& diffuse) const
	{
		return drawAt(center->x, center->y, diffuse);
	}

	RectF Texture::drawAt(const double x, const double y, const ColorF& diffuse) const
	{
		const Size size = SIV3D_ENGINE(Texture)->getSize(m_handle->id());
		const double wHalf = (size.x * 0.5);
		const double hHalf = (size.y * 0.5);

		SIV3D_ENGINE(Renderer2D)->addTextureRegion(
			*this,
			{ (x - wHalf), (y - hHalf), (x + wHalf), (y + hHalf) },
			{ 0.0f, 0.0f, 1.0f, 1.0f },
			diffuse.toFloat4()
		);

		return{ (x - wHalf), (y - hHalf), size };
	}

	RectF Texture::drawAt(const double x, const double y, const ColorF& color0, const ColorF& color1, const ColorF& color2, const ColorF& color3) const
	{
		const Size size = SIV3D_ENGINE(Texture)->getSize(m_handle->id());
		const double wHalf = (size.x * 0.5);
		const double hHalf = (size.y * 0.5);

		SIV3D_ENGINE(Renderer2D)->addTextureRegion(
			*this,
			{ (x - wHalf), (y - hHalf), (x + wHalf), (y + hHalf) },
			{ 0.0f, 0.0f, 1.0f, 1.0f },
			{ color0.toFloat4(), color1.toFloat4(), color2.toFloat4(), color3.toFloat4() }
		);

		return{ (x - wHalf), (y - hHalf), size };
	}

	RectF Texture::drawAt(const Vec2& pos, const ColorF& diffuse) const
	{
		return drawAt(pos.x, pos.y, diffuse);
	}

	RectF Texture::drawAt(const Vec2& pos, const ColorF& color0, const ColorF& color1, const ColorF& color2, const ColorF& color3) const
	{
		return drawAt(pos.x, pos.y, color0, color1, color2, color3);
	}
}
