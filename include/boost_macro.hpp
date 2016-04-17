#ifndef _BOOST_MACRO_
#define _BOOST_MACRO_

# include <boost/python/detail/prefix.hpp>
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/stringize.hpp>


# ifndef MY_BOOST_PYTHON_MODULE_INIT

namespace boost { namespace python { namespace detail {
      BOOST_PYTHON_DECL PyObject* init_module(char const* name, void(*)());
}}}

#   define _MY_BOOST_PYTHON_MODULE_INIT(name)              \
  void BOOST_PP_CAT(init,name)()                        \
{                                                       \
    boost::python::detail::init_module(                 \
        BOOST_PP_STRINGIZE(name),&BOOST_PP_CAT(init_module_,name)); \
}                                                       \
  void BOOST_PP_CAT(init_module_,name)()


#  if (defined(_WIN32) || defined(__CYGWIN__)) && !defined(BOOST_PYTHON_STATIC_MODULE)

#   define MY_BOOST_PYTHON_MODULE_INIT(name)                           \
  void BOOST_PP_CAT(init_module_,name)();                           \
 __declspec(dllexport) _MY_BOOST_PYTHON_MODULE_INIT(name)

#  elif BOOST_PYTHON_USE_GCC_SYMBOL_VISIBILITY

#   define MY_BOOST_PYTHON_MODULE_INIT(name)                               \
  void BOOST_PP_CAT(init_module_,name)();                               \
 __attribute__ ((__visibility__("default"))) _MY_BOOST_PYTHON_MODULE_INIT(name)

#  else

#   define MY_BOOST_PYTHON_MODULE_INIT(name)                               \
  void BOOST_PP_CAT(init_module_,name)();                               \
 _MY_BOOST_PYTHON_MODULE_INIT(name)

#  endif


#  endif // MY_BOOST_PYTHON_MODULE_INIT

#endif //_BOOST_MACRO
