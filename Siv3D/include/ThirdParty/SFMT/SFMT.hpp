//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Platform.hpp>

# if SIV3D_WITH_FEATURE(SSE2)

	# define HAVE_SSE2

# else

	# error

# endif

////////////////////////////////////////////////////////////////////////////////////////////////
//
//

//
//	SFMT ver. 1.5.1
//	SIMD oriented Fast Mersenne Twister(SFMT)
//
//	Copyright (c) 2006,2007 Mutsuo Saito, Makoto Matsumoto and Hiroshima
//	University.
//	Copyright (c) 2012 Mutsuo Saito, Makoto Matsumoto, Hiroshima University
//	and The University of Tokyo.
//	All rights reserved.
//	
//	Redistribution and use in source and binary forms, with or without
//	modification, are permitted provided that the following conditions are
//	met:
//	
//	* Redistributions of source code must retain the above copyright
//	notice, this list of conditions and the following disclaimer.
//	* Redistributions in binary form must reproduce the above
//	copyright notice, this list of conditions and the following
//	disclaimer in the documentation and/or other materials provided
//	with the distribution.
//	* Neither the names of Hiroshima University, The University of
//	Tokyo nor the names of its contributors may be used to endorse
//	or promote products derived from this software without specific
//	prior written permission.
//	
//	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
//	"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
//	LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//	A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
//	OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
//	SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
//	LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//	DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//	THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
//	OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//

/*-----------------
BASIC DEFINITIONS
-----------------*/
/** Mersenne Exponent. The period of the sequence
*  is a multiple of 2^MEXP-1. */
# define SFMT_MEXP 19937
/** SFMT generator has an internal state array of 128-bit integers,
* and N is its size. */
# define SFMT_N (SFMT_MEXP / 128 + 1)
/** N32 is the size of internal state array when regarded as an array
* of 32-bit integers.*/
# define SFMT_N32 (SFMT_N * 4)
/** N64 is the size of internal state array when regarded as an array
* of 64-bit integers.*/
# define SFMT_N64 (SFMT_N * 2)

/*----------------------
the parameters of SFMT
----------------------*/
# define SFMT_POS1	122
# define SFMT_SL1	18
# define SFMT_SL2	1
# define SFMT_SR1	11
# define SFMT_SR2	1
# define SFMT_MSK1	0xdfffffefU
# define SFMT_MSK2	0xddfecb7fU
# define SFMT_MSK3	0xbffaffffU
# define SFMT_MSK4	0xbffffff6U
# define SFMT_PARITY1	0x00000001U
# define SFMT_PARITY2	0x00000000U
# define SFMT_PARITY3	0x00000000U
# define SFMT_PARITY4	0x13c9e684U

# define SFMT_ALTI_SL1	{SFMT_SL1, SFMT_SL1, SFMT_SL1, SFMT_SL1}
# define SFMT_ALTI_SR1	{SFMT_SR1, SFMT_SR1, SFMT_SR1, SFMT_SR1}
# define SFMT_ALTI_MSK	{SFMT_MSK1, SFMT_MSK2, SFMT_MSK3, SFMT_MSK4}
# define SFMT_ALTI_MSK64	{SFMT_MSK2, SFMT_MSK1, SFMT_MSK4, SFMT_MSK3}
# define SFMT_ALTI_SL2_PERM	{1,2,3,23,5,6,7,0,9,10,11,4,13,14,15,8}
# define SFMT_ALTI_SL2_PERM64 {1,2,3,4,5,6,7,31,9,10,11,12,13,14,15,0}
# define SFMT_ALTI_SR2_PERM	{7,0,1,2,11,4,5,6,15,8,9,10,17,12,13,14}
# define SFMT_ALTI_SR2_PERM64 {15,0,1,2,3,4,5,6,17,8,9,10,11,12,13,14}

# define SFMT_IDSTR	"SFMT-19937:122-18-1-11-1:dfffffef-ddfecb7f-bffaffff-bffffff6"

/*------------------------------------------
128-bit SIMD like data type for standard C
------------------------------------------*/
# if defined(HAVE_ALTIVEC)

# if !defined(__APPLE__)

	# include <altivec.h>

# endif

# elif defined(HAVE_NEON)

	# include <arm_neon.h>

# elif defined(HAVE_SSE2)

	# include <emmintrin.h>

# endif

