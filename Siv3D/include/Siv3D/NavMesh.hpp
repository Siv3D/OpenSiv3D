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
# include <memory>
# include "Fwd.hpp"
# include "Array.hpp"
# include "PointVector.hpp"
# include "Math.hpp"

namespace s3d
{
	struct NavMeshConfig
	{
		double cellSize = 1.0;

		double cellHeight = 0.2;

		double agentMaxSlope = Math::ToRadians(45);

		double agentHeight = 2.0;

		double agentMaxClimb = 0.9;

		double agentRadius = 0.25;

		[[nodiscard]] static constexpr NavMeshConfig Default()
		{
			return NavMeshConfig();
		}
	};

	class NavMesh
	{
	private:

		class NavMeshDetail;

		std::shared_ptr<NavMeshDetail> pImpl;

	public:

		NavMesh();

		~NavMesh();

		bool build(const Array<Float3>& vertices, const Array<uint16>& indices, const NavMeshConfig& config = NavMeshConfig::Default());

		bool build(const Array<Float3>& vertices, const Array<uint16>& indices, const Array<uint8>& areaIDs, const NavMeshConfig& config = NavMeshConfig::Default());

		[[nodiscard]] Array<Vec3> query(const Vec3& start, const Vec3& end) const;
	};
}
