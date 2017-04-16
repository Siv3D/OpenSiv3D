/**
 * MIT License
 * 
 * Copyright (c) 2017 Tessil
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef TSL_HOPSCOTCH_HASH_H
#define TSL_HOPSCOTCH_HASH_H


#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <exception>
#include <functional>
#include <initializer_list>
#include <iterator>
#include <memory>
#include <ratio>
#include <stdexcept>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>

#if (defined(__GNUC__) && (__GNUC__ == 4) && (__GNUC_MINOR__ < 9))
#define TSL_NO_RANGE_ERASE_WITH_CONST_ITERATOR
#endif



/*
 * Only activate tsl_assert if TSL_DEBUG is defined. 
 * This way we avoid the performance hit when NDEBUG is not defined with assert as tsl_assert is used a lot
 * (people usually compile with "-O3" and not "-O3 -DNDEBUG").
 */
#ifdef TSL_DEBUG
#define tsl_assert(expr) assert(expr)
#else
#define tsl_assert(expr) (static_cast<void>(0))
#endif

namespace tsl {

/**
 * Grow the map by a factor of two keeping bucket_count to a power of two. It allows
 * the map to use a mask operation instead of a modulo operation to map a hash to a bucket.
 */
class power_of_two_growth_policy {
public:
    /**
     * Called on map creation and rehash. The number of buckets requested is passed by parameter.
     * This number is a minimum, the policy may update this value with a higher value if needed.
     */
    power_of_two_growth_policy(std::size_t& min_bucket_count_in_out) {
        const std::size_t min_bucket_count = MIN_BUCKETS_SIZE;
        
        min_bucket_count_in_out = std::max(min_bucket_count, min_bucket_count_in_out);
        min_bucket_count_in_out = round_up_to_power_of_two(min_bucket_count_in_out);
        m_mask = min_bucket_count_in_out - 1;
    }
    
    /**
     * Return the bucket [0, bucket_count()) to which the hash belongs.
     */
    std::size_t bucket_for_hash(std::size_t hash) const {
        return hash & m_mask;
    }
    
    /**
     * Return the bucket count to uses when the bucket array grows on rehash.
     */
    std::size_t next_bucket_count() const {
        return (m_mask + 1) * 2;
    }
    
private:    
    // TODO could be faster
    static std::size_t round_up_to_power_of_two(std::size_t value) {
        if(is_power_of_two(value)) {
            return value;
        }
        
        std::size_t power = 1;
        while(power < value) {
            power <<= 1;
        }
        
        return power;
    }
    
    static constexpr bool is_power_of_two(std::size_t value) {
        return value != 0 && (value & (value - 1)) == 0;
    }    
private:
    static const std::size_t MIN_BUCKETS_SIZE = 2;
    
    std::size_t m_mask;
};

/**
 * Grow the map by GrowthFactor::num/GrowthFactor::den and use a modulo to map a hash
 * to a bucket. Slower but it can be usefull if you want a slower growth.
 */
template<class GrowthFactor = std::ratio<3, 2>>
class mod_growth_policy {
public:
    mod_growth_policy(std::size_t& min_bucket_count_in_out) {
        const std::size_t min_bucket_count = MIN_BUCKETS_SIZE;
        
        min_bucket_count_in_out = std::max(min_bucket_count, min_bucket_count_in_out);
        m_bucket_count = min_bucket_count_in_out;
    }
    
    std::size_t bucket_for_hash(std::size_t hash) const {
        tsl_assert(m_bucket_count != 0);
        return hash % m_bucket_count;
    }
    
    std::size_t next_bucket_count() const {
        return static_cast<std::size_t>(
                    std::ceil(static_cast<double>(m_bucket_count) * REHASH_SIZE_MULTIPLICATION_FACTOR));
    }
    
private:
    static const std::size_t MIN_BUCKETS_SIZE = 2;
    static constexpr double REHASH_SIZE_MULTIPLICATION_FACTOR = 1.0*GrowthFactor::num/GrowthFactor::den;
    static_assert(REHASH_SIZE_MULTIPLICATION_FACTOR >= 1.1, "Grow factor should be >= 1.1.");
    
    std::size_t m_bucket_count;
};



namespace detail_hopscotch_hash {

static constexpr const std::array<std::size_t, 38> PRIMES = {{
    17ul, 29ul, 37ul, 53ul, 67ul, 79ul, 97ul, 131ul, 193ul, 257ul, 389ul, 521ul, 769ul, 1031ul, 1543ul, 2053ul, 
    3079ul, 6151ul, 12289ul, 24593ul, 49157ul, 98317ul, 196613ul, 393241ul, 786433ul, 1572869ul, 3145739ul, 
    6291469ul, 12582917ul, 25165843ul, 50331653ul, 100663319ul, 201326611ul, 402653189ul, 805306457ul, 
    1610612741ul, 3221225473ul, 4294967291ul
}};

template<unsigned int IPrime>
static std::size_t mod(std::size_t hash) { return hash % PRIMES[IPrime]; }

// MOD_PRIME[iprime](hash) returns hash % PRIMES[iprime]. This table allows for faster modulo as the
// compiler can optimize the modulo code better with a constant known at the compilation.
static constexpr const std::array<std::size_t(*)(std::size_t), 38> MOD_PRIME = {{ 
    &mod<0>, &mod<1>, &mod<2>, &mod<3>, &mod<4>, &mod<5>, &mod<6>, &mod<7>, &mod<8>, &mod<9>, &mod<10>, 
    &mod<11>, &mod<12>, &mod<13>, &mod<14>, &mod<15>, &mod<16>, &mod<17>, &mod<18>, &mod<19>, &mod<20>, 
    &mod<21>, &mod<22>, &mod<23>, &mod<24>, &mod<25>, &mod<26>, &mod<27>, &mod<28>, &mod<29>, &mod<30>, 
    &mod<31>, &mod<32>, &mod<33>, &mod<34>, &mod<35>, &mod<36>, &mod<37> 
}};

}

/**
 * Grow the map by using prime numbers as size. Slower than tsl::power_of_two_growth_policy in general 
 * but will probably distribute the values around better in the buckets with a poor hash function.
 */
class prime_growth_policy {
public:
    prime_growth_policy(std::size_t& min_bucket_count_in_out) {
        auto it_prime = std::lower_bound(tsl::detail_hopscotch_hash::PRIMES.begin(), 
                                         tsl::detail_hopscotch_hash::PRIMES.end(), min_bucket_count_in_out);
        if(it_prime == tsl::detail_hopscotch_hash::PRIMES.end()) {
            throw std::length_error("The map exceeds its maxmimum size.");
        }
        
        m_iprime = static_cast<unsigned int>(std::distance(tsl::detail_hopscotch_hash::PRIMES.begin(), it_prime));
        min_bucket_count_in_out = *it_prime;
    }
    
    std::size_t bucket_for_hash(std::size_t hash) const {
        return bucket_for_hash_iprime(hash, m_iprime);
    }
    
