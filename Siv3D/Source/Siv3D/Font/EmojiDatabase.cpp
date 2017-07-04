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

# include "EmojiDatabase.hpp"

namespace s3d
{
	EmojiDatabase::EmojiDatabase()
	{
		const std::vector<std::vector<std::uint32_t>> codePoints =
		{
			#include "EmojiCodePoints.txt"
		};

		size_t currentNode = rootNode; /* 現在のノード番号 */
		size_t total = 2;

		std::vector<std::vector<uint32_t>> childIdx = { { 1 },{} };
		std::vector<std::vector<uint32_t>> childCodePoint = { { 0 },{} };
		std::vector<uint8_t> _isEmoji = { '0', '0' };

		{
			std::vector<size_t> parent = { 0, 0 };
			std::vector<uint32_t> prv = {};

			for (const auto& codePoint : codePoints)
			{
				const size_t prvLength = prv.size();
				const size_t codePointLength = codePoint.size();
				const size_t minLength = std::min<size_t>(prvLength, codePointLength);

				size_t common = 0;
				while (common < minLength && prv[common] == codePoint[common]) common++;

				for (size_t i = 0; i < prvLength - common; ++i)
				{
					currentNode = parent[currentNode];
				}

				for (size_t i = common; i < codePointLength; ++i)
				{
					//printf("%d:%x\n",i,codePoint[i]);
					parent.emplace_back(currentNode);

					childIdx[currentNode].emplace_back(total);
					childIdx.emplace_back(std::vector<uint32_t>());

					childCodePoint[currentNode].emplace_back(codePoint[i]);
					childCodePoint.emplace_back(std::vector<uint32_t>());

					_isEmoji.emplace_back('0');
					currentNode = total++;
				}

				_isEmoji[currentNode] = '1';
				prv = codePoint;
			}
		}


		{
			/* 木のビット表現 */
			uint8_t* BIT;
			BIT = new uint8_t[2 * total];
			size_t BITLength = 0;

			/* 親への辺に対応するcodePoint */
			edgeCodePoint = new uint32_t[total];

			/* ノードが絵文字であるか判定 */
			isEmojiUint8Length = (total + 7) / 8; // ceil(total/8) -> (total+7)/8
			isEmoji = new uint8_t[isEmojiUint8Length];

			/* 深さ優先順 から　幅優先順 への 木のインデックスの並び替え */
			std::queue<size_t> q;
			q.push(0);

			while (!q.empty())
			{
				size_t current_idx = q.front();
				q.pop();

				for (size_t i = 0; i < childIdx[current_idx].size(); ++i)
				{
					BIT[BITLength++] = '1';
					edgeCodePoint[edgeCodePointLength++] = childCodePoint[current_idx][i];
					q.push(childIdx[current_idx][i]);
				}
				BIT[BITLength++] = '0';

				const size_t upperPos = isEmojiLength >> 3;
				const size_t lowerPos = isEmojiLength & 0x07;
				const uint8_t lowerPosMask = (1 << (7 - lowerPos));
				isEmojiLength++;

				if (_isEmoji[current_idx] == '1')
				{
					isEmoji[upperPos] |= lowerPosMask;
				}
				else
				{
					isEmoji[upperPos] &= ~lowerPosMask;
				}
			}

			BIT[BITLength++] = '\0';
			trieTree = new FID(BIT);
			delete[] BIT;
		}

		return;
	}

	EmojiDatabase::~EmojiDatabase()
	{
		delete trieTree;
		delete[] edgeCodePoint;
		delete[] isEmoji;
	}

	size_t EmojiDatabase::check(std::vector<char32_t>::const_iterator it, std::vector<char32_t>::const_iterator itEnd) const
	{
		size_t emojiLength = 0;
		size_t currentLength = 0;
		size_t currentNode = rootNode; /* 現在のノード番号 */

		while (it != itEnd)
		{
			const std::uint32_t codePoint = *(it++);

			const uint16_t from = trieTree->select(currentNode - 1, 0) + 1;
			const uint16_t to = trieTree->select(currentNode + 1 - 1, 0);

			/* ノードがない場合は探索を打ち切る。*/
			if (from == to) break;

			/* BinarySearchを追記する。*/

			uint16_t lower = from, upper = to;
			while (upper - lower > 1)
			{
				const uint16_t mid = (lower + upper) / 2;
				//printf("%d:%x %x\n",trieTree->rank(mid, 1),edgeCodePoint[trieTree->rank(mid, 1)],codePoint);
				if (edgeCodePoint[trieTree->rank(mid + 1, 1)] <= codePoint)
				{
					lower = mid;
				}
				else
				{
					upper = mid;
				}
			}

			/* ノードが見つからない場合も探索を打ち切る */

			if (edgeCodePoint[trieTree->rank(lower + 1, 1)] != codePoint) break;

			/* ノードの遷移と文字列の長さの調整 */
			currentNode = trieTree->rank(lower + 1, 1);
			currentLength++;

			const size_t upperPos = currentNode >> 3;
			const size_t lowerPos = currentNode & 0x07;
			const uint8_t lowerPosMask = (1 << (7 - lowerPos));

			if (isEmoji[upperPos] & lowerPosMask)
			{
				/* 絵文字が存在するノードの場合、絵文字の長さを更新*/
				/* 複数マッチングする絵文字がある場合には、最長の長さとなる */
				emojiLength = currentLength;
			}
		}

		return emojiLength;
	}
}