namespace s3d::sfmt
{
	/*------------------------------------------
	128-bit SIMD like data type for standard C
	------------------------------------------*/
# if defined(HAVE_ALTIVEC)
	/** 128-bit data structure */
	union W128_T {
		vector unsigned int s;
		uint32_t u[4];
		uint64_t u64[2];
	};
# elif defined(HAVE_NEON)
	/** 128-bit data structure */
	union W128_T {
		uint32_t u[4];
		uint64_t u64[2];
		uint32x4_t si;
	};
# elif defined(HAVE_SSE2)
	/** 128-bit data structure */
	union W128_T {
		uint32_t u[4];
		uint64_t u64[2];
		__m128i si;
	};
# else
	/** 128-bit data structure */
	union W128_T {
		uint32_t u[4];
		uint64_t u64[2];
	};
# endif

	/** 128-bit data type */
	typedef union W128_T w128_t;

	/**
	* SFMT internal state
	*/
	struct SFMT_T {
		/** the 128-bit internal state array */
		w128_t state[SFMT_N];
		/** index counter to the 32-bit internal state array */
		int idx;
	};

	typedef struct SFMT_T sfmt_t;

	void sfmt_fill_array32(sfmt_t * sfmt, uint32_t * array, int size);
	void sfmt_fill_array64(sfmt_t * sfmt, uint64_t * array, int size);
	void sfmt_init_gen_rand(sfmt_t * sfmt, uint32_t seed);
	void sfmt_init_by_array(sfmt_t * sfmt, uint32_t * init_key, int key_length);
	int sfmt_get_min_array_size32(sfmt_t * sfmt);
	int sfmt_get_min_array_size64(sfmt_t * sfmt);
	void sfmt_gen_rand_all(sfmt_t * sfmt);

# ifndef ONLY64
	/**
	* This function generates and returns 32-bit pseudorandom number.
	* init_gen_rand or init_by_array must be called before this function.
	* @param sfmt SFMT internal state
	* @return 32-bit pseudorandom number
	*/
	inline static uint32_t sfmt_genrand_uint32(sfmt_t * sfmt) {
		uint32_t r;
		uint32_t * psfmt32 = &sfmt->state[0].u[0];

		if (sfmt->idx >= SFMT_N32) {
			sfmt_gen_rand_all(sfmt);
			sfmt->idx = 0;
		}
		r = psfmt32[sfmt->idx++];
		return r;
	}
#endif
	/**
	* This function generates and returns 64-bit pseudorandom number.
	* init_gen_rand or init_by_array must be called before this function.
	* The function gen_rand64 should not be called after gen_rand32,
	* unless an initialization is again executed.
	* @param sfmt SFMT internal state
	* @return 64-bit pseudorandom number
	*/
	inline static uint64_t sfmt_genrand_uint64(sfmt_t * sfmt) {
#if defined(BIG_ENDIAN64) && !defined(ONLY64)
		uint32_t * psfmt32 = &sfmt->state[0].u[0];
		uint32_t r1, r2;
#else
		uint64_t r;
#endif
		uint64_t * psfmt64 = &sfmt->state[0].u64[0];
		assert(sfmt->idx % 2 == 0);

		if (sfmt->idx >= SFMT_N32) {
			sfmt_gen_rand_all(sfmt);
			sfmt->idx = 0;
		}
#if defined(BIG_ENDIAN64) && !defined(ONLY64)
		r1 = psfmt32[sfmt->idx];
		r2 = psfmt32[sfmt->idx + 1];
		sfmt->idx += 2;
		return ((uint64_t)r2 << 32) | r1;
#else
		r = psfmt64[sfmt->idx / 2];
		sfmt->idx += 2;
		return r;
#endif
	}

	/* =================================================
	The following real versions are due to Isaku Wada
	================================================= */
	/**
	* converts an unsigned 32-bit number to a double on [0,1]-real-interval.
	* @param v 32-bit unsigned integer
	* @return double on [0,1]-real-interval
	*/
	inline static double sfmt_to_real1(uint32_t v)
	{
		return v * (1.0 / 4294967295.0);
		/* divided by 2^32-1 */
	}

	/**
	* generates a random number on [0,1]-real-interval
	* @param sfmt SFMT internal state
	* @return double on [0,1]-real-interval
	*/
	inline static double sfmt_genrand_real1(sfmt_t * sfmt)
	{
		return sfmt_to_real1(sfmt_genrand_uint32(sfmt));
	}