    std::size_t next_bucket_count() const {
        if(m_iprime + 1 >= tsl::detail_hopscotch_hash::PRIMES.size()) {
            throw std::length_error("The map exceeds its maxmimum size.");
        }
        
        return tsl::detail_hopscotch_hash::PRIMES[m_iprime + 1];
    }   
    
private:  
    std::size_t bucket_for_hash_iprime(std::size_t hash, unsigned int iprime) const {
        tsl_assert(iprime < tsl::detail_hopscotch_hash::MOD_PRIME.size());
        return tsl::detail_hopscotch_hash::MOD_PRIME[iprime](hash);
    }
    
private:
    unsigned int m_iprime;
};


namespace detail_hopscotch_hash {
    
    
    
template<typename T>
struct make_void {
    using type = void;
};


template<typename T, typename = void>
struct has_is_transparent : std::false_type {
};

template<typename T>
struct has_is_transparent<T, typename make_void<typename T::is_transparent>::type> : std::true_type {
};

template<typename T, typename = void>
struct has_key_compare : std::false_type {
};

template<typename T>
struct has_key_compare<T, typename make_void<typename T::key_compare>::type> : std::true_type {
};





/*
 * smallest_type_for_min_bits::type returns the smallest type that can fit MinBits.
 */
static const size_t SMALLEST_TYPE_MAX_BITS_SUPPORTED = 64;
template<unsigned int MinBits, typename Enable = void>
class smallest_type_for_min_bits {
};

template<unsigned int MinBits>
class smallest_type_for_min_bits<MinBits, typename std::enable_if<(MinBits > 0) && (MinBits <= 8)>::type> {
public:
    using type = std::uint8_t;
};

template<unsigned int MinBits>
class smallest_type_for_min_bits<MinBits, typename std::enable_if<(MinBits > 8) && (MinBits <= 16)>::type> {
public:
    using type = std::uint16_t;
};

template<unsigned int MinBits>
class smallest_type_for_min_bits<MinBits, typename std::enable_if<(MinBits > 16) && (MinBits <= 32)>::type> {
public:
    using type = std::uint32_t;
};

template<unsigned int MinBits>
class smallest_type_for_min_bits<MinBits, typename std::enable_if<(MinBits > 32) && (MinBits <= 64)>::type> {
public:
    using type = std::uint64_t;
};
        


/*
 * Each bucket may store up to three elements:
 * - An aligned storage to store a value_type object with placement-new.
 * - An (optional) hash of the value in the bucket.
 * - An unsigned integer of type neighborhood_bitmap used to tell us which buckets in the neighborhood of the 
 *   current bucket contain a value with a hash belonging to the current bucket. 
 * 
 * For a bucket 'b' a bit 'i' (counting from 0 and from the least significant bit to the most significant) 
 * set to 1 means that the bucket 'b+i' contains a value with a hash belonging to bucket 'b'.
 * The bits used for that, start from the third least significant bit.
 * 
 * The least significant bit is set to 1 if there is a value in the bucket storage.
 * The second least significant bit is set to 1 if there is an overflow. More than NeighborhoodSize values 
 * give the same hash, all overflow values are stored in the m_overflow_elements list of the map.
 */
static const size_t NB_RESERVED_BITS_IN_NEIGHBORHOOD = 2; 


template<bool StoreHash>
class hopscotch_bucket_hash {
public:    
    using hash_type = std::false_type;
    
    bool bucket_hash_equal(std::size_t /*hash*/) const {
        return true;
    }
    
    std::size_t truncated_bucket_hash() const {
        assert(false);
        return 0;
    }
    
protected:    
    void copy_hash(const hopscotch_bucket_hash& ) {
    }
    
    void set_hash(std::size_t /*hash*/) {
    }
};

template<>
class hopscotch_bucket_hash<true> {
public:
    using hash_type = std::uint32_t;
    
    bool bucket_hash_equal(std::size_t hash) const {
        return m_hash == static_cast<std::uint32_t>(hash);
    }
    
    std::size_t truncated_bucket_hash() const {
        return m_hash;
    }
    
protected:    
    void copy_hash(const hopscotch_bucket_hash& bucket) {
        m_hash = bucket.m_hash;
    }
    
    void set_hash(std::size_t hash) {
        m_hash = static_cast<std::uint32_t>(hash);
    }
    
private:    
    hash_type m_hash;
};

template<typename ValueType, unsigned int NeighborhoodSize, bool StoreHash>
class hopscotch_bucket : public hopscotch_bucket_hash<StoreHash> {
private:
    static const size_t MAX_NEIGHBORHOOD_SIZE = SMALLEST_TYPE_MAX_BITS_SUPPORTED - NB_RESERVED_BITS_IN_NEIGHBORHOOD; 
    
    /*
     * NeighborhoodSize need to be between 0 and MAX_NEIGHBORHOOD_SIZE.
     */
    static_assert(NeighborhoodSize > 0, "NeighborhoodSize should be > 0.");
    static_assert(NeighborhoodSize <= MAX_NEIGHBORHOOD_SIZE, "NeighborhoodSize should be <= 62.");
    static_assert(!StoreHash || NeighborhoodSize <= MAX_NEIGHBORHOOD_SIZE - 32, 
                  "NeighborhoodSize should be <= 30 if StoreHash is true.");
    
public:
    using value_type = ValueType;
    using neighborhood_bitmap = 
                    typename smallest_type_for_min_bits<NeighborhoodSize + NB_RESERVED_BITS_IN_NEIGHBORHOOD>::type;


    hopscotch_bucket() noexcept : m_neighborhood_infos(0) {
        tsl_assert(is_empty());
    }
    
    
    hopscotch_bucket(const hopscotch_bucket& bucket) 
        noexcept(std::is_nothrow_copy_constructible<value_type>::value) : m_neighborhood_infos(0) 
    {
        if(!bucket.is_empty()) {
            ::new (static_cast<void*>(std::addressof(m_value))) value_type(bucket.get_value());
            this->copy_hash(bucket);
        }
        
        m_neighborhood_infos = bucket.m_neighborhood_infos;
    }
    
    hopscotch_bucket(hopscotch_bucket&& bucket)
        noexcept(std::is_nothrow_move_constructible<value_type>::value) : m_neighborhood_infos(0) 
    {
        if(!bucket.is_empty()) {
            ::new (static_cast<void*>(std::addressof(m_value))) value_type(std::move(bucket.get_value()));
            this->copy_hash(bucket);
        }
        
        m_neighborhood_infos = bucket.m_neighborhood_infos;
    }
     
    hopscotch_bucket& operator=(const hopscotch_bucket& bucket) 
        noexcept(std::is_nothrow_copy_constructible<value_type>::value) 
    {
        if(this != &bucket) {
            if(!is_empty()) {
                destroy_value();
                set_is_empty(true);
            }
            
            if(!bucket.is_empty()) {
                ::new (static_cast<void*>(std::addressof(m_value))) value_type(bucket.get_value());
                this->copy_hash(bucket);
            }
            
            m_neighborhood_infos = bucket.m_neighborhood_infos;
        }
        
        return *this;
    }
    
    hopscotch_bucket& operator=(hopscotch_bucket&& bucket) 
         noexcept(std::is_nothrow_move_constructible<value_type>::value) 
    {
        if(!is_empty()) {
            destroy_value();
            set_is_empty(true);
        }

        if(!bucket.is_empty()) {
            ::new (static_cast<void*>(std::addressof(m_value))) value_type(std::move(bucket.get_value()));
            this->copy_hash(bucket);
        }

        m_neighborhood_infos = bucket.m_neighborhood_infos;

        return *this;
    }        
     
    ~hopscotch_bucket() noexcept {
        if(!is_empty()) {
            destroy_value();
        }
        
        m_neighborhood_infos = 0;
    }
    
    neighborhood_bitmap get_neighborhood_infos() const noexcept {
        return static_cast<neighborhood_bitmap>(m_neighborhood_infos >> NB_RESERVED_BITS_IN_NEIGHBORHOOD);
    }
    
    void set_overflow(bool has_overflow) noexcept {
        if(has_overflow) {
            m_neighborhood_infos = static_cast<neighborhood_bitmap>(m_neighborhood_infos | 2);
        }
        else {
            m_neighborhood_infos = static_cast<neighborhood_bitmap>(m_neighborhood_infos & ~2);
        }
    }
    
    bool has_overflow() const noexcept {
        return (m_neighborhood_infos & 2) != 0;
    }
    
    bool is_empty() const noexcept {
        return (m_neighborhood_infos & 1) == 0;
    }
    
