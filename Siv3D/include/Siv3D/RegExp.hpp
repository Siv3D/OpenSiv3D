//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <memory>
# include "Common.hpp"
# include "MatchResults.hpp"

namespace s3d
{
	/// @brief 正規表現
	class RegExp
	{
	private:

		class RegExpDetail;

		std::shared_ptr<RegExpDetail> pImpl;

	public:

		SIV3D_NODISCARD_CXX20
		RegExp();

		SIV3D_NODISCARD_CXX20
		explicit RegExp(StringView pattern);

		[[nodiscard]]
		bool isValid() const noexcept;

		[[nodiscard]]
		explicit operator bool() const noexcept;

		[[nodiscard]]
		bool fullMatch(StringView s) const;

		[[nodiscard]]
		MatchResults match(StringView s) const;

		[[nodiscard]]
		MatchResults search(StringView s) const;

		[[nodiscard]]
		Array<MatchResults> findAll(StringView s) const;
	};

	inline namespace Literals
	{
		inline namespace RegExpLiterals
		{
			[[nodiscard]]
			inline RegExp operator ""_re(const char32_t* s, size_t length) noexcept;
		}
	}
}

# include "detail/RegExp.ipp"