	/**
	* converts an unsigned 32-bit integer to a double on [0,1)-real-interval.
	* @param v 32-bit unsigned integer
	* @return double on [0,1)-real-interval
	*/
	inline static double sfmt_to_real2(uint32_t v)
	{
		return v * (1.0 / 4294967296.0);
		/* divided by 2^32 */
	}

	/**
	* generates a random number on [0,1)-real-interval
	* @param sfmt SFMT internal state
	* @return double on [0,1)-real-interval
	*/
	inline static double sfmt_genrand_real2(sfmt_t * sfmt)
	{
		return sfmt_to_real2(sfmt_genrand_uint32(sfmt));
	}

	/**
	* converts an unsigned 32-bit integer to a double on (0,1)-real-interval.
	* @param v 32-bit unsigned integer
	* @return double on (0,1)-real-interval
	*/
	inline static double sfmt_to_real3(uint32_t v)
	{
		return (((double)v) + 0.5)*(1.0 / 4294967296.0);
		/* divided by 2^32 */
	}

	/**
	* generates a random number on (0,1)-real-interval
	* @param sfmt SFMT internal state
	* @return double on (0,1)-real-interval
	*/
	inline static double sfmt_genrand_real3(sfmt_t * sfmt)
	{
		return sfmt_to_real3(sfmt_genrand_uint32(sfmt));
	}

	/**
	* converts an unsigned 32-bit integer to double on [0,1)
	* with 53-bit resolution.
	* @param v 32-bit unsigned integer
	* @return double on [0,1)-real-interval with 53-bit resolution.
	*/
	inline static double sfmt_to_res53(uint64_t v)
	{
		return (v >> 11) * (1.0 / 9007199254740992.0);
	}

	/**
	* generates a random number on [0,1) with 53-bit resolution
	* @param sfmt SFMT internal state
	* @return double on [0,1) with 53-bit resolution
	*/
	inline static double sfmt_genrand_res53(sfmt_t * sfmt)
	{
		return sfmt_to_res53(sfmt_genrand_uint64(sfmt));
	}


	/* =================================================
	The following function are added by Saito.
	================================================= */
	/**
	* generates a random number on [0,1) with 53-bit resolution from two
	* 32 bit integers
	*/
	inline static double sfmt_to_res53_mix(uint32_t x, uint32_t y)
	{
		return sfmt_to_res53(x | ((uint64_t)y << 32));
	}

	/**
	* generates a random number on [0,1) with 53-bit resolution
	* using two 32bit integers.
	* @param sfmt SFMT internal state
	* @return double on [0,1) with 53-bit resolution
	*/
	inline static double sfmt_genrand_res53_mix(sfmt_t * sfmt)
	{
		uint32_t x, y;

		x = sfmt_genrand_uint32(sfmt);
		y = sfmt_genrand_uint32(sfmt);
		return sfmt_to_res53_mix(x, y);
	}

	inline static void do_recursion(w128_t * r, w128_t * a, w128_t * b,
		w128_t * c, w128_t * d);

	inline static void rshift128(w128_t *out, w128_t const *in, int shift);
	inline static void lshift128(w128_t *out, w128_t const *in, int shift);

