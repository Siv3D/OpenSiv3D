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

# include <Siv3D/SFMT.hpp>
# include <Siv3D/RNG.hpp>
# include <Siv3D/HardwareRNG.hpp>

# if SIV3D_WITH_FEATURE(SSE2)

	# define HAVE_SSE2

# else

	# error

# endif

namespace s3d
{
	namespace sfmt
	{
	#if defined(HAVE_ALTIVEC)

		vector unsigned int vec_recursion(vector unsigned int a,
			vector unsigned int b,
			vector unsigned int c,
			vector unsigned int d);

		/**
		* This function represents the recursion formula in AltiVec and BIG ENDIAN.
		* @param a a 128-bit part of the interal state array
		* @param b a 128-bit part of the interal state array
		* @param c a 128-bit part of the interal state array
		* @param d a 128-bit part of the interal state array
		* @return output
		*/
		vector unsigned int vec_recursion(vector unsigned int a,
			vector unsigned int b,
			vector unsigned int c,
			vector unsigned int d) {

			const vector unsigned int sl1 = SFMT_ALTI_SL1;
			const vector unsigned int sr1 = SFMT_ALTI_SR1;
	#ifdef ONLY64
			const vector unsigned int mask = SFMT_ALTI_MSK64;
			const vector unsigned char perm_sl = SFMT_ALTI_SL2_PERM64;
			const vector unsigned char perm_sr = SFMT_ALTI_SR2_PERM64;
	#else
			const vector unsigned int mask = SFMT_ALTI_MSK;
			const vector unsigned char perm_sl = SFMT_ALTI_SL2_PERM;
			const vector unsigned char perm_sr = SFMT_ALTI_SR2_PERM;
	#endif
			vector unsigned int v, w, x, y, z;
			x = vec_perm(a, (vector unsigned int)perm_sl, perm_sl);
			v = a;
			y = vec_sr(b, sr1);
			z = vec_perm(c, (vector unsigned int)perm_sr, perm_sr);
			w = vec_sl(d, sl1);
			z = vec_xor(z, w);
			y = vec_and(y, mask);
			v = vec_xor(v, x);
			z = vec_xor(z, y);
			z = vec_xor(z, v);
			return z;
		}

		/**
		* This function fills the internal state array with pseudorandom
		* integers.
		*/
		void sfmt_gen_rand_all(sfmt_t * sfmt) {
			int i;
			vector unsigned int r, r1, r2;

			r1 = sfmt->state[N - 2].s;
			r2 = sfmt->state[N - 1].s;
			for (i = 0; i < N - POS1; i++) {
				r = vec_recursion(sfmt->state[i].s, sfmt->state[i + POS1].s, r1, r2);
				sfmt->state[i].s = r;
				r1 = r2;
				r2 = r;
			}
			for (; i < N; i++) {
				r = vec_recursion(sfmt->state[i].s, sfmt->state[i + POS1 - N].s, r1, r2);
				sfmt->state[i].s = r;
				r1 = r2;
				r2 = r;
			}
		}

		/**
		* This function fills the user-specified array with pseudorandom
		* integers.
		*
		* @param array an 128-bit array to be filled by pseudorandom numbers.
		* @param size number of 128-bit pesudorandom numbers to be generated.
		*/
		void gen_rand_array(sfmt_t * sfmt, w128_t *array, int size) {
			int i, j;
			vector unsigned int r, r1, r2;

			r1 = sfmt->state[N - 2].s;
			r2 = sfmt->state[N - 1].s;
			for (i = 0; i < N - POS1; i++) {
				r = vec_recursion(sfmt->state[i].s, sfmt->state[i + POS1].s, r1, r2);
				array[i].s = r;
				r1 = r2;
				r2 = r;
			}
			for (; i < N; i++) {
				r = vec_recursion(sfmt->state[i].s, array[i + POS1 - N].s, r1, r2);
				array[i].s = r;
				r1 = r2;
				r2 = r;
			}
			/* main loop */
			for (; i < size - N; i++) {
				r = vec_recursion(array[i - N].s, array[i + POS1 - N].s, r1, r2);
				array[i].s = r;
				r1 = r2;
				r2 = r;
			}
			for (j = 0; j < 2 * N - size; j++) {
				sfmt->state[j].s = array[j + size - N].s;
			}
			for (; i < size; i++) {
				r = vec_recursion(array[i - N].s, array[i + POS1 - N].s, r1, r2);
				array[i].s = r;
				sfmt->state[j++].s = r;
				r1 = r2;
				r2 = r;
			}
		}

