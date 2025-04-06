// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.
// Copyright (c) 2013 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2020.
// Modifications copyright (c) 2020 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_EXTENSIONS_ALGEBRA_CORE_COORDINATE_SYSTEM_HPP
#define BOOST_GEOMETRY_EXTENSIONS_ALGEBRA_CORE_COORDINATE_SYSTEM_HPP

#include <boost/geometry/core/coordinate_system.hpp>

#include <boost/geometry/extensions/algebra/core/tags.hpp>

namespace boost { namespace geometry {

#ifndef DOXYGEN_NO_DISPATCH
namespace core_dispatch {

template <typename Vector>
struct coordinate_system<vector_tag, Vector>
{
    typedef typename traits::coordinate_system<
        typename detail::remove_cptrref<Vector>::type
    >::type type;
};

//template <typename G>
//struct coordinate_system<quaternion_tag, G>
//{
//    typedef typename traits::coordinate_system<
//        typename detail::remove_cptrref<G>::type
//    >::type type;
//};
//
//template <typename G>
//struct coordinate_system<matrix_tag, G>
//{
//    typedef typename traits::coordinate_system<
//        typename detail::remove_cptrref<G>::type
//    >::type type;
//};


template <typename G>
struct coordinate_system<rotation_quaternion_tag, G>
{
    typedef typename traits::coordinate_system<
        typename detail::remove_cptrref<G>::type
    >::type type;
};

template <typename G>
struct coordinate_system<rotation_matrix_tag, G>
{
    typedef typename traits::coordinate_system<
        typename detail::remove_cptrref<G>::type
    >::type type;
};

} // namespace core_dispatch
#endif // DOXYGEN_NO_DISPATCH

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_EXTENSIONS_ALGEBRA_CORE_COORDINATE_SYSTEM_HPP