    template<typename P>
    void set_value(P&& value, std::size_t hash) {
        if(!is_empty()) {
            destroy_value();
            ::new (static_cast<void*>(std::addressof(m_value))) value_type(std::forward<P>(value));
        }
        else {
            ::new (static_cast<void*>(std::addressof(m_value))) value_type(std::forward<P>(value));
            set_is_empty(false);
        }
        
        this->set_hash(hash);
    }
    
    void remove_value() noexcept {
        if(!is_empty()) {
            destroy_value();
            set_is_empty(true);
        }
    }
    
    void toggle_neighbor_presence(std::size_t ineighbor) noexcept {
        tsl_assert(ineighbor <= NeighborhoodSize);
        m_neighborhood_infos = static_cast<neighborhood_bitmap>(
                                    m_neighborhood_infos ^ (1ull << (ineighbor + NB_RESERVED_BITS_IN_NEIGHBORHOOD)));
    }
    
    bool check_neighbor_presence(std::size_t ineighbor) const noexcept {
        tsl_assert(ineighbor <= NeighborhoodSize);
        if(((m_neighborhood_infos >> (ineighbor + NB_RESERVED_BITS_IN_NEIGHBORHOOD)) & 1) == 1) {
            return true;
        }
        
        return false;
    }
    
    value_type& get_value() noexcept {
        tsl_assert(!is_empty());
        return *reinterpret_cast<value_type*>(std::addressof(m_value));
    }
    
    const value_type& get_value() const noexcept {
        tsl_assert(!is_empty());
        return *reinterpret_cast<const value_type*>(std::addressof(m_value));
    }
    
    void swap_value_into_empty_bucket(hopscotch_bucket& empty_bucket) {
        tsl_assert(empty_bucket.is_empty());
        if(!is_empty()) {
            ::new (static_cast<void*>(std::addressof(empty_bucket.m_value))) value_type(std::move(get_value()));
            empty_bucket.copy_hash(*this);
            empty_bucket.set_is_empty(false);
            
            destroy_value();
            set_is_empty(true);
        }
    }
    
    void clear() noexcept {
        if(!is_empty()) {
            destroy_value();
        }
        
        m_neighborhood_infos = 0;
        tsl_assert(is_empty());
    }
    
private:
    void set_is_empty(bool is_empty) noexcept {
        if(is_empty) {
            m_neighborhood_infos = static_cast<neighborhood_bitmap>(m_neighborhood_infos & ~1);
        }
        else {
            m_neighborhood_infos = static_cast<neighborhood_bitmap>(m_neighborhood_infos | 1);
        }
    }
    
    void destroy_value() noexcept {
        try {
            tsl_assert(!is_empty());
            
            get_value().~value_type();
        }
        catch(...) {
            std::terminate();
        }
    }
    
private:
    using storage = typename std::aligned_storage<sizeof(value_type), alignof(value_type)>::type;
    
    neighborhood_bitmap m_neighborhood_infos;
    storage m_value;
};


/**
 * Internal common class used by hopscotch_(sc)_map and hopscotch_(sc)_set.
 * 
 * ValueType is what will be stored by hopscotch_hash (usually std::pair<Key, T> for map and Key for set).
 * 
 * KeySelect should be a FunctionObject which takes a ValueType in parameter and returns a reference to the key.
 * 
 * ValueSelect should be a FunctionObject which takes a ValueType in parameter and returns a reference to the value.
 * ValueSelect should be void if there is no value (in set for example).
 * 
 * OverflowContainer will be used as containers for overflown elements. Usually it should be a list<ValueType>
 * or a set<Key>/map<Key, T>.
 */
template<class ValueType,
         class KeySelect,
         class ValueSelect,
         class Hash,
         class KeyEqual,
         class Allocator,
         unsigned int NeighborhoodSize,
         bool StoreHash,
         class GrowthPolicy,
         class OverflowContainer>
class hopscotch_hash {
    static_assert(!StoreHash || std::is_same<GrowthPolicy, tsl::power_of_two_growth_policy>::value, 
                  "StoreHash can only be used with the tsl::power_of_two_growth_policy GrowthPolicy.");
    
public:
    template<bool is_const>
    class hopscotch_iterator;
    
    using key_type = typename KeySelect::key_type;
    using value_type = ValueType;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using hasher = Hash;
    using key_equal = KeyEqual;
    using allocator_type = Allocator;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using iterator = hopscotch_iterator<false>;
    using const_iterator = hopscotch_iterator<true>;
    
private:
    using hopscotch_bucket = tsl::detail_hopscotch_hash::hopscotch_bucket<ValueType, NeighborhoodSize, StoreHash>;
    using neighborhood_bitmap = typename hopscotch_bucket::neighborhood_bitmap;
    
    using buckets_allocator = typename std::allocator_traits<allocator_type>::template rebind_alloc<hopscotch_bucket>;
    using buckets_container_type = std::vector<hopscotch_bucket, buckets_allocator>;  
    
    using overflow_container_type = OverflowContainer;
    
    using iterator_buckets = typename buckets_container_type::iterator; 
    using const_iterator_buckets = typename buckets_container_type::const_iterator;
    
    using iterator_overflow = typename overflow_container_type::iterator; 
    using const_iterator_overflow = typename overflow_container_type::const_iterator; 
    
public:    
    /**
     * The 'operator*()' and 'operator->()' methods return a const reference and const pointer respectively to the 
     * stored value type.
     * 
     * In case of a map, to get a modifiable reference to the value associated to a key (the '.second' in the 
     * stored pair), you have to call 'value()'.
     */
    template<bool is_const>
    class hopscotch_iterator {
        friend class hopscotch_hash;
    private:
        using iterator_bucket = typename std::conditional<is_const, 
                                                            typename hopscotch_hash::const_iterator_buckets, 
                                                            typename hopscotch_hash::iterator_buckets>::type;
        using iterator_overflow = typename std::conditional<is_const, 
                                                            typename hopscotch_hash::const_iterator_overflow, 
                                                            typename hopscotch_hash::iterator_overflow>::type;
    
        
        hopscotch_iterator(iterator_bucket buckets_iterator, iterator_bucket buckets_end_iterator, 
                           iterator_overflow overflow_iterator) noexcept : 
            m_buckets_iterator(buckets_iterator), m_buckets_end_iterator(buckets_end_iterator),
            m_overflow_iterator(overflow_iterator)
        {
        }
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = const typename hopscotch_hash::value_type;
        using difference_type = std::ptrdiff_t;
        using reference = value_type&;
        using pointer = value_type*;
        
        
        hopscotch_iterator() noexcept {
        }
        
        hopscotch_iterator(const hopscotch_iterator<false>& other) noexcept :
            m_buckets_iterator(other.m_buckets_iterator), m_buckets_end_iterator(other.m_buckets_end_iterator),
            m_overflow_iterator(other.m_overflow_iterator)
        {
        }
        
        const typename hopscotch_hash::key_type& key() const {
            if(m_buckets_iterator != m_buckets_end_iterator) {
                return KeySelect()(m_buckets_iterator->get_value());
            }
            
            return KeySelect()(*m_overflow_iterator);
        }

        template<class U = ValueSelect, typename std::enable_if<!std::is_same<U, void>::value>::type* = nullptr>
        typename std::conditional<is_const, const typename U::value_type&, typename U::value_type&>::type value() const
        {
            if(m_buckets_iterator != m_buckets_end_iterator) {
                return m_buckets_iterator->get_value().second;
            }
            
            return m_overflow_iterator->second;
        }
        
        reference operator*() const { 
            if(m_buckets_iterator != m_buckets_end_iterator) {
                return m_buckets_iterator->get_value();
            }
            
            return *m_overflow_iterator;
        }
        
        pointer operator->() const { 
            if(m_buckets_iterator != m_buckets_end_iterator) {
                return std::addressof(m_buckets_iterator->get_value()); 
            }
            
            return std::addressof(*m_overflow_iterator); 
        }
        