	#ifndef ONLY64
	#if defined(__APPLE__)
	#define SFMT_ALTI_SWAP (vector unsigned char) \
		(4, 5, 6, 7, 0, 1, 2, 3, 12, 13, 14, 15, 8, 9, 10, 11)
	#else
	#define SFMT_ALTI_SWAP {4, 5, 6, 7, 0, 1, 2, 3, 12, 13, 14, 15, 8, 9, 10, 11}
	#endif
		/**
		* This function swaps high and low 32-bit of 64-bit integers in user
		* specified array.
		*
		* @param array an 128-bit array to be swaped.
		* @param size size of 128-bit array.
		*/
		void swap(w128_t *array, int size) {
			int i;
			const vector unsigned char perm = SFMT_ALTI_SWAP;

			for (i = 0; i < size; i++) {
				array[i].s = vec_perm(array[i].s, (vector unsigned int)perm, perm);
			}
		}
	#endif

	#elif defined(HAVE_SSE2)
		/**
		* parameters used by sse2.
		*/
		static const w128_t sse2_param_mask = { { SFMT_MSK1, SFMT_MSK2,
			SFMT_MSK3, SFMT_MSK4 } };
	#if defined(_MSC_VER)

		__m128i __vectorcall mm_recursion(__m128i a, __m128i b,
			__m128i c, __m128i d);

