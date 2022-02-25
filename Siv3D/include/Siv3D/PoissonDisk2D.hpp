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
# include "Common.hpp"
# include "PointVector.hpp"
# include "Array.hpp"
# include "Grid.hpp"
# include "Optional.hpp"
# include "PredefinedYesNo.hpp"
# include "RandomVec2.hpp"

namespace s3d
{
	class PoissonDisk2D
	{
	public:

		SIV3D_NODISCARD_CXX20
		PoissonDisk2D() = default;

		SIV3D_NODISCARD_CXX20
		explicit PoissonDisk2D(const Size& size, double r, Precompute precompute = Precompute::Yes);

		SIV3D_CONCEPT_URBG
		SIV3D_NODISCARD_CXX20
		explicit PoissonDisk2D(const Size& size, double r, URBG&& urbg, Precompute precompute = Precompute::Yes);

		SIV3D_NODISCARD_CXX20
		explicit PoissonDisk2D(const Size& size, double r, const Vec2& initialPos, Precompute precompute = Precompute::Yes);

		SIV3D_CONCEPT_URBG
		SIV3D_NODISCARD_CXX20
		explicit PoissonDisk2D(const Size& size, double r, const Vec2& initialPos, URBG&& urbg, Precompute precompute = Precompute::Yes);

		[[nodiscard]]
		bool isComplete() const noexcept;

		size_t update(size_t iterations = 100);

		SIV3D_CONCEPT_URBG
		size_t update(URBG&& urbg, size_t iterations = 100);

		[[nodiscard]]
		const Array<Vec2>& getPoints() const noexcept;

	private:

		static constexpr size_t k = 30;

		Size m_size = Size{ 0, 0 };

		double m_r = 0.0;

		double m_cellSize = 0.0;

		Array<Vec2> m_activeList;

		Grid<Optional<Vec2>> m_grid;

		Array<Vec2> m_results;
	};
}

# include "detail/PoissonDisk2D.ipp"
