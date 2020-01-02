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

# include <Siv3D/Windows.hpp>
# include <dwmapi.h>
# include <dxgi1_5.h>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/EngineError.hpp>
# include <Siv3D/PointVector.hpp>
# include <Siv3D/Rectangle.hpp>
# include <Siv3D/Math.hpp>
# include <Siv3D/Window.hpp>
# include <Siv3D/DLL.hpp>
# include "D3D11SwapChain.hpp"

namespace s3d
{
	namespace detail
	{
		static double GetPerformanceFrequency()
		{
			::LARGE_INTEGER frequency;
			::QueryPerformanceFrequency(&frequency);
			return static_cast<double>(frequency.QuadPart);
		}

		static double ToMillisec(const uint64 count)
		{
			static const double scale = 1'000 / GetPerformanceFrequency();
			return count * scale;
		}

		static double GetDisplayRefreshPeriodMillisec()
		{
			DWM_TIMING_INFO timingInfo = {};
			timingInfo.cbSize = sizeof(DWM_TIMING_INFO);
			::DwmGetCompositionTimingInfo(nullptr, &timingInfo);
			return ToMillisec(timingInfo.qpcRefreshPeriod);
		}
	}

	D3D11SwapChain::D3D11SwapChain(const D3D11Device& device, HWND hWnd, const Size& clientSize)
		: m_hWnd(hWnd)
		, m_device(device.getDevice())
		, m_context(device.getContext())
		, m_useFlipModel(device.hasDXGI_1_4())
	{
		LOG_TRACE(U"D3D11SwapChain::D3D11SwapChain()");
		LOG_TRACE(U"Use flip model = {}"_fmt(m_useFlipModel));

		if (HMODULE user32 = DLL::LoadSystemLibrary(L"User32.dll"))
		{
			p_GetDpiForWindow = DLL::GetFunctionNoThrow(user32, "GetDpiForWindow");
		}

		m_desc.Width		= clientSize.x;
		m_desc.Height		= clientSize.y;
		m_desc.Format		= DXGI_FORMAT_R8G8B8A8_UNORM;
		m_desc.Stereo		= FALSE;
		m_desc.SampleDesc	= { 1, 0 };
		m_desc.BufferUsage	= DXGI_USAGE_RENDER_TARGET_OUTPUT;
		m_desc.BufferCount	= 2;
		m_desc.Scaling		= DXGI_SCALING_STRETCH;
		m_desc.SwapEffect	= m_useFlipModel ? DXGI_SWAP_EFFECT_FLIP_DISCARD : DXGI_SWAP_EFFECT_DISCARD;
		m_desc.AlphaMode	= DXGI_ALPHA_MODE_IGNORE;
		m_desc.Flags		= 0;
		
		LOG_TRACE(U"IDXGIFactory2::CreateSwapChainForHwnd()");
		if (FAILED(device.getDXGIFactory2()->CreateSwapChainForHwnd(
			m_device,
			hWnd,
			&m_desc,
			nullptr,
			nullptr,
			&m_swapChain1)))
		{
			throw EngineError(U"IDXGIFactory2::CreateSwapChainForHwnd() failed");
		}

		LOG_TRACE(U"IDXGIFactory1::MakeWindowAssociation()");
		if (FAILED(device.getDXGIFactory2()->MakeWindowAssociation(hWnd, DXGI_MWA_NO_WINDOW_CHANGES | DXGI_MWA_NO_ALT_ENTER)))
		{
			throw EngineError(U"IDXGIFactory2::MakeWindowAssociation() failed");
		}

		updateDisplayInfo();
		m_previousWindowBounds = Window::GetState().bounds;
	}

	D3D11SwapChain::~D3D11SwapChain()
	{

	}

	bool D3D11SwapChain::present()
	{
		if (const Rect windowBounds = Window::GetState().bounds;
			windowBounds != m_previousWindowBounds)
		{
			updateDisplayInfo();

			m_previousWindowBounds = windowBounds;
		}

		const bool vSync = !m_targetFrameRateHz.has_value()
			|| ((30.0 <= m_targetFrameRateHz) && (Math::AbsDiff(m_targetFrameRateHz.value(), m_currentDisplayRefreshRateHz) <= 3.0));

		return vSync ? presentVSync() : presentNonVSync();
	}

	void D3D11SwapChain::updateDisplayInfo()
	{
		double displayRefreshRateHz;
		std::tie(m_dpiScaling, displayRefreshRateHz) = checkCurrentDisplay();

		if (displayRefreshRateHz != m_currentDisplayRefreshRateHz)
		{
			m_currentDisplayRefreshRateHz = displayRefreshRateHz;
			LOG_INFO(U"Display refresh rate: {:.0f} Hz"_fmt(m_currentDisplayRefreshRateHz));
		}
	}

