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

# pragma once
# include "../IGraphics.hpp"

namespace s3d
{
	class CGraphics_D3D11 : public ISiv3DGraphics
	{
	private:

	public:

		CGraphics_D3D11();

		~CGraphics_D3D11() override;

		bool init() override;
	};
}
