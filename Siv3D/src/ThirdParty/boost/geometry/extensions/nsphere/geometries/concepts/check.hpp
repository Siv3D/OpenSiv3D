// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.
// Copyright (c) 2013 Adam Wulkiewicz, Lodz, Poland.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_GEOMETRY_EXTENSIONS_NSPHERE_GEOMETRIES_CONCEPTS_CHECK_HPP
#define BOOST_GEOMETRY_EXTENSIONS_NSPHERE_GEOMETRIES_CONCEPTS_CHECK_HPP


#include <boost/geometry/geometries/concepts/check.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template <typename Geometry>
struct check<Geometry, nsphere_tag, true>
    : detail::concept_check::check<concepts::ConstNsphere<Geometry> >
{};

template <typename Geometry>
struct check<Geometry, nsphere_tag, false>
    : detail::concept_check::check<concepts::Nsphere<Geometry> >
{};

} // namespace dispatch
#endif




}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_EXTENSIONS_NSPHERE_GEOMETRIES_CONCEPTS_CHECK_HPP
