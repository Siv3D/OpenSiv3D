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

		template <class Type>
		KeyGroup& operator |=(const Type& key)
		{
			append(key);
			return *this;
		}

		bool down() const;

		bool pressed() const;

		bool up() const;

		int32 num_pressed() const;

		MillisecondsF pressedDuration() const;

		const Array<Key>& keys() const
		{
			return m_keys;
		}

		const Array<KeyConjunction>& keyConjunctions() const
		{
			return m_keyConjunctions;
		}
	};
}
