//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Icon.hpp>
# include <Siv3D/Image.hpp>
# include <Siv3D/SDF.hpp>
# include <Siv3DEngine.hpp>
# include <Font/IFont.hpp>

namespace s3d
{
	Image Icon::CreateImage(const uint32 _code, const int32 _size)
	{
		return Siv3DEngine::Get<ISiv3DFont>()->getAwesomeIcon(static_cast<uint16>(_code), _size);
	}

	Image Icon::CreateMSDFImage(const uint32 _code, const double scale)
	{
		return SDF::GenerateMSDFIcon(_code, scale);
	}
}
