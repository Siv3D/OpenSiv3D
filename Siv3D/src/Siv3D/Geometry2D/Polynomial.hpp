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

# pragma once
# include <Siv3D/Common.hpp>
# include <Siv3D/PointVector.hpp>
# include <Siv3D/Array.hpp>
# include <Siv3D/Optional.hpp>

//
// "Polynomial.hpp" is based on
// kld-polynomial https://github.com/Quazistax/kld-polynomial
//
//	Copyright(c) 2013, Kevin Lindsey
//	All rights reserved.
//
//	Redistribution and use in source and binary forms, with or without modification,
//	are permitted provided that the following conditions are met :
//
//	Redistributions of source code must retain the above copyright notice, this
//	list of conditions and the following disclaimer.
//
//	Redistributions in binary form must reproduce the above copyright notice, this
//	list of conditions and the following disclaimer in the documentation and/or
//	other materials provided with the distribution.
//
//	Neither the name of the{ organization } nor the names of its
//	contributors may be used to endorse or promote products derived from
//	this software without specific prior written permission.
//
//	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
//	ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
//	WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
//	DISCLAIMED.IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
//	ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
//	(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
//	LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
//	ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
//	SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

namespace s3d
{
	struct Y_DY
	{
		double y;
		double dy;
	};

	struct Bound
	{
		double minX;
		double maxX;
	};

	struct NegXPosX
	{
		double negX;
		double posX;
	};

	struct MaxNearmax
	{
		double max;
		double nearmax;
	};

	class Polynomial
	{
		static constexpr double TOLERANCE = 1e-6;
		static constexpr double ACCURACY = 15;
		static constexpr double LN10 = 2.302585092994046;
		static constexpr double LN2 = 0.6931471805599453;

		Array<double> coefs;
		double _s = 0.0;

		// ok
		static constexpr int32 Sign(const double x)
		{
			return x < 0 ? -1 : x > 0 ? 1 : 0;
		};

		// ok
		static Y_DY Interpolate(const Array<double>& xs, const Array<double>& ys, const int32 n, const int32 offset, const double x)
		{
			double y = 0;
			double dy = 0;
			Array<double> c(n);
			Array<double> d(n);
			int32 ns = 0;
			Y_DY result;

			double diff = std::abs(x - xs[offset]);
			for (int32 i = 0; i < n; ++i) {
				double dift = std::abs(x - xs[offset + i]);

				if (dift < diff) {
					ns = i;
					diff = dift;
				}
				c[i] = d[i] = ys[offset + i];
			}
			y = ys[offset + ns];
			ns--;

			for (int32 m = 1; m < n; m++) {
				for (int32 i = 0; i < n - m; ++i) {
					double ho = xs[offset + i] - x;
					double hp = xs[offset + i + m] - x;
					double w = c[i + 1] - d[i];
					double den = ho - hp;

					if (den == 0.0) {
						result = { 0, 0 };
						break;
					}

					den = w / den;
					d[i] = hp*den;
					c[i] = ho*den;
				}
				dy = (2 * (ns + 1) < (n - m)) ? c[ns + 1] : d[ns--];
				y += dy;
			}

			return { y, dy };
		}

	public:

		Polynomial() = default;

		Polynomial(Array<double> _coefs)
			: coefs(_coefs.reversed()) {}

		// ok
		double eval(const double x) const
		{
			assert(!std::isnan(x));

			double result = 0;

			for (int32 i = static_cast<int32>(this->coefs.size()) - 1; i >= 0; i--)
			{
				result = result * x + this->coefs[i];
			}

			return result;
		}

		//Polynomial add(Polynomial that) const
		//{
		//	Polynomial result;
		//	int32 d1 = this->getDegree();
		//	int32 d2 = that.getDegree();
		//	int32 dmax = std::max(d1, d2);

		//	for (int32 i = 0; i <= dmax; ++i) {
		//		double v1 = (i <= d1) ? this->coefs[i] : 0;
		//		double v2 = (i <= d2) ? that.coefs[i] : 0;

		//		result.coefs.push_back(v1 + v2);
		//	}

		//	return result;
		//}

		//Polynomial multiply(Polynomial that) const
		//{
		//	Polynomial result;

		//	for (int32 i = 0; i <= this->getDegree() + that.getDegree(); ++i)
		//		result.coefs.push_back(0);