	/**
	* This function simulates SIMD 128-bit right shift by the standard C.
	* The 128-bit integer given in in is shifted by (shift * 8) bits.
	* This function simulates the LITTLE ENDIAN SIMD.
	* @param out the output of this function
	* @param in the 128-bit data to be shifted
	* @param shift the shift value
	*/
#ifdef ONLY64
	inline static void rshift128(w128_t *out, w128_t const *in, int shift) {
		uint64_t th, tl, oh, ol;

		th = ((uint64_t)in->u[2] << 32) | ((uint64_t)in->u[3]);
		tl = ((uint64_t)in->u[0] << 32) | ((uint64_t)in->u[1]);

		oh = th >> (shift * 8);
		ol = tl >> (shift * 8);
		ol |= th << (64 - shift * 8);
		out->u[0] = (uint32_t)(ol >> 32);
		out->u[1] = (uint32_t)ol;
		out->u[2] = (uint32_t)(oh >> 32);
		out->u[3] = (uint32_t)oh;
	}
#else
	inline static void rshift128(w128_t *out, w128_t const *in, int shift)
	{
		uint64_t th, tl, oh, ol;

		th = ((uint64_t)in->u[3] << 32) | ((uint64_t)in->u[2]);
		tl = ((uint64_t)in->u[1] << 32) | ((uint64_t)in->u[0]);

		oh = th >> (shift * 8);
		ol = tl >> (shift * 8);
		ol |= th << (64 - shift * 8);
		out->u[1] = (uint32_t)(ol >> 32);
		out->u[0] = (uint32_t)ol;
		out->u[3] = (uint32_t)(oh >> 32);
		out->u[2] = (uint32_t)oh;
	}
#endif
	/**
	* This function simulates SIMD 128-bit left shift by the standard C.
	* The 128-bit integer given in in is shifted by (shift * 8) bits.
	* This function simulates the LITTLE ENDIAN SIMD.
	* @param out the output of this function
	* @param in the 128-bit data to be shifted
	* @param shift the shift value
	*/
#ifdef ONLY64
	inline static void lshift128(w128_t *out, w128_t const *in, int shift) {
		uint64_t th, tl, oh, ol;

		th = ((uint64_t)in->u[2] << 32) | ((uint64_t)in->u[3]);
		tl = ((uint64_t)in->u[0] << 32) | ((uint64_t)in->u[1]);

		oh = th << (shift * 8);
		ol = tl << (shift * 8);
		oh |= tl >> (64 - shift * 8);
		out->u[0] = (uint32_t)(ol >> 32);
		out->u[1] = (uint32_t)ol;
		out->u[2] = (uint32_t)(oh >> 32);
		out->u[3] = (uint32_t)oh;
	}
#else
	inline static void lshift128(w128_t *out, w128_t const *in, int shift)
	{
		uint64_t th, tl, oh, ol;

		th = ((uint64_t)in->u[3] << 32) | ((uint64_t)in->u[2]);
		tl = ((uint64_t)in->u[1] << 32) | ((uint64_t)in->u[0]);

		oh = th << (shift * 8);
		ol = tl << (shift * 8);
		oh |= tl >> (64 - shift * 8);
		out->u[1] = (uint32_t)(ol >> 32);
		out->u[0] = (uint32_t)ol;
		out->u[3] = (uint32_t)(oh >> 32);
		out->u[2] = (uint32_t)oh;
	}
#endif
	/**
	* This function represents the recursion formula.
	* @param r output
	* @param a a 128-bit part of the internal state array
	* @param b a 128-bit part of the internal state array
	* @param c a 128-bit part of the internal state array
	* @param d a 128-bit part of the internal state array
	*/
#ifdef ONLY64
	inline static void do_recursion(w128_t *r, w128_t *a, w128_t *b, w128_t *c,
		w128_t *d) {
		w128_t x;
		w128_t y;

		lshift128(&x, a, SFMT_SL2);
		rshift128(&y, c, SFMT_SR2);
		r->u[0] = a->u[0] ^ x.u[0] ^ ((b->u[0] >> SFMT_SR1) & SFMT_MSK2) ^ y.u[0]
			^ (d->u[0] << SFMT_SL1);
		r->u[1] = a->u[1] ^ x.u[1] ^ ((b->u[1] >> SFMT_SR1) & SFMT_MSK1) ^ y.u[1]
			^ (d->u[1] << SFMT_SL1);
		r->u[2] = a->u[2] ^ x.u[2] ^ ((b->u[2] >> SFMT_SR1) & SFMT_MSK4) ^ y.u[2]
			^ (d->u[2] << SFMT_SL1);
		r->u[3] = a->u[3] ^ x.u[3] ^ ((b->u[3] >> SFMT_SR1) & SFMT_MSK3) ^ y.u[3]
			^ (d->u[3] << SFMT_SL1);
	}
#else
	inline static void do_recursion(w128_t *r, w128_t *a, w128_t *b,
		w128_t *c, w128_t *d)
	{
		w128_t x;
		w128_t y;

		lshift128(&x, a, SFMT_SL2);
		rshift128(&y, c, SFMT_SR2);
		r->u[0] = a->u[0] ^ x.u[0] ^ ((b->u[0] >> SFMT_SR1) & SFMT_MSK1)
			^ y.u[0] ^ (d->u[0] << SFMT_SL1);
		r->u[1] = a->u[1] ^ x.u[1] ^ ((b->u[1] >> SFMT_SR1) & SFMT_MSK2)
			^ y.u[1] ^ (d->u[1] << SFMT_SL1);
		r->u[2] = a->u[2] ^ x.u[2] ^ ((b->u[2] >> SFMT_SR1) & SFMT_MSK3)
			^ y.u[2] ^ (d->u[2] << SFMT_SL1);
		r->u[3] = a->u[3] ^ x.u[3] ^ ((b->u[3] >> SFMT_SR1) & SFMT_MSK4)
			^ y.u[3] ^ (d->u[3] << SFMT_SL1);
	}
# endif

#if defined(__BIG_ENDIAN__) && !defined(__amd64) && !defined(BIG_ENDIAN64)
#define BIG_ENDIAN64 1
#endif
#if defined(HAVE_ALTIVEC) && !defined(BIG_ENDIAN64)
#define BIG_ENDIAN64 1
#endif
#if defined(ONLY64) && !defined(BIG_ENDIAN64)
#if defined(__GNUC__)
#error "-DONLY64 must be specified with -DBIG_ENDIAN64"
#endif
#undef ONLY64
#endif

