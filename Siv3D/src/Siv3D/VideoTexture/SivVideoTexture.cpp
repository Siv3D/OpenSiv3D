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

# include <Siv3D/VideoTexture.hpp>
# include <Siv3D/VideoTexture/VideoTextureDetail.hpp>

namespace s3d
{
	VideoTexture::VideoTexture()
		: pImpl{ std::make_shared<VideoTextureDetail>() } {}

	VideoTexture::VideoTexture(const FilePathView path, const Loop loop, const TextureDesc desc)
		: VideoTexture{}
	{
		pImpl->load(path, loop, desc);
	}

	bool VideoTexture::isEmpty() const noexcept
	{
		return pImpl->getTexture().isEmpty();
	}

	VideoTexture::operator bool() const noexcept
	{
		return (not isEmpty());
	}

	void VideoTexture::release()
	{
		*this = VideoTexture{};
	}

	void VideoTexture::advance(const double deltaTimeSec) const
	{
		pImpl->advance(deltaTimeSec);
	}

	void VideoTexture::reset() const
	{
		pImpl->reset();
	}

	bool VideoTexture::isLoop() const noexcept
	{
		return pImpl->isLoop();
	}

	double VideoTexture::posSec() const noexcept
	{
		return pImpl->posSec();
	}

	double VideoTexture::lengthSec() const
	{
		return getVideoReader().getLengthSec();
	}

	void VideoTexture::setPosSec(const double posSec) const
	{
		pImpl->setPosSec(posSec);
	}

	const Texture& VideoTexture::getTexture() const noexcept
	{
		return pImpl->getTexture();
	}

	VideoTexture::operator const Texture& () const noexcept
	{
		return pImpl->getTexture();
	}

	const VideoReader& VideoTexture::getVideoReader() const noexcept
	{
		return pImpl->getVideoReader();
	}

	int32 VideoTexture::width() const
	{
		return getTexture().width();
	}

	int32 VideoTexture::height() const
	{
		return getTexture().height();
	}

	Size VideoTexture::size() const
	{
		return getTexture().size();
	}

	TextureDesc VideoTexture::getDesc() const
	{
		return getTexture().getDesc();
	}

	TextureFormat VideoTexture::getFormat() const
	{
		return getTexture().getFormat();
	}

	bool VideoTexture::hasMipMap() const
	{
		return getTexture().hasMipMap();
	}

	bool VideoTexture::isSDF() const
	{
		return getTexture().isSDF();
	}

	Rect VideoTexture::region(const int32 x, const int32 y) const
	{
		return getTexture().region(x, y);
	}

	Rect VideoTexture::region(const Point pos) const
	{
		return getTexture().region(pos);
	}

	RectF VideoTexture::region(const double x, const double y) const
	{
		return getTexture().region(x, y);
	}

	RectF VideoTexture::region(const Vec2 pos) const
	{
		return getTexture().region(pos);
	}

	RectF VideoTexture::regionAt(const double x, const double y) const
	{
		return getTexture().regionAt(x, y);
	}

	RectF VideoTexture::regionAt(const Vec2 pos) const
	{
		return getTexture().regionAt(pos);
	}

	RectF VideoTexture::draw(const ColorF& diffuse) const
	{
		return getTexture().draw(diffuse);
	}

	RectF VideoTexture::draw(const ColorF& color0, const ColorF& color1, const ColorF& color2, const ColorF& color3) const
	{
		return getTexture().draw(color0, color1, color2, color3);
	}

	RectF VideoTexture::draw(const Arg::top_<ColorF> topColor, const Arg::bottom_<ColorF> bottomColor) const
	{
		return getTexture().draw(topColor, bottomColor);
	}

	RectF VideoTexture::draw(const Arg::left_<ColorF> leftColor, const Arg::right_<ColorF> rightColor) const
	{
		return getTexture().draw(leftColor, rightColor);
	}

	RectF VideoTexture::draw(const double x, const double y, const ColorF& diffuse) const
	{
		return getTexture().draw(x, y, diffuse);
	}

	RectF VideoTexture::draw(const double x, const double y, const ColorF& color0, const ColorF& color1, const ColorF& color2, const ColorF& color3) const
	{
		return getTexture().draw(x, y, color0, color1, color2, color3);
	}

