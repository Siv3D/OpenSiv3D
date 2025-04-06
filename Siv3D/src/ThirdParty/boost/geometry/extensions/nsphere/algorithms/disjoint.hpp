// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2019 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2020.
// Modifications copyright (c) 2020, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_EXTENSIONS_NSPHERE_ALGORITHMS_DISJOINT_HPP
#define BOOST_GEOMETRY_EXTENSIONS_NSPHERE_ALGORITHMS_DISJOINT_HPP

#include <type_traits>

#include <boost/geometry/algorithms/disjoint.hpp>
#include <boost/geometry/algorithms/comparable_distance.hpp>
#include <boost/geometry/core/static_assert.hpp>
#include <boost/geometry/extensions/nsphere/views/center_view.hpp>
#include <boost/geometry/util/select_most_precise.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace disjoint
{

// Arvo's algorithm implemented
// TODO - implement the method mentioned in the article below and compare performance
// "On Faster Sphere-Box Overlap Testing" - Larsson, T.; Akeine-Moller, T.; Lengyel, E.
template
<
    typename Box, typename NSphere,
    std::size_t Dimension, std::size_t DimensionCount
>
struct box_nsphere_comparable_distance_cartesian
{
    typedef typename geometry::select_most_precise
        <
            typename coordinate_type<Box>::type,
            typename coordinate_type<NSphere>::type
        >::type coordinate_type;

    typedef typename geometry::default_distance_result
        <
            Box,
            typename point_type<NSphere>::type
        >::type result_type;

    static inline result_type apply(Box const& box, NSphere const& nsphere)
    {
        result_type r = 0;

        if( get<Dimension>(nsphere) < get<min_corner, Dimension>(box) )
        {
            coordinate_type tmp = get<min_corner, Dimension>(box) - get<Dimension>(nsphere);
            r = tmp*tmp;
        }
        else if( get<max_corner, Dimension>(box) < get<Dimension>(nsphere) )
        {
            coordinate_type tmp = get<Dimension>(nsphere) - get<max_corner, Dimension>(box);
            r = tmp*tmp;
        }

        return r + box_nsphere_comparable_distance_cartesian<
                        Box, NSphere, Dimension + 1, DimensionCount
                    >::apply(box, nsphere);
    }
};

template <typename Box, typename NSphere, std::size_t DimensionCount>
struct box_nsphere_comparable_distance_cartesian<Box, NSphere, DimensionCount, DimensionCount>
{
    static inline int apply(Box const& , NSphere const& )
    {
        return 0;
    }
};

}} // namespace detail::disjoint
#endif // DOXYGEN_NO_DETAIL

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template <typename Point, typename NSphere, std::size_t DimensionCount, bool Reverse>
struct disjoint<Point, NSphere, DimensionCount, point_tag, nsphere_tag, Reverse>
{
    // TODO: Implement as strategy
    template <typename Strategy>
    static inline bool apply(Point const& p, NSphere const& s, Strategy const& )
    {
        typedef typename coordinate_system<Point>::type p_cs;
        typedef typename coordinate_system<NSphere>::type s_cs;
        static const bool check_cs = std::is_same<p_cs, cs::cartesian>::value
                                  && std::is_same<s_cs, cs::cartesian>::value;
        BOOST_GEOMETRY_STATIC_ASSERT(
            check_cs,
            "Not implemented for those coordinate systems.",
            p_cs, s_cs);

        typename radius_type<NSphere>::type const r = get_radius<0>(s);
        center_view<const NSphere> const c(s);

        // TODO: comparable_distance is correct only for default cartesian strategy
        //       call specific strategy directly
        return r * r < geometry::comparable_distance(p, c);
    }
};

template <typename NSphere, typename Box, std::size_t DimensionCount, bool Reverse>
struct disjoint<NSphere, Box, DimensionCount, nsphere_tag, box_tag, Reverse>
{
    // TODO: Implement as strategy
    template <typename Strategy>
    static inline bool apply(NSphere const& s, Box const& b, Strategy const& )
    {
        typedef typename coordinate_system<Box>::type b_cs;
        typedef typename coordinate_system<NSphere>::type s_cs;
        static const bool check_cs = std::is_same<b_cs, cs::cartesian>::value
                                  && std::is_same<s_cs, cs::cartesian>::value;
        BOOST_GEOMETRY_STATIC_ASSERT(
            check_cs,
            "Not implemented for those coordinate systems.",
            b_cs, s_cs);

        typename radius_type<NSphere>::type const r = get_radius<0>(s);

        return r * r < geometry::detail::disjoint::box_nsphere_comparable_distance_cartesian
                           <
                               Box, NSphere, 0, DimensionCount
                           >::apply(b, s);
    }
};

template <typename NSphere1, typename NSphere2, std::size_t DimensionCount, bool Reverse>
struct disjoint<NSphere1, NSphere2, DimensionCount, nsphere_tag, nsphere_tag, Reverse>
{
    // TODO: Implement as strategy
    template <typename Strategy>
    static inline bool apply(NSphere1 const& s1, NSphere2 const& s2, Strategy const& )
    {
        typedef typename coordinate_system<NSphere1>::type s1_cs;
        typedef typename coordinate_system<NSphere2>::type s2_cs;
        static const bool check_cs = std::is_same<s1_cs, cs::cartesian>::value
                                  && std::is_same<s2_cs, cs::cartesian>::value;
        BOOST_GEOMETRY_STATIC_ASSERT(
            check_cs,
            "Not implemented for those coordinate systems.",
            s1_cs, s2_cs);

        /*return get_radius<0>(s1) + get_radius<0>(s2)
               <   ::sqrt(geometry::comparable_distance(center_view<NSphere>(s1), center_view<NSphere>(s2)));*/

        typename radius_type<NSphere1>::type const r1 = get_radius<0>(s1);
        typename radius_type<NSphere2>::type const r2 = get_radius<0>(s2);
        center_view<NSphere1 const> const c1(s1);
        center_view<NSphere2 const> const c2(s2);

        // TODO: comparable_distance is correct only for default cartesian strategy
        //       call specific strategy directly
        return r1 * r1 + 2 * r1 * r2 + r2 * r2
                < geometry::comparable_distance(c1, c2);
    }
};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_EXTENSIONS_NSPHERE_ALGORITHMS_DISJOINT_HPP
