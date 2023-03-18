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
# include <Siv3D/ResourceOption.hpp>

namespace s3d
{
	class SIV3D_NOVTABLE ISiv3DResource
	{
	public:

		static ISiv3DResource* Create();

		virtual ~ISiv3DResource() = default;

		virtual void init() = 0;

		virtual void setResourceOption(ResourceOption resourceOption) = 0;

		virtual ResourceOption getResourceOption() const noexcept = 0;
	};
}
