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
	inline PoissonDisk2D::PoissonDisk2D(const Size& size, const double r, const Precompute precompute)
		: PoissonDisk2D{ size, r, ((size / 2.0) + RandomVec2(r / Math::Sqrt2)), precompute } {}

	SIV3D_CONCEPT_URBG_
	inline PoissonDisk2D::PoissonDisk2D(const Size& size, const double r, URBG&& urbg, const Precompute precompute)
		: PoissonDisk2D{ size, r, ((size / 2.0) + RandomVec2(r / Math::Sqrt2), std::forward<URBG>(urbg)), std::forward<URBG>(urbg), precompute } {}

	inline PoissonDisk2D::PoissonDisk2D(const Size& size, const double r, const Vec2& initialPos, const Precompute precompute)
		: PoissonDisk2D{ size, r, initialPos, GetDefaultRNG(), precompute } {}

	SIV3D_CONCEPT_URBG_
	inline PoissonDisk2D::PoissonDisk2D(const Size& size, const double r, const Vec2& initialPos, URBG&& urbg, const Precompute precompute)
		: m_size{ size }
		, m_r{ r }
		, m_cellSize{ (m_r / Math::Sqrt2) }
		, m_grid((static_cast<int32>(m_size.x / m_cellSize) + 1), (static_cast<int32>(m_size.y / m_cellSize) + 1))
	{
		const Vec2 pos = initialPos;
		const int32 indexY = (static_cast<int32>(pos.y / m_cellSize));
		const int32 indexX = (static_cast<int32>(pos.x / m_cellSize));

		if (not m_grid.inBounds(indexY, indexX))
		{
			return;
		}

		m_grid[indexY][indexX] = pos;
		m_activeList << pos;
		m_results << pos;

		if (precompute)
		{
			while (not isComplete())
			{
				update(std::forward<URBG>(urbg), Largest<size_t>);
			}
		}
	}

	inline bool PoissonDisk2D::isComplete() const noexcept
	{
		return m_activeList.isEmpty();
	}

	inline size_t PoissonDisk2D::update(const size_t iterations)
	{
		return update(GetDefaultRNG(), iterations);
	}

	SIV3D_CONCEPT_URBG_
	inline size_t PoissonDisk2D::update(URBG&& urbg, const size_t iterations)
	{
		if (isComplete())
		{
			return 0;
		}

		for (size_t i = 0; i < iterations; ++i)
		{
			// Reference:
			// - Fast Poisson Disk Sampling in Arbitrary Dimensions
			//   https://www.cs.ubc.ca/~rbridson/docs/bridson-siggraph07-poissondisk.pdf

			if (not m_activeList)
			{
				break;
			}

			const size_t randomIndex = Random((m_activeList.size() - 1), std::forward<URBG>(urbg));
			const Vec2 pos		= m_activeList[randomIndex];
			const int32 cols	= static_cast<int32>(m_grid.width());
			const int32 rows	= static_cast<int32>(m_grid.height());
			const double rSq	= (m_r * m_r);
			bool found			= false;

			for (size_t n = 0; n < k; ++n)
			{
				const Vec2 sample = (RandomVec2(Random(m_r, 2 * m_r, std::forward<URBG>(urbg)), std::forward<URBG>(urbg)) + pos);
				const int32 x = static_cast<int32>(sample.x / m_cellSize);
				const int32 y = static_cast<int32>(sample.y / m_cellSize);

				if ((not InRange(x, 0, cols - 1))
					|| (not InRange(y, 0, rows - 1))
					|| m_grid[y][x])
				{
					continue;
				}

				bool exist = false;

				for (int32 dy : Range(-1, 1))
				{
					if (not InRange((y + dy), 0, (rows - 1)))
					{
						continue;
					}

					for (int32 dx : Range(-1, 1))
					{
						if (not InRange((x + dx), 0, (cols - 1)))
						{
							continue;
						}

						if (const Optional<Vec2>& neighbor = m_grid[(y + dy)][(x + dx)])
						{
							if (neighbor->distanceFromSq(sample) < rSq)
							{
								exist = true;
								break;
							}
						}
					}
				}

				if (not exist)
				{
					found = true;
					m_grid[y][x] = sample;
					m_activeList << sample;
					m_results << sample;
					break;
				}
			}

			if (not found)
			{
				m_activeList.remove_at(randomIndex);
			}
		}

		const size_t activeListSize = m_activeList.size();

		if (activeListSize == 0)
		{
			m_grid.release();
			m_activeList.release();
		}

		return activeListSize;
	}

	inline const Array<Vec2>& PoissonDisk2D::getPoints() const noexcept
	{
		return m_results;
	}
}
