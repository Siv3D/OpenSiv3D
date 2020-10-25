
# pragma once
# include <cstring>
# include <Siv3D/SIMD.hpp>

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
//	    * Redistributions of source code must retain the above copyright
//	      notice, this list of conditions and the following disclaimer.
//	    * Redistributions in binary form must reproduce the above
//	      copyright notice, this list of conditions and the following
//	      disclaimer in the documentation and/or other materials provided
//	      with the distribution.
//	    * Neither the names of Hiroshima University, The University of
//	      Tokyo nor the names of its contributors may be used to endorse
//	      or promote products derived from this software without specific
//	      prior written permission.
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


# define HAVE_SSE2

/** Mersenne Exponent. The period of the sequence
 *  is a multiple of 2^MEXP-1. */
#define SFMT_MEXP 19937

/** SFMT generator has an internal state array of 128-bit integers,
 * and N is its size. */
#define SFMT_N (SFMT_MEXP / 128 + 1)

/** N32 is the size of internal state array when regarded as an array
 * of 32-bit integers.*/
#define SFMT_N32 (SFMT_N * 4)

/** N64 is the size of internal state array when regarded as an array
 * of 64-bit integers.*/
#define SFMT_N64 (SFMT_N * 2)

#define SFMT_POS1	122
#define SFMT_SL1	18
#define SFMT_SL2	1
#define SFMT_SR1	11
#define SFMT_SR2	1
#define SFMT_MSK1	0xdfffffefU
#define SFMT_MSK2	0xddfecb7fU
#define SFMT_MSK3	0xbffaffffU
#define SFMT_MSK4	0xbffffff6U
#define SFMT_PARITY1	0x00000001U
#define SFMT_PARITY2	0x00000000U
#define SFMT_PARITY3	0x00000000U
#define SFMT_PARITY4	0x13c9e684U

/* PARAMETERS FOR ALTIVEC */
#if defined(__APPLE__)	/* For OSX */
    #define SFMT_ALTI_SL1 \
	(vector unsigned int)(SFMT_SL1, SFMT_SL1, SFMT_SL1, SFMT_SL1)
    #define SFMT_ALTI_SR1 \
	(vector unsigned int)(SFMT_SR1, SFMT_SR1, SFMT_SR1, SFMT_SR1)
    #define SFMT_ALTI_MSK \
	(vector unsigned int)(SFMT_MSK1, SFMT_MSK2, SFMT_MSK3, SFMT_MSK4)
    #define SFMT_ALTI_MSK64 \
	(vector unsigned int)(SFMT_MSK2, SFMT_MSK1, SFMT_MSK4, SFMT_MSK3)
    #define SFMT_ALTI_SL2_PERM \
	(vector unsigned char)(1,2,3,23,5,6,7,0,9,10,11,4,13,14,15,8)
    #define SFMT_ALTI_SL2_PERM64 \
	(vector unsigned char)(1,2,3,4,5,6,7,31,9,10,11,12,13,14,15,0)
    #define SFMT_ALTI_SR2_PERM \
	(vector unsigned char)(7,0,1,2,11,4,5,6,15,8,9,10,17,12,13,14)
    #define SFMT_ALTI_SR2_PERM64 \
	(vector unsigned char)(15,0,1,2,3,4,5,6,17,8,9,10,11,12,13,14)
#else	/* For OTHER OSs(Linux?) */
    #define SFMT_ALTI_SL1	{SFMT_SL1, SFMT_SL1, SFMT_SL1, SFMT_SL1}
    #define SFMT_ALTI_SR1	{SFMT_SR1, SFMT_SR1, SFMT_SR1, SFMT_SR1}
    #define SFMT_ALTI_MSK	{SFMT_MSK1, SFMT_MSK2, SFMT_MSK3, SFMT_MSK4}
    #define SFMT_ALTI_MSK64	{SFMT_MSK2, SFMT_MSK1, SFMT_MSK4, SFMT_MSK3}
    #define SFMT_ALTI_SL2_PERM	{1,2,3,23,5,6,7,0,9,10,11,4,13,14,15,8}
    #define SFMT_ALTI_SL2_PERM64 {1,2,3,4,5,6,7,31,9,10,11,12,13,14,15,0}
    #define SFMT_ALTI_SR2_PERM	{7,0,1,2,11,4,5,6,15,8,9,10,17,12,13,14}
    #define SFMT_ALTI_SR2_PERM64 {15,0,1,2,3,4,5,6,17,8,9,10,11,12,13,14}
#endif	/* For OSX */
#define SFMT_IDSTR	"SFMT-19937:122-18-1-11-1:dfffffef-ddfecb7f-bffaffff-bffffff6"

namespace s3d::detail
{
# if defined(HAVE_SSE2)

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

	inline constexpr int idxof(int i) noexcept {
		return i;
	}

	static const w128_t sse2_param_mask = { {SFMT_MSK1, SFMT_MSK2,
										SFMT_MSK3, SFMT_MSK4} };

# if SIV3D_PLATFORM(WINDOWS)

