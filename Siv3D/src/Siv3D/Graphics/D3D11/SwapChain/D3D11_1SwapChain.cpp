//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_WINDOWS)

# define  NOMINMAX
# define  STRICT
# define  _WIN32_WINNT _WIN32_WINNT_WINBLUE
# define  NTDDI_VERSION NTDDI_WINBLUE
# include <Windows.h>
# include <ShellScalingApi.h>
# include <dwmapi.h>
# undef _WIN32_WINNT
# undef	NTDDI_VERSION
# include "D3D11_1SwapChain.hpp"
# include "../../../Siv3DEngine.hpp"
# include "../../../EngineUtility.hpp"
# include "../../../Window/IWindow.hpp"
# include "../../../Graphics/IGraphics.hpp"
# include <Siv3D/Monitor.hpp>
# include <Siv3D/Math.hpp>
# include <Siv3D/Logger.hpp>

namespace s3d
{
	namespace detail
	{
		// 高 DPI ディスプレイで、フルスクリーン使用時に High DPI Aware を有効にしないと、
		// Windows の互換性マネージャーによって
		// HKEY_CURRENT_USER/Software/Microsoft/Windows NT/CurrentVersion/AppCompatFlags/Layers
		// に高 DPI が既定の設定として登録されてしまう。
		static void SetHighDPI()
		{
			if (HINSTANCE shcore =::LoadLibraryExW(L"shcore.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32))
			{
				decltype(SetProcessDpiAwareness)* p_SetProcessDpiAwareness = FunctionPointer(shcore, "SetProcessDpiAwareness");

				p_SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);

				::FreeLibrary(shcore);
			}
			else
			{
				::SetProcessDPIAware();
			}
		}

		inline double GetPerformanceFrequency()
		{
			::LARGE_INTEGER frequency;
			::QueryPerformanceFrequency(&frequency);
			return static_cast<double>(frequency.QuadPart);
		}

		inline double ToMillisec(const uint64 count)
		{
			static const double scale = 1'000 / detail::GetPerformanceFrequency();
			return count * scale;
		}

		inline double GetDisplayRefreshPeriodMillisec()
		{
			DWM_TIMING_INFO timingInfo = {};
			timingInfo.cbSize = sizeof(DWM_TIMING_INFO);
			::DwmGetCompositionTimingInfo(nullptr, &timingInfo);
			return detail::ToMillisec(timingInfo.qpcRefreshPeriod);
		}
	}

	D3D11_1SwapChain::D3D11_1SwapChain(const D3D11_1Device& device)
		: m_DXGIFactory(device.getDXGIFactory())
		, m_device(device.getDevice())
		, m_context(device.getContext())
		, m_adapter(device.getAdapter())
	{

	}

	D3D11_1SwapChain::~D3D11_1SwapChain()
	{
		if (m_swapChain)
		{
			m_swapChain->SetFullscreenState(false, nullptr);
		}
	}

	bool D3D11_1SwapChain::init()
	{
		HWND hWnd = Siv3DEngine::GetWindow()->getHandle();
		m_desc.BufferDesc.Width						= Window::DefaultClientSize.x;
		m_desc.BufferDesc.Height					= Window::DefaultClientSize.y;
		m_desc.BufferDesc.RefreshRate.Numerator		= 0;
		m_desc.BufferDesc.RefreshRate.Denominator	= 0;
		m_desc.BufferDesc.Format					= DXGI_FORMAT_R8G8B8A8_UNORM;
		m_desc.BufferDesc.ScanlineOrdering			= DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		m_desc.BufferDesc.Scaling					= DXGI_MODE_SCALING_UNSPECIFIED;
		m_desc.SampleDesc.Count						= 1;
		m_desc.SampleDesc.Quality					= 0;
		m_desc.BufferUsage							= DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;
		m_desc.BufferCount							= 1;
		m_desc.OutputWindow							= hWnd;
		m_desc.Windowed								= true;
		m_desc.SwapEffect							= DXGI_SWAP_EFFECT_DISCARD;
		m_desc.Flags								= DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		HRESULT hr = m_DXGIFactory->CreateSwapChain(m_device, &m_desc, &m_swapChain);

		if (FAILED(hr))
		{
			LOG_FAIL(U"❌ CreateSwapChain() failed");
			return false;
		}
		else
		{
			LOG_INFO(U"🆗 CreateSwapChain() succeeded");
		}

		m_currentDisplayRefreshRateHz = 1000.0 / detail::GetDisplayRefreshPeriodMillisec();
		LOG_INFO(U"ℹ️ currentDisplayRefresh: {} Hz"_fmt(m_currentDisplayRefreshRateHz));

		return true;
	}