	RectF VideoTexture::draw(const double x, const double y, const Arg::top_<ColorF> topColor, const Arg::bottom_<ColorF> bottomColor) const
	{
		return getTexture().draw(x, y, topColor, bottomColor);
	}

	RectF VideoTexture::draw(const double x, const double y, const Arg::left_<ColorF> leftColor, const Arg::right_<ColorF> rightColor) const
	{
		return getTexture().draw(x, y, leftColor, rightColor);
	}

	RectF VideoTexture::draw(const Vec2& pos, const ColorF& diffuse) const
	{
		return getTexture().draw(pos, diffuse);
	}

	RectF VideoTexture::draw(const Vec2& pos, const ColorF& color0, const ColorF& color1, const ColorF& color2, const ColorF& color3) const
	{
		return getTexture().draw(pos, color0, color1, color2, color3);
	}

	RectF VideoTexture::draw(const Vec2& pos, const Arg::top_<ColorF> topColor, const Arg::bottom_<ColorF> bottomColor) const
	{
		return getTexture().draw(pos, topColor, bottomColor);
	}

	RectF VideoTexture::draw(const Vec2& pos, const Arg::left_<ColorF> leftColor, const Arg::right_<ColorF> rightColor) const
	{
		return getTexture().draw(pos, leftColor, rightColor);
	}

	RectF VideoTexture::draw(const Arg::topLeft_<Vec2> topLeft, const ColorF& diffuse) const
	{
		return getTexture().draw(topLeft, diffuse);
	}

	RectF VideoTexture::draw(const Arg::topRight_<Vec2> topRight, const ColorF& diffuse) const
	{
		return getTexture().draw(topRight, diffuse);
	}

	RectF VideoTexture::draw(const Arg::bottomLeft_<Vec2> bottomLeft, const ColorF& diffuse) const
	{
		return getTexture().draw(bottomLeft, diffuse);
	}

	RectF VideoTexture::draw(const Arg::bottomRight_<Vec2> bottomRight, const ColorF& diffuse) const
	{
		return getTexture().draw(bottomRight, diffuse);
	}

	RectF VideoTexture::draw(const Arg::topCenter_<Vec2> topCenter, const ColorF& diffuse) const
	{
		return getTexture().draw(topCenter, diffuse);
	}

	RectF VideoTexture::draw(const Arg::bottomCenter_<Vec2> bottomCenter, const ColorF& diffuse) const
	{
		return getTexture().draw(bottomCenter, diffuse);
	}

	RectF VideoTexture::draw(const Arg::leftCenter_<Vec2> leftCenter, const ColorF& diffuse) const
	{
		return getTexture().draw(leftCenter, diffuse);
	}

	RectF VideoTexture::draw(const Arg::rightCenter_<Vec2>rightCenter, const ColorF& diffuse) const
	{
		return getTexture().draw(rightCenter, diffuse);
	}

	RectF VideoTexture::draw(const Arg::center_<Vec2> center, const ColorF& diffuse) const
	{
		return getTexture().draw(center, diffuse);
	}

	RectF VideoTexture::drawAt(const double x, const double y, const ColorF& diffuse) const
	{
		return getTexture().drawAt(x, y, diffuse);
	}

	RectF VideoTexture::drawAt(const double x, const double y, const ColorF& color0, const ColorF& color1, const ColorF& color2, const ColorF& color3) const
	{
		return getTexture().drawAt(x, y, color0, color1, color2, color3);
	}

	RectF VideoTexture::drawAt(const Vec2& pos, const ColorF& diffuse) const
	{
		return getTexture().drawAt(pos, diffuse);
	}

	RectF VideoTexture::drawAt(const Vec2& pos, const ColorF& color0, const ColorF& color1, const ColorF& color2, const ColorF& color3) const
	{
		return getTexture().drawAt(pos, color0, color1, color2, color3);
	}

	RectF VideoTexture::drawClipped(const double x, const double y, const RectF& clipRect, const ColorF& diffuse) const
	{
		return getTexture().drawClipped(x, y, clipRect, diffuse);
	}

	RectF VideoTexture::drawClipped(const Vec2& pos, const RectF& clipRect, const ColorF& diffuse) const
	{
		return getTexture().drawClipped(pos, clipRect, diffuse);
	}

	RectF VideoTexture::drawAtClipped(const double x, const double y, const RectF& clipRect, const ColorF& diffuse) const
	{
		return getTexture().drawAtClipped(x, y, clipRect, diffuse);
	}

