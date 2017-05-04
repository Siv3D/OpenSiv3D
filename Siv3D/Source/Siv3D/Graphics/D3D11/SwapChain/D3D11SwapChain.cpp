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
			if (HINSTANCE shcore = ::LoadLibraryW(L"shcore.dll"))
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

		m_desc.BufferDesc.Width						= m_size.x;
		m_desc.BufferDesc.Height					= m_size.y;
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
			&& size == m_size
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

			// フルスクリーン化
			if (!setBestFullScreenMode(size, displayIndex, refreshRateHz))
			{
				return false;
			}
		}
		else
		{
			// フルスクリーンを解除
			m_swapChain->SetFullscreenState(false, nullptr);

			Siv3DEngine::GetGraphics()->beginResize();

			auto targetDesc = m_desc.BufferDesc;
			targetDesc.Width = size.x;
			targetDesc.Height = size.y;
			m_swapChain->ResizeTarget(&targetDesc);
			m_swapChain->ResizeBuffers(1, size.x, size.y, DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH);

			Siv3DEngine::GetGraphics()->endResize(size);

			DWM_TIMING_INFO timingInfo = {};
			timingInfo.cbSize = sizeof(DWM_TIMING_INFO);
			::DwmGetCompositionTimingInfo(nullptr, &timingInfo);
			const double displayRefreshPeriodMillisec = detail::ToMillisec(timingInfo.qpcRefreshPeriod);
			m_currentDisplayRefreshRateHz = 1000.0 / displayRefreshPeriodMillisec;
		}

		m_fullScreen = fullScreen;
		m_size = size;
		m_currentDisplayIndex = displayIndex;

		Siv3DEngine::GetWindow()->updateClientSize(m_fullScreen, size);

		return true;
	}

	IDXGISwapChain* D3D11SwapChain::getSwapChain() const
	{
		return m_swapChain.Get();
	}

	bool D3D11SwapChain::present()
	{
		const bool vSync = (m_targetFrameRateHz == 0.0);

		if (m_targetFrameRateHz)
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

				double timeToSleep;

				do
				{
					::QueryPerformanceCounter(&counter);

					const double timeSinceFlip = detail::ToMillisec(counter.QuadPart - m_lastFlipTime);

					timeToSleep = (targetRefreshPeriodMillisec - timeSinceFlip);

					if (timeToSleep > 0.0)
					{
						::Sleep(static_cast<int32>(timeToSleep));
					}
				} while (timeToSleep > 0.0);
			}

			const HRESULT hr = m_swapChain->Present(0, 0);

			if (FAILED(hr))
			{
				return false;
			}

			m_lastFlipTime = counter.QuadPart;
		}
		else
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

		return true;
	}

	void D3D11SwapChain::setVSyncEnabled(const bool enabled)
	{
		m_vSyncEnabled = enabled;
	}

	bool D3D11SwapChain::isVSyncEnabled() const
	{
		return m_vSyncEnabled;
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

	bool D3D11SwapChain::setBestFullScreenMode(const Size& size, const size_t displayIndex, const double refreshRateHz)
	{
		assert(!m_fullScreen);

		ComPtr<IDXGIOutput> pOutput;
		
		if (FAILED(m_adapter->EnumOutputs(static_cast<uint32>(displayIndex), &pOutput)))
		{
			if (FAILED(m_adapter->EnumOutputs(0, &pOutput)))
			{
				return false;
			}
		}

		Array<DXGI_MODE_DESC> displayModeList;

		uint32 numModes;

		if (SUCCEEDED(pOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, 0, &numModes, nullptr)))
		{
			displayModeList.resize(numModes);

			if (FAILED(pOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, 0, &numModes, displayModeList.data())))
			{
				return false;
			}
		}

		if (numModes == 0)
		{
			return false;
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
				const double diff = ::abs(refreshRateHz - rate) + (desc.Scaling == DXGI_MODE_SCALING_STRETCHED ? 0.0 : desc.Scaling == DXGI_MODE_SCALING_UNSPECIFIED ? 0.0001 : 0.0002);

				if (diff < bestDiff)
				{
					bestDiff = diff;
					bestIndex = i;
				}
			}
		}

		if (!bestIndex)
		{
			return false;
		}

		//Log << displayModeList[bestIndex].Width;
		//Log << displayModeList[bestIndex].Height;
		//Log << static_cast<double>(displayModeList[bestIndex].RefreshRate.Numerator) / displayModeList[bestIndex].RefreshRate.Denominator;
		//Log << (int32)displayModeList[bestIndex].Scaling;

		detail::SetHighDPI();

		Siv3DEngine::GetGraphics()->beginResize();

		const auto& bestDisplayMode = displayModeList[bestIndex.value()];

		m_swapChain->ResizeTarget(&bestDisplayMode);
		m_swapChain->ResizeBuffers(1, bestDisplayMode.Width, bestDisplayMode.Height, DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH);
		
		Siv3DEngine::GetGraphics()->endResize(size);
		
		m_swapChain->SetFullscreenState(true, pOutput.Get());

		m_currentDisplayRefreshRateHz = static_cast<double>(bestDisplayMode.RefreshRate.Denominator) / bestDisplayMode.RefreshRate.Numerator;

		return true;
	}
}

# endif
