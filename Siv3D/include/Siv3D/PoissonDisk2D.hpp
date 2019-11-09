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

# pragma once
# include "Fwd.hpp"
# include "PointVector.hpp"
# include "Optional.hpp"
# include "Array.hpp"
# include "Grid.hpp"

namespace s3d
{
	class PoissonDisk2D
	{
	private:

		static constexpr size_t k = 30;

		Size m_size = Size(0, 0);

		double m_r = 0.0;

		double m_cellSize = 0.0;

		Array<Vec2> m_activeList;

		Grid<Optional<Vec2>> m_grid;

		Array<Vec2> m_results;

		bool m_isComplete = true;

	public:

		PoissonDisk2D() = default;

		PoissonDisk2D(const PoissonDisk2D&) = default;

		PoissonDisk2D(PoissonDisk2D&&) = default;

		explicit PoissonDisk2D(const Size& size, double r, bool precalculate = true);

		explicit PoissonDisk2D(const Size& size, double r, const Vec2& initialPos, bool precalculate = true);

		PoissonDisk2D& operator =(const PoissonDisk2D&) = default;

		PoissonDisk2D& operator =(PoissonDisk2D&&) = default;

		[[nodiscard]] bool isComplete() const noexcept;

		size_t update(size_t iterations = 100);

		[[nodiscard]] const Array<Vec2>& getPoints() const noexcept;
	};
}
