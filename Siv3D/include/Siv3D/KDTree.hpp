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

SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4127)
# include <ThirdParty/nanoflann/nanoflann.hpp>
SIV3D_DISABLE_MSVC_WARNINGS_POP()

namespace s3d
{
	namespace detail
	{
		template <class DatasetAdapter>
		class KDAdapter
		{
		public:

			using point_type = typename DatasetAdapter::point_type;

			using element_type = typename DatasetAdapter::element_type;

			using dataset_type = typename DatasetAdapter::dataset_type;

			static constexpr int32 Dimensions = DatasetAdapter::Dimensions;

			static_assert(sizeof(point_type) == sizeof(element_type) * Dimensions);

		private:

			const dataset_type& m_dataset;

		public:

			explicit KDAdapter(const dataset_type& dataset)
				: m_dataset(dataset) {}

			[[nodiscard]] size_t kdtree_get_point_count() const
			{
				return std::size(m_dataset);
			}

			[[nodiscard]] element_type kdtree_get_pt(const size_t index, const size_t dim) const
			{
				return DatasetAdapter::GetElement(m_dataset, index, dim);
			}

			[[nodiscard]] element_type kdtree_distance(const element_type* p0, const size_t index_p1, size_t) const
			{
				return DatasetAdapter::DistanceSq(m_dataset, index_p1, p0);
			}

			template <class BBOX>
			bool kdtree_get_bbox(BBOX&) const
			{
				return false;
			}

			[[nodiscard]] static const element_type* GetPointer(const point_type& point)
			{
				return DatasetAdapter::GetPointer(point);
			}
		};
	}

	template <class DatasetAdapter>
	class KDTree
	{
	public:

		using adapter_type = detail::KDAdapter<DatasetAdapter>;

		using point_type = typename adapter_type::point_type;

		using element_type = typename adapter_type::element_type;

		using dataset_type = typename adapter_type::dataset_type;

		static constexpr int32 Dimensions = adapter_type::Dimensions;

	private:

		adapter_type m_adapter;

		nanoflann::KDTreeSingleIndexAdaptor<nanoflann::L2_Simple_Adaptor<element_type, adapter_type>, adapter_type, Dimensions> m_index;

	public:

		KDTree() = default;

		explicit KDTree(const dataset_type& dataset)
			: m_adapter(dataset)
			, m_index(Dimensions, m_adapter, nanoflann::KDTreeSingleIndexAdaptorParams(10))
		{
			rebuildIndex();
		}

		void rebuildIndex()
		{
			m_index.buildIndex();
		}

		void release()
		{
			m_index.freeIndex();
		}

		[[nodiscard]] size_t usedMemory() const
		{
			return m_index.usedMemory();
		}

		[[nodiscard]] Array<size_t> knnSearch(size_t k, const point_type& point) const
		{
			Array<size_t> results;

			knnSearch(results, k, point);

			return results;
		}

		void knnSearch(Array<size_t>& results, size_t k, const point_type& point) const
		{
			results.resize(k);

			Array<element_type> distanceSqs(k);

			k = m_index.knnSearch(adapter_type::GetPointer(point), k, &results[0], &distanceSqs[0]);

			results.resize(k);
		}

		[[nodiscard]] Array<size_t> radiusSearch(const point_type& point, const element_type radius, const bool sortByDistance = false) const
		{
			Array<size_t> results;

			radiusSearch(results, point, radius, sortByDistance);

			return results;
		}

		void radiusSearch(Array<size_t>& results, const point_type& point, const element_type radius, const bool sortByDistance = false) const
		{
			std::vector<std::pair<size_t, element_type>> matches;

			const nanoflann::SearchParams params(32, 0.0f, sortByDistance);

			const size_t num_matches = m_index.radiusSearch(adapter_type::GetPointer(point), radius * radius, matches, params);

			results.resize(num_matches);

			for (size_t i = 0; i < num_matches; ++i)
			{
				results[i] = matches[i].first;
			}
		}
	};

	template <class Dataset, class Point, class Element, int32 Dim>
	struct KDTreeAdapter
	{
		using dataset_type	= Dataset;
		using point_type	= Point;
		using element_type	= Element;
		static constexpr int32 Dimensions = Dim;
	};
}
