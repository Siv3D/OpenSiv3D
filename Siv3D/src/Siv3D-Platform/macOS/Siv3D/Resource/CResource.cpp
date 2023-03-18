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

# include <Siv3D/Common.hpp>
# include <Siv3D/EngineLog.hpp>
# include "CResource.hpp"

namespace s3d
{
	CResource::CResource() = default;

	CResource::~CResource()
	{
		LOG_SCOPED_TRACE(U"CResource::~CResource()");
	}

	void CResource::init()
	{
		LOG_SCOPED_TRACE(U"CResource::init()");
	}

	void CResource::setResourceOption(const ResourceOption resourceOption)
	{
		LOG_TRACE(U"CResource::setResourceOption({})"_fmt(FromEnum(resourceOption)));

		m_resourceOption = resourceOption;
	}

	ResourceOption CResource::getResourceOption() const noexcept
	{
		return m_resourceOption;
	}	
}
