// Boost.Geometry Index
//
// Copyright (c) 2011-2015 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_EXTENSIONS_NSPHERE_INDEX_DETAIL_IS_INDEXABLE_HPP
#define BOOST_GEOMETRY_EXTENSIONS_NSPHERE_INDEX_DETAIL_IS_INDEXABLE_HPP

#include <boost/geometry/index/detail/is_bounding_geometry.hpp>

namespace boost { namespace geometry { namespace index {

namespace detail {

template <typename NSphere>
struct is_indexable<NSphere, geometry::nsphere_tag>
{
    static const bool value = true;
};

} // namespace detail

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_EXTENSIONS_NSPHERE_INDEX_DETAIL_IS_INDEXABLE_HPP
