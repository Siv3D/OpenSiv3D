//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2017 Ryo Suzuki
//	Copyright (C) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/MathParser.hpp>
# include "../../ThirdParty/muparser/muParser.h"

namespace s3d
{
	class MathParser::CMathParser
	{
	private:

		mu::Parser m_parser;

	public:

		CMathParser();

		~CMathParser();

	};
}
