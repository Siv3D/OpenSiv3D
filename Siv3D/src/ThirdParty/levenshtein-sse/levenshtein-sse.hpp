/**
 * Copyright (c) 2016 Anna Henningsen <sqrt@entless.org>
 * 
 * MIT License
 */

#ifndef LSTSSE_LEVENSHTEIN_SSE_HPP
#define LSTSSE_LEVENSHTEIN_SSE_HPP

#include <algorithm>
#include <vector>
#include <iterator>
#include <cstdint>
#include <cassert>
#include <limits>

namespace levenshteinSSE {

/**
 * Public methods
 */

/**
 * Compute the Levenshtein distances of [a, aEnd) and [b, bEnd).
 * Both types of iterators need to be bidirectional, e.g.
 * fulfill the requirements of BidirectionalIterator, but may just be
 * pointers.
 * 
 * For pointers to types where SIMD instructions make sense, these are
 * used when available.
 */
template<typename Iterator1, typename Iterator2>
std::size_t levenshtein(Iterator1 a, Iterator1 aEnd, Iterator2 b, Iterator2 bEnd);

/**
 * Compute the Levenshtein distances of a and b.
 * Both containers need to support bidirectional start and end iterators
 * (via std::begin() and std::end()).
 * 
 * If both containers provide .data() and .size(), these are used to
 * get pointers to the start and past-end elements. This holds true
 * for std::string, std::vector, std::array and possibly more, but
 * if you want to use this with custom container types, bear in mind that
 * this also means that the available memory area needs to be contiguous.
 */
template<typename Container1, typename Container2>
std::size_t levenshtein(const Container1& a, const Container2& b);

/**
 * Only implementation-specific stuff below
 */

/**
 * C++ STL allocator returning aligned memory with additional memory
 * on both sides to safely allow garbage reads/writes
 * 
 * based on https://stackoverflow.com/a/8545389/688904
 */
template <typename T, std::size_t N = 16>
class AlignmentAllocator;

#ifdef __SSE2__
template <typename T, std::size_t N>
class AlignmentAllocator {
public:
  typedef T value_type;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;

  typedef T* pointer;
  typedef const T* const_pointer;

  typedef T& reference;
  typedef const T& const_reference;

  constexpr inline AlignmentAllocator () noexcept { }

  template <typename T2>
  constexpr inline AlignmentAllocator (const AlignmentAllocator<T2, N> &) noexcept { }

  inline ~AlignmentAllocator () noexcept { }

  inline pointer address (reference r) {
    return &r;
  }

  inline const_pointer address (const_reference r) const {
    return &r;
  }

  inline pointer allocate (size_type n) {
    // this allocator is special in that it leaves 4*N bytes before and after
    // the allocated area for garbage reads/writes
    return reinterpret_cast<pointer>(reinterpret_cast<char*>(_mm_malloc(n * sizeof(value_type) + 8 * N, N)) + 4*N);
  }

  inline void deallocate (pointer p, size_type) {
    _mm_free(reinterpret_cast<char*>(p) - 4*N);
  }

  inline void construct (pointer p, const value_type& value) {
     new (p) value_type (value);
  }

  inline void destroy (pointer p) {
    p->~value_type ();
  }

  constexpr inline size_type max_size () const noexcept {
    return size_type (-1) / sizeof (value_type);
  }

  template <typename T2>
  struct rebind {
    typedef AlignmentAllocator<T2, N> other;
  };

  constexpr bool operator!=(const AlignmentAllocator<T,N>& other) const  {
    return !(*this == other);
  }

  // Returns true if and only if storage allocated from *this
  // can be deallocated from other, and vice versa.
  // Always returns true for stateless allocators.
  constexpr bool operator==(const AlignmentAllocator<T,N>& other) const {
    return other.usesMMAlloc;
  }
  
