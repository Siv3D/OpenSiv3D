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

# include <Siv3DEngine.hpp>
# include <Renderer2D/IRenderer2D.hpp>
# include <AssetHandleManager/AssetReport.hpp>
# include <Siv3D/EngineMessageBox.hpp>
# include <Siv3D/Rectangle.hpp>
# include <Siv3D/Texture.hpp>
# include <Siv3D/FloatRect.hpp>
# include <Siv3D/TextureRegion.hpp>
# include <Siv3D/TexturedQuad.hpp>
# include <Siv3D/Image.hpp>
# include <Siv3D/ImageProcessing.hpp>
# include <Siv3D/Emoji.hpp>
# include <Siv3D/Icon.hpp>
# include "ITexture.hpp"

namespace s3d
{
	template <>
	AssetHandle<Texture::Tag>::AssetHandle()
	{
		if (!Siv3DEngine::isActive())
		{
			EngineMessageBox::Show(U"`Texture` must be initialized after engine setup.");
			std::exit(-1);
		}
	}

	template <>
	AssetHandle<Texture::Tag>::AssetHandle(const IDWrapperType id) noexcept
		: m_id(id)
	{
		if (!Siv3DEngine::isActive())
		{
			EngineMessageBox::Show(U"`Texture` must be initialized after engine setup.");
			std::exit(-1);
		}
	}

	template <>
	AssetHandle<Texture::Tag>::~AssetHandle()
	{
		if (!Siv3DEngine::isActive())
		{
			return;
		}
		
		if (auto p = Siv3DEngine::Get<ISiv3DTexture>())
		{
			p->release(m_id);
		}
	}

	Texture::Texture(Dynamic, const uint32 width, const uint32 height, const void* pData, const uint32 stride, const TextureFormat format, const TextureDesc desc)
		: m_handle(std::make_shared<TextureHandle>(Siv3DEngine::Get<ISiv3DTexture>()->createDynamic(Size(width, height), pData, stride, format, desc)))
	{
		ReportAssetCreation();
	}

	Texture::Texture(Dynamic, const uint32 width, const uint32 height, const ColorF& color, const TextureFormat format, const TextureDesc desc)
		: m_handle(std::make_shared<TextureHandle>(Siv3DEngine::Get<ISiv3DTexture>()->createDynamic(Size(width, height), color, format, desc)))
	{
		ReportAssetCreation();
	}

	Texture::Texture(Render, const uint32 width, const uint32 height, TextureFormat format)
		: m_handle(std::make_shared<TextureHandle>(Siv3DEngine::Get<ISiv3DTexture>()->createRT(Size(width, height), format)))
	{
		ReportAssetCreation();
	}

	Texture::Texture(Render, const Image& image)
		: m_handle(std::make_shared<TextureHandle>(Siv3DEngine::Get<ISiv3DTexture>()->createRT(image)))
	{

	}

	Texture::Texture()
		: m_handle(std::make_shared<TextureHandle>())
	{

	}

	Texture::Texture(const Image& image, const TextureDesc desc)
		: m_handle(std::make_shared<TextureHandle>(
				detail::IsMipped(desc) ?
					Siv3DEngine::Get<ISiv3DTexture>()->create(image, ImageProcessing::GenerateMips(image), desc) :
					Siv3DEngine::Get<ISiv3DTexture>()->createUnmipped(image, desc)))
	{
		ReportAssetCreation();
	}

	Texture::Texture(const Image& image, const Array<Image>& mipmaps, const TextureDesc desc)
		: m_handle(std::make_shared<TextureHandle>(Siv3DEngine::Get<ISiv3DTexture>()->create(image, mipmaps, desc)))
	{
		ReportAssetCreation();
	}

	Texture::Texture(const FilePath& path, const TextureDesc desc)
		: Texture(Image(path), desc)
	{

	}

	Texture::Texture(IReader&& reader, const TextureDesc desc)
		: Texture(Image(std::move(reader)), desc)
	{

	}

	Texture::Texture(const FilePath& rgb, const FilePath& alpha, const TextureDesc desc)
		: Texture(Image(rgb, alpha), desc)
	{

	}

	Texture::Texture(const Color& rgb, const FilePath& alpha, const TextureDesc desc)
		: Texture(Image(rgb, alpha), desc)
	{

	}
	
	Texture::Texture(const Emoji& emoji, const TextureDesc desc)
		: Texture(Emoji::CreateImage(emoji.codePoints), desc)
	{

	}

	Texture::Texture(const Icon& icon, const TextureDesc desc)
		: Texture(Icon::CreateImage(icon.code, icon.size), desc)
	{

	}
	
