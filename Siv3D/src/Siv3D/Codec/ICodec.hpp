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
	class ISiv3DCodec
	{
	public:

		static ISiv3DCodec* Create();

		virtual ~ISiv3DCodec() = default;

		virtual bool init() = 0;

		virtual Wave decode(IReader& reader) = 0;
	};
}
