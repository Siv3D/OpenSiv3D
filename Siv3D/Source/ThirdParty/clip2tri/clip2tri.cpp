/*
* clip2tri.h
*
* Authors: kaen, raptor, sam686, watusimoto
*
* Originally from the bitfighter source code
*/

# include "clip2tri.h"
# include "../poly2tri/poly2tri.h"

using namespace p2t;
using namespace ClipperLib;

namespace s3d
{
	static constexpr double CLIPPER_SCALE_FACT = 16777216.0;
	static constexpr double CLIPPER_SCALE_FACT_INVERSE = 1.0 / 16777216.0;

	static Path UpscaleClipperPoints(const Array<Vec2>& inputPolygon)
	{
		Path outputPolygon;
		outputPolygon.resize(inputPolygon.size());

		for (size_t i = 0; i < inputPolygon.size(); i++)
		{
			outputPolygon[i] = IntPoint(int64(inputPolygon[i].x * CLIPPER_SCALE_FACT), int64(inputPolygon[i].y * CLIPPER_SCALE_FACT));
		}

		return outputPolygon;
	}

	static Paths UpscaleClipperPoints(const Array<Array<Vec2>>& inputPolygons)
	{
		Paths outputPolygons;

		outputPolygons.resize(inputPolygons.size());

		for (size_t i = 0; i < inputPolygons.size(); i++)
		{
			outputPolygons[i].resize(inputPolygons[i].size());

			for (size_t j = 0; j < inputPolygons[i].size(); j++)
			{
				outputPolygons[i][j] = IntPoint(int64(inputPolygons[i][j].x * CLIPPER_SCALE_FACT), int64(inputPolygons[i][j].y * CLIPPER_SCALE_FACT));
			}
		}

		return outputPolygons;
	}

	// Use Clipper to merge inputPolygons, placing the result in a Polytree
	// NOTE: this does NOT downscale the Clipper points.  You must do this afterwards
	//
	// Here you add all your non-navigatable objects (e.g. walls, barriers, etc.)
	bool MergePolysToPolyTree(const Array<Array<Vec2>>& inputPolygons, PolyTree& solution)
	{
		Paths input = UpscaleClipperPoints(inputPolygons);

		// Fire up clipper and union!
		Clipper clipper;
		clipper.StrictlySimple(true);

		try  // there is a "throw" in AddPolygon
		{
			clipper.AddPaths(input, ptSubject, true);
		}
		catch (...)
		{
			printf("clipper.AddPaths, something went wrong\n");
		}

		return clipper.Execute(ctUnion, solution, pftNonZero, pftNonZero);
	}

	// Shrink large polygons by reducing each coordinate by 1 in the
	// general direction of the last point as we wind around
	//
	// This normally wouldn't work in every case, but our upscaled-by-1000 polygons
	// have little chance to create new duplicate points with this method.
	//
	// For information on why this was needed, see:
	//
	//    https://code.google.com/p/poly2tri/issues/detail?id=90
	//
	//static void edgeShrink(Path& path)
	//{
	//	size_t prev = path.size() - 1;

	//	for (size_t i = 0; i < path.size(); i++)
	//	{
	//		// Adjust coordinate by 1 depending on the direction
	//		path[i].X - path[prev].X > 0 ? path[i].X-- : path[i].X++;
	//		path[i].Y - path[prev].Y > 0 ? path[i].Y-- : path[i].Y++;

	//		prev = i;
	//	}
	//}

	// This uses poly2tri to triangulate.  poly2tri isn't very robust so clipper needs to do
	// the cleaning of points before getting here.
	//
	// A tree structure of polygons is required for doing complex polygons-within-polygons.
	// For reference discussion on how this started to be developed, see here:
	//
	//    https://code.google.com/p/poly2tri/issues/detail?id=74
	//
	// For assistance with a special case crash, see this utility:
	//    http://javascript.poly2tri.googlecode.com/hg/index.html
	//
	// FIXME: what is ignoreFills and ignoreHoles for?  kaen?
	bool Triangulate(const Array<Array<Vec2>>& inputPolygons, const Array<Vec2>& boundingPolygon, Array<Float2> &vertices, Array<uint32>& indices)
	{
		// Use clipper to clean.  This upscales the floating point input
		PolyTree polyTree;
		MergePolysToPolyTree(inputPolygons, polyTree);

		Path outline = UpscaleClipperPoints(boundingPolygon);

		PolyNode tempNode;
		PolyNode* rootNode = (polyTree.Total() == 0) ? &tempNode : polyTree.GetFirst()->Parent;
		rootNode->Contour = outline;

		Array<p2t::Point> base;

		// Now traverse our polyline nodes and triangulate them with only their children holes
		for (PolyNode *currentNode = rootNode; currentNode != nullptr; currentNode = currentNode->GetNext())
		{
			if (!currentNode->IsHole())
			{
				continue;
			}

			// A Clipper hole is actually what we want to build zones for; they become our bounding
			// polylines.  poly2tri holes are therefore the inverse
			const size_t contourSize = currentNode->Contour.size();

			for (size_t i = 0; i < contourSize; ++i)
			{
				base.emplace_back(static_cast<double>(currentNode->Contour[i].X), static_cast<double>(currentNode->Contour[i].Y));
			}

			size_t holeBaseSize = 0;

			for (const auto& childNode : currentNode->Childs)
			{
				//edgeShrink(childNode->Contour); // Slightly modify the polygon to guarantee no duplicate points

				holeBaseSize += childNode->Contour.size();
			}

			base.reserve(contourSize + holeBaseSize);

			// Build up this polyline in poly2tri's format (downscale Clipper points)
			std::vector<p2t::Point*> polyline(base.size());

			for (size_t i = 0; i < contourSize; ++i)
			{
				polyline[i] = &base[i];
			}

			// Set our polyline in poly2tri
			p2t::CDT cdt(polyline);

			for (const auto& childNode : currentNode->Childs)
			{
				const size_t holeSize = childNode->Contour.size();

				std::vector<p2t::Point*> hole(holeSize);

				for (size_t i = 0; i < holeSize; ++i)
				{
					base.emplace_back(double(childNode->Contour[i].X), double(childNode->Contour[i].Y));

					hole[i] = &base.back();
				}

				cdt.AddHole(hole);
			}

			cdt.Triangulate();

			if (base.isEmpty())
			{
				return false;
			}

			for (const auto& v : base)
			{
				vertices.emplace_back(v.x * CLIPPER_SCALE_FACT_INVERSE, v.y * CLIPPER_SCALE_FACT_INVERSE);
			}

			const size_t num_triangles = cdt.GetTriangles().size();
			indices.resize(num_triangles * 3);
			const auto begin = &base[0];
			uint32* pDstIndex = indices.data();

			for (auto& currentTriangle : cdt.GetTriangles())
			{
				*pDstIndex++ = static_cast<uint32>(currentTriangle->GetPoint(0) - begin);
				*pDstIndex++ = static_cast<uint32>(currentTriangle->GetPoint(1) - begin);
				*pDstIndex++ = static_cast<uint32>(currentTriangle->GetPoint(2) - begin);
			}

			break;
		}

		return true;
	}
}