//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "../Siv3DEngine.hpp"
# include "ITexture.hpp"
# include "../Renderer2D/IRenderer2D.hpp"
# include "../Profiler/IProfiler.hpp"
# include <Siv3D/Texture.hpp>
# include <Siv3D/TextureRegion.hpp>
# include <Siv3D/TexturedQuad.hpp>
# include <Siv3D/Image.hpp>
# include <Siv3D/ImageProcessing.hpp>
# include <Siv3D/Emoji.hpp>
# include <Siv3D/Icon.hpp>

namespace s3d
{
	template <>
	AssetHandle<Texture::Handle>::~AssetHandle()
	{
		if (!Siv3DEngine::isActive())
		{
			return;
		}

		if (auto p = Siv3DEngine::GetTexture())
		{
			p->release(m_id);
		}
	}

	Texture::Texture(BackBuffer)
		: m_handle(std::make_shared<TextureHandle>(Siv3DEngine::GetTexture()->createFromBackBuffer()))
	{

	}

	Texture::Texture(Dynamic, const uint32 width, const uint32 height, const void* pData, const uint32 stride, const TextureFormat format, const TextureDesc desc)
		: m_handle(std::make_shared<TextureHandle>(Siv3DEngine::GetTexture()->createDynamic(Size(width, height), pData, stride, format, desc)))
	{
		ASSET_CREATION();
	}

	Texture::Texture(Dynamic, const uint32 width, const uint32 height, const ColorF& color, const TextureFormat format, const TextureDesc desc)
		: m_handle(std::make_shared<TextureHandle>(Siv3DEngine::GetTexture()->createDynamic(Size(width, height), color, format, desc)))
	{
		ASSET_CREATION();
	}

	Texture::Texture(Render, const Size& size, const uint32 multisampleCount)
		: m_handle(std::make_shared<TextureHandle>(Siv3DEngine::GetTexture()->createRT(size, multisampleCount)))
	{
		ASSET_CREATION();
	}

	Texture::Texture()
		: m_handle(std::make_shared<TextureHandle>())
	{

	}

	Texture::Texture(const Image& image, const TextureDesc desc)
		: m_handle(std::make_shared<TextureHandle>(
				detail::IsMipped(desc) ?
					Siv3DEngine::GetTexture()->create(image, ImageProcessing::GenerateMips(image), desc) :
					Siv3DEngine::GetTexture()->create(image, desc)))
	{
		ASSET_CREATION();
	}

	Texture::Texture(const Image& image, const Array<Image>& mipmaps, const TextureDesc desc)
		: m_handle(std::make_shared<TextureHandle>(Siv3DEngine::GetTexture()->create(image, mipmaps, desc)))
	{
		ASSET_CREATION();
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

	Texture::Texture(const Emoji& emoji, TextureDesc desc)
		: Texture(Emoji::LoadImage(emoji.codePoints), desc)
	{

	}

	Texture::Texture(const Icon& icon, TextureDesc desc)
		: Texture(Icon::LoadImage(icon.code, icon.size), desc)
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
		return Siv3DEngine::GetTexture()->getSize(m_handle->id()).x;
	}

	int32 Texture::height() const
	{
		return Siv3DEngine::GetTexture()->getSize(m_handle->id()).y;
	}

	Size Texture::size() const
	{
		return Siv3DEngine::GetTexture()->getSize(m_handle->id());
	}

	TextureDesc Texture::getDesc() const
	{
		return Siv3DEngine::GetTexture()->getDesc(m_handle->id());
	}

	bool Texture::isMipped() const
	{
		const TextureDesc desc = Siv3DEngine::GetTexture()->getDesc(m_handle->id());

		return (desc == TextureDesc::UnmippedSRGB) || (desc == TextureDesc::MippedSRGB);
	}

	bool Texture::isSDF() const
	{
		const TextureDesc desc = Siv3DEngine::GetTexture()->getDesc(m_handle->id());

		return (desc == TextureDesc::SDF);
	}

	RectF Texture::draw(const double x, const double y, const ColorF& diffuse) const
	{
		const Size size = Siv3DEngine::GetTexture()->getSize(m_handle->id());

		Siv3DEngine::GetRenderer2D()->addTextureRegion(
			*this,
			FloatRect(x, y, x + size.x, y + size.y),
			FloatRect(0.0f, 0.0f, 1.0f, 1.0f),
			diffuse.toFloat4()
		);

		return RectF(x, y, size);
	}

	RectF Texture::drawClipped(double x, double y, const RectF& clipRect, const ColorF& diffuse) const
	{
		const Size size = Siv3DEngine::GetTexture()->getSize(m_handle->id());

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

		Siv3DEngine::GetRenderer2D()->addTextureRegion(
			*this,
			FloatRect(left, top, right, bottom),
			FloatRect(uLeftTrimmed, vTopTrimmed, 1.0 - uRightTrimmed, 1.0 - vBottomTrimmed),
			diffuse.toFloat4()
		);

		return RectF(left, top, right - left, bottom - top);
	}

	RectF Texture::drawAt(const double x, const double y, const ColorF& diffuse) const
	{
		const Size size = Siv3DEngine::GetTexture()->getSize(m_handle->id());
		const double wHalf = size.x * 0.5;
		const double hHalf = size.y * 0.5;

		Siv3DEngine::GetRenderer2D()->addTextureRegion(
			*this,
			{ x - wHalf, y - hHalf, x + wHalf, y + hHalf },
			{ 0.0f, 0.0f, 1.0f, 1.0f },
			diffuse.toFloat4()
		);

		return RectF(x - wHalf, y - hHalf, size);
	}

	RectF Texture::drawAtClipped(double x, double y, const RectF& clipRect, const ColorF& diffuse) const
	{
		const Size size = Siv3DEngine::GetTexture()->getSize(m_handle->id());
		const double wHalf = size.x * 0.5;
		const double hHalf = size.y * 0.5;

		return drawClipped(x - wHalf, y - hHalf, clipRect, diffuse);
	}

	TextureRegion Texture::operator ()(const double x, const double y, const double w, const double h) const
	{
		const Size size = Siv3DEngine::GetTexture()->getSize(m_handle->id());
		
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
		const Size size = Siv3DEngine::GetTexture()->getSize(m_handle->id());

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
		const Size size = Siv3DEngine::GetTexture()->getSize(m_handle->id());

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
		const Size texSize = Siv3DEngine::GetTexture()->getSize(m_handle->id());

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
		const Size size = Siv3DEngine::GetTexture()->getSize(m_handle->id());

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
		const Size size = Siv3DEngine::GetTexture()->getSize(m_handle->id());

		return TextureRegion(*this,
			0.0f, 0.0f, static_cast<float>(size.x / width), static_cast<float>(size.y / height),
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
		const Size size = Siv3DEngine::GetTexture()->getSize(m_handle->id());

		return TexturedQuad(*this,
			0.0f, 0.0f, 1.0f, 1.0f,
			Rect(size).rotated(angle),
			Float2(size.x * 0.5, size.y * 0.5));
	}

	TexturedQuad Texture::rotatedAt(const double x, const double y, const double angle) const
	{
		const Size size = Siv3DEngine::GetTexture()->getSize(m_handle->id());

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
