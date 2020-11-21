//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
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

	template <class DatasetAdapter>
	class KDTree
	{
	public:

		using adapter_type	= detail::KDAdapter<DatasetAdapter>;

		using point_type	= typename adapter_type::point_type;

		using element_type	= typename adapter_type::element_type;

		using dataset_type	= typename adapter_type::dataset_type;

		static constexpr int32 Dimensions = adapter_type::Dimensions;

		KDTree() = default;

		explicit KDTree(const dataset_type& dataset);

		void rebuildIndex();

		void release();

		[[nodiscard]]
		size_t usedMemory() const;

		[[nodiscard]]
		Array<size_t> knnSearch(size_t k, const point_type& point) const;

		void knnSearch(Array<size_t>& results, size_t k, const point_type& point) const;

		void knnSearch(Array<size_t>& results, Array<element_type>& distanceSqResults, size_t k, const point_type& point) const;

		[[nodiscard]]
		Array<size_t> radiusSearch(const point_type& point, element_type radius, SortByDistance sortByDistance = SortByDistance::No) const;

		void radiusSearch(Array<size_t>& results, const point_type& point, element_type radius, const SortByDistance sortByDistance = SortByDistance::No) const;

	private:

		adapter_type m_adapter;

		nanoflann::KDTreeSingleIndexAdaptor<nanoflann::L2_Simple_Adaptor<element_type, adapter_type>, adapter_type, Dimensions> m_index;
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
