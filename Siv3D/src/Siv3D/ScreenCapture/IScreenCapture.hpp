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
	class ISiv3DScreenCapture
	{
	public:

		static ISiv3DScreenCapture* Create();

		virtual ~ISiv3DScreenCapture() = default;

		virtual bool init() = 0;

		virtual bool update() = 0;

		virtual const FilePath& getDefaultScreenshotDirectory() const = 0;

		virtual void requestScreenCapture(const FilePath& path) = 0;
	};
}
