#pragma once
#ifndef LUA_TYPE_USINGS_H
#define LUA_TYPE_USINGS_H

#include "Lua/lua.hpp"

namespace lua_types {



	using lua_function = int(*)(lua_State*);


	template<typename T_type>
	using lua_member_function = int(T_type::*)(lua_State*);


	template<typename T_lua_type>
	using lua_constructor = T_lua_type * (*)(lua_State*);


	template<typename T_lua_type>
	using lua_destructor = void(*)(T_lua_type*);



}

#endif // !LUA_TYPE_USINGS_H