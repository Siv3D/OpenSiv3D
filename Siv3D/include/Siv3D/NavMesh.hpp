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
# include "NavMeshConfig.hpp"
# include "TriangleIndex.hpp"
# include "Polygon.hpp"

namespace s3d
{
	/// @brief ナビメッシュ
	class NavMesh
	{
	public:

		/// @brief デフォルトコンストラクタ
		SIV3D_NODISCARD_CXX20
		NavMesh();

		/// @brief Polygon から 2D のナビメッシュを構築します。
		/// @param polygon ナビメッシュ用の地形データ
		/// @param config ナビメッシュの設定
		SIV3D_NODISCARD_CXX20
		explicit NavMesh(const Polygon& polygon, const NavMeshConfig& config = {});

		/// @brief Polygon から 2D のナビメッシュを構築します。
		/// @param polygon ナビメッシュ用の地形データ
		/// @param areaIDs 各三角形のエリア ID, 指定しない場合のデフォルト値は 63
		/// @param config ナビメッシュの設定
		SIV3D_NODISCARD_CXX20
		NavMesh(const Polygon& polygon, const Array<uint8>& areaIDs, const NavMeshConfig& config = {});

		/// @brief 頂点配列とインデックス配列から 2D のナビメッシュを構築します。
		/// @param vertices ナビメッシュ用の地形データの頂点配列
		/// @param indices ナビメッシュ用の地形データのインデックス配列
		/// @param config ナビメッシュの設定	
		SIV3D_NODISCARD_CXX20
		NavMesh(const Array<Float2>& vertices, const Array<TriangleIndex>& indices, const NavMeshConfig& config = {});

		/// @brief 頂点配列とインデックス配列から 2D のナビメッシュを構築します。
		/// @param vertices ナビメッシュ用の地形データの頂点配列
		/// @param indices ナビメッシュ用の地形データのインデックス配列
		/// @param areaIDs 各三角形のエリア ID, 指定しない場合のデフォルト値は 63
		/// @param config ナビメッシュの設定	
		SIV3D_NODISCARD_CXX20
		NavMesh(const Array<Float2>& vertices, const Array<TriangleIndex>& indices, const Array<uint8>& areaIDs, const NavMeshConfig& config = {});

		/// @brief 頂点配列とインデックス配列から 3D のナビメッシュを構築します。
		/// @param vertices ナビメッシュ用の地形データの頂点配列
		/// @param indices ナビメッシュ用の地形データのインデックス配列
		/// @param config ナビメッシュの設定
		SIV3D_NODISCARD_CXX20
		NavMesh(const Array<Float3>& vertices, const Array<TriangleIndex>& indices, const NavMeshConfig& config = {});

		/// @brief 頂点配列とインデックス配列から 3D のナビメッシュを構築します。
		/// @param vertices ナビメッシュ用の地形データの頂点配列
		/// @param indices ナビメッシュ用の地形データのインデックス配列
		/// @param areaIDs 各三角形のエリア ID, 指定しない場合のデフォルト値は 63
		/// @param config ナビメッシュの設定	
		SIV3D_NODISCARD_CXX20
		NavMesh(const Array<Float3>& vertices, const Array<TriangleIndex>& indices, const Array<uint8>& areaIDs, const NavMeshConfig& config = {});

		/// @brief デストラクタ
		~NavMesh();

		/// @brief ナビメッシュが構築されているかを返します。
		/// @return ナビメッシュが構築されている場合 true, それ以外の場合は false
		[[nodiscard]]
		bool isValid() const noexcept;

		/// @brief ナビメッシュが構築されているかを返します。
		/// @remark `isVlaid()` と同じです。
		/// @return ナビメッシュが構築されている場合 true, それ以外の場合は false
		[[nodiscard]]
		explicit operator bool() const noexcept;

		/// @brief Polygon から 2D のナビメッシュを構築します。
		/// @param polygon ナビメッシュ用の地形データ
		/// @param config ナビメッシュの設定
		/// @return ナビメッシュの構築に成功した場合 true, それ以外の場合は false
		bool build(const Polygon& polygon, const NavMeshConfig& config = {});

