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
# include <Console/IConsole.hpp>

namespace s3d
{
	class CConsole : public ISiv3DConsole
	{
	private:


	public:

		CConsole();

		~CConsole() override;

		void open() override;

		void close() override;
	};
}
