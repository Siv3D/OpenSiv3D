/**
 * MIT License
 * 
 * Copyright (c) 2018 Tessil
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
#ifndef TSL_HOPSCOTCH_GROWTH_POLICY_H
#define TSL_HOPSCOTCH_GROWTH_POLICY_H 


#include <algorithm>
#include <array>
#include <climits>
#include <cmath>
#include <cstddef>
#include <iterator>
#include <limits>
#include <ratio>
#include <stdexcept>


namespace tsl {
namespace hh {

/**
 * Grow the hash table by a factor of GrowthFactor keeping the bucket count to a power of two. It allows
 * the table to use a mask operation instead of a modulo operation to map a hash to a bucket.
 * 
 * GrowthFactor must be a power of two >= 2.
 */
template<std::size_t GrowthFactor>
class power_of_two_growth_policy {
public:
    /**
     * Called on the hash table creation and on rehash. The number of buckets for the table is passed in parameter.
     * This number is a minimum, the policy may update this value with a higher value if needed (but not lower).
     *
     * If 0 is given, min_bucket_count_in_out must still be 0 after the policy creation and
     * bucket_for_hash must always return 0 in this case.
     */
    explicit power_of_two_growth_policy(std::size_t& min_bucket_count_in_out) {
        if(min_bucket_count_in_out > max_bucket_count()) {
            throw std::length_error("The hash table exceeds its maxmimum size.");
        }
        
        if(min_bucket_count_in_out > 0) {
            min_bucket_count_in_out = round_up_to_power_of_two(min_bucket_count_in_out);
            m_mask = min_bucket_count_in_out - 1;
        }
        else {
            m_mask = 0;
        }
    }
    
    /**
     * Return the bucket [0, bucket_count()) to which the hash belongs. 
     * If bucket_count() is 0, it must always return 0.
     */
    std::size_t bucket_for_hash(std::size_t hash) const noexcept {
        return hash & m_mask;
    }
    
    /**
     * Return the bucket count to use when the bucket array grows on rehash.
     */
    std::size_t next_bucket_count() const {
        if((m_mask + 1) > max_bucket_count() / GrowthFactor) {
            throw std::length_error("The hash table exceeds its maxmimum size.");
        }
        
        return (m_mask + 1) * GrowthFactor;
    }
    
    /**
     * Return the maximum number of buckets supported by the policy.
     */
    std::size_t max_bucket_count() const {
        // Largest power of two.
        return (std::numeric_limits<std::size_t>::max() / 2) + 1;
    }
    
    /**
     * Reset the growth policy as if it was created with a bucket count of 0.
     * After a clear, the policy must always return 0 when bucket_for_hash is called.
     */
    void clear() noexcept {
        m_mask = 0;
    }
    
private:
    static std::size_t round_up_to_power_of_two(std::size_t value) {
        if(is_power_of_two(value)) {
            return value;
        }
        
        if(value == 0) {
            return 1;
        }
            
        --value;
        for(std::size_t i = 1; i < sizeof(std::size_t) * CHAR_BIT; i *= 2) {
            value |= value >> i;
        }
        
        return value + 1;
    }
    
    static constexpr bool is_power_of_two(std::size_t value) {
        return value != 0 && (value & (value - 1)) == 0;
    }
    
private:
    static_assert(is_power_of_two(GrowthFactor) && GrowthFactor >= 2, "GrowthFactor must be a power of two >= 2.");
    
    std::size_t m_mask;
};


/**
 * Grow the hash table by GrowthFactor::num / GrowthFactor::den and use a modulo to map a hash
 * to a bucket. Slower but it can be useful if you want a slower growth.
 */
template<class GrowthFactor = std::ratio<3, 2>>
class mod_growth_policy {
public:
    explicit mod_growth_policy(std::size_t& min_bucket_count_in_out) {
        if(min_bucket_count_in_out > max_bucket_count()) {
            throw std::length_error("The hash table exceeds its maxmimum size.");
        }
        
        if(min_bucket_count_in_out > 0) {
            m_mod = min_bucket_count_in_out;
        }
        else {
            m_mod = 1;
        }
    }
    
    std::size_t bucket_for_hash(std::size_t hash) const noexcept {
        return hash % m_mod;
    }
    
    std::size_t next_bucket_count() const {
        if(m_mod == max_bucket_count()) {
            throw std::length_error("The hash table exceeds its maxmimum size.");
        }
        
        const double next_bucket_count = std::ceil(double(m_mod) * REHASH_SIZE_MULTIPLICATION_FACTOR);
        if(!std::isnormal(next_bucket_count)) {
            throw std::length_error("The hash table exceeds its maxmimum size.");
        }
        
        if(next_bucket_count > double(max_bucket_count())) {
            return max_bucket_count();
        }
        else {
            return std::size_t(next_bucket_count);
        }
    }
    
    std::size_t max_bucket_count() const {
        return MAX_BUCKET_COUNT;
    }
    
    void clear() noexcept {
        m_mod = 1;
    }
    
private:
    static constexpr double REHASH_SIZE_MULTIPLICATION_FACTOR = 1.0 * GrowthFactor::num / GrowthFactor::den;
    static const std::size_t MAX_BUCKET_COUNT = 
            std::size_t(double(
                    std::numeric_limits<std::size_t>::max() / REHASH_SIZE_MULTIPLICATION_FACTOR
            ));
            
    static_assert(REHASH_SIZE_MULTIPLICATION_FACTOR >= 1.1, "Growth factor should be >= 1.1.");
    
    std::size_t m_mod;
};





/**
 * Grow the hash table by using prime numbers as bucket count. Slower than tsl::hh::power_of_two_growth_policy in  
 * general but will probably distribute the values around better in the buckets with a poor hash function.
 * 
 * To allow the compiler to optimize the modulo operation, a lookup table is used with constant primes numbers.
 * 
 * With a switch the code would look like:
 * \code
 * switch(iprime) { // iprime is the current prime of the hash table
 *     case 0: hash % 5ul;
 *             break;
 *     case 1: hash % 17ul;
 *             break;
 *     case 2: hash % 29ul;
 *             break;
 *     ...
 * }    
 * \endcode
 * 
 * Due to the constant variable in the modulo the compiler is able to optimize the operation
 * by a series of multiplications, substractions and shifts. 
 * 
 * The 'hash % 5' could become something like 'hash - (hash * 0xCCCCCCCD) >> 34) * 5' in a 64 bits environement.
 */
class prime_growth_policy {
public:
	explicit prime_growth_policy(std::size_t& min_bucket_count_in_out);
    
	std::size_t bucket_for_hash(std::size_t hash) const noexcept;
    
	std::size_t next_bucket_count() const;
    
	std::size_t max_bucket_count() const;
    
    void clear() noexcept {
        m_iprime = 0;
    }
    
private:
    unsigned int m_iprime;
   
}; 

}
}

#endif
