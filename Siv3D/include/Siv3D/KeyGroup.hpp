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
# include "Array.hpp"
# include "KeyConjunction.hpp"

namespace s3d
{
	class KeyGroup
	{
	private:

		Array<Key> m_keys;

		Array<KeyConjunction> m_keyConjunctions;

		template <class Type, class ...Args>
		void append(const Type& key, const Args&... args)
		{
			append(key);
			append(args...);
		}

		void append();

		void append(const Key& key);

		void append(const KeyConjunction& conjunction);

		void append(const KeyGroup& group);

	public:

		template <class ...Args>
		explicit KeyGroup(const Args&... args)
		{
			append(args...);
		}

		KeyGroup& operator |=(const Key& key);

		KeyGroup& operator |=(const KeyConjunction& conjunction);

		KeyGroup& operator |=(const KeyGroup& group);

		[[nodiscard]] bool down() const;

		[[nodiscard]] bool pressed() const;

		[[nodiscard]] bool up() const;

		[[nodiscard]] int32 num_pressed() const;

		[[nodiscard]] Duration pressedDuration() const;

		[[nodiscard]] const Array<Key>& keys() const;

		[[nodiscard]] const Array<KeyConjunction>& keyConjunctions() const;

		[[nodiscard]] String name() const;
	};

	[[nodiscard]] KeyGroup operator |(const Key& key1, const Key& key2);

	[[nodiscard]] KeyGroup operator |(const Key& key1, const KeyConjunction& key2);

	[[nodiscard]] KeyGroup operator |(const Key& key1, const KeyGroup& key2);

	[[nodiscard]] KeyGroup operator |(const KeyConjunction& key1, const Key& key2);

	[[nodiscard]] KeyGroup operator |(const KeyConjunction& key1, const KeyConjunction& key2);

	[[nodiscard]] KeyGroup operator |(const KeyConjunction& key1, const KeyGroup& key2);

	[[nodiscard]] KeyGroup operator |(const KeyGroup& key1, const Key& key2);

	[[nodiscard]] KeyGroup operator |(const KeyGroup& key1, const KeyConjunction& key2);

	[[nodiscard]] KeyGroup operator |(const KeyGroup& key1, const KeyGroup& key2);

	[[nodiscard]] bool operator ==(const KeyGroup& group1, const KeyGroup& group2);

	[[nodiscard]] bool operator !=(const KeyGroup& group1, const KeyGroup& group2);
}

//////////////////////////////////////////////////////////////////////////////
//
//	Formatting KeyGroup
//
//	[x] Siv3D Formatter
//	[x] ostream
//	[x] wostream
//	[ ] istream
//	[ ] wistream
//	[p] fmtlib BasicFormatter<wchar>
//
namespace s3d
{
	void Formatter(FormatData& formatData, const KeyGroup& group);

	template <class CharType>
	inline std::basic_ostream<CharType> & operator <<(std::basic_ostream<CharType> os, const KeyGroup& group)
	{
		return os << group.name();
	}
}
//
//////////////////////////////////////////////////////////////////////////////
