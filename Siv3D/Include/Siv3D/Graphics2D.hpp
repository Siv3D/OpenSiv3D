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
# include "Fwd.hpp"
# include "BlendState.hpp"
# include "Rectangle.hpp"

namespace s3d
{
	/// <summary>
	/// 2D グラフィックス
	/// </summary>
	/// <remarks>
	/// 2D　グラフィックスに関連する機能を提供します。
	/// </remarks>
	namespace Graphics2D
	{
		/// <summary>
		/// 2D 描画のブレンドステートを設定します。
		/// </summary>
		/// <param name="blendState">
		/// ブレンドステート
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void SetBlendState(const BlendState& blendState);

		/// <summary>
		/// 現在の 2D 描画のブレンドステートを取得します。
		/// </summary>
		/// <returns>
		/// 現在の 2D 描画のブレンドステート
		/// </returns>
		BlendState GetBlendState();

		void SetViewport(const Optional<Rect>& viewport);

		Optional<Rect> GetViewport();
	}

	class RenderStateBlock2D
	{
	private:

		Optional<BlendState> m_oldBlendState;

		void clear()
		{
			m_oldBlendState.reset();
		}

	public:

		RenderStateBlock2D() = default;

		RenderStateBlock2D(const BlendState& blendState)
			: m_oldBlendState(Graphics2D::GetBlendState())
		{
			Graphics2D::SetBlendState(blendState);
		}

		RenderStateBlock2D(RenderStateBlock2D&& block)
		{
			m_oldBlendState = block.m_oldBlendState;

			block.clear();
		}

		~RenderStateBlock2D()
		{
			m_oldBlendState.then(Graphics2D::SetBlendState);
		}

		RenderStateBlock2D& operator =(RenderStateBlock2D&& block)
		{
			if (!m_oldBlendState && block.m_oldBlendState)
			{
				m_oldBlendState = block.m_oldBlendState;
			}

			block.clear();

			return *this;
		}
	};

	class ViewportBlock2D
	{
	private:

		Optional<Optional<Rect>> m_oldViewport;

		void clear()
		{
			m_oldViewport.reset();
		}

	public:
		
		ViewportBlock2D() = default;

		explicit ViewportBlock2D(const Optional<Rect>& viewport)
			: m_oldViewport(Graphics2D::GetViewport())
		{
			Graphics2D::SetViewport(viewport);
		}

		ViewportBlock2D(int32 x, int32 y, int32 w, int32 h)
			: ViewportBlock2D(Rect(x, y, w, h)) {}

		ViewportBlock2D(const Point& pos, int32 w, int32 h)
			: ViewportBlock2D(Rect(pos, w, h)) {}

		ViewportBlock2D(int32 x, int32 y, const Size& size)
			: ViewportBlock2D(Rect(x, y, size)) {}

		ViewportBlock2D(const Point& pos, const Size& size)
			: ViewportBlock2D(Rect(pos, size)) {}

		ViewportBlock2D(ViewportBlock2D&& block)
		{
			m_oldViewport = block.m_oldViewport;

			block.clear();
		}

		~ViewportBlock2D()
		{
			m_oldViewport.then(Graphics2D::SetViewport);
		}

		ViewportBlock2D& operator =(ViewportBlock2D&& block)
		{
			if (!m_oldViewport && block.m_oldViewport)
			{
				m_oldViewport = block.m_oldViewport;
			}

			block.clear();

			return *this;
		}
	};
}