	/**
	 * This function represents the recursion formula.
	 * @param a a 128-bit part of the interal state array
	 * @param b a 128-bit part of the interal state array
	 * @param c a 128-bit part of the interal state array
	 * @param d a 128-bit part of the interal state array
	 * @return new value
	 */
	inline static __m128i __vectorcall mm_recursion(__m128i a, __m128i b,
		__m128i c, __m128i d)
	{
		__m128i v, x, y, z;

		y = _mm_srli_epi32(b, SFMT_SR1);
		z = _mm_srli_si128(c, SFMT_SR2);
		v = _mm_slli_epi32(d, SFMT_SL1);
		z = _mm_xor_si128(z, a);
		z = _mm_xor_si128(z, v);
		x = _mm_slli_si128(a, SFMT_SL2);
		y = _mm_and_si128(y, sse2_param_mask.si);
		z = _mm_xor_si128(z, x);
		return _mm_xor_si128(z, y);
	}

	/**
	 * This function fills the internal state array with pseudorandom
	 * integers.
	 * @param sfmt SFMT internal state
	 */
	inline void sfmt_gen_rand_all(sfmt_t* sfmt) {
		int i;
		__m128i r1, r2;
		w128_t* pstate = sfmt->state;

		r1 = pstate[SFMT_N - 2].si;
		r2 = pstate[SFMT_N - 1].si;
		for (i = 0; i < SFMT_N - SFMT_POS1; i++) {
			pstate[i].si = mm_recursion(pstate[i].si,
				pstate[i + SFMT_POS1].si, r1, r2);
			r1 = r2;
			r2 = pstate[i].si;
		}
		for (; i < SFMT_N; i++) {
			pstate[i].si = mm_recursion(pstate[i].si,
				pstate[i + SFMT_POS1 - SFMT_N].si,
				r1, r2);
			r1 = r2;
			r2 = pstate[i].si;
		}
	}

# else

	/**
	 * This function represents the recursion formula.
	 * @param r an output
	 * @param a a 128-bit part of the interal state array
	 * @param b a 128-bit part of the interal state array
	 * @param c a 128-bit part of the interal state array
	 * @param d a 128-bit part of the interal state array
	 */
	inline static void mm_recursion(__m128i* r, __m128i a, __m128i b,
		__m128i c, __m128i d)
	{
		__m128i v, x, y, z;

		y = _mm_srli_epi32(b, SFMT_SR1);
		z = _mm_srli_si128(c, SFMT_SR2);
		v = _mm_slli_epi32(d, SFMT_SL1);
		z = _mm_xor_si128(z, a);
		z = _mm_xor_si128(z, v);
		x = _mm_slli_si128(a, SFMT_SL2);
		y = _mm_and_si128(y, sse2_param_mask.si);
		z = _mm_xor_si128(z, x);
		z = _mm_xor_si128(z, y);
		*r = z;
	}

	/**
	 * This function fills the internal state array with pseudorandom
	 * integers.
	 * @param sfmt SFMT internal state
	 */
	inline void sfmt_gen_rand_all(sfmt_t* sfmt) {
		int i;
		__m128i r1, r2;
		w128_t* pstate = sfmt->state;

		r1 = pstate[SFMT_N - 2].si;
		r2 = pstate[SFMT_N - 1].si;
		for (i = 0; i < SFMT_N - SFMT_POS1; i++) {
			mm_recursion(&pstate[i].si, pstate[i].si,
				pstate[i + SFMT_POS1].si, r1, r2);
			r1 = r2;
			r2 = pstate[i].si;
		}
		for (; i < SFMT_N; i++) {
			mm_recursion(&pstate[i].si, pstate[i].si,
				pstate[i + SFMT_POS1 - SFMT_N].si,
				r1, r2);
			r1 = r2;
			r2 = pstate[i].si;
		}
	}

# endif

	/**
	 * This function represents a function used in the initialization
	 * by init_by_array
	 * @param x 32-bit integer
	 * @return 32-bit integer
	 */
	inline constexpr uint32_t func1(uint32_t x) {
		return (x ^ (x >> 27)) * (uint32_t)1664525UL;
	}

	/**
	 * This function represents a function used in the initialization
	 * by init_by_array
	 * @param x 32-bit integer
	 * @return 32-bit integer
	 */
	inline constexpr uint32_t func2(uint32_t x) {
		return (x ^ (x >> 27)) * (uint32_t)1566083941UL;
	}