  static constexpr bool usesMMAlloc = true;
};
#endif

template <typename T>
class AlignmentAllocator<T, 1> : public std::allocator<T> {
public:
  static constexpr bool usesMMAlloc = false;
};

#ifdef __SSSE3__
constexpr std::size_t alignment = 16;
#else
#warning "No SIMD extensions enabled"
constexpr std::size_t alignment = 1;
#endif

/**
 * Some notes on the algorithm used here:
 * 
 * The standard Levenshtein metric is usually calculated using the
 * Wagner–Fischer algorithm [1]. This essentially means calculating
 * Levenshtein(a[:n], b[:m]) for all prefixes a[:n] and b[:m] of a and b,
 * storing the results in a table (and possibly “forgetting”
 * the previous rows to save memory). Normally, this is performed
 * row by row, but this approach has the disadvantage that it is not
 * easily converted to using SIMD instructions.
 * 
 * The “diagonal” algorithm variants in this file calculate the minor
 * diagonals one by one. There, the index `i` always corresponds to the
 * table row in which we currently are and `j` always denotes the column. 
 * Note that the tables have a trivial i=0 row and j=0 column; The
 * table entry [i,j] corresponds to the comparison a[i-1] == b[j-1].
 * A diagonal is defined by its index `k`, yielding the inner loop invariant
 * k == i + j.
 * 
 * The outer loop iterates over all diagonals from k = 0 to
 * k = len(a)+len(b) (compare with the table in [1] to verify), meaning
 * that the length of the diagonals may vary between iterations.
 * The current diagonal and the previous diagonal are kept in memory,
 * referred to as diag and diag2 respectively.
 * 
 * In the inner loop, the rows are treated in descending order,
 * i.e. `i` decreases from iteration to iteration, to avoid overwriting
 * data needed in the next iteration.
 * 
 * [1]: https://en.wikipedia.org/wiki/Wagner%E2%80%93Fischer_algorithm
 */

/**
 * Trivial implementation of one inner loop iteration.
 * 
 * Note that i is passed as a reference; The SIMD version may decrease it
 * by more than 1.
 */
template<typename Vec1, typename Vec2, typename Iterator1, typename Iterator2>
struct LevenshteinIterationBase {
static inline void perform(const Iterator1& a, const Iterator2& b,
  std::size_t& i, std::size_t j, [[maybe_unused]] std::size_t bLen, Vec1& diag, const Vec2& diag2)
{
  std::uint32_t min = static_cast<std::uint32_t>(std::min(diag2[i], diag2[i-1]));
  if (min < diag[i-1]) {
    diag[i] = min + 1;
  }
  else {
    diag[i] = diag[i-1] + (a[i-1] != b[j-1]);
  }
  --i;
}
};

/**
 * Start SIMD-Land
 * 
 * Currently, only SSSE3+ is supported, since we use
 * _mm_shuffle_epi8 and _mm_alignr_epi8.
 * 
 * If you are not familiar with SSE and/or the intrinsics,
 * you can just believe me that they do about the same thing
 * as LevenshteinIterationBase::perform.
 */

#ifdef __SSSE3__
#ifndef __SSE4_1__
// straightforward _mm_min_epi32 polyfill using only SSE2
inline __m128i _mm_min_epi32 (__m128i a, __m128i b) {
  __m128i compare = _mm_cmpgt_epi32(a, b);
  __m128i aIsSmaller = _mm_andnot_si128(a, compare);
  __m128i bIsSmaller = _mm_and_si128   (b, compare);
  return _mm_or_si128(aIsSmaller, bIsSmaller);
}
#endif // __SSE4_1__
#endif // __SSSE3__

#ifdef __AVX2__
// provide an AVX2 version of _mm256_alignr_epi32(a, b, 7)
// (i.e. move a one epi32 to the left and write the highest
// bytes of b to the lowest of a)
/*#ifndef __AVX512F__*/
__m256i _mm256_alignr_epi32_7(__m256i a, __m256i b) {
  const __m256i rotl1_256_epi32 = _mm256_setr_epi32(7, 0, 1, 2, 3, 4, 5, 6);
  __m256i combined = _mm256_blend_epi32(a, b, 0x80);
  return _mm256_permutevar8x32_epi32(combined, rotl1_256_epi32);
}
/*
#else
__m256i _mm256_alignr_epi32_7(__m256i a, __m256i b) {
  return _mm256_alignr_epi32(a, b, 7);
}
#endif*/
#endif

template<typename T>
struct LevenshteinIterationSIMD {
/* Decide which implementation is acceptable */
static inline void performSIMD(const T* a, const T* b,
  std::size_t& i, std::size_t j, std::size_t bLen,
  std::uint32_t* diag, const std::uint32_t* diag2)
{

#ifdef __AVX2__
  if (i >= 32 && bLen - j >= 32) {
    performSSE_AVX2(a, b, i, j, bLen, diag, diag2);
    return;
  }
#endif

#ifdef __SSSE3__
  if (i >= 16 && bLen - j >= 16) {
    performSSE(a, b, i, j, bLen, diag, diag2);
    return;
  }
#endif
  
  LevenshteinIterationBase<std::uint32_t*, const std::uint32_t*, const T*, const T*>
    ::perform(a, b, i, j, bLen, diag, diag2);
}

#ifdef __SSSE3__
static inline void performSSE(const T* a, const T* b,
  std::size_t& i, std::size_t j, [[maybe_unused]] std::size_t bLen,
  std::uint32_t* diag, const std::uint32_t* diag2)
{
  const __m128i one128_epi32 = _mm_set1_epi32(1);
  const __m128i reversedIdentity128_epi8 = _mm_setr_epi8(
    15, 14, 13, 12,
    11, 10,  9,  8,
     7,  6,  5,  4,
     3,  2,  1,  0
  );
  const __m128i reversedIdentity128_epi16 = _mm_setr_epi8(
    14, 15, 12, 13,
    10, 11,  8,  9,
     6,  7,  4,  5,
     2,  3,  0,  1
  );
  const __m128i blockwiseReversed128_epi8_4 = _mm_setr_epi8(
     3,  2,  1,  0,
     7,  6,  5,  4,
    11, 10,  9,  8,
    15, 14, 13, 12
  );
  const __m128i blockwiseReversed128_epi16_4 = _mm_setr_epi8(
     6,  7,  4,  5,
     2,  3,  0,  1,
    14, 15, 12, 13,
    10, 11,  8,  9
  );

  __m128i substitutionCost32[4];
  std::size_t k;
  
  // We support 1, 2, and 4 byte objects for SSE comparison.
  // We always process 16 entries at once, so we may need multiple fetches
  // depending on object size.
  if constexpr (sizeof(T) <= 2) {
    __m128i substitutionCost16LX, substitutionCost16HX;
    
    if constexpr (sizeof(T) == 1) {
      __m128i a_ = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&a[i-16]));
      __m128i b_ = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&b[j-1]));
      a_ = _mm_shuffle_epi8(a_, reversedIdentity128_epi8);
      
      // int substitutionCost = a[i-1] == b[j-1] ? -1 : 0;
      
