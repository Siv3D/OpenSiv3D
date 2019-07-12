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

# pragma once
# include <Siv3D/Fwd.hpp>

namespace s3d
{
	class ISiv3DCPU
	{
	public:

		static ISiv3DCPU* Create();

		virtual ~ISiv3DCPU() = default;

		virtual void init() = 0;

		virtual void setFeature(const CPUFeature& feature) = 0;

		virtual const CPUFeature& getFeature() const = 0;
	};
}