	/**
	 * This function certificate the period of 2^{MEXP}
	 * @param sfmt SFMT internal state
	 */
	inline void period_certification(sfmt_t* sfmt) {
		uint32_t inner = 0;
		int i, j;
		uint32_t work;
		uint32_t* psfmt32 = &sfmt->state[0].u[0];
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

	/**
	 * This function generates and returns 64-bit pseudorandom number.
	 * init_gen_rand or init_by_array must be called before this function.
	 * The function gen_rand64 should not be called after gen_rand32,
	 * unless an initialization is again executed.
	 * @param sfmt SFMT internal state
	 * @return 64-bit pseudorandom number
	 */
	inline uint64_t sfmt_genrand_uint64(sfmt_t* sfmt) {
		uint64_t r;
		uint64_t* psfmt64 = &sfmt->state[0].u64[0];
		assert(sfmt->idx % 2 == 0);

		if (sfmt->idx >= SFMT_N32) {
			sfmt_gen_rand_all(sfmt);
			sfmt->idx = 0;
		}
		r = psfmt64[sfmt->idx / 2];
		sfmt->idx += 2;
		return r;
	}

	/**
	 * This function initializes the internal state array,
	 * with an array of 32-bit integers used as the seeds
	 * @param sfmt SFMT internal state
	 * @param init_key the array of 32-bit integers, used as a seed.
	 * @param key_length the length of init_key.
	 */
	inline void sfmt_init_by_array(sfmt_t* sfmt, uint32_t* init_key, int key_length) {
		int i, j, count;
		uint32_t r;
		int lag;
		int mid;
		int size = SFMT_N * 4;
		uint32_t* psfmt32 = &sfmt->state[0].u[0];

		if (size >= 623) {
			lag = 11;
		}
		else if (size >= 68) {
			lag = 7;
		}
		else if (size >= 39) {
			lag = 5;
		}
		else {
			lag = 3;
		}
		mid = (size - lag) / 2;

		memset(sfmt, 0x8b, sizeof(sfmt_t));
		if (key_length + 1 > SFMT_N32) {
			count = key_length + 1;
		}
		else {
			count = SFMT_N32;
		}
		r = func1(psfmt32[idxof(0)] ^ psfmt32[idxof(mid)]
			^ psfmt32[idxof(SFMT_N32 - 1)]);
		psfmt32[idxof(mid)] += r;
		r += key_length;
		psfmt32[idxof(mid + lag)] += r;
		psfmt32[idxof(0)] = r;

		count--;
		for (i = 1, j = 0; (j < count) && (j < key_length); j++) {
			r = func1(psfmt32[idxof(i)] ^ psfmt32[idxof((i + mid) % SFMT_N32)]
				^ psfmt32[idxof((i + SFMT_N32 - 1) % SFMT_N32)]);
			psfmt32[idxof((i + mid) % SFMT_N32)] += r;
			r += init_key[j] + i;
			psfmt32[idxof((i + mid + lag) % SFMT_N32)] += r;
			psfmt32[idxof(i)] = r;
			i = (i + 1) % SFMT_N32;
		}
		for (; j < count; j++) {
			r = func1(psfmt32[idxof(i)] ^ psfmt32[idxof((i + mid) % SFMT_N32)]
				^ psfmt32[idxof((i + SFMT_N32 - 1) % SFMT_N32)]);
			psfmt32[idxof((i + mid) % SFMT_N32)] += r;
			r += i;
			psfmt32[idxof((i + mid + lag) % SFMT_N32)] += r;
			psfmt32[idxof(i)] = r;
			i = (i + 1) % SFMT_N32;
		}
		for (j = 0; j < SFMT_N32; j++) {
			r = func2(psfmt32[idxof(i)] + psfmt32[idxof((i + mid) % SFMT_N32)]
				+ psfmt32[idxof((i + SFMT_N32 - 1) % SFMT_N32)]);
			psfmt32[idxof((i + mid) % SFMT_N32)] ^= r;
			r -= i;
			psfmt32[idxof((i + mid + lag) % SFMT_N32)] ^= r;
			psfmt32[idxof(i)] = r;
			i = (i + 1) % SFMT_N32;
		}

		sfmt->idx = SFMT_N32;
		period_certification(sfmt);
	}

	/**
	 * converts an unsigned 32-bit integer to double on [0,1)
	 * with 53-bit resolution.
	 * @param v 32-bit unsigned integer
	 * @return double on [0,1)-real-interval with 53-bit resolution.
	 */
	inline constexpr double sfmt_to_res53(uint64_t v) noexcept
	{
		return (v >> 11) * (1.0 / 9007199254740992.0);
	}

	/**
	 * generates a random number on [0,1) with 53-bit resolution
	 * @param sfmt SFMT internal state
	 * @return double on [0,1) with 53-bit resolution
	 */
	inline double sfmt_genrand_res53(sfmt_t* sfmt) noexcept
	{
		return sfmt_to_res53(sfmt_genrand_uint64(sfmt));
	}
}

# if SIV3D_INTRINSIC(SSE)
#   undef HAVE_SSE2
# else
#	undef HAVE_SSE2
#	undef SIMDE_ENABLE_NATIVE_ALIASES
# endif
# undef SFMT_MEXP
# undef SFMT_N
# undef SFMT_N32
# undef SFMT_N64
