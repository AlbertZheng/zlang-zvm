/*
 * Put any default '#undef' or '#define' here, they will be copied to top of 'config.h.in'.
 */
@TOP@


/*
 * Here are requied macros by 'AC_DEFINE()' in 'configure.in'.
 */
#undef __linux__
#undef __solaris__

#undef ENABLE_DEBUG_ZLS_malloc
#undef ENABLE_THREADS
#undef HAVE_PTHREAD_H
#undef HAVE_CXX_EH
#undef HAVE_CXX_NS
#undef HAVE_CXX_STL
#undef ENABLE_OVERLOAD_OPERATOR_NEW
#undef NDEBUG

#undef HAVE_ASM_ATOMIC_H
#undef HAVE_SYS_ATOMIC_H
#undef HAVE_ATOMIC
#undef HAVE_PTHREAD_MUTEX_RECURSIVE
#undef HAVE_STRUCT_ICMPHDR
#undef HAVE_TCP_STATES
#undef HAVE_STRUCT_UDPHDR

#undef ENABLE_ZVM_DEBUG
#undef ENABLE_ZVM_OPTIMIZATION


@BOTTOM@
/*
 * Put any default '#undef' or '#define' here, they will be copied to bottom of 'config.h.in'.
 */