	RectF VideoTexture::drawAtClipped(const Vec2& pos, const RectF& clipRect, const ColorF& diffuse) const
	{
		return getTexture().drawAtClipped(pos, clipRect, diffuse);
	}

	TextureRegion VideoTexture::operator ()(const double x, const double y, const double w, const double h) const
	{
		return getTexture()(x, y, w, h);
	}

	TextureRegion VideoTexture::operator ()(const Vec2& xy, const double w, const double h) const
	{
		return getTexture()(xy, w, h);
	}

	TextureRegion VideoTexture::operator ()(const double x, const double y, const double size) const
	{
		return getTexture()(x, y, size);
	}

	TextureRegion VideoTexture::operator ()(const double x, const double y, const Vec2& size) const
	{
		return getTexture()(x, y, size);
	}

	TextureRegion VideoTexture::operator ()(const Vec2& xy, const Vec2& size) const
	{
		return getTexture()(xy, size);
	}

	TextureRegion VideoTexture::operator ()(const RectF& rect) const
	{
		return getTexture()(rect);
	}

	TextureRegion VideoTexture::uv(const double u, const double v, const double w, const double h) const
	{
		return getTexture().uv(u, v, w, h);
	}

	TextureRegion VideoTexture::uv(const RectF& rect) const
	{
		return getTexture().uv(rect);
	}

	TextureRegion VideoTexture::mirrored() const
	{
		return getTexture().mirrored();
	}

	TextureRegion VideoTexture::mirrored(const bool doMirror) const
	{
		return getTexture().mirrored(doMirror);
	}

	TextureRegion VideoTexture::flipped() const
	{
		return getTexture().flipped();
	}

	TextureRegion VideoTexture::flipped(const bool doFlip) const
	{
		return getTexture().flipped(doFlip);
	}

	TextureRegion VideoTexture::scaled(const double s) const
	{
		return getTexture().scaled(s);
	}

	TextureRegion VideoTexture::scaled(const double sx, const double sy) const
	{
		return getTexture().scaled(sx, sy);
	}

	TextureRegion VideoTexture::scaled(const Vec2 s) const
	{
		return getTexture().scaled(s);
	}

	TextureRegion VideoTexture::resized(const double size) const
	{
		return getTexture().resized(size);
	}

	TextureRegion VideoTexture::resized(const double width, const double height) const
	{
		return getTexture().resized(width, height);
	}

	TextureRegion VideoTexture::resized(const Vec2 size) const
	{
		return getTexture().resized(size);
	}

	TextureRegion VideoTexture::repeated(const double xRepeat, const double yRepeat) const
	{
		return getTexture().repeated(xRepeat, yRepeat);
	}

	TextureRegion VideoTexture::repeated(const Vec2 _repeat) const
	{
		return getTexture().repeated(_repeat);
	}

	TextureRegion VideoTexture::mapped(const double width, const double height) const
	{
		return getTexture().mapped(width, height);
	}

	TextureRegion VideoTexture::mapped(const Vec2 size) const
	{
		return getTexture().mapped(size);
	}

	TextureRegion VideoTexture::fitted(const double width, const double height, const AllowScaleUp allowScaleUp) const
	{
		return getTexture().fitted(width, height, allowScaleUp);
	}

	TextureRegion VideoTexture::fitted(const Vec2& size, const AllowScaleUp allowScaleUp) const
	{
		return getTexture().fitted(size, allowScaleUp);
	}

	TexturedQuad VideoTexture::rotated(const double angle) const
	{
		return getTexture().rotated(angle);
	}

	TexturedQuad VideoTexture::rotatedAt(const double x, const double y, const double angle) const
	{
		return getTexture().rotatedAt(x, y, angle);
	}

	TexturedQuad VideoTexture::rotatedAt(const Vec2& pos, const double angle) const
	{
		return getTexture().rotatedAt(pos, angle);
	}

	TexturedRoundRect VideoTexture::rounded(const double r) const
	{
		return getTexture().rounded(r);
	}

	TexturedRoundRect VideoTexture::rounded(const double x, const double y, const double w, const double h, const double r) const
	{
		return getTexture().rounded(x, y, w, h, r);
	}

	void VideoTexture::swap(VideoTexture& other) noexcept
	{
		pImpl.swap(other.pImpl);
	}
}