		//	for (int32 i = 0; i <= this->getDegree(); ++i)
		//		for (int32 j = 0; j <= that.getDegree(); ++j)
		//			result.coefs[i + j] += this->coefs[i] * that.coefs[j];

		//	return result;
		//}

		// ok
		Polynomial& divide_scalar(const double scalar)
		{
			for (size_t i = 0; i < this->coefs.size(); ++i)
				this->coefs[i] /= scalar;

			return *this;
		}

		// ok
		Polynomial& simplify()
		{
			const double _TOLERANCE = 1e-15;
			for (int32 i = this->getDegree(); i >= 0; i--)
			{
				if (std::abs(this->coefs[i]) <= _TOLERANCE)
				{
					this->coefs.pop_back();

					//Log << L"pop_back";
				}
				else
				{
					break;
				}
			}

			return *this;
		}

		// ok
		Optional<double> bisection(double min, double max) const
		{
			double minValue = this->eval(min);
			double maxValue = this->eval(max);
			Optional<double> result;

			if (std::abs(minValue) <= TOLERANCE)
			{
				result = min;
			}
			else if (std::abs(maxValue) <= TOLERANCE)
			{
				result = max;
			}
			else if (minValue * maxValue <= 0)
			{
				const double tmp1 = std::log(max - min);
				const double tmp2 = LN10 * ACCURACY;
				const double iters = std::ceil((tmp1 + tmp2) / LN2);

				for (int32 i = 0; i < iters; ++i)
				{
					result = 0.5 * (min + max);
					const double value = this->eval(result.value());

					if (std::abs(value) <= TOLERANCE)
					{
						break;
					}

					if (value * minValue < 0)
					{
						max = result.value();
						maxValue = value;
					}
					else
					{
						min = result.value();
						minValue = value;
					}
				}
			}

			//if (!result)
			//{
			//	Log << L"bisection none";
			//}

			return result;
		}

		// ok
		double trapezoid(const double min, const double max, const int32 n)
		{
			assert(!std::isnan(min) && !std::isnan(max));

			const double range = max - min;

			if (n == 1)
			{
				const double minValue = this->eval(min);
				const double maxValue = this->eval(max);
				this->_s = 0.5*range*(minValue + maxValue);
			}
			else
			{
				const int32 it = 1 << (n - 2);
				const double delta = range / it;
				double x = min + 0.5*delta;
				double sum = 0;

				for (int32 i = 0; i < it; ++i)
				{
					sum += this->eval(x);
					x += delta;
				}

				this->_s = 0.5*(this->_s + range*sum / it);
			}

			return this->_s;
		}

		//double simpson(double min, double max) const
		//{
		//	double range = max - min;
		//	double st = 0.5 * range * (this->eval(min) + this->eval(max));
		//	double t = st;
		//	double s = 4.0*st / 3.0;
		//	double os = s;
		//	double ost = st;
		//	double _TOLERANCE = 1e-7;

		//	int32 it = 1;
		//	for (int32 n = 2; n <= 20; n++) {
		//		double delta = range / it;
		//		double x = min + 0.5*delta;
		//		double sum = 0;

		//		for (int32 i = 1; i <= it; ++i) {
		//			sum += this->eval(x);
		//			x += delta;
		//		}

		//		t = 0.5 * (t + range * sum / it);
		//		st = t;
		//		s = (4.0*st - ost) / 3.0;

		//		if (std::abs(s - os) < _TOLERANCE*std::abs(os))
		//			break;

		//		os = s;
		//		ost = st;
		//		it <<= 1;
		//	}

		//	return s;
		//}

		//double romberg(double min, double max)
		//{
		//	int32 MAX = 20;
		//	int32 K = 3;
		//	double _TOLERANCE = 1e-6;
		//	Array<double> s = Array<double>(MAX + 1);
		//	Array<double> h = Array<double>(MAX + 1);
		//	Y_DY result = { 0, 0 };

		//	h[0] = 1.0;
		//	for (int32 j = 1; j <= MAX; ++j) {
		//		s[j - 1] = this->trapezoid(min, max, j);
		//		if (j >= K) {
		//			result = Polynomial::Interpolate(h, s, K, j - K, 0.0);
		//			if (std::abs(result.dy) <= _TOLERANCE*result.y) break;
		//		}
		//		s[j] = s[j - 1];
		//		h[j] = 0.25 * h[j - 1];
		//	}

