#ifndef __TYPELIST_H__
#define __TYPELIST_H__

#include <cstddef>
#include <type_traits>

template <typename... T>
struct TypeList {};

namespace __TypeList_inner__ {

template <typename List>
struct Size;

template <typename... T>
struct Size<TypeList<T...>> {
  static constexpr size_t size = sizeof...(T);
};

template <typename Elem, typename List>
struct PushBack;
  
template <typename Elem, typename... T>
struct PushBack<Elem, TypeList<T...>> {
  using type = TypeList<T..., Elem>;
};

template <typename Elem, typename List>
struct PushFront;

template <typename Elem, typename... T>
struct PushFront<Elem, TypeList<T...>> {
  using type = TypeList<Elem, T...>;
};

template <size_t i, typename List>
struct Get;

template <typename T1, typename... T2>
struct Get<0, TypeList<T1, T2...>> {
  using type = T1;
};

template <size_t i, typename T1, typename... T2>
struct Get<i, TypeList<T1, T2...>> {
  using type = typename Get<i - 1, TypeList<T2...>>::type;
};

template <size_t i>
struct Get<i, TypeList<>> {
  static_assert(i < 0, "Index out of borders!");
};

template <typename Type, typename List>
struct Contains;

template <typename Type, typename... T>
struct Contains<Type, TypeList<T...>> {
  static constexpr bool value = (std::is_same_v<Type, T> || ...);
};

template <typename Type, int i, typename List>
struct IndexOf;

template <typename Type, int i, typename T1, typename... T2>
struct IndexOf<Type, i, TypeList<T1, T2...>> {
  static constexpr int index =
      std::is_same_v<Type, T1> ? i
                               : IndexOf<Type, i + 1, TypeList<T2...>>::index;
};

template <typename Type, int i>
struct IndexOf<Type, i, TypeList<>> {
  static constexpr int index = -1;
};
};  // namespace __TypeList_inner__

template <typename List>
inline constexpr size_t Size = __TypeList_inner__::Size<List>::size;

template <typename List, typename Elem>
using PushBack = typename __TypeList_inner__::PushBack<Elem, List>::type;

template <typename List, typename Elem>
using PushFront = typename __TypeList_inner__::PushFront<Elem, List>::type;

template <typename List, size_t i>
using Get = typename __TypeList_inner__::Get<i, List>::type;

template <typename List, typename Type>
inline constexpr int IndexOf =
    __TypeList_inner__::IndexOf<Type, 0, List>::index;

template <typename List, typename Type>
inline constexpr bool Contains =
    __TypeList_inner__::Contains<Type, List>::value;

#endif