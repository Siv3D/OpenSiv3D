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

#ifndef BOOST_GEOMETRY_EXTENSIONS_NSPHERE_ALGORITHMS_WITHIN_HPP
#define BOOST_GEOMETRY_EXTENSIONS_NSPHERE_ALGORITHMS_WITHIN_HPP

#include <boost/core/ignore_unused.hpp>

#include <boost/geometry/algorithms/distance.hpp>
#include <boost/geometry/algorithms/make.hpp>
#include <boost/geometry/algorithms/within.hpp>
#include <boost/geometry/strategies/distance.hpp>

#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/extensions/nsphere/core/access.hpp>
#include <boost/geometry/extensions/nsphere/core/radius.hpp>
#include <boost/geometry/extensions/nsphere/core/tags.hpp>
#include <boost/geometry/extensions/nsphere/algorithms/assign.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace within
{

// TODO: This is not fully correct for all geometries
//   For more complex geometries than Point if at least one point is in the
//   interior of nsphere within should return true even if other points are
//   on the boudary

template<typename B, typename C, typename S>
inline bool box_in_circle(B const& b, C const& c, S const& s)
{
    typedef typename point_type<B>::type point_type;

    // Currently only implemented for 2d geometries
    assert_dimension<point_type, 2>();
    assert_dimension<C, 2>();
    ::boost::ignore_unused(s);

    // Box: all four points must lie within circle
    
    // Check points lower-left and upper-right, then lower-right and upper-left
    return s.apply(geometry::make<point_type>(get<min_corner, 0>(b), get<min_corner, 1>(b)), c)
        && s.apply(geometry::make<point_type>(get<max_corner, 0>(b), get<max_corner, 1>(b)), c)
        && s.apply(geometry::make<point_type>(get<min_corner, 0>(b), get<max_corner, 1>(b)), c)
        && s.apply(geometry::make<point_type>(get<max_corner, 0>(b), get<min_corner, 1>(b)), c);
}

// Generic "range-in-circle", true if all points within circle
template<typename R, typename C, typename S>
inline bool range_in_circle(R const& range, C const& c, S const& s)
{
    ::boost::ignore_unused(s);

    for (typename boost::range_iterator<R const>::type it = boost::begin(range);
         it != boost::end(range); ++it)
    {
        if (! s.apply(*it, c))
        {
            return false;
        }
    }

    return true;
}

template<typename Y, typename C, typename S>
inline bool polygon_in_circle(Y const& poly, C const& c, S const& s)
{
    return range_in_circle(exterior_ring(poly), c, s);
}



template<typename I, typename C, typename S>
inline bool multi_polygon_in_circle(I const& m, C const& c, S const& s)
{
    for (typename I::const_iterator i = m.begin(); i != m.end(); i++)
    {
        if (! polygon_in_circle(*i, c, s))
        {
            return false;
        }
    }
    return true;
}



}} // namespace detail::within
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename P, typename Circle>
struct within<P, Circle, point_tag, nsphere_tag>
{
    template <typename Strategy>
    static inline bool apply(P const& p, Circle const& c, Strategy const& strategy)
    {
        ::boost::ignore_unused(strategy);
        return strategy.apply(p, c);
    }
};

template <typename Box, typename Circle>
struct within<Box, Circle, box_tag, nsphere_tag>
{
    template <typename Strategy>
    static inline bool apply(Box const& b, Circle const& c, Strategy const& s)
    {
        return detail::within::box_in_circle(b, c, s);
    }
};

template <typename Linestring, typename Circle>
struct within<Linestring, Circle, linestring_tag, nsphere_tag>
{
    template <typename Strategy>
    static inline bool apply(Linestring const& ln, Circle const& c, Strategy const& s)
    {
        return detail::within::range_in_circle(ln, c, s);
    }
};

template <typename Ring, typename Circle>
struct within<Ring, Circle, ring_tag, nsphere_tag>
{
    template <typename Strategy>
    static inline bool apply(Ring const& r, Circle const& c, Strategy const& s)
    {
        return detail::within::range_in_circle(r, c, s);
    }
};

template <typename Polygon, typename Circle>
struct within<Polygon, Circle, polygon_tag, nsphere_tag>
{
    template <typename Strategy>
    static inline bool apply(Polygon const& poly, Circle const& c, Strategy const& s)
    {
        return detail::within::polygon_in_circle(poly, c, s);
    }
};

template <typename M, typename C>
struct within<M, C, multi_polygon_tag, nsphere_tag>
{
    template <typename Strategy>
    static inline bool apply(M const& m, C const& c, Strategy const& s)
    {
        return detail::within::multi_polygon_in_circle(m, c, s);
    }
};



template <typename NSphere, typename Box>
struct within<NSphere, Box, nsphere_tag, box_tag>
{
    template <typename Strategy>
    static inline bool apply(NSphere const& nsphere, Box const& box, Strategy const& strategy)
    {
        assert_dimension_equal<NSphere, Box>();
        boost::ignore_unused(strategy);
        return strategy.apply(nsphere, box);
    }
};

} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_EXTENSIONS_NSPHERE_ALGORITHMS_WITHIN_HPP
