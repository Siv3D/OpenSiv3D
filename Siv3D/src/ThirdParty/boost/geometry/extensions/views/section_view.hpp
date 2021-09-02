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

#ifndef BOOST_GEOMETRY_VIEWS_SECTION_VIEW_HPP
#define BOOST_GEOMETRY_VIEWS_SECTION_VIEW_HPP

// Note the addition of this whole file was committed to SVN by accident,
// probably obsolete

#include <boost/range/iterator.hpp>

#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/util/type_traits.hpp>


namespace boost { namespace geometry
{


template <typename Geometry, typename Section>
class section_view
{
    typedef typename detail::range_type<Geometry>::type range_type;
public :
    typedef typename boost::range_iterator
        <
            range_type
        >::type iterator;
    typedef typename boost::range_iterator
        <
            range_type const
        >::type const_iterator;

    explicit section_view(Geometry& geometry, Section const& section)
    {
        get_section(geometry, section, m_begin, m_end);
    }

    const_iterator begin() const { return m_begin; }
    const_iterator end() const { return m_end; }
    iterator begin() { return m_begin; }
    iterator end() { return m_end; }

private :
    // Might be replaced declaring as BOOST_AUTO
    typedef typename boost::range_iterator
        <
            detail::transcribe_const_t<Geometry, range_type>
        >::type iterator_type;

    iterator_type m_begin, m_end;
};



}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_VIEWS_SECTION_VIEW_HPP
