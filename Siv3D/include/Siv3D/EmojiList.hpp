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
	class EmojiList
	{
	private:

		class EmojiDictionaryDetail;

		std::shared_ptr<EmojiDictionaryDetail> pImpl;

	public:

		using const_iterator = typename Array<String>::const_iterator;

		EmojiList();

		EmojiList(FilePathView path);
	
		~EmojiList();
		
		bool load(FilePathView path);

		[[nodiscard]] bool isEmpty() const noexcept;

		[[nodiscard]] explicit operator bool() const noexcept
		{
			return !isEmpty();
		}

		[[nodiscard]] size_t size() const noexcept;

		[[nodiscard]] StringView operator[](size_t index) const noexcept;

		void clear();

		[[nodiscard]] const_iterator begin() const noexcept;

		[[nodiscard]] const_iterator end() const noexcept;

		[[nodiscard]] const Array<String>& getList() const;

		[[nodiscard]] size_t check(String::const_iterator it, const String::const_iterator& itEnd);
	};
}
