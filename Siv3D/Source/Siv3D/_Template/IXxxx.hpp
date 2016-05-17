//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//	Copyright (C) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Fwd.hpp>

namespace s3d
{
	class ISiv3DXxxx
	{
	public:

		static ISiv3DXxxx* Create();

		virtual ~ISiv3DXxxx() = default;

		virtual bool init() = 0;
	};
}
