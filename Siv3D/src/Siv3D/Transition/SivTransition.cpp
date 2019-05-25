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

# include <Siv3D/Transition.hpp>

namespace s3d
{
	void Transition::update(const bool in, const double deltaSec)
	{
		if (in)
		{
			if (m_inDuration <= 0.0)
			{
				m_value = 1.0;
				return;
			}

			m_value = std::min(m_value + (deltaSec / m_inDuration), 1.0);
		}
		else
		{
			if (m_outDuration <= 0.0)
			{
				m_value = 0.0;
				return;
			}

			m_value = std::max(m_value - (deltaSec / m_outDuration), 0.0);
		}
	}
}
