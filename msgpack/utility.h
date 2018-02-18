#ifndef RPC_UTILITY_H__
#define RPC_UTILITY_H__

#include "object.h"

namespace rpc {

namespace detail {

/*
    Helper functions for move
*/

template <class T>
struct remove_reference { typedef T type; };

template <class T>
struct remove_reference<T&> { typedef T type; };

template <class T>
struct remove_reference<T&&> { typedef T type; };

/*
    Helper function for get tuple
*/

template<int index, typename First, typename... Rest>
struct get_impl {
        static auto value(const tuple<First, Rest...>* t) -> decltype(get_impl<index - 1, Rest...>::value(t)) {
                return get_impl<index - 1, Rest...>::value(t);
        }
};

template<typename First, typename... Rest>
struct get_impl<0, First, Rest...> {
        static First value(const tuple<First, Rest...>* t) {
                return t->first;
                }
};

} // namespace detail

template <typename T>
typename detail::remove_reference<T>::type&& move(T&& arg)
{
        return static_cast<typename detail::remove_reference<T>::type&&>(arg);
}

template<typename First, typename... Rest>
struct tuple: public tuple<Rest...> {
        tuple(First first, Rest... rest): tuple<Rest...>(rest...), first(first) {}

        First first;
};

template<typename First>
struct tuple<First> {
        tuple(First first): first(first) {}

        First first;
};


template<int index, typename First, typename... Rest>
auto get(const tuple<First, Rest...>& t) -> decltype(detial::get_impl<index, First, Rest...>::value(&t)) {
        return detial::get_impl<index, First, Rest...>::value(&t);
}


} // namespace rpc


#endif
