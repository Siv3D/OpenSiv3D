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
# include <atomic>
# include <thread>
# include <mutex>
# include <Texture/ITexture.hpp>
# include <AssetHandleManager/AssetHandleManager.hpp>
# include "Texture_GL.hpp"

namespace s3d
{
	class CTexture_GL : public ISiv3DTexture
	{
	private:

		AssetHandleManager<TextureID, Texture_GL> m_textures{ U"Texture" };

		const std::thread::id m_id = std::this_thread::get_id();
		
		struct Request
		{
			const Image *pImage = nullptr;
			
			const Array<Image> *pMipmaps = nullptr;
			
			const TextureDesc* pDesc = nullptr;
			
			std::reference_wrapper<TextureID> idResult;
			
			std::reference_wrapper<std::atomic<bool>> waiting;
		};
		
		Array<Request> m_requests;
		
		std::mutex m_requestsMutex;
		
		bool isMainThread() const;
		
		TextureID pushRequest(const Image& image, const Array<Image>& mipmaps, const TextureDesc desc);
		
	public:

		~CTexture_GL() override;

		void init();

		void updateAsync(size_t maxUpdate) override;

		TextureID createUnmipped(const Image& image, TextureDesc desc) override;

		TextureID create(const Image& image, const Array<Image>& mips, TextureDesc desc) override;

		TextureID createDynamic(const Size& size, const void* pData, uint32 stride, const TextureFormat& format, TextureDesc desc) override;

		TextureID createDynamic(const Size& size, const ColorF& color, const TextureFormat& format, TextureDesc desc) override;
		
		TextureID createRT(const Size& size, const TextureFormat& format) override;
		
		TextureID createRT(const Image& image) override;
		
		TextureID createRT(const Grid<float>& image) override;
		
		TextureID createRT(const Grid<Float2>& image) override;
		
		TextureID createRT(const Grid<Float4>& image) override;
		
		TextureID createMSRT(const Size& size, const TextureFormat& format) override;

		void release(TextureID handleID) override;

		Size getSize(TextureID handleID) override;

		TextureDesc getDesc(TextureID handleID) override;
		
		TextureFormat getFormat(TextureID handleID) override;
		
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
		
		
		GLuint getTexture(TextureID handleID);
		
		GLuint getFrameBuffer(TextureID handleID);
	};
}
