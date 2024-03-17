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

# include <Siv3D/Texture.hpp>
# include <Siv3D/TextureRegion.hpp>
# include <Siv3D/TexturedQuad.hpp>
# include <Siv3D/TexturedRoundRect.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/2DShapes.hpp>
# include <Siv3D/FloatRect.hpp>
# include <Siv3D/Emoji.hpp>
# include <Siv3D/Icon.hpp>
# include <Siv3D/Troubleshooting/Troubleshooting.hpp>
# include <Siv3D/Texture/ITexture.hpp>
# include <Siv3D/Renderer2D/IRenderer2D.hpp>
# include <Siv3D/AssetMonitor/IAssetMonitor.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

# if SIV3D_PLATFORM(WINDOWS)
#	include <Siv3D/Texture/D3D11/CTexture_D3D11.hpp>
# endif

namespace s3d
{
	namespace detail
	{
		static void CheckEngine(const StringView type = U"Texture")
		{
			if (not Siv3DEngine::isActive())
			{
				Troubleshooting::Show(Troubleshooting::Error::AssetInitializationBeforeEngineStartup, type);
				std::exit(EXIT_FAILURE);
			}
		}
	}

	template <>
	AssetIDWrapper<AssetHandle<Texture>>::AssetIDWrapper()
	{
		detail::CheckEngine();
	}

	template <>
	AssetIDWrapper<AssetHandle<Texture>>::~AssetIDWrapper()
	{
		if (not Siv3DEngine::isActive())
		{
			return;
		}

		if (auto p = SIV3D_ENGINE(Texture))
		{
			p->release(m_id);
		}
	}

	Texture::Texture() {}

	Texture::Texture(const Image& image, const TextureDesc desc)
		: AssetHandle{ (detail::CheckEngine(), std::make_shared<AssetIDWrapperType>(SIV3D_ENGINE(Texture)->create(image, desc))) }
	{
		SIV3D_ENGINE(AssetMonitor)->created();
	}

	Texture::Texture(const Image& image, const Array<Image>& mipmaps, const TextureDesc desc)
		: AssetHandle{ (detail::CheckEngine(), std::make_shared<AssetIDWrapperType>(SIV3D_ENGINE(Texture)->create(image, mipmaps, desc))) }
	{
		SIV3D_ENGINE(AssetMonitor)->created();
	}

	Texture::Texture(const FilePathView path, const TextureDesc desc)
		: Texture{ (detail::CheckEngine(), Image{ path }), desc } {}

	Texture::Texture(IReader&& reader, const TextureDesc desc)
		: Texture{ (detail::CheckEngine(), Image{ std::move(reader) }), desc } {}

	Texture::Texture(const FilePathView rgb, const FilePathView alpha, const TextureDesc desc)
		: Texture{ (detail::CheckEngine(), Image{ rgb, alpha }), desc } {}

	Texture::Texture(const Color& rgb, const FilePathView alpha, const TextureDesc desc)
		: Texture{ (detail::CheckEngine(), Image{ rgb, alpha }), desc } {}

	Texture::Texture(const Emoji& emoji, const TextureDesc desc)
		: Texture{ (detail::CheckEngine(), Emoji::CreateImage(emoji.codePoints)), desc } {}

	Texture::Texture(const Icon& icon, const int32 size, const TextureDesc desc)
		: Texture{ (detail::CheckEngine(), Icon::CreateImage(icon.type, icon.code, size)), desc } {}

	Texture::~Texture() {}

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

	bool Texture::hasMipMap() const
	{
		return detail::HasMipMap(SIV3D_ENGINE(Texture)->getDesc(m_handle->id()));
	}

	bool Texture::srgbSampling() const
	{
		return SIV3D_ENGINE(Texture)->getFormat(m_handle->id()).isSRGB();
	}

	bool Texture::isSDF() const
	{
		return detail::IsSDF(SIV3D_ENGINE(Texture)->getDesc(m_handle->id()));
	}

