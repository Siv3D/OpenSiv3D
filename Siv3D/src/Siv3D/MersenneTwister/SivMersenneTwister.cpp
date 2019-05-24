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

# include <sstream>
# include <Siv3D/MersenneTwister.hpp>
# include <Siv3D/HardwareRNG.hpp>

namespace s3d
{
	MT11213b::MT11213b()
	{
		HardwareRNG rng;

		std::seed_seq seeds{ rng(), rng(), rng(), rng(), rng(), rng(), rng(), rng() };

		m_engine.seed(seeds);
	}

	MT11213b::MT11213b(const uint32 seed)
		: m_engine(seed)
	{
	
	}

	MT11213b::MT11213b(const std::array<uint32, 8>& seeds)
	{
		seed(seeds);
	}

	void MT11213b::seed(const uint32 seed)
	{
		m_engine.seed(seed);
	}

	void MT11213b::seed(const std::array<uint32, 8>& seeds)
	{
		std::seed_seq seq(std::begin(seeds), std::end(seeds));

		m_engine.seed(seq);
	}

	std::string MT11213b::serialize() const
	{
		std::ostringstream os;
		os << m_engine;
		return os.str();
	}

	void MT11213b::deserialize(const std::string& representation)
	{
		std::istringstream(representation) >> m_engine;
	}


	MT19937::MT19937()
	{
		HardwareRNG rng;

		std::seed_seq seeds{ rng(), rng(), rng(), rng(), rng(), rng(), rng(), rng() };

		m_engine.seed(seeds);
	}

	MT19937::MT19937(uint32 seed)
		: m_engine(seed)
	{
	
	}

	MT19937::MT19937(const std::array<uint32, 8>& seeds)
	{
		seed(seeds);
	}

	void MT19937::seed(const uint32 seed)
	{
		m_engine.seed(seed);
	}

	void MT19937::seed(const std::array<uint32, 8>& seeds)
	{
		std::seed_seq seq(std::begin(seeds), std::end(seeds));

		m_engine.seed(seq);
	}

	std::string MT19937::serialize() const
	{
		std::ostringstream os;
		os << m_engine;
		return os.str();
	}

	void MT19937::deserialize(const std::string& representation)
	{
		std::istringstream(representation) >> m_engine;
	}


	MT19937_64::MT19937_64()
	{
		uint64 seeds[8];

		HardwareRNG rng;

		for (auto& seed : seeds)
		{
			seed = (static_cast<uint64>(rng()) << 32) | rng();
		}

		std::seed_seq seq(std::begin(seeds), std::end(seeds));

		m_engine.seed(seq);
	}

	MT19937_64::MT19937_64(const uint64 seed)
		: m_engine(seed)
	{
	
	}

	MT19937_64::MT19937_64(const std::array<uint64, 8> & seeds)
	{
		seed(seeds);
	}

	void MT19937_64::seed(uint64 seed)
	{
		m_engine.seed(seed);
	}

	void MT19937_64::seed(const std::array<uint64, 8> & seeds)
	{
		std::seed_seq seq(std::begin(seeds), std::end(seeds));

		m_engine.seed(seq);
	}

	std::string MT19937_64::serialize() const
	{
		std::ostringstream os;
		os << m_engine;
		return os.str();
	}

	void MT19937_64::deserialize(const std::string& representation)
	{
		std::istringstream(representation) >> m_engine;
	}
}