		//	return result.y;
		//}

		// ok
		int32 getDegree() const
		{
			return static_cast<int32>(this->coefs.size()) - 1;
		}

		// ok
		Polynomial getDerivative() const
		{
			Polynomial derivative;

			for (size_t i = 1; i < this->coefs.size(); ++i)
			{
				derivative.coefs.push_back(i * this->coefs[i]);
			}

			return derivative;
		}

		// ok
		auto getRoots()
		{
			Array<double> result;

			this->simplify();

			//Log << L"getDegree: " << this->getDegree();

			switch (this->getDegree()) {
			case 0: result = Array<double>();             break;
			case 1: result = this->getLinearRoot();     break;
			case 2: result = this->getQuadraticRoots(); break;
			case 3: result = this->getCubicRoots();     break;
			case 4: result = this->getQuarticRoots();   break;
			default:
				result = Array<double>();
				// should try Newton's method and/or bisection
			}

			return result;
		}

		// ok
		Array<double> getRootsInInterval(const double min, const double max) const
		{
			Array<double> roots;
			Optional<double> root;

			if (this->getDegree() == 1)
			{
				root = this->bisection(min, max);
				
				if (root)
				{
					roots.push_back(*root);
				}
			}
			else
			{
				// get roots of derivative
				const Polynomial deriv = this->getDerivative();
				const Array<double> droots = deriv.getRootsInInterval(min, max);

				if (droots.size() > 0)
				{
					// find root on [min, droots[0]]
					root = this->bisection(min, droots[0]);

					if (root)
					{
						roots.push_back(*root);
					}

					// find root on [droots[i],droots[i+1]] for 0 <= i <= count-2
					for (int32 i = 0; i <= static_cast<int32>(droots.size()) - 2; ++i)
					{
						root = this->bisection(droots[i], droots[i + 1]);

						if (root)
						{
							roots.push_back(*root);
						}
					}

					// find root on [droots[count-1],xmax]
					root = this->bisection(droots[droots.size() - 1], max);
					
					if (root)
					{
						roots.push_back(*root);
					}
				}
				else
				{
					// polynomial is monotone on [min,max], has at most one root
					root = this->bisection(min, max);

					if (root)
					{
						roots.push_back(*root);
					}
				}
			}

			return roots;
		}

		// ok
		Array<double> getLinearRoot() const
		{
			Array<double> result;
			const double a = this->coefs[1];

			if (a != 0)
			{
				result.push_back(-this->coefs[0] / a);
			}

			return result;
		}

		// ok
		Array<double> getQuadraticRoots() const
		{
			Array<double> results;

			if (this->getDegree() == 2)
			{
				const double a = this->coefs[2];
				const double b = this->coefs[1] / a;
				const double c = this->coefs[0] / a;
				const double d = b*b - 4 * c;

				if (d > 0)
				{
					const double e = std::sqrt(d);
					results.push_back(0.5 * (-b + e));
					results.push_back(0.5 * (-b - e));
				}
				else if (d == 0)
				{
					// really two roots with same value, but we only return one
					results.push_back(0.5 * -b);
				}
			}

			return results;
		}

