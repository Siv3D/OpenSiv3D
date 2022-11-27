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
	inline bool OSCArgument::getBool() const
	{
		return std::get<bool>(value);
	}

	inline char OSCArgument::getChar() const
	{
		return std::get<char>(value);
	}

	inline int32 OSCArgument::getInt32() const
	{
		return std::get<int32>(value);
	}

	inline int64 OSCArgument::getInt64() const
	{
		return std::get<int64>(value);
	}

	inline float OSCArgument::getFloat() const
	{
		return std::get<float>(value);
	}

	inline double OSCArgument::getDouble() const
	{
		return std::get<double>(value);
	}

	inline uint32 OSCArgument::getMIDIMessage() const
	{
		return std::get<uint32>(value);
	}

	inline uint64 OSCArgument::getTimeTag() const
	{
		return std::get<uint64>(value);
	}

	inline Color OSCArgument::getColor() const
	{
		return std::get<Color>(value);
	}

	inline const String& OSCArgument::getString() const
	{
		return std::get<String>(value);
	}

	inline const Blob& OSCArgument::getBlob() const
	{
		return std::get<Blob>(value);
	}
}