	Texture::~Texture()
	{

	}

	void Texture::release()
	{
		m_handle = std::make_shared<TextureHandle>();
	}

	bool Texture::isEmpty() const
	{
		return m_handle->id().isNullAsset();
	}

	TextureID Texture::id() const
	{
		return m_handle->id();
	}

	bool Texture::operator ==(const Texture& texture) const
	{
		return m_handle->id() == texture.m_handle->id();
	}

	bool Texture::operator !=(const Texture& texture) const
	{
		return m_handle->id() != texture.m_handle->id();
	}

	int32 Texture::width() const
	{
		return Siv3DEngine::Get<ISiv3DTexture>()->getSize(m_handle->id()).x;
	}

	int32 Texture::height() const
	{
		return Siv3DEngine::Get<ISiv3DTexture>()->getSize(m_handle->id()).y;
	}

	Size Texture::size() const
	{
		return Siv3DEngine::Get<ISiv3DTexture>()->getSize(m_handle->id());
	}

	TextureDesc Texture::getDesc() const
	{
		return Siv3DEngine::Get<ISiv3DTexture>()->getDesc(m_handle->id());
	}

	bool Texture::isMipped() const
	{
		return detail::IsMipped(Siv3DEngine::Get<ISiv3DTexture>()->getDesc(m_handle->id()));
	}

	bool Texture::isSDF() const
	{
		const TextureDesc desc = Siv3DEngine::Get<ISiv3DTexture>()->getDesc(m_handle->id());

		return (desc == TextureDesc::SDF);
	}

	Rect Texture::region(const int32 x, const int32 y) const
	{
		return{ x, y, size() };
	}

	Rect Texture::region(const Point& pos) const
	{
		return region(pos.x, pos.y);
	}

	RectF Texture::region(const double x, const double y) const
	{
		return{ x, y, size() };
	}

	RectF Texture::region(const Vec2& pos) const
	{
		return region(pos.x, pos.y);
	}

	RectF Texture::regionAt(const double x, const double y) const
	{
		const Size s = size();
		return{ x - s.x * 0.5, y - s.y * 0.5, s };
	}

	RectF Texture::regionAt(const Vec2& pos) const
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
		const Size size = Siv3DEngine::Get<ISiv3DTexture>()->getSize(m_handle->id());

		Siv3DEngine::Get<ISiv3DRenderer2D>()->addTextureRegion(
			*this,
			FloatRect(x, y, x + size.x, y + size.y),
			FloatRect(0.0f, 0.0f, 1.0f, 1.0f),
			diffuse.toFloat4()
		);

