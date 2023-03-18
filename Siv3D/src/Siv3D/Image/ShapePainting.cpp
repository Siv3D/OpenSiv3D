//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <cfloat>
# include <climits>
# include <Siv3D/2DShapes.hpp>
# include <Siv3D/LineString.hpp>
# include "ShapePainting.hpp"

namespace s3d
{
	/*M///////////////////////////////////////////////////////////////////////////////////////
	//
	//  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
	//
	//  By downloading, copying, installing or using the software you agree to this license.
	//  If you do not agree to this license, do not download, install,
	//  copy or use the software.
	//
	//
	//                        Intel License Agreement
	//                For Open Source Computer Vision Library
	//
	// Copyright (C) 2000, Intel Corporation, all rights reserved.
	// Third party copyrights are property of their respective owners.
	//
	// Redistribution and use in source and binary forms, with or without modification,
	// are permitted provided that the following conditions are met:
	//
	//   * Redistribution's of source code must retain the above copyright notice,
	//     this list of conditions and the following disclaimer.
	//
	//   * Redistribution's in binary form must reproduce the above copyright notice,
	//     this list of conditions and the following disclaimer in the documentation
	//     and/or other materials provided with the distribution.
	//
	//   * The name of Intel Corporation may not be used to endorse or promote products
	//     derived from this software without specific prior written permission.
	//
	// This software is provided by the copyright holders and contributors "as is" and
	// any express or implied warranties, including, but not limited to, the implied
	// warranties of merchantability and fitness for a particular purpose are disclaimed.
	// In no event shall the Intel Corporation or contributors be liable for any direct,
	// indirect, incidental, special, exemplary, or consequential damages
	// (including, but not limited to, procurement of substitute goods or services;
	// loss of use, data, or profits; or business interruption) however caused
	// and on any theory of liability, whether in contract, strict liability,
	// or tort (including negligence or otherwise) arising in any way out of
	// the use of this software, even if advised of the possibility of such damage.
	//
	//M*/
	constexpr int32 XY_SHIFT = 16;
	constexpr int32 XY_ONE = 1 << XY_SHIFT;

	inline int cvRound2(double value)
	{
#if ((defined _MSC_VER && defined _M_X64) || (defined __GNUC__ && defined __x86_64__ \
    && defined __SSE2__ && !defined __APPLE__)) && !defined(__CUDACC__)
		__m128d t = _mm_set_sd(value);
		return _mm_cvtsd_si32(t);
#elif defined _MSC_VER && defined _M_IX86
		int t;
		__asm
		{
			fld value;
			fistp t;
		}
		return t;
#else
		/* it's ok if round does not comply with IEEE754 standard;
		the tests should allow +/-1 difference when the tested functions use round */
		return (int)(value + (value >= 0 ? 0.5 : -0.5));
