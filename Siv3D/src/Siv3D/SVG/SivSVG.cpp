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

# include <Siv3D/SVG.hpp>
# include <Siv3D/Image.hpp>
# include <Siv3D/SVG/SVGDetail.hpp>

namespace s3d
{
	SVG::SVG()
		: pImpl{ std::make_shared<SVGDetail>() }
	{
		// do nothing
	}

	SVG::SVG(const FilePathView path)
		: SVG{}
	{
		load(path);
	}

	SVG::SVG(std::unique_ptr<IReader>&& reader)
		: SVG{}
	{
		load(std::move(reader));
	}

	bool SVG::load(const FilePathView path)
	{
		return pImpl->load(path);
	}

	bool SVG::load(std::unique_ptr<IReader>&& reader)
	{
		return pImpl->load(std::move(reader));
	}

	bool SVG::parse(const std::string& source)
	{
		return pImpl->parse(source);
	}

	bool SVG::parse(const StringView source)
	{
		return pImpl->parse(source);
	}

	bool SVG::isEmpty() const noexcept
	{
		return pImpl->isEmpty();
	}

	int32 SVG::width() const
	{
		return static_cast<int32>(std::ceil(pImpl->width()));
	}

	int32 SVG::height() const
	{
		return static_cast<int32>(std::ceil(pImpl->height()));
	}

	Size SVG::size() const
	{
		return{ width(), height() };
	}

	double SVG::widthF() const
	{
		return pImpl->width();
	}

	double SVG::heightF() const
	{
		return pImpl->height();
	}

	SizeF SVG::sizeF() const
	{
		return{ widthF(), heightF() };
	}

	void SVG::clear()
	{
		pImpl->clear();
	}

	Image SVG::render(const Color& background) const
	{
		return pImpl->render(unspecified, unspecified, background);
	}

	Image SVG::render(const Optional<int32>& maxWidth, const Optional<int32>& maxHeight, const Color& background) const
	{
		return pImpl->render(maxWidth, maxHeight, background);
	}

	Image SVG::render(const Optional<Size>& maxSize, const Color& background) const
	{
		if (maxSize)
		{
			return pImpl->render(maxSize->x, maxSize->y, background);
		}
		else
		{
			return pImpl->render(unspecified, unspecified, background);
		}
	}

	SVG SVG::Load(const FilePathView path)
	{
		return SVG{ path };
	}

	SVG SVG::Parse(const std::string& source)
	{
		SVG svg;
		svg.parse(source);
		return svg;
	}

	SVG SVG::Parse(const StringView source)
	{
		SVG svg;
		svg.parse(source);
		return svg;
	}
}