      // diag/diag2 will contain the following entries from the diagonal:
      // index  [0]0 [0]1 [0]2 [0]3 [1]0 [1]1 [1]2 [1]3 ... [4]0 [4]1 [4]2 [4]3
      // diag+i   -3   -2   -1    0   -7   -6   -5   -4 ...  -19  -18  -17  -16
      
      // substitutionCost8 contains the comparisons for the following indices in a and b:
      // index  0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15
      // a+i   -1  -2  -3  -4  -5  -6  -7  -8  -9 -10 -11 -12 -13 -14 -15 -16
      // b+j   -1   0   1   2   3   4   5   6   7   8   9  10  11  12  13  14
      // in substitutionCost8X we shuffle this so that it matches up with diag/diag2
      // (barring the offset induces by comparing i-1 against j-1)
      __m128i substitutionCost8 = _mm_cmpeq_epi8(a_, b_);
      __m128i substitutionCost8X = _mm_shuffle_epi8(substitutionCost8, blockwiseReversed128_epi8_4);
      // unpack with self so that 00 -> 00 00 and ff -> ff ff
      substitutionCost16LX = _mm_unpacklo_epi8(substitutionCost8X, substitutionCost8X);
      substitutionCost16HX = _mm_unpackhi_epi8(substitutionCost8X, substitutionCost8X);
    } else {
      __m128i a0 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&a[i-8]));
      __m128i a1 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&a[i-16]));
      __m128i b0 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&b[j-1]));
      __m128i b1 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&b[j+7]));
      a0 = _mm_shuffle_epi8(a0, reversedIdentity128_epi16);
      a1 = _mm_shuffle_epi8(a1, reversedIdentity128_epi16);
      __m128i substitutionCost16L = _mm_cmpeq_epi16(a0, b0);
      __m128i substitutionCost16H = _mm_cmpeq_epi16(a1, b1);
      substitutionCost16LX = _mm_shuffle_epi8(substitutionCost16L, blockwiseReversed128_epi16_4);
      substitutionCost16HX = _mm_shuffle_epi8(substitutionCost16H, blockwiseReversed128_epi16_4);
    }
    
    substitutionCost32[0] = _mm_unpacklo_epi16(substitutionCost16LX, substitutionCost16LX);
    substitutionCost32[1] = _mm_unpackhi_epi16(substitutionCost16LX, substitutionCost16LX);
    substitutionCost32[2] = _mm_unpacklo_epi16(substitutionCost16HX, substitutionCost16HX);
    substitutionCost32[3] = _mm_unpackhi_epi16(substitutionCost16HX, substitutionCost16HX);
  } else {
    assert(sizeof(T) == 4);
    
    for (k = 0; k < 4; ++k) {
      __m128i a_ = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&a[i-4-k*4]));
      __m128i b_ = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&b[j-1+k*4]));
      b_ = _mm_shuffle_epi32(b_, 0x1b); // simple reverse
      substitutionCost32[k] = _mm_cmpeq_epi32(a_, b_);
    }
  }
  
  __m128i diag_[5], diag2_[5];
  for (k = 0; k < 5; ++k) {
    diag_ [k] = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&diag [i-3-k*4]));
  }
  for (k = 0; k < 5; ++k) {
    diag2_[k] = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&diag2[i-3-k*4]));
  }
  
  // There’s a ton of debug stuff down here. You can use it for reference
  // or, of course, compile with -DLSTSSE_DEBUG if you’re feeling funny.
#ifdef LSTSSE_DEBUG
  for (k = 0; k < 5; ++k) {
    std::uint32_t diag0 = _mm_extract_epi32(diag_[k], 0);
    std::uint32_t diag1 = _mm_extract_epi32(diag_[k], 1);
    std::uint32_t diag2 = _mm_extract_epi32(diag_[k], 2);
    std::uint32_t diag3 = _mm_extract_epi32(diag_[k], 3);
    assert(diag0 == diag[i-k*4-3]);
    assert(diag1 == diag[i-k*4-2]);
    assert(diag2 == diag[i-k*4-1]);
    assert(diag3 == diag[i-k*4-0]);
  }
  for (k = 0; k < 5; ++k) {
    std::uint32_t diag20 = _mm_extract_epi32(diag2_[k], 0);
    std::uint32_t diag21 = _mm_extract_epi32(diag2_[k], 1);
    std::uint32_t diag22 = _mm_extract_epi32(diag2_[k], 2);
    std::uint32_t diag23 = _mm_extract_epi32(diag2_[k], 3);
    assert(diag20 == diag2[i-k*4-3]);
    assert(diag21 == diag2[i-k*4-2]);
    assert(diag22 == diag2[i-k*4-1]);
    assert(diag23 == diag2[i-k*4-0]);
  }
  
  for (k = 0; k < 4; ++k) {
    int sc0 = _mm_extract_epi32(substitutionCost32[k], 0);
    int sc1 = _mm_extract_epi32(substitutionCost32[k], 1);
    int sc2 = _mm_extract_epi32(substitutionCost32[k], 2);
    int sc3 = _mm_extract_epi32(substitutionCost32[k], 3);
    assert(sc0 == ((a[i-1-k*4-3] == b[j-1+k*4+3]) ? -1 : 0));
    assert(sc1 == ((a[i-1-k*4-2] == b[j-1+k*4+2]) ? -1 : 0));
    assert(sc2 == ((a[i-1-k*4-1] == b[j-1+k*4+1]) ? -1 : 0));
    assert(sc3 == ((a[i-1-k*4-0] == b[j-1+k*4+0]) ? -1 : 0));
  }
