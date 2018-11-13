#pragma once
#ifndef LUA_TYPE_INFORMATION_H
#define LUA_TYPE_INFORMATION_H

#include <string>

#include "Lua/lua.hpp"

#include "Lua_type_usings.h"

namespace lua_types {



	template<typename T_type, lua_member_function<T_type> function_ptr, const char* function_name>
	struct member_function_information {
		constexpr static const char * name = function_name;
		constexpr static lua_member_function<T_type> function = function_ptr;
	};



}

#endif // !LUA_TYPE_INFORMATION_H
