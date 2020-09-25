#ifndef INIT_GUARD_MACRO_INC
#define INIT_GUARD_MACRO_INC

#define GET_MACRO(_1, _2, NAME, ...) NAME
#define INIT_GUARD(...)                                                        \
    GET_MACRO(__VA_ARGS__, INIT_GUARD2, INIT_GUARD1)(__VA_ARGS__)

#define INIT_GUARD1(FLAG)                                                      \
    if (!FLAG)                                                                 \
        return;
#define INIT_GUARD2(FLAG, value2)                                              \
    if (!FLAG)                                                                 \
        return value2;
#endif // INIT_GUARD_MACRO_INC
