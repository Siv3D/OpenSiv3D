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

# include <Siv3D/FileSystem.hpp>
# include <Siv3D/ImageDecoder/CImageDecoder.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/ImageFormat/GenericDecoder.hpp>

namespace s3d
{
	void CImageDecoder::init()
	{
		LOG_SCOPED_TRACE(U"CImageDecoder::init()");

		m_decoders.push_back(std::make_unique<GenericDecoder>());
	}
}
