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

# include <Siv3D/Resource.hpp>
# include <Siv3D/Resource/IResource.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	void SetResourceOption(const ResourceOption resourceOption)
	{
		SIV3D_ENGINE(Resource)->setResourceOption(resourceOption);
	}

	ResourceOption GetResourceOption() noexcept
	{
		return SIV3D_ENGINE(Resource)->getResourceOption();
	}
}
