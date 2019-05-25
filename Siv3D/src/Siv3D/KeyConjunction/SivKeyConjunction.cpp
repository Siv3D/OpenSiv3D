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

# include <Siv3D/KeyConjunction.hpp>

namespace s3d
{
	bool KeyConjunction::down() const
	{
		return m_key1.pressed() && m_key2.down();
	}

	bool KeyConjunction::pressed() const
	{
		const auto t1 = m_key1.pressedDuration();
		const auto t2 = m_key2.pressedDuration();

		if (t1 < t2)
		{
			return false;
		}

		return m_key1.pressed() && m_key2.pressed();
	}

	bool KeyConjunction::up() const
	{
		return m_key1.pressed() && m_key2.up();
	}

	Duration KeyConjunction::pressedDuration() const
	{
		const auto t1 = m_key1.pressedDuration();
		const auto t2 = m_key2.pressedDuration();
		const bool pr = m_key1.pressed() && m_key2.pressed();

		if (!pr || t1 < t2)
		{
			return Duration(0);
		}

		return t2;
	}

	String KeyConjunction::name() const
	{
		return m_key1.name() + U'+' + m_key2.name();
	}

	void Formatter(FormatData& formatData, const KeyConjunction& conjunction)
	{
		formatData.string.append(conjunction.name());
	}
}