		return RectF(x, y, size);
	}

	RectF Texture::draw(const double x, const double y, const ColorF& color0, const ColorF& color1, const ColorF& color2, const ColorF& color3) const
	{
		const Size size = Siv3DEngine::Get<ISiv3DTexture>()->getSize(m_handle->id());

		Siv3DEngine::Get<ISiv3DRenderer2D>()->addTextureRegion(
			*this,
			FloatRect(x, y, x + size.x, y + size.y),
			FloatRect(0.0f, 0.0f, 1.0f, 1.0f),
			{ color0.toFloat4(), color1.toFloat4(), color2.toFloat4(), color3.toFloat4() }
		);

		return RectF(x, y, size);
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

	RectF Texture::drawClipped(const double x, const double y, const RectF& clipRect, const ColorF& diffuse) const
	{
		const Size size = Siv3DEngine::Get<ISiv3DTexture>()->getSize(m_handle->id());

		const double clipRight = clipRect.x + clipRect.w;
		const double clipBottom = clipRect.y + clipRect.h;

		const double left = std::max(x, clipRect.x);
		const double right = std::min(x + size.x, clipRight);
		const double top = std::max(y, clipRect.y);
		const double bottom = std::min(y + size.y, clipBottom);

		if (clipRight <= left
			|| right <= clipRect.x
			|| clipBottom <= top
			|| bottom <= clipRect.y)
		{
			return RectF(left, top, 0, 0);
		}

		const double xLeftTrimmed = left - x;
		const double xRightTrimmed = (x + size.x) - right;
		const double yTopTrimmed = top - y;
		const double yBottomTrimmed = (y + size.y) - bottom;

		const double uLeftTrimmed = xLeftTrimmed / size.x;
		const double uRightTrimmed = xRightTrimmed / size.x;
		const double vTopTrimmed = yTopTrimmed / size.y;
		const double vBottomTrimmed = yBottomTrimmed / size.y;

		Siv3DEngine::Get<ISiv3DRenderer2D>()->addTextureRegion(
			*this,
			FloatRect(left, top, right, bottom),
			FloatRect(uLeftTrimmed, vTopTrimmed, 1.0 - uRightTrimmed, 1.0 - vBottomTrimmed),
			diffuse.toFloat4()
		);

		return RectF(left, top, right - left, bottom - top);
	}

	RectF Texture::drawClipped(const Vec2& pos, const RectF& clipRect, const ColorF& diffuse) const
	{
		return drawClipped(pos.x, pos.y, clipRect, diffuse);
	}

	RectF Texture::drawAt(const double x, const double y, const ColorF& diffuse) const
	{
		const Size size = Siv3DEngine::Get<ISiv3DTexture>()->getSize(m_handle->id());
		const double wHalf = size.x * 0.5;
		const double hHalf = size.y * 0.5;

		Siv3DEngine::Get<ISiv3DRenderer2D>()->addTextureRegion(
			*this,
			{ x - wHalf, y - hHalf, x + wHalf, y + hHalf },
			{ 0.0f, 0.0f, 1.0f, 1.0f },
			diffuse.toFloat4()
		);

		return RectF(x - wHalf, y - hHalf, size);
	}

	RectF Texture::drawAt(double x, double y, const ColorF& color0, const ColorF& color1, const ColorF& color2, const ColorF& color3) const
	{
		const Size size = Siv3DEngine::Get<ISiv3DTexture>()->getSize(m_handle->id());
		const double wHalf = size.x * 0.5;
		const double hHalf = size.y * 0.5;

		Siv3DEngine::Get<ISiv3DRenderer2D>()->addTextureRegion(
			*this,
			{ x - wHalf, y - hHalf, x + wHalf, y + hHalf },
			{ 0.0f, 0.0f, 1.0f, 1.0f },
			{ color0.toFloat4(), color1.toFloat4(), color2.toFloat4(), color3.toFloat4() }
		);

		return RectF(x - wHalf, y - hHalf, size);
	}

	RectF Texture::drawAt(const Vec2& pos, const ColorF& diffuse) const
	{
		return drawAt(pos.x, pos.y, diffuse);
	}

	RectF Texture::drawAt(const Vec2& pos, const ColorF& color0, const ColorF& color1, const ColorF& color2, const ColorF& color3) const
	{
		return drawAt(pos.x, pos.y, color0, color1, color2, color3);
	}

	RectF Texture::drawAtClipped(double x, double y, const RectF& clipRect, const ColorF& diffuse) const
	{
		const Size size = Siv3DEngine::Get<ISiv3DTexture>()->getSize(m_handle->id());
		const double wHalf = size.x * 0.5;
		const double hHalf = size.y * 0.5;

		return drawClipped(x - wHalf, y - hHalf, clipRect, diffuse);
	}

	RectF Texture::drawAtClipped(const Vec2& pos, const RectF& clipRect, const ColorF& diffuse) const
	{
		return drawAtClipped(pos.x, pos.y, clipRect, diffuse);
	}

	TextureRegion Texture::operator ()(const double x, const double y, const double w, const double h) const
	{
		const Size size = Siv3DEngine::Get<ISiv3DTexture>()->getSize(m_handle->id());
		
		return TextureRegion(*this,
			static_cast<float>(x / size.x), static_cast<float>(y / size.y), static_cast<float>((x + w) / size.x), static_cast<float>((y + h) / size.y),
			w, h);
	}

	TextureRegion Texture::operator ()(const Vec2& xy, const double w, const double h) const
	{
		return operator ()(xy.x, xy.y, w, h);
	}

	TextureRegion Texture::operator ()(const double x, const double y, const double size) const
	{
		return operator ()(x, y, size, size);
	}

	TextureRegion Texture::operator ()(const double x, const double y, const Vec2& size) const
	{
		return operator ()(x, y, size.x, size.y);
	}

	TextureRegion Texture::operator ()(const Vec2& xy, const Vec2& size) const
	{
		return operator ()(xy.x, xy.y, size.x, size.y);
	}

	TextureRegion Texture::operator ()(const RectF& rect) const
	{
		return operator ()(rect.x, rect.y, rect.w, rect.h);
	}

	TextureRegion Texture::uv(const double u, const double v, const double w, const double h) const
	{
		const Size size = Siv3DEngine::Get<ISiv3DTexture>()->getSize(m_handle->id());

		return TextureRegion(*this,
			static_cast<float>(u), static_cast<float>(v), static_cast<float>(u + w), static_cast<float>(v + h),
			size.x * w, size.y * h);
	}

	TextureRegion Texture::uv(const RectF& rect) const
	{
		return operator ()(rect.x, rect.y, rect.x + rect.w, rect.y + rect.h);
	}

	TextureRegion Texture::mirrored() const
	{
		return TextureRegion(*this,
			{ 1.0f, 0.0f, 0.0f, 1.0f },
			size());
	}

	TextureRegion Texture::mirrored(const bool doMirror) const
	{
		if (doMirror)
		{
			return mirrored();
		}
		else
		{
			return TextureRegion(*this);
		}
	}

	TextureRegion Texture::flipped() const
	{
		return TextureRegion(*this,
			{ 0.0f, 1.0f, 1.0f, 0.0f },
			size());
	}

	TextureRegion Texture::flipped(const bool doFlip) const
	{
		if (doFlip)
		{
			return flipped();
		}
		else
		{
			return TextureRegion(*this);
		}
	}

	TextureRegion Texture::scaled(const double s) const
	{
		return scaled({ s, s });
	}

	TextureRegion Texture::scaled(const double sx, const double sy) const
	{
		const Size size = Siv3DEngine::Get<ISiv3DTexture>()->getSize(m_handle->id());

		return TextureRegion(*this,
			0.0f, 0.0f, 1.0f, 1.0f,
			size.x * sx, size.y * sy);
	}

	TextureRegion Texture::scaled(const Vec2& s) const
	{
		return scaled(s.x, s.y);
	}

	TextureRegion Texture::resized(const double size) const
	{
		const Size texSize = Siv3DEngine::Get<ISiv3DTexture>()->getSize(m_handle->id());

		return scaled(static_cast<double>(size) / std::max(texSize.x, texSize.y));
	}

	TextureRegion Texture::resized(const double width, const double height) const
	{
		return TextureRegion(*this,
			0.0f, 0.0f, 1.0f, 1.0f,
			width, height);
	}

	TextureRegion Texture::resized(const Vec2& size) const
	{
		return resized(size.x, size.y);
	}

	TextureRegion Texture::repeated(const double xRepeat, const double yRepeat) const
	{
		const Size size = Siv3DEngine::Get<ISiv3DTexture>()->getSize(m_handle->id());

		return TextureRegion(*this,
			0.0f, 0.0f, static_cast<float>(xRepeat), static_cast<float>(yRepeat),
			size.x * xRepeat, size.y * yRepeat);
	}

	TextureRegion Texture::repeated(const Vec2& _repeat) const
	{
		return repeated(_repeat.x, _repeat.y);
	}

	TextureRegion Texture::mapped(const double width, const double height) const
	{
		const Size size = Siv3DEngine::Get<ISiv3DTexture>()->getSize(m_handle->id());

		return TextureRegion(*this,
			0.0f, 0.0f, static_cast<float>(width / size.x), static_cast<float>(height / size.y),
			width, height);
	}

	TextureRegion Texture::mapped(const Vec2& size) const
	{
		return mapped(size.x, size.y);
	}

	TextureRegion Texture::fitted(double width, double height, const bool scaleUp) const
	{
		if (!scaleUp)
		{
			width = std::min<double>(width, this->width());
			height = std::min<double>(height, this->height());
		}

		const double w = this->width();
		const double h = this->height();
		double ws = width / w;	// ‰½% scaling‚·‚é‚©
		double hs = height / h;

		double targetWidth, targetHeight;

		if (ws < hs)
		{
			targetWidth = width;
			targetHeight = h * ws;
		}
		else
		{
			targetWidth = w * hs;
			targetHeight = height;
		}

		TextureRegion result = *this;
		result.size = Float2(targetWidth, targetHeight);

		return result;
	}

	TextureRegion Texture::fitted(const Vec2& size, const bool scaleUp) const
	{
		return fitted(size.x, size.y, scaleUp);
	}

	TexturedQuad Texture::rotated(const double angle) const
	{
		const Size size = Siv3DEngine::Get<ISiv3DTexture>()->getSize(m_handle->id());

		return TexturedQuad(*this,
			0.0f, 0.0f, 1.0f, 1.0f,
			Rect(size).rotated(angle),
			Float2(size.x * 0.5, size.y * 0.5));
	}

	TexturedQuad Texture::rotatedAt(const double x, const double y, const double angle) const
	{
		const Size size = Siv3DEngine::Get<ISiv3DTexture>()->getSize(m_handle->id());

		return TexturedQuad(*this,
			0.0f, 0.0f, 1.0f, 1.0f,
			Rect(size).rotatedAt(x, y, angle),
			Float2(x, y));
	}

	TexturedQuad Texture::rotatedAt(const Vec2& pos, const double angle) const
	{
		return rotatedAt(pos.x, pos.y, angle);
	}
}
