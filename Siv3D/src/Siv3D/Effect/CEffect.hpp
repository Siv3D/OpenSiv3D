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
# include "IEffect.hpp"

namespace s3d
{
	class CEffect final : public ISiv3DEffect
	{
	private:

	public:

		CEffect();

		~CEffect();

		void init() override;

		void update() override;
	};
}
