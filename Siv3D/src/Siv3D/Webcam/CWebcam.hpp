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
# include "IWebcam.hpp"
# include <Siv3D/Webcam.hpp>

namespace s3d
{
	class CWebcam : public ISiv3DWebcam
	{
	private:

	public:

		CWebcam();

		~CWebcam() override;

		bool init() override;
	};
}
