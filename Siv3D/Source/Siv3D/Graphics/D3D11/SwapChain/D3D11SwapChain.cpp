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
# include "D3D11SwapChain.hpp"
# include "../../../Siv3DEngine.hpp"
# include "../../../EngineUtility.hpp"
# include "../../../Window/IWindow.hpp"
# include "../../../Graphics/IGraphics.hpp"
# include <Siv3D/Monitor.hpp>

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
			if (HINSTANCE shcore = ::LoadLibraryW(S3DWSTR("shcore.dll")))
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
	}

	D3D11SwapChain::D3D11SwapChain(ID3D11Device* device, ID3D11DeviceContext* context, IDXGIAdapter* adapter)
		: m_device(device)
		, m_context(context)
		, m_adapter(adapter)
	{

	}

	D3D11SwapChain::~D3D11SwapChain()
	{
		if (m_swapChain && m_fullScreen)
		{
			m_swapChain->SetFullscreenState(false, nullptr);
		}
	}

	bool D3D11SwapChain::init()
	{
		m_hWnd = Siv3DEngine::GetWindow()->getHandle();

		m_desc.BufferDesc.Width						= m_actualSize.x;
		m_desc.BufferDesc.Height					= m_actualSize.y;
		m_desc.BufferDesc.RefreshRate.Numerator		= 0;
		m_desc.BufferDesc.RefreshRate.Denominator	= 0;
		m_desc.BufferDesc.Format					= DXGI_FORMAT_R8G8B8A8_UNORM;
		m_desc.BufferDesc.ScanlineOrdering			= DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		m_desc.BufferDesc.Scaling					= DXGI_MODE_SCALING_UNSPECIFIED;
		m_desc.SampleDesc.Count						= 1;
		m_desc.SampleDesc.Quality					= 0;
		m_desc.BufferUsage							= DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;
		m_desc.BufferCount							= 1;
		m_desc.OutputWindow							= m_hWnd;
		m_desc.Windowed								= true;
		m_desc.SwapEffect							= DXGI_SWAP_EFFECT_DISCARD;
		m_desc.Flags								= DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		if (!m_adapter)
		{
			return false;
		}

		ComPtr<IDXGIFactory> dxgiFactory;

		if (FAILED(m_adapter->GetParent(__uuidof(IDXGIFactory), &dxgiFactory)))
		{
			return false;
		}

		if (FAILED(dxgiFactory->CreateSwapChain(m_device, &m_desc, &m_swapChain)))
		{
			return false;
		}

		if (FAILED(dxgiFactory->MakeWindowAssociation(m_hWnd, DXGI_MWA_NO_WINDOW_CHANGES | DXGI_MWA_NO_ALT_ENTER)))
		{
			return false;
		}

		DWM_TIMING_INFO timingInfo = {};
		timingInfo.cbSize = sizeof(DWM_TIMING_INFO);
		::DwmGetCompositionTimingInfo(nullptr, &timingInfo);
		const double displayRefreshPeriodMillisec = detail::ToMillisec(timingInfo.qpcRefreshPeriod);
		m_currentDisplayRefreshRateHz = 1000.0 / displayRefreshPeriodMillisec;

		return true;
	}

	Array<DisplayOutput> D3D11SwapChain::enumOutputs()
	{
		Array<DisplayOutput> outputs;

		for(uint32 i = 0;; ++i)
		{
			ComPtr<IDXGIOutput> pOutput;
			
			if (SUCCEEDED(m_adapter->EnumOutputs(i, &pOutput)))
			{
				DisplayOutput output;

				{
					DXGI_OUTPUT_DESC desc;

					if (FAILED(pOutput->GetDesc(&desc)))
					{
						continue;
					}

					output.name = desc.DeviceName;
					output.displayRect.x = desc.DesktopCoordinates.left;
					output.displayRect.y = desc.DesktopCoordinates.top;
					output.displayRect.w = desc.DesktopCoordinates.right - desc.DesktopCoordinates.left;
					output.displayRect.h = desc.DesktopCoordinates.bottom - desc.DesktopCoordinates.top;
					output.rotation = desc.Rotation ? 0 : (static_cast<int32>(desc.Rotation) - 1) * 90;
				}

				Array<DXGI_MODE_DESC> displayModeList;

				uint32 numModes;

				if (SUCCEEDED(pOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, 0, &numModes, nullptr)))
				{
					displayModeList.resize(numModes);

					if (FAILED(pOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, 0, &numModes, displayModeList.data())))
					{
						continue;
					}
				}

				for (auto const& desc : displayModeList)
				{
					if (desc.Scaling == DXGI_MODE_SCALING_CENTERED)
					{
						continue;
					}

					DisplayMode mode;
					mode.size.set(desc.Width, desc.Height);
					mode.refreshRateHz = static_cast<double>(desc.RefreshRate.Numerator) / desc.RefreshRate.Denominator;
					output.displayModes.push_back(mode);
				}

				outputs.push_back(output);
			}
			else
			{
				break;
			}
		}

		const auto monitors = System::EnumActiveMonitors();

		for (auto& output : outputs)
		{
			for (const auto& monitor : monitors)
			{
				if (output.name == monitor.displayDeviceName)
				{
					output.name = monitor.name;
					break;
				}
			}
		}

		return outputs;
	}

	bool D3D11SwapChain::setFullScreen(const bool fullScreen, const Size& size, const size_t displayIndex, const double refreshRateHz)
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
				setFullScreen(false, size, displayIndex, refreshRateHz);
			}

			const auto bestMode = getBestFullScreenMode(size, displayIndex, refreshRateHz);

			if (!bestMode)
			{
				return false;
			}

			detail::SetHighDPI();

			if (!resizeTarget(bestMode->first))
			{
				return false;
			}

			m_targetSize = size;

			if (FAILED(m_swapChain->SetFullscreenState(true, bestMode->second.Get())))
			{
				return false;
			}

			m_fullScreen = true;

			m_currentDisplayRefreshRateHz = static_cast<double>(bestMode->first.RefreshRate.Denominator) / bestMode->first.RefreshRate.Numerator;
		
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

			DWM_TIMING_INFO timingInfo = {};
			timingInfo.cbSize = sizeof(DWM_TIMING_INFO);
			::DwmGetCompositionTimingInfo(nullptr, &timingInfo);
			const double displayRefreshPeriodMillisec = detail::ToMillisec(timingInfo.qpcRefreshPeriod);
			m_currentDisplayRefreshRateHz = 1000.0 / displayRefreshPeriodMillisec;
		}
		
		m_currentDisplayIndex = displayIndex;

		return true;
	}

	IDXGISwapChain* D3D11SwapChain::getSwapChain() const
	{
		return m_swapChain.Get();
	}

	bool D3D11SwapChain::present()
	{
		const bool vSync = !m_targetFrameRateHz.has_value() ||
			(m_targetFrameRateHz.value() >= 30 && std::abs(m_targetFrameRateHz.value() - m_currentDisplayRefreshRateHz) <= 3.0);

		if (vSync)
		{
			const HRESULT hr = m_swapChain->Present(1, 0);
			
			if (FAILED(hr))
			{
				return false;
			}
			else if (hr == DXGI_STATUS_OCCLUDED)
			{
				::Sleep(static_cast<int32>(1000 / m_currentDisplayRefreshRateHz * 0.9));
			}
			
			LARGE_INTEGER counter;
			::QueryPerformanceCounter(&counter);
			m_lastFlipTime = counter.QuadPart;
		}
		else
		{
			const double targetRefreshRateHz = m_targetFrameRateHz.value();
			const double targetRefreshPeriodMillisec = (1000.0f / targetRefreshRateHz);
			
			DWM_TIMING_INFO timingInfo = {};
			timingInfo.cbSize = sizeof(DWM_TIMING_INFO);
			::DwmGetCompositionTimingInfo(nullptr, &timingInfo);
			const double displayRefreshPeriodMillisec = detail::ToMillisec(timingInfo.qpcRefreshPeriod);
			
			LARGE_INTEGER counter;
			::QueryPerformanceCounter(&counter);
			//const double cputTime = detail::ToMillisec(counter.QuadPart - m_lastFlipTime);
			
			{
				m_context->Flush();
				
				if (vSync)
				{
					::DwmFlush();
				}
				
				double timeToSleepMillisec;
				
				do
				{
					::QueryPerformanceCounter(&counter);
					
					const double timeSinceFlipMillisec = detail::ToMillisec(counter.QuadPart - m_lastFlipTime);
					
					timeToSleepMillisec = (targetRefreshPeriodMillisec - timeSinceFlipMillisec);
					
					if (timeToSleepMillisec > 0.0)
					{
						::Sleep(static_cast<int32>(timeToSleepMillisec));
					}
				} while (timeToSleepMillisec > 0.0);
			}
			
			const HRESULT hr = m_swapChain->Present(0, 0);
			
			if (FAILED(hr))
			{
				return false;
			}
			
			m_lastFlipTime = counter.QuadPart;
		}

		return true;
	}

	void D3D11SwapChain::setTargetFrameRateHz(const Optional<double>& targetFrameRateHz)
	{
		m_targetFrameRateHz = targetFrameRateHz;
	}

	Optional<double> D3D11SwapChain::getTargetFrameRateHz() const
	{
		return m_targetFrameRateHz;
	}

	double D3D11SwapChain::getDisplayRefreshRateHz() const
	{
		return m_currentDisplayRefreshRateHz;
	}

	bool D3D11SwapChain::resizeTargetWindowed(const Size& size)
	{
		auto targetDesc		= m_desc.BufferDesc;
		targetDesc.Width	= size.x;
		targetDesc.Height	= size.y;
		m_targetSize = size;

		return resizeTarget(targetDesc);
	}

	bool D3D11SwapChain::resizeTarget(const DXGI_MODE_DESC& modeDesc)
	{
		const Size size(modeDesc.Width, modeDesc.Height);

		Siv3DEngine::GetGraphics()->beginResize();
		{
			if (FAILED(m_swapChain->ResizeTarget(&modeDesc)))
			{
				LOG_FAIL(L"❌ D3D11SwapChain: IDXGISwapChain::ResizeTarget() failed");

				return false;
			}
			
			if (FAILED(m_swapChain->ResizeBuffers(1, modeDesc.Width, modeDesc.Height, DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH)))
			{
				LOG_FAIL(L"❌ D3D11SwapChain: IDXGISwapChain::ResizeBuffers() failed");

				return false;
			}
		}
		
		if (!Siv3DEngine::GetGraphics()->endResize(size))
		{
			LOG_FAIL(L"❌ D3D11SwapChain: CGraphics_D3D11::endResize() failed");

			return false;
		}

		m_actualSize = size;

		LOG_DEBUG(L"✅ Changed resolution to {0}x{1}"_fmt(size.x, size.y));

		return true;
	}

	Optional<Size> D3D11SwapChain::shouldResize() const
	{
		if (m_actualSize == m_targetSize)
		{
			return none;
		}

		return m_targetSize;
	}

	Optional<std::pair<DXGI_MODE_DESC, ComPtr<IDXGIOutput>>> D3D11SwapChain::getBestFullScreenMode(const Size& size, const size_t displayIndex, const double refreshRateHz)
	{
		assert(!m_fullScreen);

		ComPtr<IDXGIOutput> pOutput;
		
		if (FAILED(m_adapter->EnumOutputs(static_cast<uint32>(displayIndex), &pOutput)))
		{
			if (FAILED(m_adapter->EnumOutputs(0, &pOutput)))
			{
				return none;
			}
		}

		Array<DXGI_MODE_DESC> displayModeList;

		uint32 numModes;

		if (SUCCEEDED(pOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, 0, &numModes, nullptr)))
		{
			displayModeList.resize(numModes);

			if (FAILED(pOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, 0, &numModes, displayModeList.data())))
			{
				return none;
			}
		}

		if (numModes == 0)
		{
			return none;
		}

		{
			DXGI_OUTPUT_DESC desc;

			if (SUCCEEDED(pOutput->GetDesc(&desc)))
			{
				Siv3DEngine::GetWindow()->setPos(
					Point(desc.DesktopCoordinates.left, desc.DesktopCoordinates.top));
			}
		}
    
		// サイズが一致するもののうちリフレッシュレートが一致するものを選択
		// サイズが一致するものが存在しなければ return false
		Optional<size_t> bestIndex;
		double bestDiff = 999999.9;

		for (size_t i = 0; i < displayModeList.size(); ++i)
		{
			const auto& desc = displayModeList[i];

			if (int32(desc.Width) == size.x && int32(desc.Height) == size.y)
			{
				const double rate = static_cast<double>(desc.RefreshRate.Numerator) / desc.RefreshRate.Denominator;
				const double diff = std::abs(refreshRateHz - rate) + (desc.Scaling == DXGI_MODE_SCALING_STRETCHED ? 0.0 : desc.Scaling == DXGI_MODE_SCALING_UNSPECIFIED ? 0.0001 : 0.0002);

				if (diff < bestDiff)
				{
					bestDiff = diff;
					bestIndex = i;
				}
			}
		}

		if (!bestIndex)
		{
			return none;
		}

		//Log << displayModeList[bestIndex].Width;
		//Log << displayModeList[bestIndex].Height;
		//Log << static_cast<double>(displayModeList[bestIndex].RefreshRate.Numerator) / displayModeList[bestIndex].RefreshRate.Denominator;
		//Log << (int32)displayModeList[bestIndex].Scaling;

		return std::pair<DXGI_MODE_DESC, ComPtr<IDXGIOutput>>(displayModeList[bestIndex.value()], std::move(pOutput));
	}
}

# endif
