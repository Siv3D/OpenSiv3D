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
	namespace detail
	{
		template <class Type>
		inline TextWriterBuffer& TextWriterBuffer::operator <<(const Type& value)
		{
			Formatter(*formatData, value);

			return *this;
		}
	}

	SIV3D_CONCEPT_FORMATTABLE_ARGS_
	inline void TextWriter::write(const Args& ... args)
	{
		write(Format(args...));
	}

	SIV3D_CONCEPT_FORMATTABLE_ARGS_
	inline void TextWriter::writeln(const Args& ... args)
	{
		writeln(Format(args...));
	}

	SIV3D_CONCEPT_FORMATTABLE_
	inline detail::TextWriterBuffer TextWriter::operator <<(const Formattable& value)
	{
		detail::TextWriterBuffer buffer(*this);

		Formatter(*(buffer.formatData), value);

		return buffer;
	}
}
