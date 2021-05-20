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
# include <memory>
# include "Common.hpp"

namespace s3d
{
	/// @brief マイク
	class Microphone
	{
	public:


	private:

		class MicrophoneDetail;

		std::shared_ptr<MicrophoneDetail> pImpl;
	};
}
