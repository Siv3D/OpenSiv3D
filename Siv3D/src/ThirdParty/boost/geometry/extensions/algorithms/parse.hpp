// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2018.
// Modifications copyright (c) 2018 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_EXTENSIONS_ALGORITHMS_PARSE_HPP
#define BOOST_GEOMETRY_EXTENSIONS_ALGORITHMS_PARSE_HPP

#include <string>

#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>

#include <boost/geometry/srs/projections/impl/dms_parser.hpp>
//#include <boost/geometry/extensions/strategies/parse.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

} // namespace detail
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{
template <typename Tag, typename G>
struct parsing
{
};

template <typename Point>
struct parsing<point_tag, Point>
{
    template <typename S>
    static inline void parse(Point& point, std::string const& c1, std::string const& c2, S const& strategy)
    {
        assert_dimension<Point, 2>();

        typedef typename coordinate_type<Point>::type coord_t;
        typedef boost::geometry::projections::detail::dms_result<coord_t> dms_result_t;
        dms_result_t r1 = strategy(c1.c_str());
        dms_result_t r2 = strategy(c2.c_str());

        if (0 == r1.axis())
            set<0>(point, r1.angle());
        else
            set<1>(point, r1.angle());

        if (0 == r2.axis())
            set<0>(point, r2.angle());
        else
            set<1>(point, r2.angle());
    }

    static inline void parse(Point& point, std::string const& c1, std::string const& c2)
    {
        typedef typename coordinate_type<Point>::type coord_t;
        // strategy-parser corresponding to degree/radian
        //typename strategy_parse
        //    <
        //        typename cs_tag<Point>::type,
        //        typename coordinate_system<Point>::type
        //    >::type strategy;
        typedef boost::geometry::projections::detail::dms_parser
                    <
                        coord_t/*,
                        as_radian*/
                    > dms_parser_t;

        parse(point, c1, c2, dms_parser_t());
    }
};

} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


/*!
    \brief parse two strings to a spherical/geographic point, using W/E/N/S
    \ingroup parse
 */
template <typename Geometry>
inline void parse(Geometry& geometry, std::string const& c1, std::string const& c2)
{
    concepts::check<Geometry>();
    dispatch::parsing<typename tag<Geometry>::type, Geometry>::parse(geometry, c1, c2);
}

/*!
    \brief parse two strings to a spherical/geographic point, using a specified strategy
    \details user can use N/E/S/O or N/O/Z/W or other formats
    \ingroup parse
 */
template <typename Geometry, typename S>
inline void parse(Geometry& geometry, std::string const& c1,
        std::string const& c2, S const& strategy)
{
    concepts::check<Geometry>();
    dispatch::parsing<typename tag<Geometry>::type, Geometry>::parse(geometry, c1, c2, strategy);
}

// There will be a parsing function with three arguments (ANGLE,ANGLE,RADIUS)

template <typename Geometry>
inline Geometry parse(std::string const& c1, std::string const& c2)
{
    concepts::check<Geometry>();

    Geometry geometry;
    dispatch::parsing<typename tag<Geometry>::type, Geometry>::parse(geometry, c1, c2);
    return geometry;
}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_EXTENSIONS_ALGORITHMS_PARSE_HPP
