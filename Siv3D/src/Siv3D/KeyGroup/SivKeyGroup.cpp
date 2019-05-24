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

# include <Siv3D/KeyGroup.hpp>

namespace s3d
{
	KeyGroup& KeyGroup::operator |=(const Key& key)
	{
		append(key);
		return *this;
	}

	KeyGroup& KeyGroup::operator |=(const KeyConjunction& conjunction)
	{
		append(conjunction);
		return *this;
	}

	KeyGroup& KeyGroup::operator |=(const KeyGroup& group)
	{
		append(group);
		return *this;
	}

	bool KeyGroup::down() const
	{
		return m_keys.any([](const Key & k) { return k.down(); })
			|| m_keyConjunctions.any([](const KeyConjunction & c) { return c.down(); });
	}

	bool KeyGroup::pressed() const
	{
		return m_keys.any([](const Key & k) { return k.pressed(); })
			|| m_keyConjunctions.any([](const KeyConjunction & c) { return c.pressed(); });
	}

	bool KeyGroup::up() const
	{
		return m_keys.any([](const Key & k) { return k.up(); })
			|| m_keyConjunctions.any([](const KeyConjunction & c) { return c.up(); });
	}

	int32 KeyGroup::num_pressed() const
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

	Duration KeyGroup::pressedDuration() const
	{
		Duration duration(0);

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

	const Array<Key>& KeyGroup::keys() const
	{
		return m_keys;
	}

	const Array<KeyConjunction>& KeyGroup::keyConjunctions() const
	{
		return m_keyConjunctions;
	}

	String KeyGroup::name() const
	{
		return m_keys.join(U"|") + m_keyConjunctions.join(U"|");
	}

	void KeyGroup::append()
	{
	
	}

	void KeyGroup::append(const Key& key)
	{
		(m_keys << key).unique();
	}

	void KeyGroup::append(const KeyConjunction & conjunction)
	{
		(m_keyConjunctions << conjunction).unique();
	}

	void KeyGroup::append(const KeyGroup & group)
	{
		m_keys.append(group.m_keys).unique();
		m_keyConjunctions.append(group.m_keyConjunctions).unique();
	}

	KeyGroup operator |(const Key& key1, const Key& key2)
	{
		return KeyGroup(key1, key2);
	}

	KeyGroup operator |(const Key& key1, const KeyConjunction& key2)
	{
		return KeyGroup(key1, key2);
	}

	KeyGroup operator |(const Key& key1, const KeyGroup& key2)
	{
		return KeyGroup(key1, key2);
	}

	KeyGroup operator |(const KeyConjunction& key1, const Key& key2)
	{
		return KeyGroup(key1, key2);
	}

	KeyGroup operator |(const KeyConjunction& key1, const KeyConjunction& key2)
	{
		return KeyGroup(key1, key2);
	}

	KeyGroup operator |(const KeyConjunction& key1, const KeyGroup& key2)
	{
		return KeyGroup(key1, key2);
	}

	KeyGroup operator |(const KeyGroup& key1, const Key& key2)
	{
		return KeyGroup(key1, key2);
	}

	KeyGroup operator |(const KeyGroup& key1, const KeyConjunction& key2)
	{
		return KeyGroup(key1, key2);
	}

	KeyGroup operator |(const KeyGroup& key1, const KeyGroup& key2)
	{
		return KeyGroup(key1, key2);
	}

	bool operator ==(const KeyGroup& group1, const KeyGroup& group2)
	{
		return group1.keys() == group2.keys() && group1.keyConjunctions() == group2.keyConjunctions();
	}

	bool operator !=(const KeyGroup& group1, const KeyGroup& group2)
	{
		return group1.keys() != group2.keys() || group1.keyConjunctions() != group2.keyConjunctions();
	}

	void Formatter(FormatData& formatData, const KeyGroup& group)
	{
		formatData.string.append(group.name());
	}
}
