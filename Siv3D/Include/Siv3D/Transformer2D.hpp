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
# include "Mat3x2.hpp"
# include "Graphics2D.hpp"
# include "Cursor.hpp"

namespace s3d
{
	class Transformer2D : Uncopyable
	{
	private:
		
		Optional<Mat3x2> m_oldGraphics2DMatrix;

		Optional<Mat3x2> m_oldCursorMatrix;
		
		void clear()
		{
			m_oldGraphics2DMatrix.reset();

			m_oldCursorMatrix.reset();
		}
		
	public:
		
		Transformer2D() = default;
		
		explicit Transformer2D(const Mat3x2& transform, bool transformCursor = false)
			: m_oldGraphics2DMatrix(Graphics2D::GetTransform())
		{
			Graphics2D::SetTransform(m_oldGraphics2DMatrix.value() * transform);

			if (transformCursor)
			{
				m_oldCursorMatrix = Cursor::GetTransform();

				Cursor::SetTransform(m_oldCursorMatrix.value() * transform);
			}
		}

		Transformer2D(Transformer2D&& transformer)
		{
			m_oldGraphics2DMatrix = transformer.m_oldGraphics2DMatrix;
			
			m_oldCursorMatrix = transformer.m_oldCursorMatrix;

			transformer.clear();
		}
		
		~Transformer2D()
		{
			m_oldGraphics2DMatrix.then(Graphics2D::SetTransform);

			m_oldCursorMatrix.then(Cursor::SetTransform);
		}
		
		Transformer2D& operator =(Transformer2D&& transformer)
		{
			if (!m_oldGraphics2DMatrix && transformer.m_oldGraphics2DMatrix)
			{
				m_oldGraphics2DMatrix = transformer.m_oldGraphics2DMatrix;
			}

			if (!m_oldCursorMatrix && transformer.m_oldCursorMatrix)
			{
				m_oldCursorMatrix = transformer.m_oldCursorMatrix;
			}
			
			transformer.clear();
			
			return *this;
		}
	};
}
