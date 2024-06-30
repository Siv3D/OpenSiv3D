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

# include <Siv3D/BinaryReader.hpp>
# include <Siv3D/Image.hpp>
# include "SVGDetail.hpp"

namespace s3d
{
	SVG::SVGDetail::SVGDetail()
	{
		// do nothing
	}

	SVG::SVGDetail::~SVGDetail()
	{
		// do nothing
	}

	bool SVG::SVGDetail::load(const FilePathView path)
	{
		std::unique_ptr<BinaryReader> reader = std::make_unique<BinaryReader>(path);

		if (not reader->isOpen())
		{
			clear();
			return{};
		}

		return load(std::move(reader));
	}

	bool SVG::SVGDetail::load(std::unique_ptr<IReader>&& reader)
	{
		std::string source(reader->size(), '\0');

		if (reader->read(source.data(), source.size())
			!= static_cast<int64>(source.size()))
		{
			clear();
			return false;
		}

		return parse(source);
	}

	bool SVG::SVGDetail::parse(const std::string& source)
	{
		clear();

		m_document = lunasvg::Document::loadFromData(source);

		m_isEmpty = (not m_document);

		return (not m_isEmpty);
	}

	bool SVG::SVGDetail::parse(const StringView source)
	{
		return parse(source.toUTF8());
	}

	bool SVG::SVGDetail::isEmpty() const noexcept
	{
		return m_isEmpty;
	}

	double SVG::SVGDetail::width() const noexcept
	{
		return m_document->width();
	}

	double SVG::SVGDetail::height() const noexcept
	{
		return m_document->height();
	}

	void SVG::SVGDetail::clear()
	{
		m_document.reset();

		m_isEmpty = true;
	}

	Image SVG::SVGDetail::render(const Optional<int32>& maxWidth, const Optional<int32>& maxHeight, const Color& background) const
	{
		const int32 imageWidth	= maxWidth.value_or_eval([&] { return static_cast<int32>(std::ceil(m_document->width())); });
		const int32 imageHeight	= maxHeight.value_or_eval([&] { return static_cast<int32>(std::ceil(m_document->height())); });
		const uint32 color = Color{ background.a, background.b, background.g, background.r }.asUint32();

		lunasvg::Bitmap bitmap = m_document->renderToBitmap(imageWidth, imageHeight, color);
		bitmap.convert(0, 1, 2, 3, true);

		Image image{ bitmap.width(), bitmap.height() };
		assert(image.size_bytes() == (bitmap.stride() * bitmap.height()));
		std::memcpy(image.data(), bitmap.data(), image.size_bytes());

		return image;
	}
}
