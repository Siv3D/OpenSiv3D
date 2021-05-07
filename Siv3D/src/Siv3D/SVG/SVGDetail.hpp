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

# pragma once
# include <Siv3D/SVG.hpp>
# include <ThirdParty/lunasvg/document.h>

namespace s3d
{
	class SVG::SVGDetail
	{
	public:

		SVGDetail();

		~SVGDetail();

		bool load(FilePathView path);

		bool load(std::unique_ptr<IReader>&& reader);

		bool parse(const std::string& source);

		bool parse(StringView source);

		[[nodiscard]]
		bool isEmpty() const noexcept;

		[[nodiscard]]
		double width() const noexcept;

		[[nodiscard]]
		double height() const noexcept;

		void clear();

		[[nodiscard]]
		Image render(const Optional<int32>& maxWidth, const Optional<int32>& maxHeight, const Color& background) const;

	private:

		std::unique_ptr<lunasvg::Document> m_document;

		bool m_isEmpty = true;
	};
}
