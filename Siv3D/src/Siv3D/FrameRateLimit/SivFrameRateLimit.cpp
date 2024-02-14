//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "CFrameRateLimit.hpp"
# include "Siv3D/Graphics.hpp"
# include "Siv3D/Error.hpp"
# include "Siv3D/Duration.hpp"

namespace s3d
{
	void CFrameRateLimit::update()
	{
		if (Graphics::IsVSyncEnabled())
		{
			// VSync が有効の場合はフレームレート制限を無視
			return;
		}

		if (not m_limiter)
		{
			// フレームレート制限が無効の場合は何もしない
			return;
		}

		m_limiter->doSleep();
	}

	void CFrameRateLimit::setTargetFrameRate(const Optional<double>& fps)
	{
		if (not fps)
		{
			// フレームレート制限を無効化
			m_limiter.reset();
			return;
		}

		if (m_limiter)
		{
			// 既にフレームレート制限が有効の場合は目標フレームレートを設定
			m_limiter->setTargetFrameRate(*fps);
		}
		else
		{
			// フレームレート制限を有効化
			m_limiter = std::make_unique<Limiter>(*fps);
		}
	}

	Optional<double> CFrameRateLimit::getTargetFrameRate() const
	{
		if (m_limiter)
		{
			return m_limiter->getTargetFrameRate();
		}
		else
		{
			return none;
		}
	}

	CFrameRateLimit::Limiter::Limiter(double fps)
		: m_fps(fps)
		, m_oneFrameDuration(FPSToOneFrameDuration(fps))
		, m_sleepUntil(clock_type::now())
	{
	}

	void CFrameRateLimit::Limiter::doSleep()
	{
		const auto now = clock_type::now();
		const auto sleepUntil = Max(m_sleepUntil + m_oneFrameDuration, now);

		if (now < sleepUntil)
		{
			std::this_thread::sleep_until(sleepUntil);
		}

		m_sleepUntil = sleepUntil;
	}

	void CFrameRateLimit::Limiter::setTargetFrameRate(double fps)
	{
		m_fps = fps;
		m_oneFrameDuration = FPSToOneFrameDuration(fps);

		// setTargetFrameRate が毎フレーム呼び出された場合に sleep 時間に誤差が生じないよう,
		// m_sleepUntil はここでは更新しない
	}

	CFrameRateLimit::clock_type::duration CFrameRateLimit::Limiter::FPSToOneFrameDuration(double fps)
	{
		if (fps <= 0.0)
		{
			throw Error{ U"FrameRateLimit::Limiter::FPSToOneFrameDuration(): Invalid fps" };
		}

		return DurationCast<clock_type::duration>(OneSecond / fps);
	}
}
