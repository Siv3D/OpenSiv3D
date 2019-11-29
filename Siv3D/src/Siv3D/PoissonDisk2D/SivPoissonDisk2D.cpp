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

# include <Siv3D/PoissonDisk2D.hpp>
# include <Siv3D/Step.hpp>
# include <Siv3D/Random.hpp>
# include <Siv3D/RandomVec2.hpp>

namespace s3d
{
	PoissonDisk2D::PoissonDisk2D(const Size & size, const double r, const bool precalculate)
		: PoissonDisk2D(size, r, size / 2.0 + RandomVec2(r / Math::Sqrt2), precalculate)
	{
	
	}

	PoissonDisk2D::PoissonDisk2D(const Size & size, const double r, const Vec2 & initialPos, const bool precalculate)
		: m_size(size)
		, m_r(r)
		, m_cellSize(m_r / Math::Sqrt2)
		, m_grid(static_cast<int32>(m_size.x / m_cellSize) + 1, static_cast<int32>(m_size.y / m_cellSize) + 1)
		, m_isComplete(false)
	{
		const Vec2 pos = initialPos;
		m_grid[static_cast<int32>(pos.y / m_cellSize)][static_cast<int32>(pos.x / m_cellSize)] = pos;
		m_activeList << pos;
		m_results << pos;

		if (precalculate)
		{
			while (!isComplete())
			{
				update();
			}
		}
	}

	bool PoissonDisk2D::isComplete() const noexcept
	{
		return m_isComplete;
	}

	size_t PoissonDisk2D::update(const size_t iterations)
	{
		if (isComplete())
		{
			return 0;
		}

		for (size_t i = 0; i < iterations; ++i)
		{
			if (!m_activeList)
			{
				break;
			}

			const size_t randomIndex = Random(m_activeList.size() - 1);
			const Vec2 pos = m_activeList[randomIndex];
			const int32 cols = static_cast<int32>(m_grid.width());
			const int32 rows = static_cast<int32>(m_grid.height());
			const double rSq = (m_r * m_r);
			bool found = false;

			for (size_t n = 0; n < k; ++n)
			{
				const Vec2 sample = RandomVec2(Random(m_r, 2 * m_r)) + pos;
				const int32 x = static_cast<int32>(sample.x / m_cellSize);
				const int32 y = static_cast<int32>(sample.y / m_cellSize);

				if (!InRange(x, 0, cols - 1) || !InRange(y, 0, rows - 1) || m_grid[y][x])
				{
					continue;
				}

				bool exist = false;

				for (int32 dy : Range(-1, 1))
				{
					if (!InRange(y + dy, 0, rows - 1))
					{
						continue;
					}

					for (int32 dx : Range(-1, 1))
					{
						if (!InRange(x + dx, 0, cols - 1))
						{
							continue;
						}

						if (const Optional<Vec2>& neighbor = m_grid[y + dy][x + dx])
						{
							if (neighbor->distanceFromSq(sample) < rSq)
							{
								exist = true;
								break;
							}
						}
					}
				}

				if (!exist)
				{
					found = true;
					m_grid[y][x] = sample;
					m_activeList << sample;
					m_results << sample;
					break;
				}
			}

			if (!found)
			{
				m_activeList.remove_at(randomIndex);
			}
		}

		const size_t activeListSize = m_activeList.size();

		if (activeListSize == 0)
		{
			m_grid.release();
			m_activeList.release();
			m_isComplete = true;
		}

		return activeListSize;
	}

	const Array<Vec2>& PoissonDisk2D::getPoints() const noexcept
	{
		return m_results;
	}
}
