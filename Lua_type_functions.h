#pragma once
#ifndef LUA_TYPE_FUNCTIONS
#define LUA_TYPE_FUNCTIONS

#include "Lua/lua.hpp"
#include "Lua_type_usings.h"
#include "Lua_type_information.h"

namespace lua_types {



	template<typename T_lua_type>
	T_lua_type* default_constructor(lua_State*);


	template<typename T_lua_type>
	void default_destructor(T_lua_type*);




	template<typename T_lua_type, lua_constructor<T_lua_type> C_constructor = default_constructor<T_lua_type>>
	int lua_create_object(lua_State* Lua_state);


	template<typename T_lua_type, lua_destructor<T_lua_type> C_destructor = default_destructor<T_lua_type>>
	int lua_delete_object(lua_State* Lua_state);


	template<typename T_lua_type, lua_member_function<T_lua_type> function>
	int lua_member_function_call(lua_State* Lua_state);



}

#endif // !LUA_TYPE_FUNCTIONS
