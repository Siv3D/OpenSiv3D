//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <queue>
# include <Siv3D/String.hpp>
# include <Siv3D/BinaryReader.hpp>
# include "EmojiDictionaryDetail.hpp"

namespace s3d
{
	EmojiDictionary::EmojiDictionaryDetail::EmojiDictionaryDetail()
	{

	}

	EmojiDictionary::EmojiDictionaryDetail::~EmojiDictionaryDetail()
	{
		clear();
	}

	bool EmojiDictionary::EmojiDictionaryDetail::load(const FilePath& path)
	{
		clear();

		BinaryReader reader(path);

		if (!reader)
		{
			return false;
		}

		{
			ByteArray data = reader.readAll();

			int64 size_to_read = data.size();

			uint32 length = 0;

			uint32 buffer[16] = {};

			while (size_to_read)
			{
				data.read(length);

				data.read(buffer, length * sizeof(uint32));

				size_to_read -= (sizeof(uint32) + length * sizeof(uint32));

				m_codePoints.push_back(String(std::begin(buffer), std::begin(buffer) + length));
			}
		}

		size_t currentNode = rootNode; /* 現在のノード番号 */
		size_t total = 2;

		std::vector<std::vector<uint32_t>> childIdx = { { 1 },{} };
		std::vector<std::vector<uint32_t>> childCodePoint = { { 0 },{} };
		std::vector<uint8_t> _isEmoji = { '0', '0' };

		{
			std::vector<size_t> parent = { 0, 0 };
			String prv;

			for (const auto& codePoint : m_codePoints)
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

					childIdx[currentNode].push_back(static_cast<uint32_t>(total));
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
			m_edgeCodePoint = new uint32_t[total];

			/* ノードが絵文字であるか判定 */
			m_isEmojiUint8Length = (total + 7) / 8; // ceil(total/8) -> (total+7)/8
			m_isEmoji = new uint8_t[m_isEmojiUint8Length];

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
					m_edgeCodePoint[m_edgeCodePointLength++] = childCodePoint[current_idx][i];
					q.push(childIdx[current_idx][i]);
				}
				BIT[BITLength++] = '0';

				const size_t upperPos = m_isEmojiLength >> 3;
				const size_t lowerPos = m_isEmojiLength & 0x07;
				const uint8_t lowerPosMask = (1 << (7 - lowerPos));
				m_isEmojiLength++;

				if (_isEmoji[current_idx] == '1')
				{
					m_isEmoji[upperPos] |= lowerPosMask;
				}
				else
				{
					m_isEmoji[upperPos] &= ~lowerPosMask;
				}
			}

			BIT[BITLength++] = '\0';
			m_trieTree = new FID(BIT);
			delete[] BIT;
		}

		return true;
	}

	size_t EmojiDictionary::EmojiDictionaryDetail::check(String::const_iterator it, const String::const_iterator& itEnd)
	{
		size_t emojiLength = 0;
		size_t currentLength = 0;
		size_t currentNode = rootNode; /* 現在のノード番号 */

		while (it != itEnd)
		{
			const std::uint32_t codePoint = *(it++);

			const size_t from = m_trieTree->select(static_cast<int32>(currentNode - 1), 0) + 1;
			const size_t to = m_trieTree->select(static_cast<int32>(currentNode + 1 - 1), 0);

			/* ノードがない場合は探索を打ち切る。*/
			if (from == to) break;

			/* BinarySearchを追記する。*/

			uint16_t lower = static_cast<uint16_t>(from), upper = static_cast<uint16_t>(to);
			while (upper - lower > 1)
			{
				const uint16_t mid = (lower + upper) / 2;
				//printf("%d:%x %x\n",trieTree->rank(mid, 1),edgeCodePoint[trieTree->rank(mid, 1)],codePoint);
				if (m_edgeCodePoint[m_trieTree->rank(mid + 1, 1)] <= codePoint)
				{
					lower = mid;
				}
				else
				{
					upper = mid;
				}
			}

			/* ノードが見つからない場合も探索を打ち切る */

			if (m_edgeCodePoint[m_trieTree->rank(lower + 1, 1)] != codePoint) break;

			/* ノードの遷移と文字列の長さの調整 */
			currentNode = m_trieTree->rank(lower + 1, 1);
			currentLength++;

			const size_t upperPos = currentNode >> 3;
			const size_t lowerPos = currentNode & 0x07;
			const uint8_t lowerPosMask = (1 << (7 - lowerPos));

			if (m_isEmoji[upperPos] & lowerPosMask)
			{
				/* 絵文字が存在するノードの場合、絵文字の長さを更新*/
				/* 複数マッチングする絵文字がある場合には、最長の長さとなる */
				emojiLength = currentLength;
			}
		}

		return emojiLength;
	}

	void EmojiDictionary::EmojiDictionaryDetail::clear()
	{
		m_codePoints.clear();

		if (m_trieTree)
		{
			delete m_trieTree;
			m_trieTree = nullptr;
		}

		if (m_edgeCodePoint)
		{
			delete[] m_edgeCodePoint;
			m_edgeCodePoint = nullptr;
		}

		if (m_isEmoji)
		{
			delete[] m_isEmoji;
			m_isEmoji = nullptr;
		}
	}

	const Array<String>& EmojiDictionary::EmojiDictionaryDetail::getList() const
	{
		return m_codePoints;
	}
}
