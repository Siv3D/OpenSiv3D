//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

namespace s3d
{
	inline Transformer2D::Transformer2D(const Mat3x2& transform, const Target target)
		: Transformer2D{ transform, TransformCursor::No, target } {}

	inline Transformer2D::Transformer2D(const Mat3x2& transform, const TransformCursor transformCursor, const Target target)
		: m_target{ target }
		, m_oldTransform{ getGraphics2DTransform() }
	{
		if (isPush())
		{
			setGraphics2DTransform(transform * (*m_oldTransform));

			if (transformCursor)
			{
				m_oldCursorTransform = getCursorTransform();
				setCursorTransform(transform * (*m_oldCursorTransform));
			}
		}
		else
		{
			setGraphics2DTransform(transform);

			if (transformCursor)
			{
				m_oldCursorTransform = getCursorTransform();
				setCursorTransform(transform);
			}
		}
	}

	inline Transformer2D::Transformer2D(const Mat3x2& graphics2DTransform, const Mat3x2& cursorTransform, const Target target)
		: m_target{ target }
		, m_oldTransform{ getGraphics2DTransform() }
		, m_oldCursorTransform{ getCursorTransform() }
	{
		if (isPush())
		{
			setGraphics2DTransform(graphics2DTransform * (*m_oldTransform));
			setCursorTransform(cursorTransform * (*m_oldCursorTransform));
		}
		else
		{
			setGraphics2DTransform(graphics2DTransform);
			setCursorTransform(cursorTransform);
		}
	}

	inline Transformer2D::Transformer2D(Transformer2D&& other) noexcept
		: m_target{ other.m_target }
		, m_oldTransform{ other.m_oldTransform }
		, m_oldCursorTransform{ other.m_oldCursorTransform }
	{
		other.clear();
	}

	inline Transformer2D::~Transformer2D()
	{
		if (m_oldTransform)
		{
			setGraphics2DTransform(*m_oldTransform);
		}

		if (m_oldCursorTransform)
		{
			setCursorTransform(*m_oldCursorTransform);
		}
	}

	inline void Transformer2D::clear() noexcept
	{
		m_oldTransform.reset();
		m_oldCursorTransform.reset();
	}

	inline bool Transformer2D::isPush() const noexcept
	{
		return ((m_target == Target::PushLocal)
			|| (m_target == Target::PushCamera));
	}

	inline bool Transformer2D::isLocal() const noexcept
	{
		return ((m_target == Target::PushLocal)
			|| (m_target == Target::SetLocal));
	}

	inline bool Transformer2D::isCamera() const noexcept
	{
		return ((m_target == Target::PushCamera)
			|| (m_target == Target::SetCamera));
	}

	inline const Mat3x2& Transformer2D::getGraphics2DTransform() const noexcept
	{
		if (isLocal())
		{
			return Graphics2D::GetLocalTransform();
		}
		else
		{
			return Graphics2D::GetCameraTransform();
		}
	}

	inline const Mat3x2& Transformer2D::getCursorTransform() const noexcept
	{
		if (isLocal())
		{
			return Cursor::GetLocalTransform();
		}
		else
		{
			return Cursor::GetCameraTransform();
		}
	}

	inline void Transformer2D::setGraphics2DTransform(const Mat3x2& transform) const
	{
		if (isLocal())
		{
			Graphics2D::Internal::SetLocalTransform(transform);
		}
		else
		{
			Graphics2D::Internal::SetCameraTransform(transform);
		}
	}

	inline void Transformer2D::setCursorTransform(const Mat3x2& transform) const
	{
		if (isLocal())
		{
			Cursor::Internal::SetLocalTransform(transform);
		}
		else
		{
			Cursor::Internal::SetCameraTransform(transform);
		}
	}
}
