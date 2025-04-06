// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.
// Copyright (c) 2013 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2018-2020.
// Modifications copyright (c) 2018-2020 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_EXTENSIONS_ALGEBRA_GEOMETRIES_CONCEPTS_VECTOR_CONCEPT_HPP
#define BOOST_GEOMETRY_EXTENSIONS_ALGEBRA_GEOMETRIES_CONCEPTS_VECTOR_CONCEPT_HPP

#include <type_traits>

#include <boost/concept_check.hpp>
#include <boost/core/ignore_unused.hpp>

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/static_assert.hpp>
#include <boost/geometry/extensions/algebra/core/access.hpp>
#include <boost/geometry/extensions/algebra/core/coordinate_dimension.hpp>
#include <boost/geometry/extensions/algebra/core/coordinate_type.hpp>
#include <boost/geometry/extensions/algebra/core/coordinate_system.hpp>

namespace boost { namespace geometry { namespace concepts {

template <typename Geometry>
class Vector
{
#ifndef DOXYGEN_NO_CONCEPT_MEMBERS

    typedef typename coordinate_type<Geometry>::type ctype;
    typedef typename coordinate_system<Geometry>::type csystem;

    enum { ccount = dimension<Geometry>::value };


    template <typename V, std::size_t Dimension, std::size_t DimensionCount>
    struct dimension_checker
    {
        static void apply()
        {
            V* v = 0;
            geometry::set<Dimension>(*v, geometry::get<Dimension>(*v));
            dimension_checker<V, Dimension+1, DimensionCount>::apply();
        }
    };


    template <typename V, std::size_t DimensionCount>
    struct dimension_checker<V, DimensionCount, DimensionCount>
    {
        static void apply() {}
    };

public:

    /// BCCL macro to apply the Vector concept
    BOOST_CONCEPT_USAGE(Vector)
    {
        static const bool cs_check = std::is_same<csystem, cs::cartesian>::value;
        BOOST_GEOMETRY_STATIC_ASSERT(cs_check,
            "Not implemented for this coordinate system.",
            csystem);

        dimension_checker<Geometry, 0, ccount>::apply();
    }
#endif
};


template <typename Geometry>
class ConstVector
{
#ifndef DOXYGEN_NO_CONCEPT_MEMBERS

    typedef typename coordinate_type<Geometry>::type ctype;
    typedef typename coordinate_system<Geometry>::type csystem;

    enum { ccount = dimension<Geometry>::value };

    template <typename V, std::size_t Dimension, std::size_t DimensionCount>
    struct dimension_checker
    {
        static void apply()
        {
            const V* v = 0;
            ctype coord(geometry::get<Dimension>(*v));
            boost::ignore_unused(coord);
            dimension_checker<V, Dimension+1, DimensionCount>::apply();
        }
    };


    template <typename V, std::size_t DimensionCount>
    struct dimension_checker<V, DimensionCount, DimensionCount>
    {
        static void apply() {}
    };

public:

    /// BCCL macro to apply the ConstVector concept
    BOOST_CONCEPT_USAGE(ConstVector)
    {
        static const bool cs_check = std::is_same<csystem, cs::cartesian>::value;
        BOOST_GEOMETRY_STATIC_ASSERT(cs_check,
            "Not implemented for this coordinate system.",
            csystem);

        dimension_checker<Geometry, 0, ccount>::apply();
    }
#endif
};

}}} // namespace boost::geometry::concepts

#endif // BOOST_GEOMETRY_EXTENSIONS_ALGEBRA_GEOMETRIES_CONCEPTS_VECTOR_CONCEPT_HPP
