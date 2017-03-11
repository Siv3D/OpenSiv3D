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

# include <memory>
# include "../IGraphics.hpp"
# include "Device/D3D11Device.hpp"
# include "SwapChain/D3D11SwapChain.hpp"

namespace s3d
{
	class CGraphics_D3D11 : public ISiv3DGraphics
	{
	private:

		std::unique_ptr<D3D11Device> m_device;

		std::unique_ptr<D3D11SwapChain> m_swapChain;

	public:

		CGraphics_D3D11();

		~CGraphics_D3D11() override;

		bool init() override;
	};
}

# endif