	bool Texture::hasDepth() const
	{
		return SIV3D_ENGINE(Texture)->hasDepth(m_handle->id());
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

	RectF Texture::draw(const Arg::top_<ColorF> topColor, const Arg::bottom_<ColorF> bottomColor) const
	{
		return draw(*topColor, *topColor, *bottomColor, *bottomColor);
	}

	RectF Texture::draw(const Arg::left_<ColorF> leftColor, const Arg::right_<ColorF> rightColor) const
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

	RectF Texture::draw(const double x, const double y, const Arg::top_<ColorF> topColor, const Arg::bottom_<ColorF> bottomColor) const
	{
		return draw(x, y, *topColor, *topColor, *bottomColor, *bottomColor);
	}

	RectF Texture::draw(const double x, const double y, const Arg::left_<ColorF> leftColor, const Arg::right_<ColorF> rightColor) const
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

	RectF Texture::draw(const Vec2& pos, const Arg::top_<ColorF> topColor, const Arg::bottom_<ColorF> bottomColor) const
	{
		return draw(pos.x, pos.y, *topColor, *topColor, *bottomColor, *bottomColor);
	}

	RectF Texture::draw(const Vec2& pos, const Arg::left_<ColorF> leftColor, const Arg::right_<ColorF> rightColor) const
	{
		return draw(pos.x, pos.y, *leftColor, *rightColor, *rightColor, *leftColor);
	}

	RectF Texture::draw(const Arg::topLeft_<Vec2> topLeft, const ColorF& diffuse) const
	{
		return draw(topLeft->x, topLeft->y, diffuse);
	}

	RectF Texture::draw(const Arg::topRight_<Vec2> topRight, const ColorF& diffuse) const
	{
		return draw(topRight->x - width(), topRight->y, diffuse);
	}

	RectF Texture::draw(const Arg::bottomLeft_<Vec2> bottomLeft, const ColorF& diffuse) const
	{
		return draw(bottomLeft->x, bottomLeft->y - height(), diffuse);
	}

	RectF Texture::draw(const Arg::bottomRight_<Vec2> bottomRight, const ColorF& diffuse) const
	{
		return draw(bottomRight->x - width(), bottomRight->y - height(), diffuse);
	}

	RectF Texture::draw(const Arg::topCenter_<Vec2> topCenter, const ColorF& diffuse) const
	{
		return draw(topCenter->x - width() * 0.5, topCenter->y, diffuse);
	}

	RectF Texture::draw(const Arg::bottomCenter_<Vec2> bottomCenter, const ColorF& diffuse) const
	{
		return draw(bottomCenter->x - width() * 0.5, bottomCenter->y - height(), diffuse);
	}

	RectF Texture::draw(const Arg::leftCenter_<Vec2> leftCenter, const ColorF& diffuse) const
	{
		return draw(leftCenter->x, leftCenter->y - height() * 0.5, diffuse);
	}

	RectF Texture::draw(const Arg::rightCenter_<Vec2>rightCenter, const ColorF& diffuse) const
	{
		return draw(rightCenter->x - width(), rightCenter->y - height() * 0.5, diffuse);
	}

	RectF Texture::draw(const Arg::center_<Vec2> center, const ColorF& diffuse) const
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
			FloatRect{ (x - wHalf), (y - hHalf), (x + wHalf), (y + hHalf) },
			FloatRect{ 0.0f, 0.0f, 1.0f, 1.0f },
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
			FloatRect{ (x - wHalf), (y - hHalf), (x + wHalf), (y + hHalf) },
			FloatRect{ 0.0f, 0.0f, 1.0f, 1.0f },
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

	RectF Texture::drawClipped(const double x, const double y, const RectF& clipRect, const ColorF& diffuse) const
	{
		const Size size = SIV3D_ENGINE(Texture)->getSize(m_handle->id());

		const double clipRight	= (clipRect.x + clipRect.w);
		const double clipBottom	= (clipRect.y + clipRect.h);

		const double left	= Max(x, clipRect.x);
		const double right	= Min((x + size.x), clipRight);
		const double top	= Max(y, clipRect.y);
		const double bottom	= Min((y + size.y), clipBottom);

		if ((clipRight <= left)
			|| (right <= clipRect.x)
			|| (clipBottom <= top)
			|| (bottom <= clipRect.y))
		{
			return{ left, top, 0, 0 };
		}

		const float xLeftTrimmed	= static_cast<float>(left - x);
		const float xRightTrimmed	= static_cast<float>((x + size.x) - right);
		const float yTopTrimmed		= static_cast<float>(top - y);
		const float yBottomTrimmed	= static_cast<float>((y + size.y) - bottom);

		const float uLeftTrimmed	= (xLeftTrimmed / size.x);
		const float uRightTrimmed	= (xRightTrimmed / size.x);
		const float vTopTrimmed		= (yTopTrimmed / size.y);
		const float vBottomTrimmed	= (yBottomTrimmed / size.y);

		SIV3D_ENGINE(Renderer2D)->addTextureRegion(
			*this,
			FloatRect{ left, top, right, bottom },
			FloatRect{ uLeftTrimmed, vTopTrimmed, (1.0f - uRightTrimmed), (1.0f - vBottomTrimmed) },
			diffuse.toFloat4()
		);

		return{ left, top, (right - left), (bottom - top) };
	}

	RectF Texture::drawClipped(const Vec2& pos, const RectF& clipRect, const ColorF& diffuse) const
	{
		return drawClipped(pos.x, pos.y, clipRect, diffuse);
	}

	RectF Texture::drawAtClipped(const double x, const double y, const RectF& clipRect, const ColorF& diffuse) const
	{
		const Size size = SIV3D_ENGINE(Texture)->getSize(m_handle->id());
		const double wHalf = (size.x * 0.5);
		const double hHalf = (size.y * 0.5);

		return drawClipped((x - wHalf), (y - hHalf), clipRect, diffuse);
	}

	RectF Texture::drawAtClipped(const Vec2& pos, const RectF& clipRect, const ColorF& diffuse) const
	{
		return drawAtClipped(pos.x, pos.y, clipRect, diffuse);
	}

	TextureRegion Texture::operator ()(const double x, const double y, const double w, const double h) const
	{
		const Size size = SIV3D_ENGINE(Texture)->getSize(m_handle->id());

		return{ *this,
			static_cast<float>(x / size.x), static_cast<float>(y / size.y),
			static_cast<float>((x + w) / size.x), static_cast<float>((y + h) / size.y),
			w, h };
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
		const Size size = SIV3D_ENGINE(Texture)->getSize(m_handle->id());

		return{ *this,
			static_cast<float>(u), static_cast<float>(v), static_cast<float>(u + w),
			static_cast<float>(v + h),
			(size.x * w), (size.y * h) };
	}

	TextureRegion Texture::uv(const RectF& rect) const
	{
		return uv(rect.x, rect.y, rect.w, rect.h);
	}

	TextureRegion Texture::mirrored() const
	{
		return{ *this, FloatRect{ 1.0f, 0.0f, 0.0f, 1.0f }, size() };
	}

	TextureRegion Texture::mirrored(const bool doMirror) const
	{
		if (doMirror)
		{
			return mirrored();
		}
		else
		{
			return TextureRegion{ *this };
		}
	}

	TextureRegion Texture::flipped() const
	{
		return{ *this, FloatRect{ 0.0f, 1.0f, 1.0f, 0.0f }, size() };
	}

	TextureRegion Texture::flipped(const bool doFlip) const
	{
		if (doFlip)
		{
			return flipped();
		}
		else
		{
			return TextureRegion{ *this };
		}
	}

	TextureRegion Texture::scaled(const double s) const
	{
		return scaled({ s, s });
	}

	TextureRegion Texture::scaled(const double sx, const double sy) const
	{
		const Size size = SIV3D_ENGINE(Texture)->getSize(m_handle->id());

		return{ *this,
			0.0f, 0.0f, 1.0f, 1.0f,
			(size.x * sx), (size.y * sy) };
	}

	TextureRegion Texture::scaled(const Vec2 s) const
	{
		return scaled(s.x, s.y);
	}

	TextureRegion Texture::resized(const double size) const
	{
		const Size texSize = SIV3D_ENGINE(Texture)->getSize(m_handle->id());

		return scaled(static_cast<double>(size) / Max(texSize.x, texSize.y));
	}

	TextureRegion Texture::resized(const double width, const double height) const
	{
		return{ *this,
			0.0f, 0.0f, 1.0f, 1.0f,
			width, height };
	}

	TextureRegion Texture::resized(const Vec2 size) const
	{
		return resized(size.x, size.y);
	}

	TextureRegion Texture::repeated(const double xRepeat, const double yRepeat) const
	{
		const Size size = SIV3D_ENGINE(Texture)->getSize(m_handle->id());

		return{ *this,
			0.0f, 0.0f, static_cast<float>(xRepeat), static_cast<float>(yRepeat),
			(size.x * xRepeat), (size.y * yRepeat) };
	}

	TextureRegion Texture::repeated(const Vec2 _repeat) const
	{
		return repeated(_repeat.x, _repeat.y);
	}

	TextureRegion Texture::mapped(const double width, const double height) const
	{
		const Size size = SIV3D_ENGINE(Texture)->getSize(m_handle->id());

		return{ *this,
			0.0f, 0.0f, static_cast<float>(width / size.x), static_cast<float>(height / size.y),
			width, height };
	}

	TextureRegion Texture::mapped(const Vec2 size) const
	{
		return mapped(size.x, size.y);
	}

	TextureRegion Texture::fitted(double width, double height, const AllowScaleUp allowScaleUp) const
	{
		if (not allowScaleUp)
		{
			width	= Min<double>(width, this->width());
			height	= Min<double>(height, this->height());
		}

		const double w = this->width();
		const double h = this->height();
		double ws = (width / w);	// 何% scalingするか
		double hs = (height / h);

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

		TextureRegion result{ *this };
		result.size = Float2{ targetWidth, targetHeight };
		return result;
	}

	TextureRegion Texture::fitted(const Vec2& size, const AllowScaleUp allowScaleUp) const
	{
		return fitted(size.x, size.y, allowScaleUp);
	}

	TexturedQuad Texture::rotated(const double angle) const
	{
		const Size size = SIV3D_ENGINE(Texture)->getSize(m_handle->id());

		return{ *this,
			0.0f, 0.0f, 1.0f, 1.0f,
			Rect{ size }.rotated(angle),
			Float2{ (size.x * 0.5f), (size.y * 0.5f) } };
	}

	TexturedQuad Texture::rotatedAt(const double x, const double y, const double angle) const
	{
		const Size size = SIV3D_ENGINE(Texture)->getSize(m_handle->id());

		return{ *this,
			0.0f, 0.0f, 1.0f, 1.0f,
			Rect{ size }.rotatedAt(x, y, angle),
			Float2{ x, y } };
	}

	TexturedQuad Texture::rotatedAt(const Vec2& pos, const double angle) const
	{
		return rotatedAt(pos.x, pos.y, angle);
	}

	TexturedRoundRect Texture::rounded(const double r) const
	{
		const Size size = SIV3D_ENGINE(Texture)->getSize(m_handle->id());

		return{
			*this,
			0.0f, 0.0f, 1.0f, 1.0f,
			RoundRect{ 0, 0, size, r }
		};
	}

	TexturedRoundRect Texture::rounded(const double x, const double y, const double w, const double h, const double r) const
	{
		const Size size = SIV3D_ENGINE(Texture)->getSize(m_handle->id());

		return{
			*this,
			static_cast<float>(x / size.x), static_cast<float>(y / size.y),
			static_cast<float>((x + w) / size.x), static_cast<float>((y + h) / size.y),
			RoundRect{ 0, 0, w, h, r }
		};
	}

	void Texture::swap(Texture& other) noexcept
	{
		m_handle.swap(other.m_handle);
	}

# if SIV3D_PLATFORM(WINDOWS)

	ID3D11Texture2D* Texture::getD3D11Texture2D()
	{
		if (auto p = dynamic_cast<CTexture_D3D11*>(SIV3D_ENGINE(Texture)))
		{
			return p->getTexture(m_handle->id());
		}
		else
		{
			return nullptr;
		}
	}

# endif

	Texture::Texture(Dynamic, const Size& size, const void* pData, const uint32 stride, const TextureFormat& format, const TextureDesc desc)
		: AssetHandle{ (detail::CheckEngine(U"DynamicTexture"), std::make_shared<AssetIDWrapperType>(SIV3D_ENGINE(Texture)->createDynamic(size, pData, stride, format, desc)))}
	{
		SIV3D_ENGINE(AssetMonitor)->created();
	}

	Texture::Texture(Dynamic, const Size& size, const ColorF& color, const TextureFormat& format, const TextureDesc desc)
		: AssetHandle{ (detail::CheckEngine(U"DynamicTexture"), std::make_shared<AssetIDWrapperType>(SIV3D_ENGINE(Texture)->createDynamic(size, color, format, desc))) }
	{
		SIV3D_ENGINE(AssetMonitor)->created();
	}

	Texture::Texture(Render, const Size& size, const TextureFormat& format, const HasDepth hasDepth, const HasMipMap hasMipMap)
		: AssetHandle{ (detail::CheckEngine(U"RenderTexture"), std::make_shared<AssetIDWrapperType>(SIV3D_ENGINE(Texture)->createRT(size, format, hasDepth, hasMipMap))) }
	{
		SIV3D_ENGINE(AssetMonitor)->created();
	}

	Texture::Texture(Render, const Image& image, const HasDepth hasDepth, const HasMipMap hasMipMap)
		: AssetHandle{ (detail::CheckEngine(U"RenderTexture"), std::make_shared<AssetIDWrapperType>(SIV3D_ENGINE(Texture)->createRT(image, hasDepth, hasMipMap))) }
	{
		SIV3D_ENGINE(AssetMonitor)->created();
	}

	Texture::Texture(Render, const Grid<float>& image, const HasDepth hasDepth, const HasMipMap hasMipMap)
		: AssetHandle{ (detail::CheckEngine(U"RenderTexture"), std::make_shared<AssetIDWrapperType>(SIV3D_ENGINE(Texture)->createRT(image, hasDepth, hasMipMap))) }
	{
		SIV3D_ENGINE(AssetMonitor)->created();
	}

	Texture::Texture(Render, const Grid<Float2>& image, const HasDepth hasDepth, const HasMipMap hasMipMap)
		: AssetHandle{ (detail::CheckEngine(U"RenderTexture"), std::make_shared<AssetIDWrapperType>(SIV3D_ENGINE(Texture)->createRT(image, hasDepth, hasMipMap))) }
	{
		SIV3D_ENGINE(AssetMonitor)->created();
	}

	Texture::Texture(Render, const Grid<Float4>& image, const HasDepth hasDepth, const HasMipMap hasMipMap)
		: AssetHandle{ (detail::CheckEngine(U"RenderTexture"), std::make_shared<AssetIDWrapperType>(SIV3D_ENGINE(Texture)->createRT(image, hasDepth, hasMipMap))) }
	{
		SIV3D_ENGINE(AssetMonitor)->created();
	}

	Texture::Texture(MSRender, const Size& size, const TextureFormat& format, const HasDepth hasDepth, const HasMipMap hasMipMap)
		: AssetHandle{ (detail::CheckEngine(U"MSRenderTexture"), std::make_shared<AssetIDWrapperType>(SIV3D_ENGINE(Texture)->createMSRT(size, format, hasDepth, hasMipMap))) }
	{
		SIV3D_ENGINE(AssetMonitor)->created();
	}
}