        hopscotch_iterator& operator++() {
            if(m_buckets_iterator == m_buckets_end_iterator) {
                ++m_overflow_iterator;
                return *this;
            }
            
            do {
                ++m_buckets_iterator;
            } while(m_buckets_iterator != m_buckets_end_iterator && m_buckets_iterator->is_empty());
            
            return *this; 
        }
        hopscotch_iterator operator++(int) {
            hopscotch_iterator tmp(*this);
            ++*this;
            
            return tmp;
        }
        
        friend bool operator==(const hopscotch_iterator& lhs, const hopscotch_iterator& rhs) { 
            return lhs.m_buckets_iterator == rhs.m_buckets_iterator && 
                   lhs.m_buckets_end_iterator == rhs.m_buckets_end_iterator &&
                   lhs.m_overflow_iterator == rhs.m_overflow_iterator; 
        }
        
        friend bool operator!=(const hopscotch_iterator& lhs, const hopscotch_iterator& rhs) { 
            return !(lhs == rhs); 
        }
    private:
        iterator_bucket m_buckets_iterator;
        iterator_bucket m_buckets_end_iterator;
        iterator_overflow m_overflow_iterator;
    };
    

    
public:
    template<class OC = OverflowContainer, typename std::enable_if<!has_key_compare<OC>::value>::type* = nullptr>
    hopscotch_hash(size_type bucket_count, 
                  const Hash& hash,
                  const KeyEqual& equal,
                  const Allocator& alloc,
                  float max_load_factor) :  m_buckets(alloc), 
                                            m_overflow_elements(alloc),
                                            m_nb_elements(0),
                                            m_growth_policy(bucket_count),
                                            m_hash(hash), m_key_equal(equal)
    {
        if(bucket_count > max_bucket_count()) {
            throw std::length_error("The map exceeds its maxmimum size.");
        }
        
        m_buckets.resize(bucket_count + NeighborhoodSize - 1);
        this->max_load_factor(max_load_factor);
    }
    
    template<class OC = OverflowContainer, typename std::enable_if<has_key_compare<OC>::value>::type* = nullptr>
    hopscotch_hash(size_type bucket_count, 
                  const Hash& hash,
                  const KeyEqual& equal,
                  const Allocator& alloc,
                  float max_load_factor,
                  const typename OC::key_compare& comp) : m_buckets(alloc), 
                                                          m_overflow_elements(comp, alloc),
                                                          m_nb_elements(0), 
                                                          m_growth_policy(bucket_count),
                                                          m_hash(hash), m_key_equal(equal)
    {
        if(bucket_count > max_bucket_count()) {
            throw std::length_error("The map exceeds its maxmimum size.");
        }
        
        m_buckets.resize(bucket_count + NeighborhoodSize - 1);
        this->max_load_factor(max_load_factor);
    }
    
    hopscotch_hash(const hopscotch_hash& other) = default;
    
    hopscotch_hash(hopscotch_hash&& other) noexcept(
                                            std::is_nothrow_move_constructible<buckets_container_type>::value &&
                                            std::is_nothrow_move_constructible<overflow_container_type>::value &&
                                            std::is_nothrow_move_constructible<Hash>::value &&
                                            std::is_nothrow_move_constructible<KeyEqual>::value
                                          )
                                          : m_buckets(std::move(other.m_buckets)),
                                            m_overflow_elements(std::move(other.m_overflow_elements)),
                                            m_nb_elements(other.m_nb_elements),
                                            m_growth_policy(other.m_growth_policy),
                                            m_max_load_factor(other.m_max_load_factor),
                                            m_load_threshold(other.m_load_threshold),
                                            m_hash(std::move(other.m_hash)),
                                            m_key_equal(std::move(other.m_key_equal))
    {
        other.clear();
    }
    
    hopscotch_hash& operator=(const hopscotch_hash& other) = default;
    
    hopscotch_hash& operator=(hopscotch_hash&& other) {
        other.swap(*this);
        other.clear();
        
        return *this;
    }
    
    allocator_type get_allocator() const {
        return m_buckets.get_allocator();
    }
    
    
    /*
     * Iterators
     */
    iterator begin() noexcept {
        return iterator(get_first_non_empty_buckets_iterator(), m_buckets.end(), m_overflow_elements.begin());
    }
    
    const_iterator begin() const noexcept {
        return cbegin();
    }
    
    const_iterator cbegin() const noexcept {
        return const_iterator(get_first_non_empty_buckets_iterator(), m_buckets.cend(), m_overflow_elements.cbegin());
    }
    
    iterator end() noexcept {
        return iterator(m_buckets.end(), m_buckets.end(), m_overflow_elements.end());
    }
    
    const_iterator end() const noexcept {
        return cend();
    }
    
    const_iterator cend() const noexcept {
        return const_iterator(m_buckets.cend(), m_buckets.cend(), m_overflow_elements.cend());
    }
    
    
    /*
     * Capacity
     */
    bool empty() const noexcept {
        return m_nb_elements == 0;
    }
    
    size_type size() const noexcept {
        return m_nb_elements;
    }
    
    size_type max_size() const noexcept {
        return m_buckets.max_size();
    }
    
    /*
     * Modifiers
     */
    void clear() noexcept {
        for(auto& bucket : m_buckets) {
            bucket.clear();
        }
        
        m_overflow_elements.clear();
        m_nb_elements = 0;
    }
    
    
    std::pair<iterator, bool> insert(const value_type& value) { 
        return insert_internal(value); 
    }
        
    template<class P, typename std::enable_if<std::is_constructible<value_type, P&&>::value>::type* = nullptr>
    std::pair<iterator, bool> insert(P&& value) { 
        return emplace(std::forward<P>(value)); 
    }
    
    std::pair<iterator, bool> insert(value_type&& value) { 
        return insert_internal(std::move(value)); 
    }
    
    
    iterator insert(const_iterator hint, const value_type& value) { 
        if(hint != cend() && m_key_equal(KeySelect()(*hint), KeySelect()(value))) { 
            return get_mutable_iterator(hint); 
        }
        
        return insert(value).first; 
    }
        
    template<class P, typename std::enable_if<std::is_constructible<value_type, P&&>::value>::type* = nullptr>
    iterator insert(const_iterator hint, P&& value) {
        value_type val(std::forward<P>(value));
        if(hint != cend() && m_key_equal(KeySelect()(*hint), KeySelect()(val))) { 
            return get_mutable_iterator(hint); 
        }
        
        return insert(std::move(val)).first;
    }
    
    iterator insert(const_iterator hint, value_type&& value) { 
        if(hint != cend() && m_key_equal(KeySelect()(*hint), KeySelect()(value))) { 
            return get_mutable_iterator(hint); 
        }
        
        return insert(std::move(value)).first; 
    }
    
    
    template<class InputIt>
    void insert(InputIt first, InputIt last) {
        if(std::is_base_of<std::forward_iterator_tag, 
                          typename std::iterator_traits<InputIt>::iterator_category>::value) 
        {
            const auto nb_elements_insert = std::distance(first, last);
            const std::size_t nb_free_buckets = m_buckets.size() - (m_nb_elements - m_overflow_elements.size());
            
            if(nb_elements_insert > 0 && nb_free_buckets < static_cast<std::size_t>(nb_elements_insert)) {
                reserve(m_nb_elements + (nb_elements_insert - nb_free_buckets));
            }
        }
        
        for(; first != last; ++first) {
            insert(*first);
        }
    }
    
    
    template<class M>
    std::pair<iterator, bool> insert_or_assign(const key_type& k, M&& obj) { 
        return insert_or_assign_internal(k, std::forward<M>(obj)); 
    }

