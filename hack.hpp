//
//  hack.hpp
//  cpp-private-hack
//
//  Created by Mashpoe on 12/23/20.
//

#ifndef hack_h
#define hack_h

#include <memory>

namespace {
  // This is a *different* type in every translation
  // unit because of the anonymous namespace.
  struct TranslationUnitTag {};
}

// here TranslationUnitTag is just a placeholder,
// this serves as a member function pointer equivalent to void*
typedef void (TranslationUnitTag::*hijack_fun_t)();

#define hijack_method(hijack_target, hijack_name)\
\
hijack_fun_t hijack_name();\
\
template <typename Tag,\
typename ForbiddenFunc,\
ForbiddenFunc forbidden_func>\
class hijack_ ## hijack_name {\
  \
	friend hijack_fun_t hijack_name() {\
		return (hijack_fun_t)forbidden_func;\
	}\
  \
  \
};\
\
template class hijack_ ## hijack_name<TranslationUnitTag, decltype(&hijack_target), &hijack_target>;

#endif /* hack_h */
