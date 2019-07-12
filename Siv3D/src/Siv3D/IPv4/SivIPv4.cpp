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

# include <Siv3D/IPv4.hpp>
# include <Siv3D/Format.hpp>

namespace s3d
{
	IPv4::IPv4(const String& ipv4)
	{
		std::istringstream(Unicode::NarrowAscii(ipv4)) >> *this;
	}

	String IPv4::toStr() const
	{
		return Format(asUint8[0], U'.', asUint8[1], U'.', asUint8[2], U'.', asUint8[3]);
	}

	void Formatter(FormatData& formatData, const IPv4& value)
	{
		formatData.string.append(value.toStr());
	}
}