    template<class M>
    std::pair<iterator, bool> insert_or_assign(key_type&& k, M&& obj) { 
        return insert_or_assign_internal(std::move(k), std::forward<M>(obj)); 
    }
    
    
    template<class M>
    iterator insert_or_assign(const_iterator hint, const key_type& k, M&& obj) {
        if(hint != cend() && m_key_equal(KeySelect()(*hint), k)) { 
            auto it = get_mutable_iterator(hint); 
            it.value() = std::forward<M>(obj);
            
            return it;
        }
        
        return insert_or_assign(k, std::forward<M>(obj)).first;
    }
    
    template<class M>
    iterator insert_or_assign(const_iterator hint, key_type&& k, M&& obj) {
        if(hint != cend() && m_key_equal(KeySelect()(*hint), k)) {
            auto it = get_mutable_iterator(hint); 
            it.value() = std::forward<M>(obj);
            
            return it;
        }
        
        return insert_or_assign(std::move(k), std::forward<M>(obj)).first;
    }
    
    
    template<class... Args>
    std::pair<iterator, bool> emplace(Args&&... args) {
        return insert(value_type(std::forward<Args>(args)...));
    }
    
    template<class... Args>
    iterator emplace_hint(const_iterator hint, Args&&... args) {
        return insert(hint, value_type(std::forward<Args>(args)...));        
    }
    
    template<class... Args>
    std::pair<iterator, bool> try_emplace(const key_type& k, Args&&... args) { 
        return try_emplace_internal(k, std::forward<Args>(args)...);
    }
    
    template<class... Args>
    std::pair<iterator, bool> try_emplace(key_type&& k, Args&&... args) {
        return try_emplace_internal(std::move(k), std::forward<Args>(args)...);
    }
    
    template<class... Args>
    iterator try_emplace(const_iterator hint, const key_type& k, Args&&... args) { 
        if(hint != cend() && m_key_equal(KeySelect()(*hint), k)) { 
            return get_mutable_iterator(hint); 
        }
        
        return try_emplace(k, std::forward<Args>(args)...).first;
    }
    
    template<class... Args>
    iterator try_emplace(const_iterator hint, key_type&& k, Args&&... args) {
        if(hint != cend() && m_key_equal(KeySelect()(*hint), k)) { 
            return get_mutable_iterator(hint); 
        }
        
        return try_emplace(std::move(k), std::forward<Args>(args)...).first;
    }
    
    
    
    iterator erase(iterator pos) {
        return erase(const_iterator(pos));
    }
    
    iterator erase(const_iterator pos) {
        const std::size_t ibucket_for_hash = bucket_for_hash(m_hash(pos.key()));
        
        if(pos.m_buckets_iterator != pos.m_buckets_end_iterator) {
            auto it_bucket = m_buckets.begin() + std::distance(m_buckets.cbegin(), pos.m_buckets_iterator);
            erase_from_bucket(it_bucket, ibucket_for_hash);
            
            return ++iterator(it_bucket, m_buckets.end(), m_overflow_elements.begin()); 
        }
        else {
            auto it_next_overflow = erase_from_overflow(pos.m_overflow_iterator, ibucket_for_hash);
            return iterator(m_buckets.end(), m_buckets.end(), it_next_overflow);
        }
    }
    
    iterator erase(const_iterator first, const_iterator last) {
        if(first == last) {
            return get_mutable_iterator(first);
        }
        
        auto to_delete = erase(first);
        while(to_delete != last) {
            to_delete = erase(to_delete);
        }
        
        return to_delete;
    }
    
    
    template<class K>
    size_type erase(const K& key) {
        const std::size_t hash = m_hash(key);
        const std::size_t ibucket_for_hash = bucket_for_hash(hash);
        
        auto it_find = find_in_buckets(key, hash, m_buckets.begin() + ibucket_for_hash);
        if(it_find != m_buckets.end()) {
            erase_from_bucket(it_find, ibucket_for_hash);

            return 1;
        }
        
        if(m_buckets[ibucket_for_hash].has_overflow()) {
            auto it_overflow = find_in_overflow(key);
            if(it_overflow != m_overflow_elements.end()) {
                erase_from_overflow(it_overflow, ibucket_for_hash);
                
                return 1;
            }
        }
        
        return 0;
    }
    
    void swap(hopscotch_hash& other) {
        using std::swap;
        
        swap(m_buckets, other.m_buckets);
        swap(m_overflow_elements, other.m_overflow_elements);
        swap(m_nb_elements, other.m_nb_elements);
        swap(m_growth_policy, other.m_growth_policy);
        swap(m_max_load_factor, other.m_max_load_factor);
        swap(m_load_threshold, other.m_load_threshold);
        swap(m_hash, other.m_hash);
        swap(m_key_equal, other.m_key_equal);
    }
    
    
    /*
     * Lookup
     */
    template<class K, class U = ValueSelect, typename std::enable_if<!std::is_same<U, void>::value>::type* = nullptr>
    typename U::value_type& at(const K& key) {
        return at(key, m_hash(key));
    }
    
    template<class K, class U = ValueSelect, typename std::enable_if<!std::is_same<U, void>::value>::type* = nullptr>
    typename U::value_type& at(const K& key, std::size_t hash) {
        return const_cast<typename U::value_type&>(static_cast<const hopscotch_hash*>(this)->at(key, hash));
    }
    
    
    template<class K, class U = ValueSelect, typename std::enable_if<!std::is_same<U, void>::value>::type* = nullptr>
    const typename U::value_type& at(const K& key) const {
        return at(key, m_hash(key));
    }
    
    template<class K, class U = ValueSelect, typename std::enable_if<!std::is_same<U, void>::value>::type* = nullptr>
    const typename U::value_type& at(const K& key, std::size_t hash) const {
        using T = typename U::value_type;
        
        const T* value = find_value_internal(key, hash, m_buckets.begin() + bucket_for_hash(hash));
        if(value == nullptr) {
            throw std::out_of_range("Couldn't find key.");
        }
        else {
            return *value;
        }
    }
    
    
    template<class K, class U = ValueSelect, typename std::enable_if<!std::is_same<U, void>::value>::type* = nullptr>
    typename U::value_type& operator[](K&& key) {
        using T = typename U::value_type;
        
        const std::size_t hash = m_hash(key);
        const std::size_t ibucket_for_hash = bucket_for_hash(hash);
        
        T* value = find_value_internal(key, hash, m_buckets.begin() + ibucket_for_hash);
        if(value != nullptr) {
            return *value;
        }
        else {
            return insert_internal(std::make_pair(std::forward<K>(key), T()), hash, ibucket_for_hash).first.value();
        }
    }
    
    
    template<class K>
    size_type count(const K& key) const {
        return count(key, m_hash(key));
    }
    
    template<class K>
    size_type count(const K& key, std::size_t hash) const {
        if(find_value_internal(key, hash, m_buckets.begin() + bucket_for_hash(hash)) == nullptr) {
            return 0;
        }
        else {
            return 1;
        }
    }
    
    
    template<class K>
    iterator find(const K& key) {
        const std::size_t hash = m_hash(key);
        
        return find_internal(key, hash, m_buckets.begin() + bucket_for_hash(hash));
    }
    
    template<class K>
    iterator find(const K& key, std::size_t hash) {
        return find_internal(key, hash, m_buckets.begin() + bucket_for_hash(hash));
    }
    
    
    template<class K>
    const_iterator find(const K& key) const {
        const std::size_t hash = m_hash(key);
        
        return find_internal(key, hash, m_buckets.begin() + bucket_for_hash(hash));
    }
    
    template<class K>
    const_iterator find(const K& key, std::size_t hash) const {
        return find_internal(key, hash, m_buckets.begin() + bucket_for_hash(hash));
    }
    
    
    template<class K>
    std::pair<iterator, iterator> equal_range(const K& key) {
        iterator it = find(key);
        return std::make_pair(it, it);
    }
    
