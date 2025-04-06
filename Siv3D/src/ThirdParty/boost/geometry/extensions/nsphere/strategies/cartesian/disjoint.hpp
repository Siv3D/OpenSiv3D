// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2019 Adam Wulkiewicz, Lodz, Poland.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_EXTENSIONS_NSPHERE_STRATEGIES_CARTESIAN_DISJOINT_HPP
#define BOOST_GEOMETRY_EXTENSIONS_NSPHERE_STRATEGIES_CARTESIAN_DISJOINT_HPP

#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/strategies/disjoint.hpp>

namespace boost { namespace geometry
{

namespace strategy { namespace disjoint
{

namespace services
{

// TODO: move code from algorithms, dummy strategies for now

template <typename Point, typename NSphere>
struct default_strategy<Point, NSphere, point_tag, nsphere_tag, 0, 2>
{
    typedef int type;
};

template <typename NSphere1, typename NSphere2>
struct default_strategy<NSphere1, NSphere2, nsphere_tag, nsphere_tag, 2, 2>
{
    typedef int type;
};

template <typename NSphere, typename Box>
struct default_strategy<NSphere, Box, nsphere_tag, box_tag, 2, 2>
{
    typedef int type;
};

} // namespace services

}} // namespace strategy::disjoint

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_EXTENSIONS_NSPHERE_STRATEGIES_CARTESIAN_DISJOINT_HPP
