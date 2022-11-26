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
# include <variant>
# include "Common.hpp"
# include "OSCTypeTag.hpp"
# include "ColorHSV.hpp"
# include "String.hpp"
# include "Blob.hpp"

namespace s3d
{
	struct OSCArgument
	{
		OSCTypeTag tag;

		std::variant<std::monostate, bool, char, int32, int64, float, double, uint32, uint64, Color, String, Blob> value;

		[[nodiscard]]
		bool getBool() const;

		[[nodiscard]]
		char getChar() const;

		[[nodiscard]]
		int32 getInt32() const;

		[[nodiscard]]
		int64 getInt64() const;

		[[nodiscard]]
		float getFloat() const;

		[[nodiscard]]
		double getDouble() const;

		[[nodiscard]]
		uint32 getMIDIMessage() const;

		[[nodiscard]]
		uint64 getTimeTag() const;

		[[nodiscard]]
		Color getColor() const;

		[[nodiscard]]
		const String& getString() const;

		[[nodiscard]]
		const Blob& getBlob() const;
	};
}

# include "detail/OSCArgument.ipp"
