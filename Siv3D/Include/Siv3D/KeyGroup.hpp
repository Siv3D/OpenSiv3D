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

		void append() {}

		void append(const Key& key)
		{
			(m_keys << key).unique();
		}

		void append(const KeyConjunction& conjunction)
		{
			(m_keyConjunctions << conjunction).unique();
		}

		void append(const KeyGroup& group)
		{
			m_keys.append(group.m_keys).unique();
			m_keyConjunctions.append(group.m_keyConjunctions).unique();
		}

	public:

		template <class ...Args>
		explicit KeyGroup(const Args&... args)
		{
			append(args...);
		}

		template <class Type>
		KeyGroup& operator |=(const Type& key)
		{
			append(key);
			return *this;
		}

		bool down() const
		{
			return m_keys.any([](const Key& k) { return k.down(); })
				|| m_keyConjunctions.any([](const KeyConjunction& c) { return c.down(); });
		}

		bool pressed() const
		{
			return m_keys.any([](const Key& k) { return k.pressed(); })
				|| m_keyConjunctions.any([](const KeyConjunction& c) { return c.pressed(); });
		}

		bool up() const
		{
			return m_keys.any([](const Key& k) { return k.up(); })
				|| m_keyConjunctions.any([](const KeyConjunction& c) { return c.up(); });
		}

		int32 num_pressed() const
		{
			int32 num = 0;

			for (const auto& key : m_keys)
			{
				num += key.pressed();
			}

			for (const auto& keyConjunction : m_keyConjunctions)
			{
				num += keyConjunction.pressed();
			}

			return num;
		}

		MillisecondsF pressedDuration() const
		{
			MillisecondsF duration(0);

			for (const auto& key : m_keys)
			{
				duration = std::max(key.pressedDuration(), duration);
			}

			for (const auto& keyConjunction : m_keyConjunctions)
			{
				duration = std::max(keyConjunction.pressedDuration(), duration);
			}

			return duration;
		}

		const Array<Key>& keys() const
		{
			return m_keys;
		}

		const Array<KeyConjunction>& keyConjunctions() const
		{
			return m_keyConjunctions;
		}

		String name() const
		{
			return m_keys.join(S3DSTR("|")) + m_keyConjunctions.join(S3DSTR("|"));
		}
	};

	inline KeyGroup operator |(const Key& key1, const Key& key2)
	{
		return KeyGroup(key1, key2);
	}

	inline KeyGroup operator |(const Key& key1, const KeyConjunction& key2)
	{
		return KeyGroup(key1, key2);
	}

	inline KeyGroup operator |(const Key& key1, const KeyGroup& key2)
	{
		return KeyGroup(key1, key2);
	}

	inline KeyGroup operator |(const KeyConjunction& key1, const Key& key2)
	{
		return KeyGroup(key1, key2);
	}

	inline KeyGroup operator |(const KeyConjunction& key1, const KeyConjunction& key2)
	{
		return KeyGroup(key1, key2);
	}

	inline KeyGroup operator |(const KeyConjunction& key1, const KeyGroup& key2)
	{
		return KeyGroup(key1, key2);
	}

	inline KeyGroup operator |(const KeyGroup& key1, const Key& key2)
	{
		return KeyGroup(key1, key2);
	}

	inline KeyGroup operator |(const KeyGroup& key1, const KeyConjunction& key2)
	{
		return KeyGroup(key1, key2);
	}

	inline KeyGroup operator |(const KeyGroup& key1, const KeyGroup& key2)
	{
		return KeyGroup(key1, key2);
	}

	inline bool operator ==(const KeyGroup& group1, const KeyGroup& group2)
	{
		return group1.keys() == group2.keys() && group1.keyConjunctions() == group2.keyConjunctions();
	}

	inline bool operator !=(const KeyGroup& group1, const KeyGroup& group2)
	{
		return group1.keys() != group2.keys() || group1.keyConjunctions() != group2.keyConjunctions();
	}
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
	inline void Formatter(FormatData& formatData, const KeyGroup& group)
	{
		formatData.string.append(group.name());
	}

	template <class CharType>
	inline std::basic_ostream<CharType> & operator <<(std::basic_ostream<CharType> os, const KeyGroup& group)
	{
		return os << group.name();
	}
}
//
//////////////////////////////////////////////////////////////////////////////
