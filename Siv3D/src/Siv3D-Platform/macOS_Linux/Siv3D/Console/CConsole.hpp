//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Console/IConsole.hpp>

namespace s3d
{
	class CConsole : public ISiv3DConsole
	{
	public:

		CConsole();

		~CConsole() override;

		void open() override;

		void close() override;

		void setSystemDefaultCodePage() override;

		void setUTF8CodePage() override;
	};
}