		/**
		* This function represents the recursion formula.
		* @param a a 128-bit part of the interal state array
		* @param b a 128-bit part of the interal state array
		* @param c a 128-bit part of the interal state array
		* @param d a 128-bit part of the interal state array
		* @return new value
		*/
		__m128i __vectorcall mm_recursion(__m128i a, __m128i b,
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
		void sfmt_gen_rand_all(sfmt_t * sfmt) {
			int i;
			__m128i r1, r2;
			w128_t * pstate = sfmt->state;

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

		/**
		* This function fills the user-specified array with pseudorandom
		* integers.
		* @param sfmt SFMT internal state.
		* @param array an 128-bit array to be filled by pseudorandom numbers.
		* @param size number of 128-bit pseudorandom numbers to be generated.
		*/
		void gen_rand_array(sfmt_t * sfmt, w128_t * array, int size)
		{
			int i, j;
			__m128i r1, r2;
			w128_t * pstate = sfmt->state;

			r1 = pstate[SFMT_N - 2].si;
			r2 = pstate[SFMT_N - 1].si;
			for (i = 0; i < SFMT_N - SFMT_POS1; i++) {
				array[i].si = mm_recursion(pstate[i].si,
					pstate[i + SFMT_POS1].si, r1, r2);
				r1 = r2;
				r2 = array[i].si;
			}
			for (; i < SFMT_N; i++) {
				array[i].si = mm_recursion(pstate[i].si,
					array[i + SFMT_POS1 - SFMT_N].si, r1, r2);
				r1 = r2;
				r2 = array[i].si;
			}
			for (; i < size - SFMT_N; i++) {
				array[i].si = mm_recursion(array[i - SFMT_N].si,
					array[i + SFMT_POS1 - SFMT_N].si, r1, r2);
				r1 = r2;
				r2 = array[i].si;
			}
			for (j = 0; j < 2 * SFMT_N - size; j++) {
				pstate[j] = array[j + size - SFMT_N];
			}
			for (; i < size; i++, j++) {
				array[i].si = mm_recursion(array[i - SFMT_N].si,
					array[i + SFMT_POS1 - SFMT_N].si, r1, r2);
				r1 = r2;
				r2 = array[i].si;
				pstate[j] = array[i];
			}
		}

	#else

		void mm_recursion(__m128i * r, __m128i a, __m128i b,
			__m128i c, __m128i d);

		/**
		* This function represents the recursion formula.
		* @param r an output
		* @param a a 128-bit part of the interal state array
		* @param b a 128-bit part of the interal state array
		* @param c a 128-bit part of the interal state array
		* @param d a 128-bit part of the interal state array
		*/
		void mm_recursion(__m128i * r, __m128i a, __m128i b,
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
		void sfmt_gen_rand_all(sfmt_t * sfmt) {
			int i;
			__m128i r1, r2;
			w128_t * pstate = sfmt->state;

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

		/**
		* This function fills the user-specified array with pseudorandom
		* integers.
		* @param sfmt SFMT internal state.
		* @param array an 128-bit array to be filled by pseudorandom numbers.
		* @param size number of 128-bit pseudorandom numbers to be generated.
		*/
		void gen_rand_array(sfmt_t * sfmt, w128_t * array, int size)
		{
			int i, j;
			__m128i r1, r2;
			w128_t * pstate = sfmt->state;

			r1 = pstate[SFMT_N - 2].si;
			r2 = pstate[SFMT_N - 1].si;
			for (i = 0; i < SFMT_N - SFMT_POS1; i++) {
				mm_recursion(&array[i].si, pstate[i].si,
					pstate[i + SFMT_POS1].si, r1, r2);
				r1 = r2;
				r2 = array[i].si;
			}
			for (; i < SFMT_N; i++) {
				mm_recursion(&array[i].si, pstate[i].si,
					array[i + SFMT_POS1 - SFMT_N].si, r1, r2);
				r1 = r2;
				r2 = array[i].si;
			}
			for (; i < size - SFMT_N; i++) {
				mm_recursion(&array[i].si, array[i - SFMT_N].si,
					array[i + SFMT_POS1 - SFMT_N].si, r1, r2);
				r1 = r2;
				r2 = array[i].si;
			}
			for (j = 0; j < 2 * SFMT_N - size; j++) {
				pstate[j] = array[j + size - SFMT_N];
			}
			for (; i < size; i++, j++) {
				mm_recursion(&array[i].si, array[i - SFMT_N].si,
					array[i + SFMT_POS1 - SFMT_N].si, r1, r2);
				r1 = r2;
				r2 = array[i].si;
				pstate[j] = array[i];
			}
		}

	#endif

	#elif defined(HAVE_NEON)

		void neon_recursion(uint32x4_t * r, uint32x4_t a, uint32x4_t b,
			uint32x4_t c, uint32x4_t d);

		/**
		* This function represents the recursion formula.
		* @param r an output
		* @param a a 128-bit part of the interal state array
		* @param b a 128-bit part of the interal state array
		* @param c a 128-bit part of the interal state array
		* @param d a 128-bit part of the interal state array
		*/
		void neon_recursion(uint32x4_t * r, uint32x4_t a, uint32x4_t b,
			uint32x4_t c, uint32x4_t d)
		{
			uint32x4_t v, x, y, z;
			static const uint32x4_t vzero = { 0,0,0,0 };
			static const uint32x4_t vmask = { SFMT_MSK1, SFMT_MSK2, SFMT_MSK3, SFMT_MSK4 };

	# define rotate_bytes(A, B, C) vreinterpretq_u32_u8(vextq_u8(vreinterpretq_u8_u32(A),vreinterpretq_u8_u32(B),(C)))

			y = vshrq_n_u32(b, SFMT_SR1);
			z = rotate_bytes(c, vzero, SFMT_SR2);
			v = vshlq_n_u32(d, SFMT_SL1);
			z = veorq_u32(z, a);
			z = veorq_u32(z, v);
			x = rotate_bytes(vzero, a, 16 - SFMT_SL2);
			y = vandq_u32(y, vmask);
			z = veorq_u32(z, x);
			z = veorq_u32(z, y);
			*r = z;

	# undef rotate_bytes
		}

		/**
		* This function fills the internal state array with pseudorandom
		* integers.
		* @param sfmt SFMT internal state
		*/
		void sfmt_gen_rand_all(sfmt_t * sfmt) {
			int i;
			uint32x4_t r1, r2;
			w128_t * pstate = sfmt->state;

			r1 = pstate[SFMT_N - 2].si;
			r2 = pstate[SFMT_N - 1].si;
			for (i = 0; i < SFMT_N - SFMT_POS1; i++) {
				neon_recursion(&pstate[i].si, pstate[i].si, pstate[i + SFMT_POS1].si, r1, r2);
				r1 = r2;
				r2 = pstate[i].si;
			}
			for (; i < SFMT_N; i++) {
				neon_recursion(&pstate[i].si, pstate[i].si, pstate[i + SFMT_POS1 - SFMT_N].si, r1, r2);
				r1 = r2;
				r2 = pstate[i].si;
			}
		}

		/**
		* This function fills the user-specified array with pseudorandom
		* integers.
		* @param sfmt SFMT internal state.
		* @param array an 128-bit array to be filled by pseudorandom numbers.
		* @param size number of 128-bit pseudorandom numbers to be generated.
		*/
		void gen_rand_array(sfmt_t * sfmt, w128_t * array, int size)
		{
			int i, j;
			uint32x4_t r1, r2;
			w128_t * pstate = sfmt->state;

			r1 = pstate[SFMT_N - 2].si;
			r2 = pstate[SFMT_N - 1].si;
			for (i = 0; i < SFMT_N - SFMT_POS1; i++) {
				neon_recursion(&array[i].si, pstate[i].si, pstate[i + SFMT_POS1].si, r1, r2);
				r1 = r2;
				r2 = array[i].si;
			}
			for (; i < SFMT_N; i++) {
				neon_recursion(&array[i].si, pstate[i].si, array[i + SFMT_POS1 - SFMT_N].si, r1, r2);
				r1 = r2;
				r2 = array[i].si;
			}
			for (; i < size - SFMT_N; i++) {
				neon_recursion(&array[i].si, array[i - SFMT_N].si, array[i + SFMT_POS1 - SFMT_N].si, r1, r2);
				r1 = r2;
				r2 = array[i].si;
			}
			for (j = 0; j < 2 * SFMT_N - size; j++) {
				pstate[j] = array[j + size - SFMT_N];
			}
			for (; i < size; i++, j++) {
				neon_recursion(&array[i].si, array[i - SFMT_N].si, array[i + SFMT_POS1 - SFMT_N].si, r1, r2);
				r1 = r2;
				r2 = pstate[j].si = array[i].si;
			}
		}

	#endif

	#if (!defined(HAVE_ALTIVEC)) && (!defined(HAVE_SSE2)) && (!defined(HAVE_NEON))
		/**
		* This function fills the user-specified array with pseudorandom
		* integers.
		*
		* @param sfmt SFMT internal state
		* @param array an 128-bit array to be filled by pseudorandom numbers.
		* @param size number of 128-bit pseudorandom numbers to be generated.
		*/
		inline void gen_rand_array(sfmt_t * sfmt, w128_t *array, int size) {
			int i, j;
			w128_t *r1, *r2;

			r1 = &sfmt->state[SFMT_N - 2];
			r2 = &sfmt->state[SFMT_N - 1];
			for (i = 0; i < SFMT_N - SFMT_POS1; i++) {
				do_recursion(&array[i], &sfmt->state[i], &sfmt->state[i + SFMT_POS1], r1, r2);
				r1 = r2;
				r2 = &array[i];
			}
			for (; i < SFMT_N; i++) {
				do_recursion(&array[i], &sfmt->state[i],
					&array[i + SFMT_POS1 - SFMT_N], r1, r2);
				r1 = r2;
				r2 = &array[i];
			}
			for (; i < size - SFMT_N; i++) {
				do_recursion(&array[i], &array[i - SFMT_N],
					&array[i + SFMT_POS1 - SFMT_N], r1, r2);
				r1 = r2;
				r2 = &array[i];
			}
			for (j = 0; j < 2 * SFMT_N - size; j++) {
				sfmt->state[j] = array[j + size - SFMT_N];
			}
			for (; i < size; i++, j++) {
				do_recursion(&array[i], &array[i - SFMT_N],
					&array[i + SFMT_POS1 - SFMT_N], r1, r2);
				r1 = r2;
				r2 = &array[i];
				sfmt->state[j] = array[i];
			}
		}
	#endif

	#if !defined(HAVE_SSE2) && !defined(HAVE_ALTIVEC) && !defined(HAVE_NEON)	
		/**
		* This function fills the internal state array with pseudorandom
		* integers.
		* @param sfmt SFMT internal state
		*/
		void sfmt_gen_rand_all(sfmt_t* sfmt) {
			int i;
			w128_t* r1, * r2;

			r1 = &sfmt->state[SFMT_N - 2];
			r2 = &sfmt->state[SFMT_N - 1];
			for (i = 0; i < SFMT_N - SFMT_POS1; i++) {
				do_recursion(&sfmt->state[i], &sfmt->state[i],
					&sfmt->state[i + SFMT_POS1], r1, r2);
				r1 = r2;
				r2 = &sfmt->state[i];
			}
			for (; i < SFMT_N; i++) {
				do_recursion(&sfmt->state[i], &sfmt->state[i],
					&sfmt->state[i + SFMT_POS1 - SFMT_N], r1, r2);
				r1 = r2;
				r2 = &sfmt->state[i];
			}
		}
	#endif

		/**
		* This function initializes the internal state array,
		* with an array of 32-bit integers used as the seeds
		* @param sfmt SFMT internal state
		* @param init_key the array of 32-bit integers, used as a seed.
		* @param key_length the length of init_key.
		*/
		void sfmt_init_by_array(sfmt_t * sfmt, uint32_t *init_key, int key_length) {
			int i, j, count;
			uint32_t r;
			int lag;
			int mid;
			int size = SFMT_N * 4;
			uint32_t *psfmt32 = &sfmt->state[0].u[0];

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
	}

	SFMT19937_64::SFMT19937_64()
	{
		HardwareRNG rng;

		uint32 keys[32];

		for (auto& key : keys)
		{
			key = rng();
		}

		sfmt::sfmt_init_by_array(&m_sfmt, keys, 16);
	}

	SFMT19937_64::SFMT19937_64(const uint64 seed)
	{
		this->seed(seed);
	}

	SFMT19937_64::SFMT19937_64(const std::array<uint64, 16>& seeds)
	{
		this->seed(seeds);
	}

	void SFMT19937_64::seed(const uint64 seed)
	{
		SplitMix64 splitmix64(seed);

		uint32 keys[32];

		for (auto& key : keys)
		{
			key = static_cast<uint32>(splitmix64.next());
		}

		sfmt::sfmt_init_by_array(&m_sfmt, keys, static_cast<int32>(std::size(keys)));
	}

	void SFMT19937_64::seed(const std::array<uint64, 16>& seeds)
	{
		uint32 keys[32];

		for (size_t i = 0; i < 16; ++i)
		{
			keys[i * 2] = static_cast<uint32>(seeds[i] >> 32);

			keys[i * 2 + 1] = static_cast<uint32>(seeds[i] & 0xffFFffFF);
		}

		sfmt::sfmt_init_by_array(&m_sfmt, keys, static_cast<int32>(std::size(keys)));
	}
}