	double D3D11SwapChain::getDPIScaling() const noexcept
	{
		return m_dpiScaling;
	}

	double D3D11SwapChain::getDisplayRefreshRateHz() const noexcept
	{
		return m_currentDisplayRefreshRateHz;
	}

	void D3D11SwapChain::setTargetFrameRateHz(const Optional<double>& targetFrameRateHz)
	{
		m_targetFrameRateHz = targetFrameRateHz;
	}

	Optional<double> D3D11SwapChain::getTargetFrameRateHz() const
	{
		return m_targetFrameRateHz;
	}

	IDXGISwapChain1* D3D11SwapChain::getSwapChain1() const
	{
		return m_swapChain1.Get();
	}

	Optional<Rect> D3D11SwapChain::getFullscreenRect()
	{
		LOG_TRACE(U"D3D11SwapChain::getFullscreenRect()");

		ComPtr<IDXGIOutput> pOutput;
		if (FAILED(m_swapChain1->GetContainingOutput(&pOutput)))
		{
			return none;
		}

		DXGI_OUTPUT_DESC desc;
		if (FAILED(pOutput->GetDesc(&desc)))
		{
			return none;
		}

		return Rect(desc.DesktopCoordinates.left, desc.DesktopCoordinates.top,
			(desc.DesktopCoordinates.right - desc.DesktopCoordinates.left),
			(desc.DesktopCoordinates.bottom - desc.DesktopCoordinates.top));
	}

	bool D3D11SwapChain::presentVSync()
	{
		const HRESULT hr = m_swapChain1->Present(1, 0);

		if (hr == DXGI_STATUS_OCCLUDED)
		{
			::Sleep(static_cast<int32>(1000 / m_currentDisplayRefreshRateHz * 0.9));
		}
		else if (hr == DXGI_ERROR_DEVICE_RESET)
		{
			LOG_FAIL(U"❌ IDXGISwapChain1::Present() failed (DXGI_ERROR_DEVICE_RESET)");
			return false;
		}
		else if (hr == DXGI_ERROR_DEVICE_REMOVED)
		{
			LOG_FAIL(U"❌ IDXGISwapChain1::Present() failed (DXGI_ERROR_DEVICE_REMOVED)");
			return false;
		}

		LARGE_INTEGER counter;
		::QueryPerformanceCounter(&counter);
		m_lastPresentTime = counter.QuadPart;

		return true;
	}

	bool D3D11SwapChain::presentNonVSync()
	{
		const double targetRefreshRateHz = m_targetFrameRateHz.value();
		const double targetRefreshPeriodMillisec = (1000.0 / targetRefreshRateHz);
		const double displayRefreshPeriodMillisec = detail::GetDisplayRefreshPeriodMillisec();

		LARGE_INTEGER counter;
		::QueryPerformanceCounter(&counter);

		{
			m_context->Flush();

			double timeToSleepMillisec = 0.0;
			::timeBeginPeriod(1);

			do
			{
				::QueryPerformanceCounter(&counter);
				const double timeSinceFlipMillisec = detail::ToMillisec(counter.QuadPart - m_lastPresentTime);

				timeToSleepMillisec = (targetRefreshPeriodMillisec - timeSinceFlipMillisec);

				if (timeToSleepMillisec > 0.0)
				{
					::Sleep(static_cast<int32>(timeToSleepMillisec));
				}
			} while (timeToSleepMillisec > 0.5);

			::timeEndPeriod(1);
		}

		const HRESULT hr = m_swapChain1->Present(0, 0);

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

		return true;
	}

	std::pair<double, double> D3D11SwapChain::checkCurrentDisplay()
	{
		ComPtr<IDXGIOutput> pOutput;
		if (FAILED(m_swapChain1->GetContainingOutput(&pOutput)))
		{
			// fallback
			return{ 1.0, detail::GetDisplayRefreshPeriodMillisec() };
		}

		DXGI_OUTPUT_DESC desc;
		if (FAILED(pOutput->GetDesc(&desc)))
		{
			// fallback
			return{ 1.0, detail::GetDisplayRefreshPeriodMillisec() };
		}

		DEVMODE devMode = {};
		devMode.dmSize = sizeof(DEVMODE);
		::EnumDisplaySettingsW(desc.DeviceName, ENUM_CURRENT_SETTINGS, &devMode);

		const double scaling = p_GetDpiForWindow ? (p_GetDpiForWindow(m_hWnd) / 96.0) : 1.0;

		return{ scaling, devMode.dmDisplayFrequency };
	}
}