		// ok
		Array<double> getCubicRoots() const
		{
			Array<double> results;

			if (this->getDegree() == 3)
			{
				const double c3 = this->coefs[3];
				const double c2 = this->coefs[2] / c3;
				const double c1 = this->coefs[1] / c3;
				const double c0 = this->coefs[0] / c3;

				const double a = (3 * c1 - c2*c2) / 3;
				const double b = (2 * c2*c2*c2 - 9 * c1*c2 + 27 * c0) / 27;
				const double offset = c2 / 3;
				double discrim = b*b / 4 + a*a*a / 27;
				const double halfB = b / 2;

				const double ZEROepsilon = this->zeroErrorEstimate(none);	
				if (std::abs(discrim) <= ZEROepsilon)
				{
					discrim = 0;
				}

				if (discrim > 0)
				{
					const double e = std::sqrt(discrim);
					double root;

					double tmp = -halfB + e;
					if (tmp >= 0)
						root = std::pow(tmp, 1 / 3.0);
					else
						root = -std::pow(-tmp, 1 / 3.0);

					tmp = -halfB - e;
					if (tmp >= 0)
						root += std::pow(tmp, 1 / 3.0);
					else
						root -= std::pow(-tmp, 1 / 3.0);

					results.push_back(root - offset);
				}
				else if (discrim < 0)
				{
					const double distance = std::sqrt(-a / 3.0);
					const double angle = std::atan2(std::sqrt(-discrim), -halfB) / 3.0;
					const double cos = std::cos(angle);
					const double sin = std::sin(angle);
					const double sqrt3 = std::sqrt(3);

					results.push_back(2 * distance*cos - offset);
					results.push_back(-distance * (cos + sqrt3 * sin) - offset);
					results.push_back(-distance * (cos - sqrt3 * sin) - offset);
				}
				else
				{
					double tmp;

					if (halfB >= 0)
						tmp = -std::pow(halfB, 1 / 3.0);
					else
						tmp = std::pow(-halfB, 1 / 3.0);

					results.push_back(2 * tmp - offset);
					// really should return next root twice, but we return only one
					results.push_back(-tmp - offset);
				}
			}

			return results;
		};

		// ok
		Array<double> getQuarticRoots() const
		{
			Array<double> results;

			int32 n = this->getDegree();
			
			if (n == 4)
			{
				Polynomial poly;
				poly.coefs = this->coefs;
				poly.divide_scalar(poly.coefs[n]);

				const double ERRF = 1e-15;
				if (std::abs(poly.coefs[0]) < 10 * ERRF * std::abs(poly.coefs[3]))
				{
					poly.coefs[0] = 0;
				}

				Polynomial poly_d = poly.getDerivative();
				const Array<double> derrt = poly_d.getRoots().sort_by([](double a, double b) { return a < b; });
		
				const int32 nr = static_cast<int32>(derrt.size()) - 1;
				
				const Bound rb = this->bounds();
				const double maxabsX = std::max(std::abs(rb.minX), std::abs(rb.maxX));
				const double ZEROepsilon = this->zeroErrorEstimate(maxabsX);

				Array<double> dery;

				for (int32 i = 0; i <= nr; ++i)
				{
					dery.push_back(poly.eval(derrt[i]));
				}

				for (int32 i = 0; i <= nr; ++i)
				{
					if (std::abs(dery[i]) < ZEROepsilon)
					{
						dery[i] = 0;
					}
				}

				int32 i = 0;
				const double dx = std::max(0.1 * (rb.maxX - rb.minX) / n, ERRF);
				Array<double> guesses;
				Array<std::pair<double, double>> minmax;
				if (nr > -1)
				{
					if (dery[0] != 0)
					{
						if (Sign(dery[0]) != Sign(poly.eval(derrt[0] - dx) - dery[0]))
						{
							guesses.push_back(derrt[0] - dx);
							minmax.push_back({ rb.minX, derrt[0] });
						}
					}
					else
					{
						results << derrt[0] << derrt[0];
						i++;
					}

					for (; i < nr; ++i)
					{
						if (dery[i + 1] == 0)
						{
							results << derrt[i + 1] << derrt[i + 1];
							i++;
						}
						else if (Sign(dery[i]) != Sign(dery[i + 1]))
						{
							guesses.push_back((derrt[i] + derrt[i + 1]) / 2.0);
							minmax.push_back({ derrt[i], derrt[i + 1] });
						}
					}

					if (dery[nr] != 0 && Sign(dery[nr]) != Sign(poly.eval(derrt[nr] + dx) - dery[nr]))
					{
						guesses.push_back(derrt[nr] + dx);
						minmax.push_back({ derrt[nr], rb.maxX });
					}
				}

				auto f = [&](double x) { return poly.eval(x); };
				auto df = [&](double x) { return poly_d.eval(x); };
				if (guesses.size() > 0)
				{
					for (size_t k = 0; k < guesses.size(); ++k)
					{
						guesses[k] = Newton_secant_bisection(guesses[k], f, df, 32, minmax[k].first, minmax[k].second);
					}
				}

				results.append(guesses);
			}

			return results;
		};