#endif // LSTSSE_DEBUG

  // reminders:
  // the arrays (diag, diag2, substitutionCost32) correspond to i:
  // index  [0]0 [0]1 [0]2 [0]3 [1]0 [1]1 [1]2 [1]3 ... [4]0 [4]1 [4]2 [4]3
  // i+       -3   -2   -1    0   -7   -6   -5   -4 ...  -19  -18  -17  -16
  // so when we need to access ...[i-1], we need to align the entries
  // in *reverse* order
  
  // diag[i] = min(
  //  diag2[i-1],
  //  diag2[i],
  //  diag[i-1] + substitutionCost
  // ) + 1;
  // 
  for (k = 0; k < 4; ++k) {
    __m128i diag2_i_m1 = _mm_alignr_epi8(diag2_[k], diag2_[k+1], 12);
    __m128i diag_i_m1  = _mm_alignr_epi8(diag_ [k], diag_ [k+1], 12);
    
    __m128i result3 = _mm_add_epi32(diag_i_m1,  substitutionCost32[k]);
    __m128i min = _mm_min_epi32(_mm_min_epi32(diag2_i_m1, diag2_[k]), result3);
    min = _mm_add_epi32(min, one128_epi32);
    
#ifdef LSTSSE_DEBUG
    std::uint32_t diag_i_m10 = _mm_extract_epi32(diag_i_m1, 0);
    std::uint32_t diag_i_m11 = _mm_extract_epi32(diag_i_m1, 1);
    std::uint32_t diag_i_m12 = _mm_extract_epi32(diag_i_m1, 2);
    std::uint32_t diag_i_m13 = _mm_extract_epi32(diag_i_m1, 3);
    assert(diag_i_m10 == diag[i-k*4-4]);
    assert(diag_i_m11 == diag[i-k*4-3]);
    assert(diag_i_m12 == diag[i-k*4-2]);
    assert(diag_i_m13 == diag[i-k*4-1]);
    
    std::uint32_t diag2_i_m10 = _mm_extract_epi32(diag2_i_m1, 0);
    std::uint32_t diag2_i_m11 = _mm_extract_epi32(diag2_i_m1, 1);
    std::uint32_t diag2_i_m12 = _mm_extract_epi32(diag2_i_m1, 2);
    std::uint32_t diag2_i_m13 = _mm_extract_epi32(diag2_i_m1, 3);
    assert(diag2_i_m10 == diag2[i-k*4-4]);
    assert(diag2_i_m11 == diag2[i-k*4-3]);
    assert(diag2_i_m12 == diag2[i-k*4-2]);
    assert(diag2_i_m13 == diag2[i-k*4-1]);
    
    std::uint32_t result30 = _mm_extract_epi32(result3, 0);
    std::uint32_t result31 = _mm_extract_epi32(result3, 1);
    std::uint32_t result32 = _mm_extract_epi32(result3, 2);
    std::uint32_t result33 = _mm_extract_epi32(result3, 3);
    
    assert(result30 == diag[i-1-k*4-3] + ((a[i-1-k*4-3] == b[j-1+k*4+3]) ? -1 : 0));
    assert(result31 == diag[i-1-k*4-2] + ((a[i-1-k*4-2] == b[j-1+k*4+2]) ? -1 : 0));
    assert(result32 == diag[i-1-k*4-1] + ((a[i-1-k*4-1] == b[j-1+k*4+1]) ? -1 : 0));
    assert(result33 == diag[i-1-k*4-0] + ((a[i-1-k*4-0] == b[j-1+k*4+0]) ? -1 : 0));
#endif // LSTSSE_DEBUG

    _mm_storeu_si128(reinterpret_cast<__m128i*>(&diag[i-k*4-3]), min);
  }
  
  // We just handled 16 entries at once. Yay!
  i -= 16;
}
#endif // __SSSE3__