    template<class K>
    std::pair<iterator, iterator> equal_range(const K& key, std::size_t hash) {
        iterator it = find(key, hash);
        return std::make_pair(it, it);
    }
    
    
    template<class K>
    std::pair<const_iterator, const_iterator> equal_range(const K& key) const {
        const_iterator it = find(key);
        return std::make_pair(it, it);
    }
    
    template<class K>
    std::pair<const_iterator, const_iterator> equal_range(const K& key, std::size_t hash) const {
        const_iterator it = find(key, hash);
        return std::make_pair(it, it);
    }
    
    /*
     * Bucket interface 
     */
    size_type bucket_count() const {
        /*
         * So that the last bucket can have NeighborhoodSize neighbors, the size of the bucket array is a little
         * bigger than the real number of buckets. We could use some of the buckets at the beginning, but
         * it is easier this way and we avoid weird behaviour with iterators.
         */
        return m_buckets.size() - NeighborhoodSize + 1; 
    }
    
    size_type max_bucket_count() const {
        if(StoreHash) {
            return std::numeric_limits<typename hopscotch_bucket_hash<StoreHash>::hash_type>::max()
                    - NeighborhoodSize + 1;
        }
        else {
            return m_buckets.max_size() - NeighborhoodSize + 1;
        }
    }
    
    
    /*
     *  Hash policy 
     */
    float load_factor() const {
        return float(m_nb_elements)/float(bucket_count());
    }
    
    float max_load_factor() const {
        return m_max_load_factor;
    }
    
    void max_load_factor(float ml) {
        m_max_load_factor = ml;
        m_load_threshold = static_cast<size_type>(static_cast<float>(bucket_count())*m_max_load_factor);
    }
    
    void rehash(size_type count) {
        count = std::max(count, static_cast<size_type>(std::ceil(static_cast<float>(size())/max_load_factor())));
        rehash_internal(count);
    }
    
    void reserve(size_type count) {
        rehash(static_cast<size_type>(std::ceil(static_cast<float>(count)/max_load_factor())));
    }
    
    
    /*
     * Observers
     */
    hasher hash_function() const {
        return m_hash;
    }
    
    key_equal key_eq() const {
        return m_key_equal;
    }
    
    /*
     * Other
     */
    size_type overflow_size() const noexcept {
        return m_overflow_elements.size();
    }
    
    template<class U = OverflowContainer, typename std::enable_if<has_key_compare<U>::value>::type* = nullptr>
    typename U::key_compare key_comp() const {
        return m_overflow_elements.key_comp();
    }
    
private:
    iterator get_mutable_iterator(const_iterator pos) {
        if(pos.m_buckets_iterator != pos.m_buckets_end_iterator) {
            // Get a non-const iterator
            auto it = m_buckets.begin() + std::distance(m_buckets.cbegin(), pos.m_buckets_iterator);
            return iterator(it, m_buckets.end(), m_overflow_elements.begin());
        }
        else {
            // Get a non-const iterator
            auto it = get_mutable_overflow_iterator(pos.m_overflow_iterator);
            
            return iterator(m_buckets.end(), m_buckets.end(), it);
        }
    }
    
    std::size_t bucket_for_hash(std::size_t hash) const {
        return m_growth_policy.bucket_for_hash(hash);
    }
    
    static_assert(std::is_nothrow_move_constructible<value_type>::value || 
                  std::is_copy_constructible<value_type>::value, 
                  "value_type must be either copy constructible or nothrow move constructible.");
    
    template<typename U = value_type, 
             typename std::enable_if<std::is_nothrow_move_constructible<U>::value>::type* = nullptr>
    void rehash_internal(size_type count) {
        hopscotch_hash new_map = new_hopscotch_hash(count);
        
        for(hopscotch_bucket& bucket : m_buckets) {
            if(bucket.is_empty()) {
                continue;
            }
            
            const std::size_t hash = StoreHash?bucket.truncated_bucket_hash():
                                               new_map.m_hash(KeySelect()(bucket.get_value()));
            const std::size_t ibucket_for_hash = new_map.bucket_for_hash(hash);
            
            new_map.insert_internal(std::move(bucket.get_value()), hash, ibucket_for_hash);
        }
        
        tsl_assert(new_map.m_overflow_elements.empty());
        if(!m_overflow_elements.empty()) {
            new_map.m_overflow_elements.swap(m_overflow_elements);
            new_map.m_nb_elements += new_map.m_overflow_elements.size();
            
            for(const value_type& value : new_map.m_overflow_elements) {
                const std::size_t ibucket_for_hash = new_map.bucket_for_hash(new_map.m_hash(KeySelect()(value)));
                new_map.m_buckets[ibucket_for_hash].set_overflow(true);
            }
        }
        
        new_map.swap(*this);
    }
    
    template<typename U = value_type, 
             typename std::enable_if<std::is_copy_constructible<U>::value && 
                                     !std::is_nothrow_move_constructible<U>::value>::type* = nullptr>
    void rehash_internal(size_type count) {
        hopscotch_hash new_map = new_hopscotch_hash(count);
                
        for(const hopscotch_bucket& bucket : m_buckets) {
            if(bucket.is_empty()) {
                continue;
            }
            
            const std::size_t hash = StoreHash?bucket.truncated_bucket_hash():
                                               new_map.m_hash(KeySelect()(bucket.get_value()));
            const std::size_t ibucket_for_hash = new_map.bucket_for_hash(hash);
            
            new_map.insert_internal(bucket.get_value(), hash, ibucket_for_hash);
        }
        
        tsl_assert(new_map.m_overflow_elements.empty());
        if(!m_overflow_elements.empty()) {
            new_map.m_overflow_elements.swap(m_overflow_elements);
            new_map.m_nb_elements += new_map.m_overflow_elements.size();
            
            for(const value_type& value : new_map.m_overflow_elements) {
                const std::size_t ibucket_for_hash = new_map.bucket_for_hash(new_map.m_hash(KeySelect()(value)));
                new_map.m_buckets[ibucket_for_hash].set_overflow(true);
            }
        }

        new_map.swap(*this);
    }  
    
    /*
     * Find in m_overflow_elements an element for which the bucket it initially belongs to, 
     * equals original_bucket_for_hash.
     * 
     * Return m_overflow_elements.end() if none.
     */
    iterator_overflow find_in_overflow_from_bucket(iterator_overflow search_start, 
                                                   std::size_t original_bucket_for_hash) 
    {
        for(auto it = search_start; it != m_overflow_elements.end(); ++it) {
            const std::size_t bucket_for_overflow_hash = bucket_for_hash(m_hash(KeySelect()(*it)));
            if(bucket_for_overflow_hash == original_bucket_for_hash) {
                return it;
            }
        }
        
        return m_overflow_elements.end();
    }
    
#ifdef TSL_NO_RANGE_ERASE_WITH_CONST_ITERATOR
    iterator_overflow get_mutable_overflow_iterator(const_iterator_overflow it) {
        return std::next(m_overflow_elements.begin(), std::distance(m_overflow_elements.cbegin(), it));        
    }
#else            
    iterator_overflow get_mutable_overflow_iterator(const_iterator_overflow it) {
        return m_overflow_elements.erase(it, it);       
    }
#endif    

    // iterator is in overflow list
    iterator_overflow erase_from_overflow(const_iterator_overflow pos, std::size_t ibucket_for_hash) {
#ifdef TSL_NO_RANGE_ERASE_WITH_CONST_ITERATOR        
        auto it_next = m_overflow_elements.erase(get_mutable_overflow_iterator(pos));
#else
        auto it_next = m_overflow_elements.erase(pos);
#endif        
        m_nb_elements--;
        
        // Check if we can remove the overflow flag
        tsl_assert(m_buckets[ibucket_for_hash].has_overflow());
        if(find_in_overflow_from_bucket(m_overflow_elements.begin(), ibucket_for_hash) == m_overflow_elements.end()) {
            m_buckets[ibucket_for_hash].set_overflow(false);
        }
        
        return it_next;
    }
    
