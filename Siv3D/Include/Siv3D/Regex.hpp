//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <regex>
# include "Fwd.hpp"
# include "String.hpp"
# include "Array.hpp"

namespace s3d
{
	/// <summary>
	/// 正規表現マッチの結果
	/// </summary>
	using Match = std::wsmatch;

	/// <summary>
	/// 正規表現
	/// </summary>
	/// <remarks>
	/// 正規表現の機能を提供します。
	/// </remarks>
	namespace Regex
	{
		/// <summary>
		/// 正規表現に一致した最初の文字列を置換します。
		/// </summary>
		/// <param name="input">
		/// 対象の文字列
		/// </param>
		/// <param name="regex">
		/// 検索する正規表現
		/// </param>
		/// <param name="replacement">
		/// 置換後の正規表現
		/// </param>
		/// <returns>
		/// 置換した文字列
		/// </returns>
		inline String ReplaceFirst(const String& input, const String& regex, const String& replacement)
		{
			return std::regex_replace(
				input.str(),
				std::wregex(regex.str()),
				replacement.str(),
				std::regex_constants::format_first_only
			);
		}

		/// <summary>
		/// 正規表現に一致した文字列を全て置換します。
		/// </summary>
		/// <param name="input">
		/// 対象の文字列
		/// </param>
		/// <param name="regex">
		/// 検索する正規表現
		/// </param>
		/// <param name="replacement">
		/// 置換後の正規表現
		/// </param>
		/// <returns>
		/// 置換した文字列
		/// </returns>
		inline String ReplaceAll(const String& input, const String& regex, const String& replacement)
		{
			return std::regex_replace(
				input.str(),
				std::wregex(regex.str()),
				replacement.str()
			);
		}

		/// <summary>
		/// 正規表現に一致する全てのマッチを返します。
		/// </summary>
		/// <param name="input">
		/// 対象の文字列
		/// </param>
		/// <param name="regex">
		/// 検索する正規表現
		/// </param>
		/// <returns>
		/// マッチの一覧
		/// </returns>
		inline Array<Match> Search(const String& input, const String& regex)
		{
			const std::wregex reg(regex.str());

			auto begin = input.begin();
			const auto end = input.end();

			std::wsmatch match;

			Array<Match> results;

			while (std::regex_search(begin, end, match, reg))
			{
				results.emplace_back(match);

				begin = match[0].second;
			}

			return results;
		}

		inline Array<String> Split(const String& input, const String& regex)
		{
			const std::wregex reg(regex.str());

			return{ std::wsregex_token_iterator{ input.begin(), input.end(), reg, -1 }, std::wsregex_token_iterator{} };
		}
	}
}