		// ok
		double zeroErrorEstimate(Optional<double> maxabsX) const
		{
			const double ERRF = 1e-15;

			if (!maxabsX)
			{
				Bound rb = bounds();
				maxabsX = std::max(std::abs(rb.minX), std::abs(rb.maxX));
			}

			if (maxabsX < 0.001)
			{
				return 2 * std::abs(eval(ERRF));
			}

			const int32 n = static_cast<int32>(coefs.size()) - 1;
			const double an = coefs[n];
			double result = 0.0;

			for (size_t i = 0; i < coefs.size(); ++i)
			{
				const double v = coefs[i];
				const double nm = v / an * std::pow(maxabsX.value(), i);
				result = nm > result ? nm : result;
			}

			return 10 * ERRF * result;
		}

		NegXPosX bounds_UpperReal_Fujiwara() const
		{
			Array<double> a = this->coefs;
			const int32 n = static_cast<int32>(a.size()) - 1;
			const double an = a[n];
			
			if (an != 1)
			{
				a = this->coefs.map([=](double v){ return v / an; });
			}
			
			int32 index = 0;

			const Array<double> b = 
				a.map([&index, n](double v) {
				int32 i = index++;
				return (i < n) ? std::pow(std::abs((i == 0) ? v / 2 : v), 1 / (n - i)) : v;
			});

			auto find2Max1 = [&](MaxNearmax acc, double bi, int32 i) {
				auto coefSelectionFunc = [&](int32 i) { return i < n && a[i] < 0; };
				if (coefSelectionFunc(i)) {
					if (acc.max < bi) {
						acc.nearmax = acc.max;
						acc.max = bi;
					}
					else if (acc.nearmax < bi) {
						acc.nearmax = bi;
					}
				}
				return acc;
			};

			MaxNearmax max_nearmax_pos{ 0,0 };
			for (size_t i = 0; i < b.size(); ++i)
			{
				max_nearmax_pos = find2Max1(max_nearmax_pos, b[i], static_cast<int32>(i));
			}

			auto find2Max2 = [&](MaxNearmax acc, double bi, int32 i) {
				auto coefSelectionFunc = [&](int32 i) { return i < n && ((n % 2 == i % 2) ? a[i] < 0 : a[i] > 0); };
				if (coefSelectionFunc(i)) {
					if (acc.max < bi) {
						acc.nearmax = acc.max;
						acc.max = bi;
					}
					else if (acc.nearmax < bi) {
						acc.nearmax = bi;
					}
				}
				return acc;
			};

			MaxNearmax max_nearmax_neg{ 0,0 };
			for (size_t i = 0; i < b.size(); ++i)
			{
				max_nearmax_neg = find2Max2(max_nearmax_neg, b[i], static_cast<int32>(i));
			}

			return {
					-2 * max_nearmax_neg.max,
					 2 * max_nearmax_pos.max
			};
		};

		// ok
		NegXPosX bounds_LowerReal_Fujiwara() const
		{
			Polynomial poly;
			poly.coefs = this->coefs.reversed();
			NegXPosX res = poly.bounds_UpperReal_Fujiwara();
			res.negX = 1.0 / res.negX;
			res.posX = 1.0 / res.posX;
			return res;
		};

		// ok
		Bound bounds() const
		{
			const NegXPosX urb = this->bounds_UpperReal_Fujiwara();
			Bound rb{ urb.negX, urb.posX };
			
			if (urb.negX == 0 && urb.posX == 0)
			{
				return rb;
			}
			
			if (urb.negX == 0)
			{
				rb.minX = this->bounds_LowerReal_Fujiwara().posX;
			}
			else if (urb.posX == 0)
			{
				rb.maxX = this->bounds_LowerReal_Fujiwara().negX;
			}

			if (rb.minX > rb.maxX)
			{
				//console.log('Polynomial.prototype.bounds: poly has no real roots? or floating point error?');
				rb.minX = rb.maxX = 0;
			}

			return rb;
			// TODO: if sure that there are no complex roots 
			// (maybe by using Sturm's theorem) use:
			//return this->bounds_Real_Laguerre();
		}

		///////////////////////////////////////////////////////////////////// 
		///**
		//Newton's (Newton-Raphson) method for finding Real roots on univariate function. <br/>
		//When using bounds, algorithm falls back to secant if newton goes out of range.
		//Bisection is fallback for secant when determined secant is not efficient enough.
		//@see {@link http://en.wikipedia.org/wiki/Newton%27s_method}
		//@see {@link http://en.wikipedia.org/wiki/Secant_method}
		//@see {@link http://en.wikipedia.org/wiki/Bisection_method}