    // iterator is in bucket
    void erase_from_bucket(iterator_buckets pos, std::size_t ibucket_for_hash) {
        const std::size_t ibucket_for_key = std::distance(m_buckets.begin(), pos);
        
        m_buckets[ibucket_for_key].remove_value();
        m_buckets[ibucket_for_hash].toggle_neighbor_presence(ibucket_for_key - ibucket_for_hash);
        m_nb_elements--;
    }
    

    
    template<class K, class M>
    std::pair<iterator, bool> insert_or_assign_internal(K&& key, M&& obj) {
        const std::size_t hash = m_hash(key);
        const std::size_t ibucket_for_hash = bucket_for_hash(hash);
        
        // Check if already presents
        auto it_find = find_internal(key, hash, m_buckets.begin() + ibucket_for_hash);
        if(it_find != end()) {
            it_find.value() = std::forward<M>(obj);
            return std::make_pair(it_find, false);
        }
        

        return insert_internal(value_type(std::forward<K>(key), std::forward<M>(obj)), hash, ibucket_for_hash);
    }
    
    template<typename P, class... Args>
    std::pair<iterator, bool> try_emplace_internal(P&& key, Args&&... args_value) {
        const std::size_t hash = m_hash(key);
        const std::size_t ibucket_for_hash = bucket_for_hash(hash);
        
        // Check if already presents
        auto it_find = find_internal(key, hash, m_buckets.begin() + ibucket_for_hash);
        if(it_find != end()) {
            return std::make_pair(it_find, false);
        }
        

        return insert_internal(value_type(std::piecewise_construct, 
                                          std::forward_as_tuple(std::forward<P>(key)), 
                                          std::forward_as_tuple(std::forward<Args>(args_value)...)), 
                               hash, ibucket_for_hash);
    }
    
    template<typename P>
    std::pair<iterator, bool> insert_internal(P&& value) {
        const std::size_t hash = m_hash(KeySelect()(value));
        const std::size_t ibucket_for_hash = bucket_for_hash(hash);
        
        // Check if already presents
        auto it_find = find_internal(KeySelect()(value), hash, m_buckets.begin() + ibucket_for_hash);
        if(it_find != end()) {
            return std::make_pair(it_find, false);
        }
        
        
        return insert_internal(std::forward<P>(value), hash, ibucket_for_hash);
    }
    
    template<typename P>
    std::pair<iterator, bool> insert_internal(P&& value, std::size_t hash, std::size_t ibucket_for_hash) {
        if((m_nb_elements - m_overflow_elements.size() + 1) > m_load_threshold) {
            rehash_internal(m_growth_policy.next_bucket_count());
            ibucket_for_hash = bucket_for_hash(hash);
        }
        
        std::size_t ibucket_empty = find_empty_bucket(ibucket_for_hash);
        if(ibucket_empty < m_buckets.size()) {
            do {
                // Empty bucket is in range of NeighborhoodSize, use it
                if(ibucket_empty - ibucket_for_hash < NeighborhoodSize) {
                    auto it = insert_in_bucket(std::forward<P>(value), hash, ibucket_empty, ibucket_for_hash);
                    return std::make_pair(iterator(it, m_buckets.end(), m_overflow_elements.begin()), true);
                }
            }
            // else, try to swap values to get a closer empty bucket
            while(swap_empty_bucket_closer(ibucket_empty));
        }
            
        // Load factor is too low or a rehash will not change the neighborhood, put the value in overflow list
        if(load_factor() < MIN_LOAD_FACTOR_FOR_REHASH || !will_neighborhood_change_on_rehash(ibucket_for_hash)) {
            auto it_insert = m_overflow_elements.insert(m_overflow_elements.end(), std::forward<P>(value));
            m_buckets[ibucket_for_hash].set_overflow(true);
            m_nb_elements++;
            
            return std::make_pair(iterator(m_buckets.end(), m_buckets.end(), it_insert), true);
        }
    
        rehash_internal(m_growth_policy.next_bucket_count());
        
        ibucket_for_hash = bucket_for_hash(hash);
        return insert_internal(std::forward<P>(value), hash, ibucket_for_hash);
    }    
    
    /*
     * Return true if a rehash will change the position of a key-value in the neighborhood of 
     * ibucket_neighborhood_check. In this case a rehash is needed instead of puting the value in overflow list.
     */
    bool will_neighborhood_change_on_rehash(size_t ibucket_neighborhood_check) const {
        std::size_t expand_bucket_count = m_growth_policy.next_bucket_count();
        GrowthPolicy expand_growth_policy(expand_bucket_count);
        
        for(size_t ibucket = ibucket_neighborhood_check; 
            ibucket < m_buckets.size() && (ibucket - ibucket_neighborhood_check) < NeighborhoodSize; 
            ++ibucket)
        {
            tsl_assert(!m_buckets[ibucket].is_empty());
            
            const size_t hash = m_hash(KeySelect()(m_buckets[ibucket].get_value()));
            if(bucket_for_hash(hash) != expand_growth_policy.bucket_for_hash(hash)) {
                return true;
            }
        }
        
        return false;
    }
    
    /*
     * Return the index of an empty bucket in m_buckets.
     * If none, the returned index equals m_buckets.size()
     */
    std::size_t find_empty_bucket(std::size_t ibucket_start) const {
        const std::size_t limit = std::min(ibucket_start + MAX_PROBES_FOR_EMPTY_BUCKET, m_buckets.size());
        for(; ibucket_start < limit; ibucket_start++) {
            if(m_buckets[ibucket_start].is_empty()) {
                return ibucket_start;
            }
        }
        
        return m_buckets.size();
    }
    
    /*
     * Insert value in ibucket_empty where value originally belongs to ibucket_for_hash
     * 
     * Return bucket iterator to ibucket_empty
     */
    template<typename P>
    iterator_buckets insert_in_bucket(P&& value, std::size_t hash, std::size_t ibucket_empty, std::size_t ibucket_for_hash) {        
        tsl_assert(ibucket_empty >= ibucket_for_hash );
        tsl_assert(m_buckets[ibucket_empty].is_empty());
        m_buckets[ibucket_empty].set_value(std::forward<P>(value), hash);
        
        tsl_assert(!m_buckets[ibucket_for_hash].is_empty());
        m_buckets[ibucket_for_hash].toggle_neighbor_presence(ibucket_empty - ibucket_for_hash);
        m_nb_elements++;
        
        return m_buckets.begin() + ibucket_empty;
    }
    
    /*
     * Try to swap the bucket ibucket_empty_in_out with a bucket preceding it while keeping the neighborhood 
     * conditions correct.
     * 
     * If a swap was possible, the position of ibucket_empty_in_out will be closer to 0 and true will re returned.
     */
    bool swap_empty_bucket_closer(std::size_t& ibucket_empty_in_out) {
        tsl_assert(ibucket_empty_in_out >= NeighborhoodSize);
        const std::size_t neighborhood_start = ibucket_empty_in_out - NeighborhoodSize + 1;
        
        for(std::size_t to_check = neighborhood_start; to_check < ibucket_empty_in_out; to_check++) {
            neighborhood_bitmap neighborhood_infos = m_buckets[to_check].get_neighborhood_infos();
            std::size_t to_swap = to_check;
            
            while(neighborhood_infos != 0 && to_swap < ibucket_empty_in_out) {
                if((neighborhood_infos & 1) == 1) {
                    tsl_assert(m_buckets[ibucket_empty_in_out].is_empty());
                    tsl_assert(!m_buckets[to_swap].is_empty());
                    
                    m_buckets[to_swap].swap_value_into_empty_bucket(m_buckets[ibucket_empty_in_out]);
                    
                    tsl_assert(!m_buckets[to_check].check_neighbor_presence(ibucket_empty_in_out - to_check));
                    tsl_assert(m_buckets[to_check].check_neighbor_presence(to_swap - to_check));
                    
                    m_buckets[to_check].toggle_neighbor_presence(ibucket_empty_in_out - to_check);
                    m_buckets[to_check].toggle_neighbor_presence(to_swap - to_check);
                    
                    
                    ibucket_empty_in_out = to_swap;
                    
                    return true;
                }
                
                to_swap++;
                neighborhood_infos = static_cast<neighborhood_bitmap>(neighborhood_infos >> 1);
            }
        }
        
        return false;
    }
    
