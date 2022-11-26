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

# pragma once

namespace s3d
{
	/// @brief OSC 型タグ
	enum class OSCTypeTag : char
	{
		False		= 'F',

		True		= 'T',

		Char		= 'c',

		Int32		= 'i',

		Int64		= 'h',

		Float		= 'f',

		Double		= 'd',

		MIDIMessage	= 'm',

		TimeTag		= 't',

		RGBAColor	= 'r',

		String		= 's',

		Symbol		= 'S',

		Blob		= 'b',

		Nil			= 'N',

		Infinitum	= 'I',

		ArrayBegin	= '[',

		ArrayEnd	= ']'
	};
}
