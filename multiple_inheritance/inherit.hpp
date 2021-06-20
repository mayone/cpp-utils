/* Inherit with template parameter pack */

namespace inherit
{
    /* Compose multiple inheritance object recursively */
    template <class T, class... Rest>
    struct compose_impl : T, compose_impl<Rest...>
    {
    };

    /* Specialization for single element. */
    template <class T>
    struct compose_impl<T> : T
    {
    };

    /* Default compose operation for variadic arguments. */
    template <class... Args>
    struct compose : compose_impl<Args...>
    {
    };

    /* Specialization for zero variadic arguments. */
    template <>
    struct compose<>
    {
    };

    /* Class to compose multiple classes */
    template <class... Args>
    struct object : compose<Args...>
    {
    };
} // namespace inherit