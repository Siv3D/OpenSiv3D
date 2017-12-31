//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/EmojiDictionary.hpp>
# include <Siv3D/BinaryWriter.hpp>
# include "../../ThirdParty/FID/FID.h"

namespace s3d
{
	class EmojiDictionary::CEmojiDictionary
	{
	private:
		
		FID* m_trieTree = nullptr;

		uint32_t* m_edgeCodePoint = nullptr;
		
		size_t m_edgeCodePointLength = 1; /* 0番ノードに対応する親への辺は存在しないため飛ばす。 */

		uint8_t* m_isEmoji = nullptr;
		
		size_t m_isEmojiLength = 0;
		
		size_t m_isEmojiUint8Length;

		const size_t rootNode = 1;

	public:

		CEmojiDictionary();

		~CEmojiDictionary();

		bool load(const FilePath& path);

		size_t check(String::const_iterator it, const String::const_iterator& itEnd);

		void clear();
	};
}
