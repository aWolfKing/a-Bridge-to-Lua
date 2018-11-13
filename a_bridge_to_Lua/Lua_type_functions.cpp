#include "Lua_type_functions.h"

namespace lua_types {



	template<typename T_lua_type>
	T_lua_type* default_constructor(lua_State*) {
		return new T_lua_type{};
	}

	template<typename T_lua_type>
	void default_destructor(T_lua_type* obj) {
		delete obj;
	}



	template<typename T_lua_type, lua_constructor<T_lua_type> C_constructor>
	int lua_create_object(lua_State* Lua_state) {
		*(reinterpret_cast<T_lua_type**>(lua_newuserdata(Lua_state, sizeof(T_lua_type*)))) = C_constructor(Lua_state);
		luaL_setmetatable(Lua_state, T_lua_type::Lua_type_info::name);
		return 1;
	}

	template<typename T_lua_type, lua_destructor<T_lua_type> C_destructor>
	int lua_delete_object(lua_State* Lua_state) {
		C_destructor(*(reinterpret_cast<T_lua_type**>(lua_touserdata(Lua_state, 1))));
		return 0;
	}



	template<typename T_lua_type, lua_member_function<T_lua_type> function>
	int lua_member_function_call(lua_State* Lua_state) {
		return ((*(reinterpret_cast<T_lua_type**>(luaL_checkudata(Lua_state, 1, T_lua_type::Lua_type_info::name))))->*function)(Lua_state);
	}



}