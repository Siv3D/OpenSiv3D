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
# include <Siv3D/Resource/IResource.hpp>

namespace s3d
{
	class CResource final : public ISiv3DResource
	{
	private:

		ResourceOption m_resourceOption = ResourceOption::Default;

	public:

		CResource();

		~CResource() override;

		void init() override;

		void setResourceOption(ResourceOption resourceOption) override;

		ResourceOption getResourceOption() const noexcept override;
	};
}
