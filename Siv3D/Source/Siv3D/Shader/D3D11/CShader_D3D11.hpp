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
# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_WINDOWS)

# include "../IShader.hpp"

namespace s3d
{
	class CShader_D3D11 : public ISiv3DShader
	{
	private:

	public:

		CShader_D3D11();

		~CShader_D3D11() override;

		bool init() override;
	};
}

# endif