    iterator_buckets get_first_non_empty_buckets_iterator() {
        auto it_first = static_cast<const hopscotch_hash*>(this)->get_first_non_empty_buckets_iterator();
        return m_buckets.begin() + std::distance(m_buckets.cbegin(), it_first); 
    }
    
    const_iterator_buckets get_first_non_empty_buckets_iterator() const {
        auto begin = m_buckets.cbegin();
        while(begin != m_buckets.cend() && begin->is_empty()) {
            ++begin;
        }
        
        return begin;
    }
    
    
    
    template<class K, class U = ValueSelect, typename std::enable_if<!std::is_same<U, void>::value>::type* = nullptr>
    typename U::value_type* find_value_internal(const K& key, std::size_t hash, iterator_buckets it_bucket) {
        return const_cast<typename U::value_type*>(
                    static_cast<const hopscotch_hash*>(this)->find_value_internal(key, hash, it_bucket));
    }
    
    /*
     * Avoid the creation of an iterator to just get the value for operator[] and at() in maps. Faster this way.
     *
     * Return null if no value for key (TODO use std::optional when available).
     */
    template<class K, class U = ValueSelect, typename std::enable_if<!std::is_same<U, void>::value>::type* = nullptr>
    const typename U::value_type* find_value_internal(const K& key, std::size_t hash, const_iterator_buckets it_bucket) const {
        auto it_find = find_in_buckets(key, hash, it_bucket);
        if(it_find != m_buckets.end()) {
            return std::addressof(ValueSelect()(it_find->get_value()));
        }
        
        if(it_bucket->has_overflow()) {
            auto it_overflow = find_in_overflow(key);
            if(it_overflow != m_overflow_elements.end()) {
                return std::addressof(ValueSelect()(*it_overflow));
            }
        }
        
        return nullptr;
    }
    
    template<class K>
    iterator find_internal(const K& key, std::size_t hash, iterator_buckets it_bucket) {
        auto it = find_in_buckets(key, hash, it_bucket);
        if(it != m_buckets.cend()) {
            return iterator(it, m_buckets.end(), m_overflow_elements.begin());
        }
        
        if(!it_bucket->has_overflow()) {
            return end();
        }
        
        return iterator(m_buckets.end(), m_buckets.end(), find_in_overflow(key));
    }
    
    template<class K>
    const_iterator find_internal(const K& key, std::size_t hash, const_iterator_buckets it_bucket) const {
        auto it = find_in_buckets(key, hash, it_bucket);
        if(it != m_buckets.cend()) {
            return const_iterator(it, m_buckets.cend(), m_overflow_elements.cbegin());
        }
        
        if(!it_bucket->has_overflow()) {
            return cend();
        }

        
        return const_iterator(m_buckets.cend(), m_buckets.cend(), find_in_overflow(key));
    }
    
    template<class K>
    iterator_buckets find_in_buckets(const K& key, std::size_t hash, iterator_buckets it_bucket) {   
        auto it_find = static_cast<const hopscotch_hash*>(this)->find_in_buckets(key, hash, it_bucket); 
        return m_buckets.begin() + std::distance(m_buckets.cbegin(), it_find);
    }

    
    template<class K>
    const_iterator_buckets find_in_buckets(const K& key, std::size_t hash, const_iterator_buckets it_bucket) const {      
        (void) hash; // Avoid warning of unused variable when StoreHash is false;

        // TODO Try to optimize the function. 
        // I tried to use ffs and  __builtin_ffs functions but I could not reduce the time the function
        // takes with -march=native
        
        neighborhood_bitmap neighborhood_infos = it_bucket->get_neighborhood_infos();
        while(neighborhood_infos != 0) {
            if((neighborhood_infos & 1) == 1) {
                // Check StoreHash before calling bucket_hash_equal. Functionally it doesn't change anythin. 
                // If StoreHash is false, bucket_hash_equal is a no-op. Avoiding the call is there to help 
                // GCC optimizes `hash` parameter away, it seems to not be able to do without this hint.
                if((!StoreHash || it_bucket->bucket_hash_equal(hash)) && m_key_equal(KeySelect()(it_bucket->get_value()), key)) {
                    return it_bucket;
                }
            }
            
            ++it_bucket;
            neighborhood_infos = static_cast<neighborhood_bitmap>(neighborhood_infos >> 1);
        }
        
        return m_buckets.end();
    }
    

    // TODO Use a better way to check if we should use 
    // std::find_if(m_overflow_elements.begin(), m_overflow_elements.end(), ...) or
    // m_overflow_elements.find(...)
    template<class K, class U = OverflowContainer, typename std::enable_if<!has_key_compare<U>::value>::type* = nullptr>
    iterator_overflow find_in_overflow(const K& key) {
        return std::find_if(m_overflow_elements.begin(), m_overflow_elements.end(), 
                            [&](const value_type& value) { 
                                return m_key_equal(key, KeySelect()(value)); 
                            });
    }
    
    template<class K, class U = OverflowContainer, typename std::enable_if<!has_key_compare<U>::value>::type* = nullptr>
    const_iterator_overflow find_in_overflow(const K& key) const {
        return std::find_if(m_overflow_elements.cbegin(), m_overflow_elements.cend(), 
                            [&](const value_type& value) { 
                                return m_key_equal(key, KeySelect()(value)); 
                            });
    }
    
    template<class K, class U = OverflowContainer, typename std::enable_if<has_key_compare<U>::value>::type* = nullptr>
    iterator_overflow find_in_overflow(const K& key) {
        return m_overflow_elements.find(key);
    }
    
    template<class K, class U = OverflowContainer, typename std::enable_if<has_key_compare<U>::value>::type* = nullptr>
    const_iterator_overflow find_in_overflow(const K& key) const {
        return m_overflow_elements.find(key);
    }
    
    template<class U = OverflowContainer, typename std::enable_if<!has_key_compare<U>::value>::type* = nullptr>
    hopscotch_hash new_hopscotch_hash(size_type bucket_count) {
        return hopscotch_hash(bucket_count, m_hash, m_key_equal, get_allocator(), m_max_load_factor);
    }
    
    template<class U = OverflowContainer, typename std::enable_if<has_key_compare<U>::value>::type* = nullptr>
    hopscotch_hash new_hopscotch_hash(size_type bucket_count) {
        return hopscotch_hash(bucket_count, m_hash, m_key_equal, get_allocator(), m_max_load_factor, key_comp());
    }
    
public:    
    static const size_type DEFAULT_INIT_BUCKETS_SIZE = 16;
    static constexpr float DEFAULT_MAX_LOAD_FACTOR = 0.95f;
    
private:    
    static const std::size_t MAX_PROBES_FOR_EMPTY_BUCKET = 10*NeighborhoodSize;
    static constexpr float MIN_LOAD_FACTOR_FOR_REHASH = has_key_compare<OverflowContainer>::value?0.3f:0.15f;
    
private:    
    buckets_container_type m_buckets;
    overflow_container_type m_overflow_elements;
    
    size_type m_nb_elements;
    GrowthPolicy m_growth_policy;
    
    
    float m_max_load_factor;
    size_type m_load_threshold;
    
    hasher m_hash;
    key_equal m_key_equal;
};

} // end namespace detail_hopscotch_hash


} // end namespace tsl

#endif
