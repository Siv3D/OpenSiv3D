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
# include <Siv3D/Common.hpp>
# include <Siv3D/Pentablet.hpp>

namespace s3d
{
	class SIV3D_NOVTABLE ISiv3DPentablet
	{
	public:

		static ISiv3DPentablet* Create();

		virtual ~ISiv3DPentablet() = default;

		virtual void init() = 0;

		virtual void update() = 0;
	};
}
