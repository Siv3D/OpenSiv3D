//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Fwd.hpp>

namespace s3d
{
	class ISiv3DSoundFont
	{
	public:

		static ISiv3DSoundFont* Create();

		virtual ~ISiv3DSoundFont() = default;

		virtual bool init() = 0;

		virtual void render(Wave& wave, size_t samples, uint32 samplingRate, uint8 instrument, uint8 key, double velocity) = 0;
	};
}