		/// @brief Polygon から 2D のナビメッシュを構築します。
		/// @param polygon ナビメッシュ用の地形データ
		/// @param areaIDs 各三角形のエリア ID, 指定しない場合のデフォルト値は 63
		/// @param config ナビメッシュの設定
		/// @return ナビメッシュの構築に成功した場合 true, それ以外の場合は false
		bool build(const Polygon& polygon, const Array<uint8>& areaIDs, const NavMeshConfig& config = {});

		/// @brief 頂点配列とインデックス配列から 2D のナビメッシュを構築します。
		/// @param vertices ナビメッシュ用の地形データの頂点配列
		/// @param indices ナビメッシュ用の地形データのインデックス配列
		/// @param config ナビメッシュの設定
		/// @return ナビメッシュの構築に成功した場合 true, それ以外の場合は false
		bool build(const Array<Float2>& vertices, const Array<TriangleIndex>& indices, const NavMeshConfig& config = {});

		/// @brief 頂点配列とインデックス配列から 2D のナビメッシュを構築します。
		/// @param vertices ナビメッシュ用の地形データの頂点配列
		/// @param indices ナビメッシュ用の地形データのインデックス配列
		/// @param areaIDs 各三角形のエリア ID, 指定しない場合のデフォルト値は 63
		/// @param config ナビメッシュの設定
		/// @return ナビメッシュの構築に成功した場合 true, それ以外の場合は false
		bool build(const Array<Float2>& vertices, const Array<TriangleIndex>& indices, const Array<uint8>& areaIDs, const NavMeshConfig& config = {});

		/// @brief 頂点配列とインデックス配列から 3D のナビメッシュを構築します。
		/// @param vertices ナビメッシュ用の地形データの頂点配列
		/// @param indices ナビメッシュ用の地形データのインデックス配列
		/// @param config ナビメッシュの設定
		/// @return ナビメッシュの構築に成功した場合 true, それ以外の場合は false
		bool build(const Array<Float3>& vertices, const Array<TriangleIndex>& indices, const NavMeshConfig& config = {});

		/// @brief 頂点配列とインデックス配列から 3D のナビメッシュを構築します。
		/// @param vertices ナビメッシュ用の地形データの頂点配列
		/// @param indices ナビメッシュ用の地形データのインデックス配列
		/// @param areaIDs 各三角形のエリア ID, 指定しない場合のデフォルト値は 63
		/// @param config ナビメッシュの設定
		/// @return ナビメッシュの構築に成功した場合 true, それ以外の場合は false
		bool build(const Array<Float3>& vertices, const Array<TriangleIndex>& indices, const Array<uint8>& areaIDs, const NavMeshConfig& config = {});

		/// @brief 目的地もしくは目的地の近くまで到達できるナビメッシュ上の経路を計算します。
		/// @param start 出発地点の座標
		/// @param end 目的地の座標
		/// @param areaCosts エリアのコスト
		/// @return ナビメッシュ上の経路
		[[nodiscard]]
		Array<Vec2> query(const Vec2& start, const Vec2& end, const Array<std::pair<int32, double>>& areaCosts = {}) const;

		/// @brief 目的地もしくは目的地の近くまで到達できるナビメッシュ上の経路を計算します。
		/// @param start 出発地点の座標
		/// @param end 目的地の座標
		/// @param dst 経路の格納先
		/// @param areaCosts エリアのコスト
		void query(const Vec2& start, const Vec2& end, Array<Vec2>& dst, const Array<std::pair<int32, double>>& areaCosts = {}) const;

		/// @brief 目的地もしくは目的地の近くまで到達できるナビメッシュ上の経路を計算します。
		/// @param start 出発地点の座標
		/// @param end 目的地の座標
		/// @param areaCosts エリアのコスト
		/// @return ナビメッシュ上の経路
		[[nodiscard]]
		Array<Vec3> query(const Vec3& start, const Vec3& end, const Array<std::pair<int32, double>>& areaCosts = {}) const;

		/// @brief 目的地もしくは目的地の近くまで到達できるナビメッシュ上の経路を計算します。
		/// @param start 出発地点の座標
		/// @param end 目的地の座標
		/// @param dst 経路の格納先
		/// @param areaCosts エリアのコスト
		void query(const Vec3& start, const Vec3& end, Array<Vec3>& dst, const Array<std::pair<int32, double>>& areaCosts = {}) const;

	private:

		class NavMeshDetail;

		std::shared_ptr<NavMeshDetail> pImpl;
	};
}
