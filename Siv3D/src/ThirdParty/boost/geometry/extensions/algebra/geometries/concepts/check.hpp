// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.
// Copyright (c) 2013 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2018.
// Modifications copyright (c) 2018 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_GEOMETRY_EXTENSIONS_ALGEBRA_GEOMETRIES_CONCEPTS_CHECK_HPP
#define BOOST_GEOMETRY_EXTENSIONS_ALGEBRA_GEOMETRIES_CONCEPTS_CHECK_HPP


#include <boost/geometry/extensions/algebra/core/tags.hpp>
#include <boost/geometry/extensions/algebra/geometries/concepts/matrix_concept.hpp>
#include <boost/geometry/extensions/algebra/geometries/concepts/quaternion_concept.hpp>
#include <boost/geometry/extensions/algebra/geometries/concepts/rotation_matrix_concept.hpp>
#include <boost/geometry/extensions/algebra/geometries/concepts/rotation_quaternion_concept.hpp>
#include <boost/geometry/extensions/algebra/geometries/concepts/vector_concept.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template <typename Geometry>
struct check<Geometry, vector_tag, true>
    : detail::concept_check::check<concepts::ConstVector<Geometry> >
{};

template <typename Geometry>
struct check<Geometry, vector_tag, false>
    : detail::concept_check::check<concepts::Vector<Geometry> >
{};

template <typename Geometry>
struct check<Geometry, rotation_quaternion_tag, true>
    : detail::concept_check::check<concepts::ConstRotationQuaternion<Geometry> >
{};

template <typename Geometry>
struct check<Geometry, rotation_quaternion_tag, false>
    : detail::concept_check::check<concepts::RotationQuaternion<Geometry> >
{};

template <typename Geometry>
struct check<Geometry, rotation_matrix_tag, true>
    : detail::concept_check::check<concepts::ConstRotationMatrix<Geometry> >
{};

template <typename Geometry>
struct check<Geometry, rotation_matrix_tag, false>
    : detail::concept_check::check<concepts::RotationMatrix<Geometry> >
{};

} // namespace dispatch
#endif




}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_EXTENSIONS_ALGEBRA_GEOMETRIES_CONCEPTS_CHECK_HPP