		//@param {Number} x0 - Inital root guess
		//@param {function(x)} f - Function which root we are trying to find
		//@param {function(x)} df - Derivative of function f
		//@param {Number} max_iterations - Maximum number of algorithm iterations
		//@param {Number} [min_x] - Left bound value
		//@param {Number} [max_x] - Right bound value
		//@returns {Number} - root
		//*/
		template <class FtyF, class FtyDF>
		static double Newton_secant_bisection(double x0, FtyF f, FtyDF df, int32 max_iterations, double min, double max)
		{
			double prev_dfx = 0, prev_x_ef_correction = 0;
			double x = x0;
			const double _ACCURACY = 14;
			const double min_correction_factor = std::pow(10, -_ACCURACY);
			//var isBounded = (typeof min == = 'number' && typeof max == = 'number');
			const bool isBounded = true;

			//if (min > max)
			//	throw new Error("newton root finding: min must be greater than max");
			double y_atmin = f(min);
			double y_atmax = f(max);
			//if (Sign(y_atmin) == Sign(y_atmax))
			//	throw new Error("newton root finding: y values of bounds must be of opposite sign");

			double x_correction = 0, x_new = 0;
			auto isEnoughCorrection = [&]()
			{
				// stop if correction is too small
				// or if correction is in simple loop
				return (std::abs(x_correction) <= min_correction_factor * std::abs(x))
					|| (prev_x_ef_correction == (x - x_correction) - x);
			};

			//var stepMethod;
			//var details = [];
			for (int32 i = 0; i < max_iterations; ++i)
			{
				double dfx = df(x);
				
				if (dfx == 0)
				{
					if (prev_dfx == 0)
					{
						// error
						//throw new Error("newton root finding: df(x) is zero");
						//return null;
						return 0;
					}
					else
					{
						// use previous derivation value
						dfx = prev_dfx;
					}
					// or move x a little?
					//dfx = df(x != 0 ? x + x * 1e-15 : 1e-15);
				}

				//stepMethod = 'newton';
				prev_dfx = dfx;
				double y = f(x);
				x_correction = y / dfx;
				x_new = x - x_correction;
				if (isEnoughCorrection())
				{
					break;
				}

				if (isBounded)
				{
					if (Sign(y) == Sign(y_atmax))
					{
						max = x;
						y_atmax = y;
					}
					else if (Sign(y) == Sign(y_atmin))
					{
						min = x;
						y_atmin = y;
					}
					else
					{
						x = x_new;
						//console.log("newton root finding: sign(y) not matched.");
						break;
					}

					if ((x_new < min) || (x_new > max))
					{
						if (Sign(y_atmin) == Sign(y_atmax))
						{
							break;
						}

						const double RATIO_LIMIT = 50;
						const double AIMED_BISECT_OFFSET = 0.25; // [0, 0.5)
						const double dy = y_atmax - y_atmin;
						const double dx = max - min;

						if (dy == 0)
						{
							//stepMethod = 'bisect';
							x_correction = x - (min + dx * 0.5);
						}
						else if (std::abs(dy / std::min(y_atmin, y_atmax)) > RATIO_LIMIT)
						{
							//stepMethod = 'aimed bisect';
							x_correction = x - (min + dx * (0.5 + (std::abs(y_atmin) < std::abs(y_atmax) ? -AIMED_BISECT_OFFSET : AIMED_BISECT_OFFSET)));
						}
						else
						{
							//stepMethod = 'secant'; 
							x_correction = x - (min - y_atmin / dy * dx);
						}

						x_new = x - x_correction;

						if (isEnoughCorrection())
						{
							break;
						}
					}
				}

				//details.push_back([stepMethod, i, x, x_new, x_correction, min, max, y]);
				prev_x_ef_correction = x - x_new;
				x = x_new;
			}

			//details.push_back([stepMethod, i, x, x_new, x_correction, min, max, y]);
			//console.log(details.join('\r\n'));
			//if (i == max_iterations)
			//    console.log('newt: steps=' + ((i==max_iterations)? i:(i + 1)));
			return x;
		};
	};
}
