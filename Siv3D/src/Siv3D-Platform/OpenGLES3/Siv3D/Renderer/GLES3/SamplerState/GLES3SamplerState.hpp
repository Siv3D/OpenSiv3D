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

# pragma once
# include <Siv3D/Common.hpp>
# include <Siv3D/Common/OpenGL.hpp>
# include <Siv3D/SamplerState.hpp>
# include <Siv3D/HashTable.hpp>
# include <Siv3D/Optional.hpp>

namespace s3d
{
	class GLES3SamplerState
	{
	private:

		struct SamplerState_GL
		{
			SamplerState_GL()
			{
				::glGenSamplers(1, &m_sampler);
			}

			~SamplerState_GL()
			{
				if (m_sampler)
				{
					::glDeleteSamplers(1, &m_sampler);
				}
			}

			GLuint m_sampler = 0;
		};

		using SamplerStateList = HashTable<SamplerState, std::unique_ptr<SamplerState_GL>>;

		SamplerStateList m_states;

		std::array<SamplerState, SamplerState::MaxSamplerCount> m_currentVSStates;

		std::array<SamplerState, SamplerState::MaxSamplerCount> m_currentPSStates;

		SamplerStateList::iterator create(const SamplerState& state);

	public:

		GLES3SamplerState();

		void setVS(uint32 slot, const SamplerState& state);

		void setVS(uint32 slot, None_t);

		void setPS(uint32 slot, const SamplerState& state);

		void setPS(uint32 slot, None_t);
	};
}
