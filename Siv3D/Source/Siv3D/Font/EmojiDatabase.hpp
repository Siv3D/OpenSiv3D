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
# include <vector>
# include <queue>
# include <algorithm>
# include <Siv3D/Fwd.hpp>
# include <Siv3D/HashMap.hpp>
# include "../../ThirdParty/FID/FID.h"

namespace s3d
{
	class EmojiDatabase
	{
	private:

		FID* trieTree;

		uint32_t* edgeCodePoint;
		size_t edgeCodePointLength = 1; /* 0番ノードに対応する親への辺は存在しないため飛ばす。 */

		uint8_t* isEmoji;
		size_t isEmojiLength = 0;
		size_t isEmojiUint8Length;

		const size_t rootNode = 1;

	public:

		EmojiDatabase();

		~EmojiDatabase();

		size_t check(std::vector<char32_t>::const_iterator it, std::vector<char32_t>::const_iterator itEnd) const;
	};
/*
	class EmojiDataHelper
	{
		friend class EmojiDatabase2;

		static constexpr std::size_t LongestCodePointLength = 7;

		template<typename T, std::size_t N>
		static constexpr std::size_t size(T(&)[N])noexcept { return N; }
		template<typename T, std::size_t N>
		static constexpr std::size_t length(const std::array<T, N>& t)noexcept {
			auto n = N - 1;
			while (n && t[n] == 0)
				--n;
			return n + 1;
		}
		static constexpr std::size_t codePointsNum()noexcept {
			constexpr std::array<std::uint32_t, LongestCodePointLength> arr[] = {
			#include "EmojiCodePoints.txt"
			};
			return size(arr);
		}
		template<std::size_t N = codePointsNum()>
		static constexpr std::array<std::array<std::uint32_t, LongestCodePointLength>, N> emojiCodePoints() {
			return{ {
				#include "EmojiCodePoints.txt"
				} };
		}
		static constexpr std::size_t trieHeadSize() {
			constexpr auto arr = emojiCodePoints();
			std::uint32_t prev = 0;
			std::uint32_t count = 1;
			for (std::size_t i = 0; i != arr.size() - 1; ++i) {
				const auto len = length(arr[i]);
				if (prev == 0) {
					prev = arr[i][0];
					continue;
				}
				if (prev != arr[i][0]) {
					prev = arr[i][0];
					++count;
				}
			}
			return count;
		}
	};

	class EmojiDatabase2
	{
	private:

		struct trie {
			std::unique_ptr<HashMap<std::uint32_t, trie>> nexts;
			std::size_t length;
		};

		template<typename T, std::size_t N>
		static constexpr std::size_t size(T(&)[N])noexcept { return N; }
		template<typename T, std::size_t N>
		static constexpr std::size_t length(const std::array<T, N>& t)noexcept {
			auto n = N - 1;
			while (n && t[n] == 0)
				--n;
			return n + 1;
		}

		trie emojiCodePoints =
			[] {
			trie tri = { std::make_unique<HashMap<std::uint32_t, trie>>(), 0 };
			tri.nexts->reserve(EmojiDataHelper::trieHeadSize() + 1);
			constexpr auto arr = EmojiDataHelper::emojiCodePoints();
			trie* ptr;
			for (std::size_t j = 0; j != arr.size() - 1; ++j) {
				ptr = &tri;
				const auto len = length(arr[j]);
				for (std::size_t i = 0; i != len; ++i) {
					if (!ptr->nexts)
						ptr->nexts = std::make_unique<HashMap<std::uint32_t, trie>>();
					ptr = &(*ptr->nexts)[arr[j][i]];
				}
				ptr->length = len;
			}
			return std::move(tri);
		}();

	public:

		EmojiDatabase2() = default;

		size_t check(std::vector<std::uint32_t>::const_iterator beg, std::vector<std::uint32_t>::const_iterator end)const
		{
			const trie* ptr = &emojiCodePoints;
			while (beg != end) {
				auto it = ptr->nexts->find(*beg);
				if (it == ptr->nexts->end())
					break;
				ptr = &it->second;
				if (!ptr->nexts)
					break;
				++beg;
			}
			return ptr->length;
		}
	};
	*/
}
