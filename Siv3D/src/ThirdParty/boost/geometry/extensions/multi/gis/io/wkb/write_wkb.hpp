// Boost.Geometry
//
// Copyright (c) 2015 Mats Taraldsvik.
//
// This file was modified by Oracle on 2020.
// Modifications copyright (c) 2020, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_MULTI_IO_WKB_WRITE_WKB_HPP
#define BOOST_GEOMETRY_MULTI_IO_WKB_WRITE_WKB_HPP

#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/extensions/multi/gis/io/wkb/detail/writer.hpp>
#include <boost/geometry/extensions/gis/io/wkb/write_wkb.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template <typename Geometry>
struct write_wkb<multi_point_tag, Geometry>
{
    template <typename OutputIterator>
    static inline bool write(const Geometry& geometry, OutputIterator iter,
                       detail::wkb::byte_order_type::enum_t byte_order)
    {
        return detail::wkb::multipoint_writer<Geometry>::write(geometry, iter, byte_order);
    }
};

template <typename Geometry>
struct write_wkb<multi_linestring_tag, Geometry>
{
    template <typename OutputIterator>
    static inline bool write(const Geometry& geometry, OutputIterator iter,
                       detail::wkb::byte_order_type::enum_t byte_order)
    {
        return detail::wkb::multilinestring_writer<Geometry>::write(geometry, iter, byte_order);
    }
};

template <typename Geometry>
struct write_wkb<multi_polygon_tag, Geometry>
{
    template <typename OutputIterator>
    static inline bool write(const Geometry& geometry, OutputIterator iter,
                       detail::wkb::byte_order_type::enum_t byte_order)
    {
        return detail::wkb::multipolygon_writer<Geometry>::write(geometry, iter, byte_order);
    }
};

} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

}} // namespace boost::geometry
#endif // BOOST_GEOMETRY_MULTI_IO_WKB_WRITE_WKB_HPP
