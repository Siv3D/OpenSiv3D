// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.
// Copyright (c) 2013 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2018-2020.
// Modifications copyright (c) 2018 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_EXTENSIONS_ALGEBRA_GEOMETRIES_CONCEPTS_ROTATION_MATRIX_CONCEPT_HPP
#define BOOST_GEOMETRY_EXTENSIONS_ALGEBRA_GEOMETRIES_CONCEPTS_ROTATION_MATRIX_CONCEPT_HPP

#include <type_traits>

#include <boost/concept_check.hpp>
#include <boost/core/ignore_unused.hpp>

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/static_assert.hpp>
#include <boost/geometry/extensions/algebra/core/access.hpp>
#include <boost/geometry/extensions/algebra/core/coordinate_dimension.hpp>
#include <boost/geometry/extensions/algebra/core/coordinate_system.hpp>
#include <boost/geometry/extensions/algebra/core/coordinate_type.hpp>

namespace boost { namespace geometry { namespace concepts {

template <typename Geometry>
class RotationMatrix
{
#ifndef DOXYGEN_NO_CONCEPT_MEMBERS

    typedef typename coordinate_type<Geometry>::type ctype;
    typedef typename coordinate_system<Geometry>::type csystem;

    enum { ccount = dimension<Geometry>::value };

    template <typename G, std::size_t I, std::size_t J, std::size_t N>
    struct dimension_checker_row
    {
        static void apply()
        {
            G* g = 0;
            geometry::set<I, J>(*g, geometry::get<I, J>(*g));
            dimension_checker_row<G, I, J+1, N>::apply();
        }
    };

    template <typename G, std::size_t I, std::size_t N>
    struct dimension_checker_row<G, I, N, N>
    {
        static void apply() {}
    };

    template <typename G, std::size_t I, std::size_t N>
    struct dimension_checker
    {
        static void apply()
        {
            dimension_checker_row<G, I, 0, N>::apply();
            dimension_checker<G, I+1, N>::apply();
        }
    };

    template <typename G, std::size_t N>
    struct dimension_checker<G, N, N>
    {
        static void apply() {}
    };

public:

    /// BCCL macro to apply the concept
    BOOST_CONCEPT_USAGE(RotationMatrix)
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
class ConstRotationMatrix
{
#ifndef DOXYGEN_NO_CONCEPT_MEMBERS

    typedef typename coordinate_type<Geometry>::type ctype;
    typedef typename coordinate_system<Geometry>::type csystem;

    enum { ccount = dimension<Geometry>::value };

    template <typename G, std::size_t I, std::size_t J, std::size_t N>
    struct dimension_checker_row
    {
        static void apply()
        {
            const G* g = 0;
            ctype coord(geometry::get<I, J>(*g));
            boost::ignore_unused(coord);
            dimension_checker_row<G, I, J+1, N>::apply();
        }
    };

    template <typename G, std::size_t I, std::size_t N>
    struct dimension_checker_row<G, I, N, N>
    {
        static void apply() {}
    };

    template <typename G, std::size_t I, std::size_t N>
    struct dimension_checker
    {
        static void apply()
        {
            dimension_checker_row<G, I, 0, N>::apply();
            dimension_checker<G, I+1, N>::apply();
        }
    };

    template <typename G, std::size_t N>
    struct dimension_checker<G, N, N>
    {
        static void apply() {}
    };

public:

    /// BCCL macro to apply the concept
    BOOST_CONCEPT_USAGE(ConstRotationMatrix)
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

#endif // BOOST_GEOMETRY_EXTENSIONS_ALGEBRA_GEOMETRIES_CONCEPTS_ROTATION_MATRIX_CONCEPT_HPP
