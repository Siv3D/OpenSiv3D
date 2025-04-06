// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2020.
// Modifications copyright (c) 2020, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_GEOMETRY_EXTENSIONS_NSPHERE_CORE_TOPOLOGICAL_DIMENSION_HPP
#define BOOST_GEOMETRY_EXTENSIONS_NSPHERE_CORE_TOPOLOGICAL_DIMENSION_HPP


#include <type_traits>

#include <boost/geometry/core/topological_dimension.hpp>

#include <boost/geometry/extensions/nsphere/core/tags.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DISPATCH
namespace core_dispatch
{



// nsphere: 2, but there is discussion. Is it CLOSED? Then 2, but
// then it should be called "disk"...
template <>
struct top_dim<nsphere_tag>    : std::integral_constant<int, 2> {};




} // namespace core_dispatch
#endif



}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_EXTENSIONS_NSPHERE_CORE_TOPOLOGICAL_DIMENSION_HPP
