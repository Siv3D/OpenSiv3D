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
# include <Siv3D/CPU.hpp>
# include "ICPU.hpp"

namespace s3d
{
	class CCPU : public ISiv3DCPU
	{
	private:

		CPUFeature m_feature;

	public:

		CCPU();

		~CCPU() override;

		void init() override;

		void setFeature(const CPUFeature& feature) override;

		const CPUFeature& getFeature() const override;
	};
}