#endif
	}

	void PutLine(Array<unsigned>& pBuffer, unsigned index, int xl, int xr)
	{
		const unsigned beg = index + xl;
		const unsigned end = index + xr;

		for (unsigned i = beg; i <= end; ++i)
		{
			pBuffer.push_back(i);
		}
	}

	bool ClipLine(Point img_size, Point& pt1, Point& pt2)
	{
		int64 x1, y1, x2, y2;
		int c1, c2;
		int64 right = img_size.x - 1, bottom = img_size.y - 1;

		if (img_size.x <= 0 || img_size.y <= 0)
			return false;

		x1 = pt1.x; y1 = pt1.y; x2 = pt2.x; y2 = pt2.y;
		c1 = (x1 < 0) + (x1 > right) * 2 + (y1 < 0) * 4 + (y1 > bottom) * 8;
		c2 = (x2 < 0) + (x2 > right) * 2 + (y2 < 0) * 4 + (y2 > bottom) * 8;

		if ((c1 & c2) == 0 && (c1 | c2) != 0)
		{
			int64 a;
			if (c1 & 12)
			{
				a = c1 < 8 ? 0 : bottom;
				x1 += (a - y1) * (x2 - x1) / (y2 - y1);
				y1 = a;
				c1 = (x1 < 0) + (x1 > right) * 2;
			}
			if (c2 & 12)
			{
				a = c2 < 8 ? 0 : bottom;
				x2 += (a - y2) * (x2 - x1) / (y2 - y1);
				y2 = a;
				c2 = (x2 < 0) + (x2 > right) * 2;
			}
			if ((c1 & c2) == 0 && (c1 | c2) != 0)
			{
				if (c1)
				{
					a = c1 == 1 ? 0 : right;
					y1 += (a - x1) * (y2 - y1) / (x2 - x1);
					x1 = a;
					c1 = 0;
				}
				if (c2)
				{
					a = c2 == 1 ? 0 : right;
					y2 += (a - x2) * (y2 - y1) / (x2 - x1);
					x2 = a;
					c2 = 0;
				}
			}

			assert((c1 & c2) != 0 || (x1 | y1 | x2 | y2) >= 0);

			pt1.x = (int)x1;
			pt1.y = (int)y1;
			pt2.x = (int)x2;
			pt2.y = (int)y2;
		}

		return (c1 | c2) == 0;
	}

	void WriteCircle(Array<unsigned>& pBuffer, const int width, const int height, Point center, int radius)
	{
		unsigned index = 0;
		int err = 0, dx = radius, dy = 0, plus = 1, minus = (radius << 1) - 1;
		int inside = center.x >= radius && center.x < width - radius &&
			center.y >= radius && center.y < height - radius;

		while (dx >= dy)
		{
			int mask;
			int y11 = center.y - dy, y12 = center.y + dy, y21 = center.y - dx, y22 = center.y + dx;
			int x11 = center.x - dx, x12 = center.x + dx, x21 = center.x - dy, x22 = center.x + dy;

			if (inside)
			{
				unsigned t0 = index + y11 * width;
				unsigned t1 = index + y12 * width;

				PutLine(pBuffer, t0, x11, x12);
				PutLine(pBuffer, t1, x11, x12);

				t0 = index + y21 * width;
				t1 = index + y22 * width;

				PutLine(pBuffer, t0, x21, x22);
				PutLine(pBuffer, t1, x21, x22);
			}
			else if (x11 < width && x12 >= 0 && y21 < height && y22 >= 0)
			{
				x11 = Max(x11, 0);
				x12 = Min(x12, width - 1);

				if ((unsigned)y11 < (unsigned)height)
				{
					unsigned t0 = index + y11 * width;
					PutLine(pBuffer, t0, x11, x12);
				}

				if ((unsigned)y12 < (unsigned)height)
				{
					unsigned t0 = index + y12 * width;
					PutLine(pBuffer, t0, x11, x12);
				}

				if (x21 < width && x22 >= 0)
				{
					x21 = Max(x21, 0);
					x22 = Min(x22, width - 1);

					if ((unsigned)y21 < (unsigned)height)
					{
						unsigned t0 = index + y21 * width;
						PutLine(pBuffer, t0, x21, x22);
					}

					if ((unsigned)y22 < (unsigned)height)
					{
						unsigned t0 = index + y22 * width;
						PutLine(pBuffer, t0, x21, x22);
					}
				}
			}
			dy++;
			err += plus;
			plus += 2;

			mask = (err <= 0) - 1;

			err -= minus & mask;
			dx += mask;
			minus -= mask & 2;
		}
	}

	void PutPoint(Array<unsigned>& pBuffer, int x, int y, int width, int height)
	{
		if (0 <= x && x < width && 0 <= y && y < height)
		{
			pBuffer.push_back(y*width + x);
		}
	}

	void Line2(Array<unsigned>& pBuffer, Point pt1, Point pt2, int width, int height)
	{
		int ecount;
		int x_step, y_step;
		Point sizeScaled(width*XY_ONE, height*XY_ONE);

		if (!ClipLine(sizeScaled, pt1, pt2))
			return;

		int dx = pt2.x - pt1.x;
		int dy = pt2.y - pt1.y;

		int j = dx < 0 ? -1 : 0;
		int ax = (dx ^ j) - j;
		int i = dy < 0 ? -1 : 0;
		int ay = (dy ^ i) - i;

		if (ax > ay)
		{
			dx = ax;
			dy = (dy ^ j) - j;
			pt1.x ^= pt2.x & j;
			pt2.x ^= pt1.x & j;
			pt1.x ^= pt2.x & j;
			pt1.y ^= pt2.y & j;
			pt2.y ^= pt1.y & j;
			pt1.y ^= pt2.y & j;

			x_step = XY_ONE;
			y_step = (int)(((int64)dy << XY_SHIFT) / (ax | 1));
			ecount = (pt2.x - pt1.x) >> XY_SHIFT;
		}
		else
		{
			dy = ay;
			dx = (dx ^ i) - i;
			pt1.x ^= pt2.x & i;
			pt2.x ^= pt1.x & i;
			pt1.x ^= pt2.x & i;
			pt1.y ^= pt2.y & i;
			pt2.y ^= pt1.y & i;
			pt1.y ^= pt2.y & i;

			x_step = (int)(((int64)dx << XY_SHIFT) / (ay | 1));
			y_step = XY_ONE;
			ecount = (pt2.y - pt1.y) >> XY_SHIFT;
		}

		pt1.x += (XY_ONE >> 1);
		pt1.y += (XY_ONE >> 1);

		{
			PutPoint(pBuffer, (pt2.x + (XY_ONE >> 1)) >> XY_SHIFT, (pt2.y + (XY_ONE >> 1)) >> XY_SHIFT, width, height);

			if (ax > ay)
			{
				pt1.x >>= XY_SHIFT;

				while (ecount >= 0)
				{
					PutPoint(pBuffer, pt1.x, pt1.y >> XY_SHIFT, width, height);
					pt1.x++;
					pt1.y += y_step;
					ecount--;
				}
			}
			else
			{
				pt1.y >>= XY_SHIFT;

				while (ecount >= 0)
				{
					PutPoint(pBuffer, pt1.x >> XY_SHIFT, pt1.y, width, height);
					pt1.x += x_step;
					pt1.y++;
					ecount--;
				}
			}
		}
	}

	void FillConvexPoly(Array<unsigned>& pBuffer, const int width, const int height, const Point* v, int npts, int shift)
	{
		struct
		{
			int idx, di;
			int x, dx, ye;
		}
		edge[2];

		int delta = shift ? 1 << (shift - 1) : 0;
		int i, y, imin = 0, left = 0, right = 1, x1, x2;
		int edges = 4;
		int xmin, xmax, ymin, ymax;

		Point size(width, height);
		Point p0;
		int delta1, delta2;

		delta1 = delta2 = XY_ONE >> 1;

		p0 = v[npts - 1];
		p0.x <<= XY_SHIFT - shift;
		p0.y <<= XY_SHIFT - shift;

		//assert(0 <= shift && shift <= XY_SHIFT);
		xmin = xmax = v[0].x;
		ymin = ymax = v[0].y;

		for (i = 0; i < npts; i++)
		{
			Point p = v[i];
			if (p.y < ymin)
			{
				ymin = p.y;
				imin = i;
			}

			ymax = Max(ymax, p.y);
			xmax = Max(xmax, p.x);
			xmin = Min(xmin, p.x);

			p.x <<= XY_SHIFT - shift;
			p.y <<= XY_SHIFT - shift;

			Line2(pBuffer, p0, p, width, height);

			p0 = p;
		}

		xmin = (xmin + delta) >> shift;
		xmax = (xmax + delta) >> shift;
		ymin = (ymin + delta) >> shift;
		ymax = (ymax + delta) >> shift;

		if (npts < 3 || xmax < 0 || ymax < 0 || xmin >= size.x || ymin >= size.y)
			return;

		ymax = Min(ymax, size.y - 1);
		edge[0].idx = edge[1].idx = imin;

		edge[0].ye = edge[1].ye = y = ymin;
		edge[0].di = 1;
		edge[1].di = npts - 1;

		unsigned index = width * y;

		do
		{
			for (i = 0; i < 2; i++)
			{
				if (y >= edge[i].ye)
				{
					int idx = edge[i].idx, di = edge[i].di;
					int xs = 0, xe, ye, ty = 0;

					for (;;)
					{
						ty = (v[idx].y + delta) >> shift;
						if (ty > y || edges == 0)
							break;
						xs = v[idx].x;
						idx += di;
						idx -= ((idx < npts) - 1) & npts; /* idx -= idx >= npts ? npts : 0 */
						edges--;
					}

					ye = ty;
					xs <<= XY_SHIFT - shift;
					xe = v[idx].x << (XY_SHIFT - shift);

					/* no more edges */
					if (y >= ye)
						return;

					edge[i].ye = ye;
					edge[i].dx = ((xe - xs) * 2 + (ye - y)) / (2 * (ye - y));
					edge[i].x = xs;
					edge[i].idx = idx;
				}
			}

			if (edge[left].x > edge[right].x)
			{
				left ^= 1;
				right ^= 1;
			}

			x1 = edge[left].x;
			x2 = edge[right].x;

			if (y >= 0)
			{
				int xx1 = (x1 + delta1) >> XY_SHIFT;
				int xx2 = (x2 + delta2) >> XY_SHIFT;

				if (xx2 >= 0 && xx1 < size.x)
				{
					if (xx1 < 0)
						xx1 = 0;
					if (xx2 >= size.x)
						xx2 = size.x - 1;

					PutLine(pBuffer, index, xx1, xx2);
				}
			}

			x1 += edge[left].dx;
			x2 += edge[right].dx;

			edge[left].x = x1;
			edge[right].x = x2;
			index += width;

		} while (++y <= ymax);
	}


	class LineIteratorX
	{
	public:

		LineIteratorX(int width, int height, Point pt1, Point pt2)
		{
			count = -1;

			if ((unsigned)pt1.x >= (unsigned)(width) ||
				(unsigned)pt2.x >= (unsigned)(width) ||
				(unsigned)pt1.y >= (unsigned)(height) ||
				(unsigned)pt2.y >= (unsigned)(height))
			{
				if (!ClipLine(Point(width, height), pt1, pt2))
				{
					m_index = 0;
					err = plusDelta = minusDelta = plusStep = minusStep = count = 0;
					return;
				}
			}

			int bt_pix0 = 4, bt_pix = bt_pix0;
			size_t istep = width * 4;

			int dx = pt2.x - pt1.x;
			int dy = pt2.y - pt1.y;
			int s = dx < 0 ? -1 : 0;

			{
				dx = (dx ^ s) - s;
				dy = (dy ^ s) - s;
				pt1.x ^= (pt1.x ^ pt2.x) & s;
				pt1.y ^= (pt1.y ^ pt2.y) & s;
			}

			m_index = pt1.y * width + pt1.x;

			s = dy < 0 ? -1 : 0;
			dy = (dy ^ s) - s;
			istep = (istep ^ s) - s;

			s = dy > dx ? -1 : 0;

			/* conditional swaps */
			dx ^= dy & s;
			dy ^= dx & s;
			dx ^= dy & s;

			bt_pix ^= istep & s;
			istep ^= bt_pix & s;
			bt_pix ^= istep & s;

			{
				//assert(dx >= 0 && dy >= 0);
				err = dx - (dy + dy);
				plusDelta = dx + dx;
				minusDelta = -(dy + dy);
				plusStep = (int)istep;
				minusStep = bt_pix;
				count = dx + 1;
			}
		}

		LineIteratorX& operator ++()
		{
			const int mask = err < 0 ? -1 : 0;
			err += minusDelta + (plusDelta & mask);
			m_index += (minusStep + (plusStep & mask)) / 4;
			return *this;
		}

		unsigned index() const
		{
			return m_index;
		}

		unsigned m_index = 0;
		int err, count;
		int minusDelta, plusDelta;
		int minusStep, plusStep;
	};


	void WriteLine(Array<unsigned>& pBuffer, int width, int height, Point pt1, Point pt2)
	{
		LineIteratorX iterator(width, height, pt1, pt2);
		const int count = iterator.count;

		for (int i = 0; i < count; i++, ++iterator)
		{
			pBuffer.push_back(iterator.index());
		}
	}

	void ThickLine(Array<unsigned>& pBuffer, const int width, const int height, Point p0, Point p1, int thickness, int flags)
	{
		static const double INV_XY_ONE = 1. / XY_ONE;
		p0.x <<= XY_SHIFT;
		p0.y <<= XY_SHIFT;
		p1.x <<= XY_SHIFT;
		p1.y <<= XY_SHIFT;

		if (thickness <= 1)
		{
			p0.x = (p0.x + (XY_ONE >> 1)) >> XY_SHIFT;
			p0.y = (p0.y + (XY_ONE >> 1)) >> XY_SHIFT;
			p1.x = (p1.x + (XY_ONE >> 1)) >> XY_SHIFT;
			p1.y = (p1.y + (XY_ONE >> 1)) >> XY_SHIFT;
			WriteLine(pBuffer, width, height, p0, p1); // OK
		}
		else
		{
			Point pt[4];
			double dx = (p0.x - p1.x)*INV_XY_ONE, dy = (p1.y - p0.y)*INV_XY_ONE;
			double r = dx * dx + dy * dy;
			int i, oddThickness = thickness & 1;
			thickness <<= XY_SHIFT - 1;

			if (fabs(r) > DBL_EPSILON)
			{
				Point dp{ 0, 0 };
				r = (thickness + static_cast<double>(oddThickness) * XY_ONE * 0.5) / std::sqrt(r);
				dp.x = cvRound2(dy * r);
				dp.y = cvRound2(dx * r);

				pt[0].x = p0.x + dp.x;
				pt[0].y = p0.y + dp.y;
				pt[1].x = p0.x - dp.x;
				pt[1].y = p0.y - dp.y;
				pt[2].x = p1.x - dp.x;
				pt[2].y = p1.y - dp.y;
				pt[3].x = p1.x + dp.x;
				pt[3].y = p1.y + dp.y;

				FillConvexPoly(pBuffer, width, height, pt, 4, XY_SHIFT); // OK
			}

			for (i = 0; i < 2; i++)
			{
				if (flags & (i + 1))
				{
					Point center;
					center.x = (p0.x + (XY_ONE >> 1)) >> XY_SHIFT;
					center.y = (p0.y + (XY_ONE >> 1)) >> XY_SHIFT;
					WriteCircle(pBuffer, width, height, center, (thickness + (XY_ONE >> 1)) >> XY_SHIFT);
				}

				p0 = p1;
			}
		}
	}

	void PolyLine(Array<unsigned>& pBuffer, const int width, const int height, const Array<Point>& v, int thickness)
	{
		if (v.empty())
			return;

		int flags = 3;

		Point p0 = v[0];

		for (size_t i = 1; i < v.size(); ++i)
		{
			Point p = v[i];

			ThickLine(pBuffer, width, height, p0, p, thickness, flags);

			p0 = p;

			flags = 2;
		}

		std::sort(pBuffer.begin(), pBuffer.end());

		pBuffer.erase(std::unique(pBuffer.begin(), pBuffer.end()), pBuffer.end());
	}

	struct PolyEdge
	{
		PolyEdge() : y0(0), y1(0), x(0), dx(0), next(0) {}
		int y0, y1;
		int x, dx;
		PolyEdge *next;
	};

	static void CollectPolyEdges(Array<unsigned>& pBuffer, const Point* v, int count, Array<PolyEdge>& edges, int width, int height)
	{
		const Point offset(0, 0);
		const int shift = 0;

		int i, delta = offset.y;
		Point pt0 = v[count - 1], pt1;
		pt0.x = (pt0.x + offset.x) << (XY_SHIFT - shift);
		pt0.y = (pt0.y + delta) >> shift;

		edges.reserve(edges.size() + count);

		for (i = 0; i < count; i++, pt0 = pt1)
		{
			Point t0, t1;
			PolyEdge edge;

			pt1 = v[i];
			pt1.x = (pt1.x + offset.x) << (XY_SHIFT - shift);
			pt1.y = (pt1.y + delta) >> shift;

			t0.y = pt0.y; t1.y = pt1.y;
			t0.x = (pt0.x + (XY_ONE >> 1)) >> XY_SHIFT;
			t1.x = (pt1.x + (XY_ONE >> 1)) >> XY_SHIFT;
			//Line(img, t0, t1, color, line_type);
			WriteLine(pBuffer, width, height, t0, t1);

			if (pt0.y == pt1.y)
				continue;

			if (pt0.y < pt1.y)
			{
				edge.y0 = pt0.y;
				edge.y1 = pt1.y;
				edge.x = pt0.x;
			}
			else
			{
				edge.y0 = pt1.y;
				edge.y1 = pt0.y;
				edge.x = pt1.x;
			}
			edge.dx = (pt1.x - pt0.x) / (pt1.y - pt0.y);
			edges.push_back(edge);
		}
	}

	struct CmpEdges
	{
		bool operator ()(const PolyEdge& e1, const PolyEdge& e2)
		{
			return e1.y0 - e2.y0 ? e1.y0 < e2.y0 :
				e1.x - e2.x ? e1.x < e2.x : e1.dx < e2.dx;
		}
	};

	static void FillEdgeCollection(Array<uint32>& pBuffer, Array<PolyEdge>& edges, int32 width, int32 height)
	{
		PolyEdge tmp;
		int i, y, total = (int)edges.size();
		const Point size(width, height);
		PolyEdge* e;
		int y_max = INT_MIN, x_max = INT_MIN, y_min = INT_MAX, x_min = INT_MAX;

		if (total < 2)
			return;

		for (i = 0; i < total; i++)
		{
			PolyEdge& e1 = edges[i];
			assert(e1.y0 < e1.y1);
			y_min = Min(y_min, e1.y0);
			y_max = Max(y_max, e1.y1);
			x_min = Min(x_min, e1.x);
			x_max = Max(x_max, e1.x);
		}

		if (y_max < 0 || y_min >= size.y || x_max < 0 || x_min >= (size.x << XY_SHIFT))
			return;

		std::sort(edges.begin(), edges.end(), CmpEdges());

		// start drawing
		tmp.y0 = INT_MAX;
		edges.push_back(tmp); // after this point we do not add
							  // any elements to edges, thus we can use pointers
		i = 0;
		tmp.next = 0;
		e = &edges[i];
		y_max = Min(y_max, size.y);

		for (y = e->y0; y < y_max; y++)
		{
			PolyEdge *last, *prelast, *keep_prelast;
			int sort_flag = 0;
			int draw = 0;
			int clipline = y < 0;

			prelast = &tmp;
			last = tmp.next;
			while (last || e->y0 == y)
			{
				if (last && last->y1 == y)
				{
					// exclude edge if y reachs its lower point
					prelast->next = last->next;
					last = last->next;
					continue;
				}
				keep_prelast = prelast;
				if (last && (e->y0 > y || last->x < e->x))
				{
					// go to the next edge in active list
					prelast = last;
					last = last->next;
				}
				else if (i < total)
				{
					// insert new edge into active list if y reachs its upper point
					prelast->next = e;
					e->next = last;
					prelast = e;
					e = &edges[++i];
				}
				else
					break;

				if (draw)
				{
					if (!clipline)
					{
						// convert x's from fixed-point to image coordinates
						//uchar *timg = img.data + y * img.step;
						unsigned index = y * width;
						int x1 = keep_prelast->x;
						int x2 = prelast->x;

						if (x1 > x2)
						{
							int t = x1;

							x1 = x2;
							x2 = t;
						}

						x1 = (x1 + XY_ONE - 1) >> XY_SHIFT;
						x2 = x2 >> XY_SHIFT;

						// clip and draw the line
						if (x1 < size.x && x2 >= 0)
						{
							if (x1 < 0)
								x1 = 0;
							if (x2 >= size.x)
								x2 = size.x - 1;

							PutLine(pBuffer, index, x1, x2);
							//ICV_HLINE(timg, x1, x2, color, pix_size);
						}
					}
					keep_prelast->x += keep_prelast->dx;
					prelast->x += prelast->dx;
				}
				draw ^= 1;
			}

			// sort edges (using bubble sort)
			keep_prelast = 0;

			do
			{
				prelast = &tmp;
				last = tmp.next;

				while (last != keep_prelast && last->next != 0)
				{
					PolyEdge *te = last->next;

					// swap edges
					if (last->x > te->x)
					{
						prelast->next = te;
						last->next = te->next;
						te->next = last;
						prelast = te;
						sort_flag = 1;
					}
					else
					{
						prelast = last;
						last = te;
					}
				}
				keep_prelast = prelast;
			} while (sort_flag && keep_prelast != tmp.next && keep_prelast != &tmp);
		}
	}

	namespace ShapePainting
	{
		void PaintLineString(Array<unsigned>& pBuffer, const LineString& lineString, int width, int height, int thickness, bool isClosed)
		{
			if (lineString.size() == 0)
			{
				return;
			}

			Array<Point> pts;

			for (size_t i = 0; i < lineString.size(); ++i)
			{
				pts.push_back(lineString[i].asPoint());
			}

			if (isClosed)
			{
				pts.push_back(lineString[0].asPoint());
			}

			PolyLine(pBuffer, width, height, pts, thickness);
		}

		void PaintLine(Array<unsigned>& pBuffer, const Line& line, int width, int height, int thickness)
		{
			const Array<Point> pts = { line.begin.asPoint(), line.end.asPoint() };

			PolyLine(pBuffer, width, height, pts, thickness);
		}

		void PaintTriangle(Array<unsigned>& pBuffer, const Triangle& triangle, int width, int height)
		{
			Array<Point> pts =
			{
				triangle.p0.asPoint(),
				triangle.p1.asPoint(),
				triangle.p2.asPoint(),
			};

			FillConvexPoly(pBuffer, width, height, pts.data(), 3, 0);

			std::sort(pBuffer.begin(), pBuffer.end());

			pBuffer.erase(std::unique(pBuffer.begin(), pBuffer.end()), pBuffer.end());
		}

		void PaintQuad(Array<unsigned>& pBuffer, const Quad& quad, int width, int height)
		{
			Array<Point> pts =
			{
				quad.p0.asPoint(),
				quad.p1.asPoint(),
				quad.p2.asPoint(),
				quad.p3.asPoint(),
			};

			FillConvexPoly(pBuffer, width, height, pts.data(), 4, 0);

			std::sort(pBuffer.begin(), pBuffer.end());

			pBuffer.erase(std::unique(pBuffer.begin(), pBuffer.end()), pBuffer.end());
		}

		void PaintPolygon(Array<uint32>& pBuffer, const Array<const Point*>& ptsList, const Array<int32>& npts, int32 width, int32 height)
		{
			const size_t ncontours = ptsList.size();

			Array<PolyEdge> edges;

			size_t total = 0;

			for (size_t i = 0; i < ncontours; ++i)
			{
				total += npts[i];
			}

			edges.reserve(total + 1);

			for (size_t i = 0; i < ncontours; ++i)
			{
				CollectPolyEdges(pBuffer, ptsList[i], npts[i], edges, width, height);
			}

			FillEdgeCollection(pBuffer, edges, width, height);

			std::sort(pBuffer.begin(), pBuffer.end());

			pBuffer.erase(std::unique(pBuffer.begin(), pBuffer.end()), pBuffer.end());
		}
	}
}
