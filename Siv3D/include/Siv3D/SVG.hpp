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
# include <memory>
# include "Common.hpp"
# include "StringView.hpp"
# include "IReader.hpp"
# include "PointVector.hpp"
# include "ColorHSV.hpp"
# include "Optional.hpp"
# include "Unspecified.hpp"

namespace s3d
{
	class SVG
	{
	public:

		SIV3D_NODISCARD_CXX20
		SVG();

		SIV3D_NODISCARD_CXX20
		explicit SVG(FilePathView path);

		template <class Reader, std::enable_if_t<std::is_base_of_v<IReader, Reader> && !std::is_lvalue_reference_v<Reader>>* = nullptr>
		SIV3D_NODISCARD_CXX20
		explicit SVG(Reader&& reader);

		SIV3D_NODISCARD_CXX20
		explicit SVG(std::unique_ptr<IReader>&& reader);

		bool load(FilePathView path);

		template <class Reader, std::enable_if_t<std::is_base_of_v<IReader, Reader> && !std::is_lvalue_reference_v<Reader>>* = nullptr>
		bool load(Reader&& reader);

		bool load(std::unique_ptr<IReader>&& reader);

		bool parse(const std::string& source);

		bool parse(StringView source);

		[[nodiscard]]
		bool isEmpty() const noexcept;

		[[nodiscard]]
		explicit operator bool() const noexcept;

		int32 width() const;

		int32 height() const;

		Size size() const;

		double widthF() const;

		double heightF() const;

		SizeF sizeF() const;

		void clear();

		Image render(const Color& background) const;

		Image render(const Optional<int32>& maxWidth, const Optional<int32>& maxHeight, const Color& background = Color{ 0, 0 }) const;

		Image render(const Optional<Size>& maxSize = unspecified, const Color& background = Color{ 0, 0 }) const;

	private:

		class SVGDetail;

		std::shared_ptr<SVGDetail> pImpl;
	};
}

# include "detail/SVG.ipp"
