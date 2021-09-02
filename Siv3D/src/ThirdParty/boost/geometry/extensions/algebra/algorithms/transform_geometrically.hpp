// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2013 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2018-2020.
// Modifications copyright (c) 2018-2020 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_EXTENSIONS_ALGEBRA_ALGORITHMS_TRANSFORM_HPP
#define BOOST_GEOMETRY_EXTENSIONS_ALGEBRA_ALGORITHMS_TRANSFORM_HPP

#include <type_traits>

#include <boost/geometry/algorithms/convert.hpp>
#include <boost/geometry/arithmetic/arithmetic.hpp>
#include <boost/geometry/core/static_assert.hpp>
#include <boost/geometry/extensions/algebra/algorithms/detail.hpp>
#include <boost/geometry/extensions/algebra/geometries/concepts/vector_concept.hpp>
#include <boost/geometry/extensions/algebra/geometries/concepts/rotation_quaternion_concept.hpp>
#include <boost/geometry/extensions/algebra/geometries/concepts/rotation_matrix_concept.hpp>
#include <boost/geometry/geometries/concepts/check.hpp>

namespace boost { namespace geometry {

namespace detail { namespace transform_geometrically {

template <typename Box, typename Vector, std::size_t Dimension>
struct box_vector_cartesian
{
    BOOST_GEOMETRY_STATIC_ASSERT(
        (Dimension > 0),
        "Dimension has to be greater than 0.",
        Box);

    static inline void apply(Box & box, Vector const& vector)
    {
        box_vector_cartesian<Box, Vector, Dimension-1>::apply(box, vector);
        set<min_corner, Dimension-1>(box, get<min_corner, Dimension-1>(box) + get<Dimension-1>(vector));
        set<max_corner, Dimension-1>(box, get<max_corner, Dimension-1>(box) + get<Dimension-1>(vector));
    }
};

template <typename Box, typename Vector>
struct box_vector_cartesian<Box, Vector, 1>
{
    static inline void apply(Box & box, Vector const& vector)
    {
        set<min_corner, 0>(box, get<min_corner, 0>(box) + get<0>(vector));
        set<max_corner, 0>(box, get<max_corner, 0>(box) + get<0>(vector));
    }
};

}} // namespace detail::transform

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch {

template <typename Geometry, typename Transform,
          typename GTag = typename tag<Geometry>::type,
          typename TTag = typename tag<Transform>::type>
struct transform_geometrically
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Not implemented for this Geometry.",
        Geometry, Transform);
};

// Point translation by Vector
template <typename Point, typename Vector>
struct transform_geometrically<Point, Vector, point_tag, vector_tag>
{
    BOOST_CONCEPT_ASSERT( (concepts::Point<Point>) );
    BOOST_CONCEPT_ASSERT( (concepts::Vector<Vector>) );

    static inline void apply(Point & point, Vector const& vector)
    {
        typedef std::is_same
            <
                typename traits::coordinate_system<Point>::type,
                cs::cartesian
            > is_cartesian;
        apply(point, vector, is_cartesian());
    }

    static inline void apply(Point & point, Vector const& vector, std::true_type /*is_cartesian*/)
    {
        for_each_coordinate(point, detail::point_operation<Vector, std::plus>(vector));
    }

    static inline void apply(Point & point, Vector const& vector, std::false_type /*is_cartesian*/)
    {
        BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
            "Not implemented for this coordinate system.",
            typename traits::coordinate_system<Point>::type);
    }
};

// Box translation by Vector
template <typename Box, typename Vector>
struct transform_geometrically<Box, Vector, box_tag, vector_tag>
{
    typedef typename traits::point_type<Box>::type point_type;

    BOOST_CONCEPT_ASSERT( (concepts::Point<point_type>) );
    BOOST_CONCEPT_ASSERT( (concepts::Vector<Vector>) );

    static inline void apply(Box & box, Vector const& vector)
    {
        typedef std::is_same
            <
                typename traits::coordinate_system<point_type>::type,
                cs::cartesian
            > is_cartesian;
        apply(box, vector, is_cartesian());
    }

    static inline void apply(Box & box, Vector const& vector, std::true_type /*is_cartesian*/)
    {
        geometry::detail::transform_geometrically::box_vector_cartesian<
            Box, Vector, traits::dimension<point_type>::value
        >::apply(box, vector);
    }

    static inline void apply(Box & box, Vector const& vector, std::false_type /*is_cartesian*/)
    {
        BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
            "Not implemented for this coordinate system.",
            typename traits::coordinate_system<point_type>::type);
    }
};

// Vector rotation by Quaternion
template <typename Vector, typename RotationQuaternion>
struct transform_geometrically<Vector, RotationQuaternion, vector_tag, rotation_quaternion_tag>
{
    static inline void apply(Vector & v, RotationQuaternion const& r)
    {
        concepts::check_concepts_and_equal_dimensions<Vector, RotationQuaternion const>();

        detail::algebra::quaternion_rotate(v, r);
    }
};

// Vector rotation by Matrix
template <typename Vector, typename RotationMatrix>
struct transform_geometrically<Vector, RotationMatrix, vector_tag, rotation_matrix_tag>
{
    static inline void apply(Vector & v, RotationMatrix const& r)
    {
        concepts::check_concepts_and_equal_dimensions<Vector, RotationMatrix const>();

        // TODO vector_type and convert from Vector
        Vector tmp(v);
        detail::algebra::matrix_rotate(r, tmp, v);
    }
};

} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

template <typename Geometry, typename Transformation>
inline void transform_geometrically(Geometry & g, Transformation const& t)
{
    dispatch::transform_geometrically<Geometry, Transformation>::apply(g, t);
}

template <typename GeometrySrc, typename Transformation, typename GeometryDst>
inline void transformed_geometrically(GeometrySrc const& gsrc, Transformation const& t, GeometryDst & gdst)
{
    geometry::convert(gsrc, gdst);
    geometry::transform_geometrically(gdst, t);
}

template <typename GeometryDst, typename GeometrySrc, typename Transformation>
inline GeometryDst return_transformed_geometrically(GeometrySrc const& gsrc, Transformation const& t)
{
    GeometryDst res;
    transformed_geometrically(gsrc, t, res);
    return res;
}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_EXTENSIONS_ALGEBRA_ALGORITHMS_TRANSFORM_HPP
