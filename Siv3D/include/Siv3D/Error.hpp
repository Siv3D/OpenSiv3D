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

# pragma once
# include "Fwd.hpp"
# include "String.hpp"
# include "Format.hpp"

namespace s3d
{
	class Error
	{
	protected:

		String m_what;

	public:

		Error() = default;

		explicit Error(const StringView what)
			: m_what(what) {}

		virtual ~Error() = default;

		const String& what() const
		{
			return m_what;
		}
	};

	class ParseError : public Error
	{
	public:

		explicit ParseError(StringView what)
			: Error(what) {}
	};
}

namespace s3d
{
	void Formatter(FormatData& formatData, const Error& value);

	std::ostream& operator <<(std::ostream& output, const Error& value);

	std::wostream& operator <<(std::wostream& output, const Error& value);
}
