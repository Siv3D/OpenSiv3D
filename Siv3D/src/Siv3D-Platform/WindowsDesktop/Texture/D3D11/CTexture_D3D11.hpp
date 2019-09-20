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
# include <Siv3D/Windows.hpp>
# include <d3d11.h>
# include <Texture/ITexture.hpp>
# include <AssetHandleManager/AssetHandleManager.hpp>
# include "Texture_D3D11.hpp"

namespace s3d
{
	class CTexture_D3D11 : public ISiv3DTexture
	{
	private:

		static constexpr uint32 SampleCount = 4;

		ID3D11Device* m_device = nullptr;

		ID3D11DeviceContext* m_context = nullptr;

		AssetHandleManager<TextureID, Texture_D3D11> m_textures{ U"Texture" };

		std::array<bool, 10> m_multiSampleAvailable = {};

	public:

		~CTexture_D3D11() override;

		void init(ID3D11Device* device, ID3D11DeviceContext* context);

		void updateAsync(size_t maxUpdate) override;

		TextureID createUnmipped(const Image& image, TextureDesc desc) override;

		TextureID create(const Image& image, const Array<Image>& mips, TextureDesc desc) override;

		TextureID createDynamic(const Size& size, const void* pData, uint32 stride, const TextureFormat& format, TextureDesc desc) override;

		TextureID createDynamic(const Size& size, const ColorF& color, const TextureFormat& format, TextureDesc desc) override;

		TextureID createRT(const Size& size, const TextureFormat& format) override;

		TextureID createRT(const Image& image) override;

		TextureID createMSRT(const Size& size, const TextureFormat& format) override;

		void release(TextureID handleID) override;

		Size getSize(TextureID handleID) override;

		TextureDesc getDesc(TextureID handleID) override;

		TextureFormat getFormat(TextureID handleID) override;

		ID3D11ShaderResourceView** getSRVPtr(TextureID handleID);

		ID3D11RenderTargetView* getRTV(TextureID handleID);

		void clearRT(TextureID handleID, const ColorF& color) override;

		void readRT(TextureID handleID, Image& image) override;

		void readRT(TextureID handleID, Grid<float>& image) override;

		void readRT(TextureID handleID, Grid<Float2>& image) override;

		void readRT(TextureID handleID, Grid<Float4>& image) override;

		void resolveMSRT(const TextureID handleID) override;

		bool fill(TextureID handleID, const ColorF& color, bool wait) override;

		bool fillRegion(TextureID handleID, const ColorF& color, const Rect& rect) override;

		bool fill(TextureID handleID, const void* src, uint32 stride, bool wait) override;

		bool fillRegion(TextureID handleID, const void* src, uint32 stride, const Rect& rect, bool wait) override;
	};
}