#ifdef __AVX2__
static inline void performSSE_AVX2(const T* a, const T* b,
  std::size_t& i, std::size_t j, std::size_t bLen,
  std::uint32_t* diag, const std::uint32_t* diag2)
{
  const __m256i one256_epi32 = _mm256_set1_epi32(1);
  const __m256i reversedIdentity256_epi8 = _mm256_setr_epi8(
    15, 14, 13, 12,
    11, 10,  9,  8,
     7,  6,  5,  4,
     3,  2,  1,  0,
    15, 14, 13, 12,
    11, 10,  9,  8,
     7,  6,  5,  4,
     3,  2,  1,  0
  );

  const __m256i blockwiseReversed256_epi8_8 = _mm256_setr_epi8(
     7,  6,  5,  4,
     3,  2,  1,  0,
    15, 14, 13, 12,
    11, 10,  9,  8,
     7,  6,  5,  4,
     3,  2,  1,  0,
    15, 14, 13, 12,
    11, 10,  9,  8
  );

  const __m256i blockwiseReversed256_epi16_8 = _mm256_setr_epi8(
    14, 15, 12, 13,
    10, 11,  8,  9,
     6,  7,  4,  5,
     2,  3,  0,  1,
    14, 15, 12, 13,
    10, 11,  8,  9,
     6,  7,  4,  5,
     2,  3,  0,  1
  );

  __m256i substitutionCost32[4];
  std::size_t k;

  if (sizeof(T) <= 2) {
    if (sizeof(T) == 1) {
      __m256i a_ = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(&a[i-32]));
      __m256i b_ = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(&b[j-1]));
      a_ = _mm256_shuffle_epi8(a_, reversedIdentity256_epi8);
      a_ = _mm256_permute2x128_si256(a_, a_, 1); // swap hi/lo

      __m256i substitutionCost8 = _mm256_cmpeq_epi8(a_, b_);
      __m256i substitutionCost8X = _mm256_shuffle_epi8(substitutionCost8, blockwiseReversed256_epi8_8);
      __m128i sc8Xlo  = _mm256_extracti128_si256(substitutionCost8X, 0);
      __m128i sc8Xhi  = _mm256_extracti128_si256(substitutionCost8X, 1);
      substitutionCost32[0] = _mm256_cvtepi8_epi32(sc8Xlo);
      substitutionCost32[1] = _mm256_cvtepi8_epi32(_mm_srli_si128(sc8Xlo, 8));
      substitutionCost32[2] = _mm256_cvtepi8_epi32(sc8Xhi);
      substitutionCost32[3] = _mm256_cvtepi8_epi32(_mm_srli_si128(sc8Xhi, 8));
    } else {
      __m256i a0 = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(&a[i-16]));
      __m256i a1 = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(&a[i-32]));
      __m256i b0 = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(&b[j-1]));
      __m256i b1 = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(&b[j+15]));
      a0 = _mm256_permute2x128_si256(a0, a0, 1); // swap hi/lo
      a1 = _mm256_permute2x128_si256(a1, a1, 1); // swap hi/lo
      b0 = _mm256_shuffle_epi8(b0, blockwiseReversed256_epi16_8);
      b1 = _mm256_shuffle_epi8(b1, blockwiseReversed256_epi16_8);
      __m256i substitutionCost16L = _mm256_cmpeq_epi16(a0, b0);
      __m256i substitutionCost16H = _mm256_cmpeq_epi16(a1, b1);
      __m128i sc16Llo = _mm256_extracti128_si256(substitutionCost16L, 0);
      __m128i sc16Lhi = _mm256_extracti128_si256(substitutionCost16L, 1);
      __m128i sc16Hlo = _mm256_extracti128_si256(substitutionCost16H, 0);
      __m128i sc16Hhi = _mm256_extracti128_si256(substitutionCost16H, 1);
      substitutionCost32[0] = _mm256_cvtepi16_epi32(sc16Llo);
      substitutionCost32[1] = _mm256_cvtepi16_epi32(sc16Lhi);
      substitutionCost32[2] = _mm256_cvtepi16_epi32(sc16Hlo);
      substitutionCost32[3] = _mm256_cvtepi16_epi32(sc16Hhi);
    }
  } else {
    assert(sizeof(T) == 4);

    for (k = 0; k < 4; ++k) {
      __m256i a_ = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(&a[i-8-k*8]));
      __m256i b_ = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(&b[j-1+k*8]));
      b_ = _mm256_shuffle_epi32(b_, 0x1b); // simple reverse
      b_ = _mm256_permute2x128_si256(b_, b_, 1); // swap hi/lo
      substitutionCost32[k] = _mm256_cmpeq_epi32(a_, b_);
    }
  }

  __m256i diag_[5], diag2_[5];
  for (k = 0; k < 5; ++k) {
    diag_ [k] = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(&diag [i-7-k*8]));
  }
  for (k = 0; k < 5; ++k) {
    diag2_[k] = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(&diag2[i-7-k*8]));
  }

#ifdef LSTSSE_DEBUG
  for (k = 0; k < 5; ++k) {
    std::uint32_t diag0 = _mm256_extract_epi32(diag_[k], 0);
    std::uint32_t diag1 = _mm256_extract_epi32(diag_[k], 1);
    std::uint32_t diag2 = _mm256_extract_epi32(diag_[k], 2);
    std::uint32_t diag3 = _mm256_extract_epi32(diag_[k], 3);
    std::uint32_t diag4 = _mm256_extract_epi32(diag_[k], 4);
    std::uint32_t diag5 = _mm256_extract_epi32(diag_[k], 5);
    std::uint32_t diag6 = _mm256_extract_epi32(diag_[k], 6);
    std::uint32_t diag7 = _mm256_extract_epi32(diag_[k], 7);
    assert(diag0 == diag[i-k*8-7]);
    assert(diag1 == diag[i-k*8-6]);
    assert(diag2 == diag[i-k*8-5]);
    assert(diag3 == diag[i-k*8-4]);
    assert(diag4 == diag[i-k*8-3]);
    assert(diag5 == diag[i-k*8-2]);
    assert(diag6 == diag[i-k*8-1]);
    assert(diag7 == diag[i-k*8-0]);
  }
  for (k = 0; k < 5; ++k) {
    std::uint32_t diag20 = _mm256_extract_epi32(diag2_[k], 0);
    std::uint32_t diag21 = _mm256_extract_epi32(diag2_[k], 1);
    std::uint32_t diag22 = _mm256_extract_epi32(diag2_[k], 2);
    std::uint32_t diag23 = _mm256_extract_epi32(diag2_[k], 3);
    std::uint32_t diag24 = _mm256_extract_epi32(diag2_[k], 4);
    std::uint32_t diag25 = _mm256_extract_epi32(diag2_[k], 5);
    std::uint32_t diag26 = _mm256_extract_epi32(diag2_[k], 6);
    std::uint32_t diag27 = _mm256_extract_epi32(diag2_[k], 7);
    assert(diag20 == diag2[i-k*8-7]);
    assert(diag21 == diag2[i-k*8-6]);
    assert(diag22 == diag2[i-k*8-5]);
    assert(diag23 == diag2[i-k*8-4]);
    assert(diag24 == diag2[i-k*8-3]);
    assert(diag25 == diag2[i-k*8-2]);
    assert(diag26 == diag2[i-k*8-1]);
    assert(diag27 == diag2[i-k*8-0]);
  }
  
  for (k = 0; k < 4; ++k) {
    int sc0 = _mm256_extract_epi32(substitutionCost32[k], 0);
    int sc1 = _mm256_extract_epi32(substitutionCost32[k], 1);
    int sc2 = _mm256_extract_epi32(substitutionCost32[k], 2);
    int sc3 = _mm256_extract_epi32(substitutionCost32[k], 3);
    int sc4 = _mm256_extract_epi32(substitutionCost32[k], 4);
    int sc5 = _mm256_extract_epi32(substitutionCost32[k], 5);
    int sc6 = _mm256_extract_epi32(substitutionCost32[k], 6);
    int sc7 = _mm256_extract_epi32(substitutionCost32[k], 7);
    assert(sc0 == ((a[i-1-k*8-7] == b[j-1+k*8+7]) ? -1 : 0));
    assert(sc1 == ((a[i-1-k*8-6] == b[j-1+k*8+6]) ? -1 : 0));
    assert(sc2 == ((a[i-1-k*8-5] == b[j-1+k*8+5]) ? -1 : 0));
    assert(sc3 == ((a[i-1-k*8-4] == b[j-1+k*8+4]) ? -1 : 0));
    assert(sc4 == ((a[i-1-k*8-3] == b[j-1+k*8+3]) ? -1 : 0));
    assert(sc5 == ((a[i-1-k*8-2] == b[j-1+k*8+2]) ? -1 : 0));
    assert(sc6 == ((a[i-1-k*8-1] == b[j-1+k*8+1]) ? -1 : 0));
    assert(sc7 == ((a[i-1-k*8-0] == b[j-1+k*8+0]) ? -1 : 0));
  }
