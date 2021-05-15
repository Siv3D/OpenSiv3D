//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "ISoundFont.hpp"

namespace s3d
{
	class CSoundFont final : public ISiv3DSoundFont
	{
	public:

		CSoundFont();

		~CSoundFont() override;

		void init() override;

	private:

		bool m_hasGMGSx = false;
	};
}
