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
# include "RenderTarget/D3D11RenderTarget.hpp"
# include "../../Texture/D3D11/CTextureD3D11.hpp"
# include "BlendState/D3D11BlendState.hpp"

namespace s3d
{
	class CGraphics_D3D11 : public ISiv3DGraphics
	{
	private:

		std::unique_ptr<D3D11Device> m_device;

		std::unique_ptr<D3D11SwapChain> m_swapChain;

		std::unique_ptr<D3D11RenderTarget> m_renderTarget;

		CTextureD3D11* m_texture;

		std::unique_ptr<D3D11BlendState> m_pBlendState;

	public:

		CGraphics_D3D11();

		~CGraphics_D3D11() override;

		bool init() override;

		void setClearColor(const ColorF& color) override;

		Array<DisplayOutput> enumOutputs() override;

		bool setFullScreen(bool fullScreen, const Size& size, size_t displayIndex, double refreshRateHz) override;

		bool present() override;

		void clear() override;

		void beginResize() override;

		bool endResize(const Size& size) override;
		
		void setVSyncEnabled(bool enabled) override;
		
		bool isVSyncEnabled() const override;
	};
}

# endif