#endif // LSTSSE_DEBUG

  for (k = 0; k < 4; ++k) {
    __m256i diag2_i_m1 = _mm256_alignr_epi32_7(diag2_[k], diag2_[k+1]);
    __m256i diag_i_m1  = _mm256_alignr_epi32_7(diag_ [k], diag_ [k+1]);

    __m256i result3 = _mm256_add_epi32(diag_i_m1,  substitutionCost32[k]);
    __m256i min = _mm256_min_epi32(_mm256_min_epi32(diag2_i_m1, diag2_[k]), result3);
    min = _mm256_add_epi32(min, one256_epi32);

#ifdef LSTSSE_DEBUG
    std::uint32_t diag_i_m10 = _mm256_extract_epi32(diag_i_m1, 0);
    std::uint32_t diag_i_m11 = _mm256_extract_epi32(diag_i_m1, 1);
    std::uint32_t diag_i_m12 = _mm256_extract_epi32(diag_i_m1, 2);
    std::uint32_t diag_i_m13 = _mm256_extract_epi32(diag_i_m1, 3);
    std::uint32_t diag_i_m14 = _mm256_extract_epi32(diag_i_m1, 4);
    std::uint32_t diag_i_m15 = _mm256_extract_epi32(diag_i_m1, 5);
    std::uint32_t diag_i_m16 = _mm256_extract_epi32(diag_i_m1, 6);
    std::uint32_t diag_i_m17 = _mm256_extract_epi32(diag_i_m1, 7);
    assert(diag_i_m10 == diag[i-k*8-8]);
    assert(diag_i_m11 == diag[i-k*8-7]);
    assert(diag_i_m12 == diag[i-k*8-6]);
    assert(diag_i_m13 == diag[i-k*8-5]);
    assert(diag_i_m14 == diag[i-k*8-4]);
    assert(diag_i_m15 == diag[i-k*8-3]);
    assert(diag_i_m16 == diag[i-k*8-2]);
    assert(diag_i_m17 == diag[i-k*8-1]);
    
    std::uint32_t diag2_i_m10 = _mm256_extract_epi32(diag2_i_m1, 0);
    std::uint32_t diag2_i_m11 = _mm256_extract_epi32(diag2_i_m1, 1);
    std::uint32_t diag2_i_m12 = _mm256_extract_epi32(diag2_i_m1, 2);
    std::uint32_t diag2_i_m13 = _mm256_extract_epi32(diag2_i_m1, 3);
    std::uint32_t diag2_i_m14 = _mm256_extract_epi32(diag2_i_m1, 4);
    std::uint32_t diag2_i_m15 = _mm256_extract_epi32(diag2_i_m1, 5);
    std::uint32_t diag2_i_m16 = _mm256_extract_epi32(diag2_i_m1, 6);
    std::uint32_t diag2_i_m17 = _mm256_extract_epi32(diag2_i_m1, 7);
    assert(diag2_i_m10 == diag2[i-k*8-8]);
    assert(diag2_i_m11 == diag2[i-k*8-7]);
    assert(diag2_i_m12 == diag2[i-k*8-6]);
    assert(diag2_i_m13 == diag2[i-k*8-5]);
    assert(diag2_i_m14 == diag2[i-k*8-4]);
    assert(diag2_i_m15 == diag2[i-k*8-3]);
    assert(diag2_i_m16 == diag2[i-k*8-2]);
    assert(diag2_i_m17 == diag2[i-k*8-1]);
    
    std::uint32_t result30 = _mm256_extract_epi32(result3, 0);
    std::uint32_t result31 = _mm256_extract_epi32(result3, 1);
    std::uint32_t result32 = _mm256_extract_epi32(result3, 2);
    std::uint32_t result33 = _mm256_extract_epi32(result3, 3);
    std::uint32_t result34 = _mm256_extract_epi32(result3, 4);
    std::uint32_t result35 = _mm256_extract_epi32(result3, 5);
    std::uint32_t result36 = _mm256_extract_epi32(result3, 6);
    std::uint32_t result37 = _mm256_extract_epi32(result3, 7);
    
    assert(result30 == diag[i-1-k*8-7] + ((a[i-1-k*8-7] == b[j-1+k*8+7]) ? -1 : 0));
    assert(result31 == diag[i-1-k*8-6] + ((a[i-1-k*8-6] == b[j-1+k*8+6]) ? -1 : 0));
    assert(result32 == diag[i-1-k*8-5] + ((a[i-1-k*8-5] == b[j-1+k*8+5]) ? -1 : 0));
    assert(result33 == diag[i-1-k*8-4] + ((a[i-1-k*8-4] == b[j-1+k*8+4]) ? -1 : 0));
    assert(result34 == diag[i-1-k*8-3] + ((a[i-1-k*8-3] == b[j-1+k*8+3]) ? -1 : 0));
    assert(result35 == diag[i-1-k*8-2] + ((a[i-1-k*8-2] == b[j-1+k*8+2]) ? -1 : 0));
    assert(result36 == diag[i-1-k*8-1] + ((a[i-1-k*8-1] == b[j-1+k*8+1]) ? -1 : 0));
    assert(result37 == diag[i-1-k*8-0] + ((a[i-1-k*8-0] == b[j-1+k*8+0]) ? -1 : 0));
#endif // LSTSSE_DEBUG

    _mm256_storeu_si256(reinterpret_cast<__m256i*>(&diag[i-k*8-7]), min);
  }

  // We just handled 32 entries at once. Yay!
  i -= 32;
}
#endif // __AVX2__

};

