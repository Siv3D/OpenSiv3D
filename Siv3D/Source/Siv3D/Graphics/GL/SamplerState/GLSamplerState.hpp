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

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

# include <cfloat>
# include <Siv3D/HashMap.hpp>
# include <Siv3D/SamplerState.hpp>

namespace s3d
{
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
		
		uint32 m_sampler = 0;
	};
	
	static const SamplerState NullSamplerState(TextureAddressMode::Repeat,
										TextureAddressMode::Repeat,
										TextureAddressMode::Repeat,
										TextureFilter::Linear,
										TextureFilter::Linear,
										TextureFilter::Linear,
										0,
										-1,
										Float4(FLT_MIN, FLT_MIN, FLT_MIN, FLT_MIN));
	
	class GLSamplerState
	{
	private:
		
		using SamplerStateList = HashMap<SamplerState, std::unique_ptr<SamplerState_GL>>;
		
		SamplerStateList m_states;
		
		std::array<SamplerState, SamplerState::MaxSamplerCount> m_currentStates;
		
		SamplerStateList::iterator create(const SamplerState& state);

	public:
		
		GLSamplerState();

		void set(uint32 slot, const SamplerState& state);
	};
}

# endif
