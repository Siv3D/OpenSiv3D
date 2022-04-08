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
# include "Array.hpp"
# include "YesNo.hpp"
# include "PredefinedYesNo.hpp"
# include <ThirdParty/nanoflann/nanoflann.hpp>

namespace s3d
{
	namespace detail
	{
		template <class DatasetAdapter>
		class KDAdapter
		{
		public:

			using point_type	= typename DatasetAdapter::point_type;

			using element_type	= typename DatasetAdapter::element_type;

			using dataset_type	= typename DatasetAdapter::dataset_type;

			static constexpr int32 Dimensions = DatasetAdapter::Dimensions;

			explicit KDAdapter(const dataset_type& dataset);

			[[nodiscard]]
			size_t kdtree_get_point_count() const;

			[[nodiscard]]
			element_type kdtree_get_pt(const size_t index, const size_t dim) const;

			template <class BBOX>
			bool kdtree_get_bbox(BBOX&) const;

			[[nodiscard]]
			static const element_type* GetPointer(const point_type& point);

		private:

			static_assert(sizeof(point_type) == sizeof(element_type) * Dimensions);

			const dataset_type& m_dataset;
		};
	}

	/// @brief kd-tree
	/// @tparam DatasetAdapter kd-tree 用のアダプタ型
	template <class DatasetAdapter>
	class KDTree
	{
	public:

		using adapter_type	= detail::KDAdapter<DatasetAdapter>;

		using point_type	= typename adapter_type::point_type;

		using element_type	= typename adapter_type::element_type;

		using dataset_type	= typename adapter_type::dataset_type;

		static constexpr int32 Dimensions = adapter_type::Dimensions;

		/// @brief デフォルトコンストラクタ
		KDTree() = default;

		/// @brief kd-tree を構築します。
		/// @param dataset データセット
		explicit KDTree(const dataset_type& dataset);

		/// @brief ツリーを再構築します。
		void rebuildIndex();

		/// @brief kd-tree を消去し、メモリから解放します。
		void release();

		/// @brief kd-tree が消費しているメモリのサイズ（バイト）を返します。
		/// @return kd-tree が消費しているメモリのサイズ（バイト）
		[[nodiscard]]
		size_t usedMemory() const;

		/// @brief 指定した座標から最も近い k 個の要素を検索して返します。
		/// @param k 検索する個数
		/// @param point 座標
		/// @return 見つかった要素一覧
		[[nodiscard]]
		Array<size_t> knnSearch(size_t k, const point_type& point) const;

		/// @brief 指定した座標から最も近い k 個の要素を検索して取得します。
		/// @param results 結果を格納する配列
		/// @param k 検索する個数
		/// @param point 中心座標
		void knnSearch(Array<size_t>& results, size_t k, const point_type& point) const;

		/// @brief 指定した座標から最も近い k 個の要素を検索して取得します。
		/// @param results 結果を格納する配列
		/// @param distanceSqResults それぞれの要素について、中心からの距離を格納する配列
		/// @param k 検索する個数
		/// @param point 中心座標
		void knnSearch(Array<size_t>& results, Array<element_type>& distanceSqResults, size_t k, const point_type& point) const;

		/// @brief 指定した座標から指定した半径以内にある要素一覧を検索して返します。
		/// @param point 中心座標
		/// @param radius 半径
		/// @param sortByDistance 結果を中心座標から近い順にソートする場合 `SortByDistance::Yes`, それ以外の場合は `SortByDistance::No`
		/// @return 指定した位置から指定した半径以内にある要素一覧
		[[nodiscard]]
		Array<size_t> radiusSearch(const point_type& point, element_type radius, SortByDistance sortByDistance = SortByDistance::No) const;

		/// @brief 指定した座標から指定した半径以内にある要素一覧を検索して取得します。
		/// @param results 結果を格納する配列
		/// @param point 中心座標
		/// @param radius 半径
		/// @param sortByDistance 結果を中心座標から近い順にソートする場合 `SortByDistance::Yes`, それ以外の場合は `SortByDistance::No`
		void radiusSearch(Array<size_t>& results, const point_type& point, element_type radius, const SortByDistance sortByDistance = SortByDistance::No) const;

	private:

		adapter_type m_adapter;

		nanoflann::KDTreeSingleIndexAdaptor<nanoflann::L2_Simple_Adaptor<element_type, adapter_type, double>, adapter_type, Dimensions, size_t> m_index;
	};

	template <class Dataset, class PointType, class ElementType = typename PointType::value_type, int32 Dim = PointType::Dimension>
	struct KDTreeAdapter
	{
		using dataset_type	= Dataset;
		
		using point_type	= PointType;
		
		using element_type	= ElementType;
		
		static constexpr int32 Dimensions = Dim;
	};
}

# include "detail/KDTree.ipp"
