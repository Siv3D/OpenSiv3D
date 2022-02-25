//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
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
	/// @brief SVG データ
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

		[[nodiscard]]
		int32 width() const;

		[[nodiscard]]
		int32 height() const;

		[[nodiscard]]
		Size size() const;

		[[nodiscard]]
		double widthF() const;

		[[nodiscard]]
		double heightF() const;

		[[nodiscard]]
		SizeF sizeF() const;

		/// @brief SVG データを消去します。
		void clear();

		/// @brief SVG を Image にレンダリングします。
		/// @param background 無色部分の背景色
		/// @return レンダリング結果
		[[nodiscard]]
		Image render(const Color& background) const;

		[[nodiscard]]
		Image render(const Optional<int32>& maxWidth, const Optional<int32>& maxHeight, const Color& background = Color{ 0, 0 }) const;

		[[nodiscard]]
		Image render(const Optional<Size>& maxSize = unspecified, const Color& background = Color{ 0, 0 }) const;

		[[nodiscard]]
		static SVG Load(FilePathView path);

		[[nodiscard]]
		static SVG Parse(const std::string& source);

		[[nodiscard]]
		static SVG Parse(StringView source);

	private:

		class SVGDetail;

		std::shared_ptr<SVGDetail> pImpl;
	};
}

# include "detail/SVG.ipp"
