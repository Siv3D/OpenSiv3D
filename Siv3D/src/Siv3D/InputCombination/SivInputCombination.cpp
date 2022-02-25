//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/InputGroups.hpp>

namespace s3d
{
	InputGroup InputCombination::operator |(const Input other) const
	{
		return InputGroup{ *this, other };
	}

	InputGroup InputCombination::operator |(const InputCombination& other) const
	{
		return InputGroup{ *this, other };
	}

	InputGroup InputCombination::operator |(const InputGroup& other) const
	{
		return InputGroup{ *this, other };
	}

	void Formatter(FormatData& formatData, const InputCombination& value)
	{
		Formatter(formatData, value.name());
	}
}
