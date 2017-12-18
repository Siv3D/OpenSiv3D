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
# if defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

# include <thread>
# include <atomic>
# include <mutex>
# include "../ITexture.hpp"
# include "Texture_GL.hpp"
# include "../../AssetHandleManager/AssetHandleManager.hpp"

# include <Siv3D/System.hpp>

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
		
		TextureID pushRequest(const Image& image, const Array<Image>& mipmaps, const TextureDesc desc)
		{
			std::atomic<bool> waiting = true;
			
			TextureID result = TextureID::NullAsset();
			
			{
				std::lock_guard<std::mutex> lock(m_requestsMutex);
				
				m_requests.push_back(Request{ &image, &mipmaps, &desc, std::ref(result), std::ref(waiting) });
			}

			while (waiting)
			{
				System::Sleep(3);
			}
			
			return result;
		}
		
	public:

		~CTexture_GL();
		
		bool init();
		
		void update(size_t maxUpdate) override
		{
			std::lock_guard<std::mutex> lock(m_requestsMutex);
			
			const size_t toProcess = std::min<size_t>(maxUpdate, m_requests.size());
			
			for (size_t i = 0; i < toProcess; ++i)
			{
				auto& request = m_requests[i];
				
				request.idResult.get() = create(*request.pImage, *request.pMipmaps, TextureDesc::Mipped);
				
				request.waiting.get() = false;
			}
			
			m_requests.erase(m_requests.begin(), m_requests.begin() + toProcess);
		}

		TextureID createFromBackBuffer() override;

		TextureID create(const Image&, TextureDesc) override;

		TextureID create(const Image& image, const Array<Image>& mipmaps, TextureDesc desc) override;

		TextureID createDynamic(const Size& size, const void* pData, uint32 stride, TextureFormat format, TextureDesc desc) override;

		TextureID createDynamic(const Size& size, const ColorF& color, TextureFormat format, TextureDesc desc) override;

		TextureID createRT(const Size& size, uint32 multisampleCount) override;

		void release(TextureID handleID) override;

		Size getSize(TextureID handleID) override;

		TextureDesc getDesc(TextureID handleID) override;

		void clearRT(TextureID, const ColorF&) override
		{
			// [Siv3D ToDo]
		}

		void beginResize(TextureID) override
		{
			// [Siv3D ToDo]
		}

		bool endResizeRT(TextureID, const Size&, const uint32) override
		{
			// [Siv3D ToDo]
			return false;
		}

		bool endResizeBackBuffer(TextureID) override
		{
			// [Siv3D ToDo]
			return false;
		}


		void setPS(uint32 slot, TextureID handleID) override;

		bool fill(TextureID handleID, const ColorF& color, bool wait) override;

		bool fill(TextureID handleID, const void* src, uint32 stride, bool wait) override;
	};
}

# endif
