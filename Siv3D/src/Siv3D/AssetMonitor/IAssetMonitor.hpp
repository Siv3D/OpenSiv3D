//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Common.hpp>

namespace s3d
{
	class SIV3D_NOVTABLE ISiv3DAssetMonitor
	{
	public:

		static ISiv3DAssetMonitor* Create();

		virtual ~ISiv3DAssetMonitor() = default;

		virtual bool update() = 0;

		virtual void setWarningEnabled(bool enabled) = 0;

		virtual void created() = 0;

		virtual void released() = 0;
	};
}