	/*----------------
	STATIC FUNCTIONS
	----------------*/
	inline static int idxof(int i);
	void gen_rand_array(sfmt_t * sfmt, w128_t *array, int size);
	inline static uint32_t func1(uint32_t x);
	inline static uint32_t func2(uint32_t x);
	static void period_certification(sfmt_t * sfmt);
#if defined(BIG_ENDIAN64) && !defined(ONLY64)
	inline static void swap(w128_t *array, int size);
#endif


	/**
	* This function simulate a 64-bit index of LITTLE ENDIAN
	* in BIG ENDIAN machine.
	*/
#ifdef ONLY64
	inline static int idxof(int i) {
		return i ^ 1;
	}
#else
	inline static int idxof(int i) {
		return i;
	}
#endif

#if defined(BIG_ENDIAN64) && !defined(ONLY64) && !defined(HAVE_ALTIVEC)
	inline static void swap(w128_t *array, int size) {
		int i;
		uint32_t x, y;

		for (i = 0; i < size; i++) {
			x = array[i].u[0];
			y = array[i].u[2];
			array[i].u[0] = array[i].u[1];
			array[i].u[2] = array[i].u[3];
			array[i].u[1] = x;
			array[i].u[3] = y;
		}
	}
#endif
	/**
	* This function represents a function used in the initialization
	* by init_by_array
	* @param x 32-bit integer
	* @return 32-bit integer
	*/
	inline static uint32_t func1(uint32_t x) {
		return (x ^ (x >> 27)) * (uint32_t)1664525UL;
	}

	/**
	* This function represents a function used in the initialization
	* by init_by_array
	* @param x 32-bit integer
	* @return 32-bit integer
	*/
	inline static uint32_t func2(uint32_t x) {
		return (x ^ (x >> 27)) * (uint32_t)1566083941UL;
	}

	/**
	* This function certificate the period of 2^{MEXP}
	* @param sfmt SFMT internal state
	*/
	inline static void period_certification(sfmt_t * sfmt) {
		uint32_t inner = 0;
		int i, j;
		uint32_t work;
		uint32_t *psfmt32 = &sfmt->state[0].u[0];
		const uint32_t parity[4] = { SFMT_PARITY1, SFMT_PARITY2,
			SFMT_PARITY3, SFMT_PARITY4 };

		for (i = 0; i < 4; i++) {
			inner ^= psfmt32[idxof(i)] & parity[i];
		}
		for (i = 16; i > 0; i >>= 1) {
			inner ^= inner >> i;
		}
		inner &= 1;
		/* check OK */
		if (inner == 1) {
			return;
		}
		/* check NG, and modification */
		for (i = 0; i < 4; i++) {
			work = 1;
			for (j = 0; j < 32; j++) {
				if ((work & parity[i]) != 0) {
					psfmt32[idxof(i)] ^= work;
					return;
				}
				work = work << 1;
			}
		}
	}

	/*----------------
	PUBLIC FUNCTIONS
	----------------*/

	/**
	* This function returns the minimum size of array used for \b
	* fill_array32() function.
	* @param sfmt SFMT internal state
	* @return minimum size of array used for fill_array32() function.
	*/
	inline int sfmt_get_min_array_size32(sfmt_t*) {
		return SFMT_N32;
	}

