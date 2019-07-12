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

# include <Siv3D/Transformer2D.hpp>
# include <Siv3D/Graphics2D.hpp>
# include <Siv3D/Cursor.hpp>

namespace s3d
{
	Transformer2D::Transformer2D(const Mat3x2& transform, const Target target)
		: Transformer2D(transform, false, target)
	{

	}

	Transformer2D::Transformer2D(const Mat3x2& transform, const bool transformCursor, const Target target)
		: m_target(target)
		, m_oldTransform(getGraphics2DTransform())
	{
		if (isPush())
		{
			setGraphics2DTransform(transform * m_oldTransform.value());

			if (transformCursor)
			{
				m_oldCursorTransform = getCursorTransform();
				setCursorTransform(transform * m_oldCursorTransform.value());
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

	Transformer2D::Transformer2D(const Mat3x2& graphics2DTransform, const Mat3x2& cursorTransform, const Target target)
		: m_target(target)
		, m_oldTransform(getGraphics2DTransform())
		, m_oldCursorTransform(getCursorTransform())
	{
		if (isPush())
		{
			setGraphics2DTransform(graphics2DTransform * m_oldTransform.value());
			setCursorTransform(cursorTransform * m_oldCursorTransform.value());
		}
		else
		{
			setGraphics2DTransform(graphics2DTransform);
			setCursorTransform(cursorTransform);
		}
	}

	Transformer2D::Transformer2D(Transformer2D&& other)
		: m_target(other.m_target)
		, m_oldTransform(other.m_oldTransform)
		, m_oldCursorTransform(other.m_oldCursorTransform)
	{
		other.clear();
	}

	Transformer2D::~Transformer2D()
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

	Transformer2D& Transformer2D::operator =(Transformer2D&& other)
	{
		if (!m_oldTransform && other.m_oldTransform)
		{
			m_oldTransform = other.m_oldTransform;
		}

		if (!m_oldCursorTransform && other.m_oldCursorTransform)
		{
			m_oldCursorTransform = other.m_oldCursorTransform;
		}

		other.clear();
		return *this;
	}

	void Transformer2D::clear() noexcept
	{
		m_oldTransform.reset();
		m_oldCursorTransform.reset();
	}

	bool Transformer2D::isPush() const noexcept
	{
		return (m_target == Target::PushLocal || m_target == Target::PushCamera);
	}

	bool Transformer2D::isLocal() const noexcept
	{
		return (m_target == Target::PushLocal || m_target == Target::SetLocal);
	}

	bool Transformer2D::isCamera() const noexcept
	{
		return (m_target == Target::PushCamera || m_target == Target::SetCamera);
	}

	const Mat3x2& Transformer2D::getGraphics2DTransform() const
	{
		return (isLocal()) ? Graphics2D::GetLocalTransform() : Graphics2D::GetCameraTransform();
	}

	const Mat3x2& Transformer2D::getCursorTransform() const
	{
		return (isLocal()) ? Cursor::GetLocalTransform() : Cursor::GetCameraTransform();
	}

	void Transformer2D::setGraphics2DTransform(const Mat3x2 & transform) const
	{
		(isLocal()) ? Graphics2D::SetLocalTransform(transform) : Graphics2D::SetCameraTransform(transform);
	}

	void Transformer2D::setCursorTransform(const Mat3x2 & transform) const
	{
		(isLocal()) ? Cursor::SetLocalTransform(transform) : Cursor::SetCameraTransform(transform);
	}
}
