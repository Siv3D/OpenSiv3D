//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "NavMeshConfig.hpp"
# include "TriangleIndex.hpp"
# include "Polygon.hpp"

namespace s3d
{
	/// @brief ナビメッシュ
	class NavMesh
	{
	public:

		SIV3D_NODISCARD_CXX20
		NavMesh();

		~NavMesh();

		/// @brief Polygon から 2D のナビメッシュを構築します。
		/// @param polygon ナビメッシュ用の地形データ
		/// @param config ナビメッシュの設定
		/// @return ナビメッシュの構築に成功した場合 true, それ以外の場合は false
		bool build(const Polygon& polygon, const NavMeshConfig& config = NavMeshConfig::Default());

		/// @brief Polygon から 2D のナビメッシュを構築します。
		/// @param polygon ナビメッシュ用の地形データ
		/// @param areaIDs 各三角形のエリア ID, 指定しない場合のデフォルト値は 63
		/// @param config ナビメッシュの設定
		/// @return ナビメッシュの構築に成功した場合 true, それ以外の場合は false
		bool build(const Polygon& polygon, const Array<uint8>& areaIDs, const NavMeshConfig& config = NavMeshConfig::Default());

		/// @brief 頂点配列とインデックス配列から 2D のナビメッシュを構築します。
		/// @param vertices ナビメッシュ用の地形データの頂点配列
		/// @param indices ナビメッシュ用の地形データのインデックス配列
		/// @param config ナビメッシュの設定
		/// @return ナビメッシュの構築に成功した場合 true, それ以外の場合は false
		bool build(const Array<Float2>& vertices, const Array<TriangleIndex>& indices, const NavMeshConfig& config = NavMeshConfig::Default());

		/// @brief 頂点配列とインデックス配列から 2D のナビメッシュを構築します。
		/// @param vertices ナビメッシュ用の地形データの頂点配列
		/// @param indices ナビメッシュ用の地形データのインデックス配列
		/// @param areaIDs 各三角形のエリア ID, 指定しない場合のデフォルト値は 63
		/// @param config ナビメッシュの設定
		/// @return ナビメッシュの構築に成功した場合 true, それ以外の場合は false
		bool build(const Array<Float2>& vertices, const Array<TriangleIndex>& indices, const Array<uint8>& areaIDs, const NavMeshConfig& config = NavMeshConfig::Default());

		/// @brief 頂点配列とインデックス配列から 3D のナビメッシュを構築します。
		/// @param vertices ナビメッシュ用の地形データの頂点配列
		/// @param indices ナビメッシュ用の地形データのインデックス配列
		/// @param config ナビメッシュの設定
		/// @return ナビメッシュの構築に成功した場合 true, それ以外の場合は false
		bool build(const Array<Float3>& vertices, const Array<TriangleIndex>& indices, const NavMeshConfig& config = NavMeshConfig::Default());

		/// @brief 頂点配列とインデックス配列から 3D のナビメッシュを構築します。
		/// @param vertices ナビメッシュ用の地形データの頂点配列
		/// @param indices ナビメッシュ用の地形データのインデックス配列
		/// @param areaIDs 各三角形のエリア ID, 指定しない場合のデフォルト値は 63
		/// @param config ナビメッシュの設定
		/// @return ナビメッシュの構築に成功した場合 true, それ以外の場合は false
		bool build(const Array<Float3>& vertices, const Array<TriangleIndex>& indices, const Array<uint8>& areaIDs, const NavMeshConfig& config = NavMeshConfig::Default());

		/// @brief 
		/// @param start 
		/// @param end 
		/// @param areaCosts 
		/// @return 
		[[nodiscard]]
		Array<Vec2> query(const Vec2& start, const Vec2& end, const Array<std::pair<int, double>>& areaCosts = {}) const;

		/// @brief 
		/// @param start 
		/// @param end 
		/// @param areaCosts 
		/// @return 
		[[nodiscard]]
		Array<Vec3> query(const Vec3& start, const Vec3& end, const Array<std::pair<int, double>>& areaCosts = {}) const;
	
	private:

		class NavMeshDetail;

		std::shared_ptr<NavMeshDetail> pImpl;
	};
}
