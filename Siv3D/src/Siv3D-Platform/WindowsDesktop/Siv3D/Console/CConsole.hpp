﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <cstdio>
# include <Siv3D/Console/IConsole.hpp>

namespace s3d
{
	class CConsole final : public ISiv3DConsole
	{
	private:

		FILE* m_fpOut	= nullptr;

		FILE* m_fpIn	= nullptr;

		FILE* m_fpErr	= nullptr;

		bool m_isOpen	= false;

	public:

		CConsole();

		~CConsole() override;

		void open() override;

		void close() override;
	};
}
