﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "IScreenCapture.hpp"
# include <Siv3D/Array.hpp>
# include <Siv3D/String.hpp>

namespace s3d
{
	class CScreenCapture : public ISiv3DScreenCapture
	{
	private:

		Array<FilePath> m_requestedPaths;

		bool m_hasRequest = false;

	public:

		CScreenCapture();

		~CScreenCapture() override;

		bool init() override;

		bool update() override;

		void requestScreenCapture(const FilePath& path) override;
	};
}