	IDXGISwapChain* D3D11_1SwapChain::getSwapChain() const
	{
		return m_swapChain.Get();
	}

	double D3D11_1SwapChain::getDisplayRefreshRateHz() const
	{
		return m_currentDisplayRefreshRateHz;
	}

	void D3D11_1SwapChain::setTargetFrameRateHz(const Optional<double>& targetFrameRateHz)
	{
		m_targetFrameRateHz = targetFrameRateHz;
	}

	Optional<double> D3D11_1SwapChain::getTargetFrameRateHz() const
	{
		return m_targetFrameRateHz;
	}

	bool D3D11_1SwapChain::present()
	{
		const bool vSync = !m_targetFrameRateHz.has_value()
			|| ((30.0 <= m_targetFrameRateHz) && (Math::AbsDiff(m_targetFrameRateHz.value(), m_currentDisplayRefreshRateHz) <= 3.0));

		if (vSync)
		{
			const HRESULT hr = m_swapChain->Present(1, 0);

			if (hr == DXGI_STATUS_OCCLUDED)
			{
				::Sleep(static_cast<int32>(1000 / m_currentDisplayRefreshRateHz * 0.9));
			}
			else if (hr == DXGI_ERROR_DEVICE_RESET)
			{
				LOG_FAIL(U"❌ IDXGISwapChain::Present() failed (DXGI_ERROR_DEVICE_RESET)");
				return false;
			}
			else if (hr == DXGI_ERROR_DEVICE_REMOVED)
			{
				LOG_FAIL(U"❌ IDXGISwapChain::Present() failed (DXGI_ERROR_DEVICE_REMOVED)");
				return false;
			}

			LARGE_INTEGER counter;
			::QueryPerformanceCounter(&counter);
			m_lastPresentTime = counter.QuadPart;
		}
		else
		{
			const double targetRefreshRateHz = m_targetFrameRateHz.value();
			const double targetRefreshPeriodMillisec = (1000.0 / targetRefreshRateHz);
			const double displayRefreshPeriodMillisec = detail::GetDisplayRefreshPeriodMillisec();

			LARGE_INTEGER counter;
			::QueryPerformanceCounter(&counter);

			{
				m_context->Flush();

				double timeToSleepMillisec = 0.0;

				do
				{
					::QueryPerformanceCounter(&counter);
					const double timeSinceFlipMillisec = detail::ToMillisec(counter.QuadPart - m_lastPresentTime);

					timeToSleepMillisec = (targetRefreshPeriodMillisec - timeSinceFlipMillisec);

					if (timeToSleepMillisec > 0.0)
					{
						::Sleep(static_cast<int32>(timeToSleepMillisec));
					}
				} while (timeToSleepMillisec > 0.0);
			}

			const HRESULT hr = m_swapChain->Present(0, 0);

			if (hr == DXGI_STATUS_OCCLUDED)
			{
				::Sleep(static_cast<int32>(1000 / m_currentDisplayRefreshRateHz * 0.9));
			}
			else if (hr == DXGI_ERROR_DEVICE_RESET)
			{
				LOG_FAIL(U"❌ IDXGISwapChain::Present() failed (DXGI_ERROR_DEVICE_RESET)");
				return false;
			}
			else if (hr == DXGI_ERROR_DEVICE_REMOVED)
			{
				LOG_FAIL(U"❌ IDXGISwapChain::Present() failed (DXGI_ERROR_DEVICE_REMOVED)");
				return false;
			}

			m_lastPresentTime = counter.QuadPart;
		}

		return true;
	}