/**
 * Default: If we don’t know better, just use the trivial implementation.
 * 
 * This is overloaded in multiple places and is the struct whose `perform`
 * method will ultimately be called from the outer loop.
 * 
 * Vec1 and Vec2 correspond to `diag` and `diag2`, respectively.
 */
template<typename Vec1, typename Vec2, typename Iterator1, typename Iterator2>
struct LevenshteinIteration : LevenshteinIterationBase<Vec1, Vec2, Iterator1, Iterator2> {
};

/**
 * Use a wrapper to decay the `diag` and `diag2` entries into pointers.
 */
template<typename Alloc1, typename Alloc2, typename T>
struct LevenshteinIterationSIMDWrap : private LevenshteinIterationSIMD<T> {
static inline void perform(const T* a, const T* b,
  std::size_t& i, std::size_t j, std::size_t bLen,
  std::vector<std::uint32_t, Alloc1>& diag,
  const std::vector<std::uint32_t, Alloc2>& diag2) {
  return LevenshteinIterationSIMD<T>::performSIMD(a, b, i, j, bLen, diag.data(), diag2.data());
}
};

/**
 * Use a wrapper to test whether we can use SSE instuctions.
 * 
 * T needs to be a scalar of size 1, 2 or 4.
 */
template<typename Alloc1, typename Alloc2, typename T>
struct LevenshteinIteration<std::vector<std::uint32_t, Alloc1>, std::vector<std::uint32_t, Alloc2>, const T*, const T*>
  : std::conditional<std::is_scalar<T>::value && (sizeof(T) == 1 || sizeof(T) == 2 || sizeof(T) == 4),
    LevenshteinIterationSIMDWrap<Alloc1, Alloc2, T>,
    LevenshteinIterationBase<std::vector<std::uint32_t, Alloc1>, std::vector<std::uint32_t, Alloc2>, const T*, const T*>
  >::type
{ };

/**
 * Always decay pointers to const.
 */
template<typename Alloc1, typename Alloc2, typename T>
struct LevenshteinIteration<std::vector<std::uint32_t, Alloc1>, std::vector<std::uint32_t, Alloc2>, T*, T*>
  : LevenshteinIteration<std::vector<std::uint32_t, Alloc1>, std::vector<std::uint32_t, Alloc2>, const T*, const T*>
{ };

/**
 * Outer loop of the diagonal algorithm variant.
 */
template<typename T, typename Iterator1, typename Iterator2>
T levenshteinDiagonal(Iterator1 a, Iterator1 aEnd, Iterator2 b, Iterator2 bEnd) {
  const std::size_t aLen = aEnd - a;
  const std::size_t bLen = bEnd - b;
  
  assert(0 < aLen);
  assert(aLen <= bLen);
  
  typedef AlignmentAllocator<T, alignment> Alloc;
  std::vector<T, Alloc> diag  (aLen + 1, T(0));
  std::vector<T, Alloc> diag2 (aLen + 1, T(0));
  
  std::size_t i, j, k;
  
  k = 0;
  for (k = 1; ; ++k) {
    assert(k <= aLen + bLen);
    
    std::size_t startRow = k > bLen ? k - bLen : 1;
    std::size_t endRow = k > aLen ? aLen : k - 1;
    
    assert(endRow >= startRow || k == 1);
    
    for (i = endRow; i >= startRow; ) {
      assert(i < k);
      j = k - i;
      
      assert(bLen >= j);
      assert(aLen >= i);
      
      LevenshteinIteration<std::vector<T, Alloc>, std::vector<T, Alloc>, Iterator1, Iterator2>
        ::perform(a, b, i, j, bLen, diag, diag2);
    }
    
    diag[0] = static_cast<T>(k);
    
    if (k <= aLen) {
      diag[k] = static_cast<T>(k);
    }
    
    if (k == aLen + bLen) {
      assert(startRow == endRow);
      return diag[startRow];
    }
    
    // switch buffers
    std::swap(diag, diag2);
  }
  
  assert(0);
}

