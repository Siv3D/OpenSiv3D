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

# include <Siv3D/Transformer3D.hpp>
# include <Siv3D/Graphics3D.hpp>

namespace s3d
{
	Transformer3D::Transformer3D(const Mat4x4& transform, const Target target)
		: m_oldTransform{ Graphics3D::GetLocalTransform() }
		, m_target{ target }
	{
		if (isPush())
		{
			Graphics3D::Internal::SetLocalTransform(transform * (*m_oldTransform));
		}
		else
		{
			Graphics3D::Internal::SetLocalTransform(transform);
		}
	}

	Transformer3D::Transformer3D(Transformer3D&& other) noexcept
		: m_oldTransform{ other.m_oldTransform }
		, m_target{ other.m_target }
	{
		other.clear();
	}

	Transformer3D::~Transformer3D()
	{
		if (m_oldTransform)
		{
			Graphics3D::Internal::SetLocalTransform(*m_oldTransform);
		}
	}

	void Transformer3D::clear() noexcept
	{
		m_oldTransform.reset();
	}

	bool Transformer3D::isPush() const noexcept
	{
		return (m_target == Target::PushLocal);
	}
}
