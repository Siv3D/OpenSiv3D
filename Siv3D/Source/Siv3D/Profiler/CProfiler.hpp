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
# include "IProfiler.hpp"

namespace s3d
{
	class CProfiler : public ISiv3DProfiler
	{
	private:

	public:

		CProfiler();

		~CProfiler() override;

		bool init() override;
	};
}
