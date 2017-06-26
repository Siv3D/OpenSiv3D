//-----------------------------------------------
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
# include <Siv3D/Fwd.hpp>
# include <Siv3D/Effect.hpp>

namespace s3d
{
	class ISiv3DEffect
	{
	public:

		static ISiv3DEffect* Create();

		virtual ~ISiv3DEffect() = default;

		virtual bool init() = 0;
	};
}
