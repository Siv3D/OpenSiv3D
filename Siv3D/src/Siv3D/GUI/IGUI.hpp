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
# include <Siv3D/Fwd.hpp>

namespace s3d
{
	class ISiv3DGUI
	{
	public:

		static ISiv3DGUI* Create();

		virtual ~ISiv3DGUI() = default;

		virtual void init() = 0;

		virtual const Font& getDefaultGUIFont() = 0;
	};
}