/**
 * Outer loop of the row-based variant, used for non-random-access iterators.
 * 
 * based on https://github.com/sindresorhus/leven
 */
template<typename T, typename Iterator1, typename Iterator2>
T levenshteinRowBased(Iterator1 a, Iterator1 aEnd, Iterator2 b, Iterator2 bEnd) {
  std::vector<T> arr;
  
  std::size_t i = 0, j = 0;
  T ret(0);
  
  for (Iterator1 it = a; it != aEnd; ++it) {
    arr.push_back(++i);
  }
  
  arr.shrink_to_fit();

  for (; b != bEnd; ++b) {
    T tmp = j++;
    ret = j;
    i = 0;
    
    for (Iterator1 it = a; it != aEnd; ++it, ++i) {
      T tmp2 = *b == *it ? tmp : tmp + 1;
      tmp = arr[i];
      ret = arr[i] = tmp > ret ? tmp2 > ret ? ret + 1 : tmp2 : tmp2 > tmp ? tmp + 1 : tmp2;
    }
  }

  return ret;
}

/**
 * Preable for edge cases and skipping common prefixes/suffixes,
 * random access version.
 */
template<typename Iterator1, typename Iterator2>
std::size_t levenshtein(Iterator1 a, Iterator1 aEnd, Iterator2 b, Iterator2 bEnd,
  std::random_access_iterator_tag, std::random_access_iterator_tag) {
  if (aEnd - a > bEnd - b) {
    return levenshtein(b, bEnd, a, aEnd);
  }
  
  // skip common prefixes and suffixes
  while (a < aEnd && a[0] == b[0])
    ++a, ++b;
  
  while (a < aEnd && aEnd[-1] == bEnd[-1])
    --aEnd, --bEnd;
  
  std::size_t aLen = aEnd - a;
  std::size_t bLen = bEnd - b;
  
  if (aLen == 0) {
    return bLen;
  }
  
  if (aLen == 1) {
    return bLen - (std::find(b, bEnd, *a) == bEnd ? 0 : 1);
  }
  
  if (aLen + bLen <= std::numeric_limits<std::uint32_t>::max())
    return levenshteinDiagonal<std::uint32_t>(a, aEnd, b, bEnd);
  
  return levenshteinDiagonal<std::size_t>(a, aEnd, b, bEnd);
}

/**
 * Preable for edge cases and skipping common prefixes/suffixes,
 * non-random access version.
 */
template<typename Iterator1, typename Iterator2>
std::size_t levenshtein(Iterator1 a, Iterator1 aEnd, Iterator2 b, Iterator2 bEnd,
  std::bidirectional_iterator_tag, std::bidirectional_iterator_tag) {
  // skip common prefixes and suffixes
  while (a != aEnd && b != bEnd && *a == *b)
    ++a, ++b;
  
  while (a != aEnd && b != bEnd && *std::prev(aEnd) == *std::prev(bEnd))
    --aEnd, --bEnd;
  
  if (a == aEnd) {
    return std::distance(b, bEnd);
  }
  
  if (b == bEnd) {
    return std::distance(a, aEnd);
  }
  
  if (std::next(a) == aEnd) {
    std::size_t ret = 0, found = 0;
    for (; b != bEnd; ++b, ++ret)
      if (*b == *a)
        found = 1;
    return ret - found;
  }
  
  if (std::next(b) == bEnd) {
    std::size_t ret = 0, found = 0;
    for (; a != aEnd; ++a, ++ret)
      if (*b == *a)
        found = 1;
    return ret - found;
  }
  
  return levenshteinRowBased<std::size_t>(a, aEnd, b, bEnd);
}

// SFINAE checker for .data() and .size()
template<typename T>
struct has_data_and_size {
private:
  struct char2 { char _[2]; };
  template<typename U> static auto test(U* a) -> decltype(a->data() + a->size(), char(0));
  template<typename U> static auto test(const U* a) -> char2;
public:
  static constexpr bool value = sizeof(test(static_cast<T*>(nullptr))) == 1;
};

template<bool useDataAndSize>
struct LevenshteinContainer {};

/**
 * Use .data(), .size() when available.
 */
template<>
struct LevenshteinContainer<true> {
template<typename Container1, typename Container2>
static inline std::size_t calc(const Container1& a, const Container2& b) {
  return levenshtein(a.data(), a.data() + a.size(), b.data(), b.data() + b.size());
}
};

/**
 * Use std::begin(), std::end() otherwise.
 */
template<>
struct LevenshteinContainer<false> {
template<typename Container1, typename Container2>
static inline std::size_t calc(const Container1& a, const Container2& b) {
  return levenshtein(std::begin(a), std::end(a), std::begin(b), std::end(b));
}
};

template<typename Iterator1, typename Iterator2>
std::size_t levenshtein(Iterator1 a, Iterator1 aEnd, Iterator2 b, Iterator2 bEnd) {
  return levenshtein(a, aEnd, b, bEnd,
    typename std::iterator_traits<Iterator1>::iterator_category(),
    typename std::iterator_traits<Iterator2>::iterator_category());
}

template<typename Container1, typename Container2>
std::size_t levenshtein(const Container1& a, const Container2& b) {
  return LevenshteinContainer<has_data_and_size<Container1>::value &&
    has_data_and_size<Container2>::value>::calc(a, b);
}
}

#endif
