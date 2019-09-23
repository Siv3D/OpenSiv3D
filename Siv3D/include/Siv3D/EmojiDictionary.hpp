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

# pragma once
# include <memory>
# include "Fwd.hpp"
# include "String.hpp"
# include "Array.hpp"

namespace s3d
{
	class EmojiDictionary
	{
	private:

		class EmojiDictionaryDetail;

		std::shared_ptr<EmojiDictionaryDetail> pImpl;

	public:

		EmojiDictionary();

		EmojiDictionary(const FilePath& path);
	
		~EmojiDictionary();
		
		bool load(const FilePath& path);

		[[nodiscard]] size_t check(String::const_iterator it, const String::const_iterator& itEnd);

		void clear();

		const Array<String>& getList() const;
	};
}