	bool D3D11_1SwapChain::setFullScreen(const bool fullScreen, const Size& size, const size_t displayIndex, const double refreshRateHz, const D3D11_1Device& device)
	{
		if (fullScreen == m_fullScreen
			&& size == m_targetSize
			&& displayIndex == m_currentDisplayIndex)
		{
			return true;
		}

		if (fullScreen)
		{
			// 一旦フルスクリーンを解除
			if (m_fullScreen)
			{
				setFullScreen(false, size, displayIndex, refreshRateHz, device);
			}

			const auto bestMode = device.getBestFullScreenMode(size, displayIndex, refreshRateHz);

			if (!bestMode)
			{
				return false;
			}

			const DXGI_MODE_DESC desc = std::get<0>(*bestMode);
			ComPtr<IDXGIOutput> pAdapter = std::get<1>(*bestMode);
			const size_t bestDisplayIndex = std::get<2>(*bestMode);
			const double bestRefreshRateHz = static_cast<double>(desc.RefreshRate.Numerator) / desc.RefreshRate.Denominator;

			LOG_INFO(U"ℹ️ closest Fullscreen mode found: displayIndex: {}, size: {} @{} Hz"_fmt(
					displayIndex, Size(desc.Width, desc.Height), bestRefreshRateHz));

			detail::SetHighDPI();

			if (FAILED(m_swapChain->SetFullscreenState(true, pAdapter.Get())))
			{
				return false;
			}
			
			if (!resizeTarget(desc))
			{
				return false;
			}

			m_targetSize = size;

			m_fullScreen = true;

			m_currentDisplayRefreshRateHz = bestRefreshRateHz;

			m_currentDisplayIndex = bestDisplayIndex;

			Siv3DEngine::GetWindow()->updateClientSize(true, size);
		}
		else
		{
			// フルスクリーンを解除
			if (m_fullScreen)
			{
				m_swapChain->SetFullscreenState(false, nullptr);
			}

			m_fullScreen = false;

			m_targetSize = size;

			Siv3DEngine::GetWindow()->updateClientSize(false, size);

			m_currentDisplayRefreshRateHz = 1000.0 / detail::GetDisplayRefreshPeriodMillisec();

			m_currentDisplayIndex = displayIndex;
		}

		return true;
	}

	bool D3D11_1SwapChain::resizeTargetWindowed(const Size& size)
	{
		auto targetDesc		= m_desc.BufferDesc;
		targetDesc.Width	= size.x;
		targetDesc.Height	= size.y;
		m_targetSize = size;

		return resizeTarget(targetDesc);
	}

	bool D3D11_1SwapChain::resizeTarget(const DXGI_MODE_DESC& modeDesc)
	{
		const Size size(modeDesc.Width, modeDesc.Height);

		Siv3DEngine::GetGraphics()->beginResize();
		{
			if (FAILED(m_swapChain->ResizeTarget(&modeDesc)))
			{
				LOG_FAIL(U"❌ D3D11SwapChain: IDXGISwapChain::ResizeTarget() failed");
				return false;
			}
			
			if (FAILED(m_swapChain->ResizeBuffers(m_desc.BufferCount, modeDesc.Width, modeDesc.Height, m_desc.BufferDesc.Format, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH)))
			{
				LOG_FAIL(U"❌ D3D11SwapChain: IDXGISwapChain::ResizeBuffers() failed");
				return false;
			}
		}
		
		if (!Siv3DEngine::GetGraphics()->endResize(size))
		{
			LOG_FAIL(U"❌ D3D11SwapChain: CGraphics_D3D11::endResize() failed");
			return false;
		}

		m_actualSize = size;

		LOG_DEBUG(U"✅ Changed resolution to {0}x{1}"_fmt(size.x, size.y));
		return true;
	}

	Optional<Size> D3D11_1SwapChain::pendingResize() const
	{
		if (m_actualSize == m_targetSize)
		{
			return none;
		}

		return m_targetSize;
	}
}

# endif
