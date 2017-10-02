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
	public:

		enum class Target
		{
			PushLocal,

			PushCamera,

			PushScreen,

			SetLocal,

			SetCamera,

			SetScreen,
		};

	private:

		Target m_target = Target::PushLocal;
		
		Optional<Mat3x2> m_oldGraphics2DMatrix;

		Optional<Mat3x2> m_oldCursorMatrix;
		
		void clear()
		{
			m_oldGraphics2DMatrix.reset();

			m_oldCursorMatrix.reset();
		}

		bool isPush() const
		{
			return (m_target == Target::PushLocal || m_target == Target::PushCamera || m_target == Target::PushScreen);
		}

		const Mat3x2& getGraphics2DTransform() const
		{
			return (m_target == Target::PushLocal || m_target == Target::SetLocal) ? Graphics2D::GetTransformLocal()
				: (m_target == Target::PushCamera || m_target == Target::SetCamera) ? Graphics2D::GetTransformCamera()
				: Graphics2D::GetTransformScreen();
		}

		const Mat3x2& getCursorTransform() const
		{
			return (m_target == Target::PushLocal || m_target == Target::SetLocal) ? Cursor::GetTransformLocal()
				: (m_target == Target::PushCamera || m_target == Target::SetCamera) ? Cursor::GetTransformCamera()
				: Cursor::GetTransformScreen();
		}

		void setGraphics2DTransform(const Mat3x2& transform) const
		{
			(m_target == Target::PushLocal || m_target == Target::SetLocal) ? Graphics2D::SetTransformLocal(transform)
				: (m_target == Target::PushCamera || m_target == Target::SetCamera) ? Graphics2D::SetTransformCamera(transform)
				: Graphics2D::SetTransformScreen(transform);
		}

		void setCursorTransform(const Mat3x2& transform) const
		{
			(m_target == Target::PushLocal || m_target == Target::SetLocal) ? Cursor::SetTransformLocal(transform)
				: (m_target == Target::PushCamera || m_target == Target::SetCamera) ? Cursor::SetTransformCamera(transform)
				: Cursor::SetTransformScreen(transform);
		}
		
	public:
		
		Transformer2D() = default;
		
		Transformer2D(const Mat3x2& transform, Target target)
			: Transformer2D(transform, false, target) {}
		
		explicit Transformer2D(const Mat3x2& transform, bool transformCursor = false, Target target = Target::PushLocal)
			: m_target(target)
			, m_oldGraphics2DMatrix(getGraphics2DTransform())
		{
			if (isPush())
			{
				setGraphics2DTransform(m_oldGraphics2DMatrix.value() * transform);

				if (transformCursor)
				{
					m_oldCursorMatrix = getCursorTransform();

					setCursorTransform(m_oldCursorMatrix.value() * transform);
				}
			}
			else
			{
				setGraphics2DTransform(transform);

				if (transformCursor)
				{
					m_oldCursorMatrix = getCursorTransform();

					setCursorTransform(transform);
				}
			}
		}

		Transformer2D(const Mat3x2& graphics2DTransform, const Mat3x2& cursorTransform, Target target = Target::PushLocal)
			: m_target(target)
			, m_oldGraphics2DMatrix(getGraphics2DTransform())
			, m_oldCursorMatrix(getCursorTransform())
		{
			if (isPush())
			{
				setGraphics2DTransform(m_oldGraphics2DMatrix.value() * graphics2DTransform);

				setCursorTransform(m_oldCursorMatrix.value() * cursorTransform);
			}
			else
			{
				setGraphics2DTransform(graphics2DTransform);

				setCursorTransform(cursorTransform);
			}
		}

		Transformer2D(Transformer2D&& transformer)
		{
			m_target = transformer.m_target;

			m_oldGraphics2DMatrix = transformer.m_oldGraphics2DMatrix;
			
			m_oldCursorMatrix = transformer.m_oldCursorMatrix;

			transformer.clear();
		}
		
		~Transformer2D()
		{
			if (m_oldGraphics2DMatrix)
			{
				setGraphics2DTransform(*m_oldGraphics2DMatrix);
			}

			if (m_oldCursorMatrix)
			{
				setCursorTransform(*m_oldCursorMatrix);
			}
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
