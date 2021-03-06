/*********************************************************************************
 *
 * Inviwo - Interactive Visualization Workshop
 *
 * Copyright (c) 2012-2015 Inviwo Foundation
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *********************************************************************************/

#ifndef IVW_STDEXTENSIONS_H
#define IVW_STDEXTENSIONS_H

#include <inviwo/core/common/inviwocoredefine.h>
#include <inviwo/core/util/glm.h>
#include <warn/push>
#include <warn/ignore/all>
#include <memory>
#include <string>
#include <iterator>
#include <algorithm>
#include <functional>
#include <numeric>
#include <vector>
#include <type_traits>
#include <future>
#include <warn/pop>

namespace inviwo {

namespace util {
// Since make_unique is a c++14 feature, roll our own in the mean time.
template <class T, class... Args>
typename std::enable_if<!std::is_array<T>::value, std::unique_ptr<T> >::type make_unique(
    Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
template <class T>
typename std::enable_if<std::is_array<T>::value, std::unique_ptr<T> >::type make_unique(
    std::size_t n) {
    typedef typename std::remove_extent<T>::type RT;
    return std::unique_ptr<T>(new RT[n]());
}

template <typename Derived, typename Base, typename Del>
std::unique_ptr<Derived, Del> static_unique_ptr_cast(std::unique_ptr<Base, Del>&& p) {
    auto d = static_cast<Derived*>(p.release());
    return std::unique_ptr<Derived, Del>(d, std::move(p.get_deleter()));
}

template <typename Derived, typename Base, typename Del>
std::unique_ptr<Derived, Del> dynamic_unique_ptr_cast(std::unique_ptr<Base, Del>&& p) {
    if (Derived* result = dynamic_cast<Derived*>(p.get())) {
        p.release();
        return std::unique_ptr<Derived, Del>(result, std::move(p.get_deleter()));
    }
    return std::unique_ptr<Derived, Del>(nullptr, p.get_deleter());
}

template <typename Derived, typename Base>
std::unique_ptr<Derived> dynamic_unique_ptr_cast(
    std::unique_ptr<Base, std::default_delete<Base>>&& p) {
    if (Derived* result = dynamic_cast<Derived*>(p.get())) {
        p.release();
        return std::unique_ptr<Derived>(result);
    }
    return std::unique_ptr<Derived>(nullptr);
}

// Default construct if possible otherwise return nullptr;
template <typename T, typename std::enable_if<
    !std::is_abstract<T>::value && std::is_default_constructible<T>::value,
    int>::type = 0>
    T* defaultConstructType() {
    return new T();
};

template <typename T, typename std::enable_if<
    std::is_abstract<T>::value || !std::is_default_constructible<T>::value,
    int>::type = 0>
    T* defaultConstructType() {
    return nullptr;
};


// type trait to check if T is derived from std::basic_string
namespace detail {
template <typename T, class Enable = void>
struct is_string : std::false_type {};

template <typename... T>
struct void_helper {
    typedef void type;
};

template <typename T>
struct is_string<T, typename void_helper<typename T::value_type, typename T::traits_type,
                                         typename T::allocator_type>::type>
    : std::is_base_of<std::basic_string<typename T::value_type, typename T::traits_type,
                                        typename T::allocator_type>,
                      T> {};
}
template <typename T>
struct is_string : detail::is_string<T> {};

template <class F, class... Args>
void for_each_argument(F f, Args&&... args) {
    [](...){}((f(std::forward<Args>(args)), 0)...);
}

template <typename T, typename V>
auto erase_remove(T& cont, const V& elem)
    -> decltype(std::distance(std::declval<T>().begin(), std::declval<T>().end())) {
    using std::begin;
    using std::end;
    auto it = std::remove(begin(cont), end(cont), elem);
    auto nelem = std::distance(it, cont.end());
    cont.erase(it, cont.end());
    return nelem;
}

template <typename T, typename Pred>
auto erase_remove_if(T& cont, Pred pred)
    -> decltype(std::distance(std::declval<T>().begin(), std::declval<T>().end())) {
    using std::begin;
    using std::end;
    auto it = std::remove_if(begin(cont), end(cont), pred);
    auto nelem = std::distance(it, cont.end());
    cont.erase(it, cont.end());
    return nelem;
}

template <typename T, typename Pred>
size_t map_erase_remove_if(T& cont, Pred pred) {
    using std::begin;
    using std::end;
    size_t removed{0};
    for (auto it = begin(cont); it != end(cont);) {
        if (pred(*it)) {
            it = cont.erase(it);
            removed++;
        } else {
            ++it;
        }
    }
    return removed;
}

template <typename T>
bool push_back_unique(T& cont, typename T::value_type elem) {
    using std::begin;
    using std::end;
    if (std::find(begin(cont), end(cont), elem) == cont.end()) {
        cont.push_back(elem);
        return true;
    } else {
        return false;
    }
}

template <typename T>
std::vector<T>& append(std::vector<T> &dest, const std::vector<T> &source) {
    dest.reserve(dest.size() + source.size());
    dest.insert(dest.end(), source.begin(), source.end());
    return dest;
}

template <typename T, typename V>
auto find(T& cont, const V& elem) -> typename T::iterator {
    using std::begin;
    using std::end;
    return std::find(begin(cont), end(cont), elem);
}

template <typename T, typename Pred>
auto find_if(T& cont, Pred pred) -> typename T::iterator {
    using std::begin;
    using std::end;
    return std::find_if(begin(cont), end(cont), pred);
}

template <typename T, typename Pred>
auto find_if(const T& cont, Pred pred) -> typename T::const_iterator {
    return std::find_if(cont.cbegin(), cont.cend(), pred);
}

template <typename T, typename V>
bool contains(T& cont, const V& elem) {
    using std::begin;
    using std::end;
    return std::find(begin(cont), end(cont), elem) != end(cont);
}

template <typename T, typename Pred>
bool contains_if(T& cont, Pred pred) {
    using std::begin;
    using std::end;
    return std::find_if(begin(cont), end(cont), pred) != end(cont);
}

template <typename T, typename P>
auto find_if_or_null(T& cont, P pred) -> typename T::value_type {
    using std::begin;
    using std::end;

    auto it = std::find_if(begin(cont), end(cont), pred);
    if (it != end(cont)) {
        return *it;
    } else {
        return nullptr;
    }
}


template <typename T, typename V>
auto find_or_null(T& cont, const V& elem) -> typename T::value_type {
    using std::begin;
    using std::end;

    auto it = std::find(begin(cont), end(cont), elem);
    if (it != end(cont)) {
        return *it;
    } else {
        return nullptr;
    }
}

template <typename T, typename V, typename Callable>
auto find_or_null(T& cont, const V& elem, Callable f) ->  typename T::value_type {
    using std::begin;
    using std::end;

    auto it = std::find(begin(cont), end(cont), elem);
    if (it != end(cont)) {
        return f(*it);
    } else {
        return nullptr;
    }
}

template <typename T>
bool has_key(T& map, const typename T::key_type& key) {
    return map.find(key) != map.end();
}
template <typename T>
bool insert_unique(T& map, const typename T::key_type& key, typename T::mapped_type& value) {
    auto it = map.find(key);
    if (it == map.end()) {
        map.insert(it, std::make_pair(key, value));
        return true;
    } else {
        return false;
    };
}

template <typename T, typename V>
auto map_find_or_null(T& cont, const V& elem) -> typename T::mapped_type {
    auto it = cont.find(elem);
    if (it != end(cont)) {
        return it->second;
    } else {
        return nullptr;
    }
}

template <typename T, typename V, typename Callable>
auto map_find_or_null(T& cont, const V& elem, Callable f)
    -> typename std::result_of<Callable(typename T::mapped_type)>::type {
    auto it = cont.find(elem);
    if (it != end(cont)) {
        return f(it->second);
    } else {
        return nullptr;
    }
}

template <typename T, typename UnaryPredicate>
bool all_of(T& cont, UnaryPredicate pred) {
    using std::begin;
    using std::end;
    return std::all_of(begin(cont), end(cont), pred);
}
template <typename T, typename UnaryPredicate>
bool any_of(T& cont, UnaryPredicate pred) {
    using std::begin;
    using std::end;
    return std::any_of(begin(cont), end(cont), pred);
}
template <typename T, typename UnaryPredicate>
bool none_of(T& cont, UnaryPredicate pred) {
    using std::begin;
    using std::end;
    return std::none_of(begin(cont), end(cont), pred);
}

template <class Iter>
struct iter_range : std::pair<Iter, Iter> {
    iter_range(std::pair<Iter, Iter> const& x) : std::pair<Iter, Iter>(x) {}
    Iter begin() const { return this->first; }
    Iter end() const { return this->second; }
};

template <class Iter>
inline iter_range<Iter> as_range(Iter begin, Iter end) {
    return iter_range<Iter>(std::make_pair(begin, end));
}

template <class Iter>
inline iter_range<Iter> as_range(std::pair<Iter, Iter> const& x) {
    return iter_range<Iter>(x);
}

template <typename T, typename OutIt, typename P>
OutIt copy_if(const T& cont, OutIt out, P pred) { 
    using std::begin;
    using std::end;
    return std::copy_if(begin(cont), end(cont), out, pred);
}

template <typename T, typename P>
auto copy_if(const T& cont, P pred) -> std::vector<typename T::value_type> {
    using std::begin;
    using std::end;
    std::vector<typename T::value_type> res;
    std::copy_if(begin(cont), end(cont), std::back_inserter(res), pred);
    return res;
}

template <typename T, typename UnaryOperation>
auto transform(const T& cont, UnaryOperation op)
    -> std::vector<typename std::result_of<UnaryOperation(typename T::value_type)>::type> {

    std::vector<typename std::result_of<UnaryOperation(typename T::value_type)>::type> res;
    res.reserve(cont.size());
    std::transform(cont.begin(), cont.end(), std::back_inserter(res), op);
    return res;
}

template <typename T, typename Pred>
auto ordering(T& cont, Pred pred) -> std::vector<size_t> {
    using std::begin;
    using std::end;
    
    std::vector<size_t> res(cont.size());
    std::iota(res.begin(), res.end(), 0);
    std::sort(res.begin(), res.end(), [&](const size_t& a, const size_t& b){
        return pred(cont[a], cont[b]);
    });
    
    return res;
}

template <typename T>
auto ordering(T& cont) -> std::vector<size_t> {
    return ordering(cont, std::less<typename T::value_type>());
}


template <typename Generator>
auto table(Generator gen, int start, int end, int step = 1) -> 
std::vector<decltype(gen(std::declval<int>()))> {
    using type = decltype(gen(std::declval<int>()));
    std::vector<type> res((end-start)/step);
    size_t count = 0;
    for(int i = start; i < end; i+=step){
        res[count] = gen(i);
        count++;
    }
    return res;
}


template <typename T>
bool is_future_ready(const std::future<T>& future) {
    return (future.valid() &&
            future.wait_for(std::chrono::duration<int, std::milli>(0)) ==
                std::future_status::ready);
}

/**
 * A type trait for std container types
 * from: http://stackoverflow.com/a/16316640
 * This is a slightly modified version to avoid constexpr.
 *
 * Requirements on Container T:
 * T::iterator = T::begin();
 * T::iterator = T::end();
 * T::const_iterator = T::begin() const;
 * T::const_iterator = T::end() const;
 * 
 * *T::iterator = T::value_type &
 * *T::const_iterator = T::value_type const &
 */

template <typename T>
class is_container {
    using test_type = typename std::remove_const<T>::type;

    template <
        typename A, class = typename std::enable_if<
            std::is_same<
                decltype(std::declval<A>().begin()),
                typename A::iterator>::value &&
            std::is_same<
                decltype(std::declval<A>().end()),
                typename A::iterator>::value &&
            std::is_same<
                decltype(std::declval<const A>().begin()),
                typename A::const_iterator>::value &&
            std::is_same<
                decltype(std::declval<const A>().end()),
                typename A::const_iterator>::value &&
            std::is_same<
                decltype(*std::declval<typename A::iterator>()),
                typename A::value_type&>::value &&
            std::is_same<
                decltype(*std::declval<const typename A::iterator>()),
                typename A::value_type const&>::value>::type>
    static std::true_type test(int);

    template <class>
    static std::false_type test(...);

public:
    static const bool value = decltype(test<test_type>(0))::value;
};

/**
 *    Function to combine several hash values
 *    http://stackoverflow.com/questions/2590677/how-do-i-combine-hash-values-in-c0x
 */
template <class T>
inline void hash_combine(std::size_t& seed, const T& v) {
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

}  // namespace util
}  // namespace inviwo

// namespace std {
// template <typename T, glm::precision P, template<typename, glm::precision> class VecType>
// struct hash<VecType<T, P>> {
//     size_t operator()(const VecType<T, P>& v) const {
//         size_t h = 0;
//         for (size_t i = 0; i < inviwo::util::flat_extent<VecType<T, P>>::value; ++i) {
//             T& val = inviwo::util::glmcomp<const VecType<T, P>&>(v, i);
//             inviwo::util::hash_combine(h, val);
//         }
//         return h;
//     }
// };
// 

namespace std {
template <typename T, glm::precision P>
struct hash<glm::detail::tvec2<T, P>> {
    size_t operator()(const glm::detail::tvec2<T, P>& v) const {
        size_t h = 0;
        for (size_t i = 0; i < inviwo::util::flat_extent<glm::detail::tvec2<T, P>>::value; ++i) {
            inviwo::util::hash_combine(h, v[i]);
        }
        return h;
    }
};

template <typename T, glm::precision P>
struct hash<glm::detail::tvec3<T, P>>
{
    size_t operator()(const glm::detail::tvec3<T, P>& v) const {
        size_t h = 0;
        for (size_t i = 0; i < inviwo::util::flat_extent<glm::detail::tvec3<T, P>>::value; ++i) {
            inviwo::util::hash_combine(h, v[i]);
        }
        return h;
    }
};

template <typename T, glm::precision P>
struct hash<glm::detail::tvec4<T, P>>
{
    size_t operator()(const glm::detail::tvec4<T, P>& v) const {
        size_t h = 0;
        for (size_t i = 0; i < inviwo::util::flat_extent<glm::detail::tvec4<T, P>>::value; ++i) {
            inviwo::util::hash_combine(h, v[i]);
        }
        return h;
    }
};


template <typename T, typename U>
struct hash<std::pair<T, U>> {
    size_t operator()(const std::pair<T, U>& p) const {
        size_t h = 0;
        inviwo::util::hash_combine(h, p.first);
        inviwo::util::hash_combine(h, p.second);
        return h;
    }
};


template <class ForwardIt> 
ForwardIt rotateRetval(ForwardIt first, ForwardIt n_first, ForwardIt last) {
#if __GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 9)
    // gcc 4.8.x has no implementation for std::rotate with a return value
    std::rotate(first, n_first, last);
    return first + (last - n_first);
#else
    return std::rotate(first, n_first, last);
#endif
}


}  // namespace std

#endif  // IVW_STDEXTENSIONS_H
