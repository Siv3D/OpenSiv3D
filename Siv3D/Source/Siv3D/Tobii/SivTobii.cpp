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

# include <Siv3D/Tobii.hpp>
# include "CTobii_Windows.hpp"
# include "CTobii_macOS.hpp"
# include "CTobii_Linux.hpp"

namespace s3d
{
	Tobii::Tobii(const FilePath& dllPath)
		: pImpl(std::make_shared<CTobii>(dllPath))
	{

	}

	Tobii::~Tobii()
	{

	}

	bool Tobii::isInitialized() const
	{
		return pImpl->isInitialized();
	}

	bool Tobii::isConnected() const
	{
		return pImpl->isConnected();
	}

	bool Tobii::reconnect()
	{
		return pImpl->reconnect();
	}

	bool Tobii::hasNewFrame()
	{
		return pImpl->hasNewFrame();
	}

	bool Tobii::getFrame(GazeInfo& info)
	{
		return pImpl->getFrame(info);
	}
}
