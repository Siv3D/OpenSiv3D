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

namespace s3d
{
	class Transformer2D : Uncopyable
	{
	private:
		
		Optional<Mat3x2> m_oldMatrix;
		
		void clear()
		{
			m_oldMatrix.reset();
		}
		
	public:
		
		Transformer2D() = default;
		
		explicit Transformer2D(const Mat3x2& transform)
			: m_oldMatrix(Graphics2D::GetTransform())
		{
			Graphics2D::SetTransform(m_oldMatrix.value() * transform);
		}

		Transformer2D(Transformer2D&& transformer)
		{
			m_oldMatrix = transformer.m_oldMatrix;
			
			transformer.clear();
		}
		
		~Transformer2D()
		{
			m_oldMatrix.then(Graphics2D::SetTransform);
		}
		
		Transformer2D& operator =(Transformer2D&& transformer)
		{
			if (!m_oldMatrix && transformer.m_oldMatrix)
			{
				m_oldMatrix = transformer.m_oldMatrix;
			}
			
			transformer.clear();
			
			return *this;
		}
	};
}
