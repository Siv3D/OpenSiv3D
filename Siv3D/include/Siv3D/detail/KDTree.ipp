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
	namespace detail
	{
		template <class DatasetAdapter>
		inline KDAdapter<DatasetAdapter>::KDAdapter(const dataset_type& dataset)
			: m_dataset{ dataset } {}

		template <class DatasetAdapter>
		inline size_t KDAdapter<DatasetAdapter>::kdtree_get_point_count() const
		{
			return std::size(m_dataset);
		}

		template <class DatasetAdapter>
		inline typename KDAdapter<DatasetAdapter>::element_type KDAdapter<DatasetAdapter>::kdtree_get_pt(const size_t index, const size_t dim) const
		{
			return DatasetAdapter::GetElement(m_dataset, index, dim);
		}

		template <class DatasetAdapter>
		template <class BBOX>
		inline bool KDAdapter<DatasetAdapter>::kdtree_get_bbox(BBOX&) const
		{
			return false;
		}

		template <class DatasetAdapter>
		inline const typename KDAdapter<DatasetAdapter>::element_type* KDAdapter<DatasetAdapter>::GetPointer(const point_type& point)
		{
			return DatasetAdapter::GetPointer(point);
		}

		template <class _DistanceType>
		class RadiusResultsAdapter
		{
		public:
			
			using DistanceType	= _DistanceType;
			
			using IndexType		= size_t;

			const DistanceType m_radius;

			Array<IndexType>& m_results;

			RadiusResultsAdapter(DistanceType radius, Array<IndexType>& results)
				: m_radius{ radius }
				, m_results{ results }
			{
				init();
			}

			void init()
			{
				clear();
			}
			
			void clear()
			{
				m_results.clear();
			}

			size_t size() const 
			{
				return m_results.size();
			}

			constexpr bool full() const
			{
				return true;
			}

			bool addPoint(const DistanceType, const IndexType index)
			{
				m_results.push_back(index);

				return true;
			}

			DistanceType worstDist() const
			{
				return m_radius;
			}
		};
	}

	template <class DatasetAdapter>
	inline KDTree<DatasetAdapter>::KDTree(const dataset_type& dataset)
		: m_adapter{ dataset }
		, m_index{ Dimensions, m_adapter, nanoflann::KDTreeSingleIndexAdaptorParams(10) }
	{
		rebuildIndex();
	}

	template <class DatasetAdapter>
	inline void KDTree<DatasetAdapter>::rebuildIndex()
	{
		m_index.buildIndex();
	}

	template <class DatasetAdapter>
	inline void KDTree<DatasetAdapter>::release()
	{
		m_index.freeIndex();
	}

	template <class DatasetAdapter>
	inline size_t KDTree<DatasetAdapter>::usedMemory() const
	{
		return m_index.usedMemory();
	}

	template <class DatasetAdapter>
	inline Array<size_t> KDTree<DatasetAdapter>::knnSearch(size_t k, const point_type& point) const
	{
		Array<size_t> results;

		knnSearch(results, k, point);

		return results;
	}

	template <class DatasetAdapter>
	inline void KDTree<DatasetAdapter>::knnSearch(Array<size_t>& results, size_t k, const point_type& point) const
	{
		results.resize(k);

		Array<element_type> distanceSqs(k);

		k = m_index.knnSearch(adapter_type::GetPointer(point), k, results.data(), distanceSqs.data());

		results.resize(k);
	}

	template <class DatasetAdapter>
	inline void KDTree<DatasetAdapter>::knnSearch(Array<size_t>& results, Array<element_type>& distanceSqResults, size_t k, const point_type& point) const
	{
		results.resize(k);
		distanceSqResults.resize(k);

		k = m_index.knnSearch(adapter_type::GetPointer(point), k, &results[0], &distanceSqResults[0]);

		results.resize(k);
		distanceSqResults.resize(k);
	}

	template <class DatasetAdapter>
	inline Array<size_t> KDTree<DatasetAdapter>::radiusSearch(const point_type& point, const element_type radius, const SortByDistance sortByDistance) const
	{
		Array<size_t> results;

		radiusSearch(results, point, radius, sortByDistance);

		return results;
	}

	template <class DatasetAdapter>
	inline void KDTree<DatasetAdapter>::radiusSearch(Array<size_t>& results, const point_type& point, const element_type radius, const SortByDistance sortByDistance) const
	{
		const nanoflann::SearchParams searchParams{ 32, 0.0f, sortByDistance.getBool() };

		if (sortByDistance)
		{
			std::vector<std::pair<size_t, element_type>> matches;

			nanoflann::RadiusResultSet<element_type, size_t> resultSet{ (radius * radius), matches };

			const size_t num_matches = m_index.radiusSearchCustomCallback(adapter_type::GetPointer(point), resultSet, searchParams);

			if (searchParams.sorted)
			{
				std::sort(matches.begin(), matches.end(), nanoflann::IndexDist_Sorter());
			}

			results.resize(num_matches);

			size_t* pDst = results.data();
			const size_t* const pDstEnd = (pDst + num_matches);
			const std::pair<size_t, element_type>* pSrc = matches.data();

			while (pDst != pDstEnd)
			{
				*pDst++ = (pSrc++)->first;
			}
		}
		else
		{
			detail::RadiusResultsAdapter<element_type> resultSet{ (radius * radius), results };

			m_index.radiusSearchCustomCallback(adapter_type::GetPointer(point), resultSet, searchParams);
		}
	}
}