	/**
	* This function returns the minimum size of array used for \b
	* fill_array64() function.
	* @param sfmt SFMT internal state
	* @return minimum size of array used for fill_array64() function.
	*/
	inline int sfmt_get_min_array_size64(sfmt_t*) {
		return SFMT_N64;
	}

#ifndef ONLY64
	/**
	* This function generates pseudorandom 32-bit integers in the
	* specified array[] by one call. The number of pseudorandom integers
	* is specified by the argument size, which must be at least 624 and a
	* multiple of four.  The generation by this function is much faster
	* than the following gen_rand function.
	*
	* For initialization, init_gen_rand or init_by_array must be called
	* before the first call of this function. This function can not be
	* used after calling gen_rand function, without initialization.
	*
	* @param sfmt SFMT internal state
	* @param array an array where pseudorandom 32-bit integers are filled
	* by this function.  The pointer to the array must be \b "aligned"
	* (namely, must be a multiple of 16) in the SIMD version, since it
	* refers to the address of a 128-bit integer.  In the standard C
	* version, the pointer is arbitrary.
	*
	* @param size the number of 32-bit pseudorandom integers to be
	* generated.  size must be a multiple of 4, and greater than or equal
	* to (MEXP / 128 + 1) * 4.
	*
	* @note \b memalign or \b posix_memalign is available to get aligned
	* memory. Mac OSX doesn't have these functions, but \b malloc of OSX
	* returns the pointer to the aligned memory block.
	*/
	inline void sfmt_fill_array32(sfmt_t * sfmt, uint32_t *array, int size) {
		assert(sfmt->idx == SFMT_N32);
		assert(size % 4 == 0);
		assert(size >= SFMT_N32);

		gen_rand_array(sfmt, (w128_t *)array, size / 4);
		sfmt->idx = SFMT_N32;
	}
#endif

	/**
	* This function generates pseudorandom 64-bit integers in the
	* specified array[] by one call. The number of pseudorandom integers
	* is specified by the argument size, which must be at least 312 and a
	* multiple of two.  The generation by this function is much faster
	* than the following gen_rand function.
	*
	* @param sfmt SFMT internal state
	* For initialization, init_gen_rand or init_by_array must be called
	* before the first call of this function. This function can not be
	* used after calling gen_rand function, without initialization.
	*
	* @param array an array where pseudorandom 64-bit integers are filled
	* by this function.  The pointer to the array must be "aligned"
	* (namely, must be a multiple of 16) in the SIMD version, since it
	* refers to the address of a 128-bit integer.  In the standard C
	* version, the pointer is arbitrary.
	*
	* @param size the number of 64-bit pseudorandom integers to be
	* generated.  size must be a multiple of 2, and greater than or equal
	* to (MEXP / 128 + 1) * 2
	*
	* @note \b memalign or \b posix_memalign is available to get aligned
	* memory. Mac OSX doesn't have these functions, but \b malloc of OSX
	* returns the pointer to the aligned memory block.
	*/
	inline void sfmt_fill_array64(sfmt_t * sfmt, uint64_t *array, int size) {
		assert(sfmt->idx == SFMT_N32);
		assert(size % 2 == 0);
		assert(size >= SFMT_N64);

		gen_rand_array(sfmt, (w128_t *)array, size / 2);
		sfmt->idx = SFMT_N32;

#if defined(BIG_ENDIAN64) && !defined(ONLY64)
		swap((w128_t *)array, size / 2);
#endif
	}

	/**
	* This function initializes the internal state array with a 32-bit
	* integer seed.
	*
	* @param sfmt SFMT internal state
	* @param seed a 32-bit integer used as the seed.
	*/
	inline void sfmt_init_gen_rand(sfmt_t * sfmt, uint32_t seed) {
		int i;

		uint32_t *psfmt32 = &sfmt->state[0].u[0];

		psfmt32[idxof(0)] = seed;
		for (i = 1; i < SFMT_N32; i++) {
			psfmt32[idxof(i)] = 1812433253UL * (psfmt32[idxof(i - 1)]
				^ (psfmt32[idxof(i - 1)] >> 30))
				+ i;
		}
		sfmt->idx = SFMT_N32;
		period_certification(sfmt);
	}
}

# if defined(BIG_ENDIAN64)

	# undef BIG_ENDIAN64

# endif

# if SIV3D_WITH_FEATURE(SSE2)

	# undef HAVE_SSE2

# endif
