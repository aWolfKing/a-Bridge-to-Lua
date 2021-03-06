﻿// My_Lua_bridge.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

#include "Lua/lua.hpp"
#include "lua_types.hpp"



template<int I>
int L_func(lua_State* ls);

template<>
int L_func<0>(lua_State* ls) {
	std::cout << "l func 0" << std::endl;
	return 0;
}

template<>
int L_func<1>(lua_State* ls) {
	std::cout << "l func 1" << std::endl;
	return 0;
}



struct my_lua_type {

public:
	constexpr static const char im_alive_name[] = "shout";
	constexpr static const char type_name[] = "my_lua_type";

	using Lua_type_info = struct{
		constexpr static const char name[] = "my_lua_type";
	};

	my_lua_type() {
		std::cout << "my_lua_type created!" << std::endl;
	}
	~my_lua_type() {
		std::cout << "my_lua_type_destructed!" << std::endl;
	}
	int print_im_alive(lua_State*) {
		std::cout << "I AM ALIVE!" << std::endl;
		return 0;
	} 
};



int main()
{
	lua_State* Lua_state = luaL_newstate();

	lua_types::register_type<my_lua_type,
		&lua_types::default_constructor<my_lua_type>,
		&lua_types::default_destructor<my_lua_type>,
		lua_types::member_function_information < my_lua_type, &my_lua_type::print_im_alive, my_lua_type::im_alive_name>
	>(Lua_state);

	std::string str_to_load = "";

	str_to_load
		.append("function da_thing()")
		.append("local obj = my_lua_type.new();")
		.append("obj:shout();")
		.append("end;")
		.append("da_thing();");

	luaL_loadstring(Lua_state, str_to_load.c_str());
	lua_pcall(Lua_state, 0, 0, 0);

	lua_close(Lua_state);

	// Test if template fuctions are accepted by lua_pushcfunction(), they should and they do.
	/*
	lua_State* Lua_state = luaL_newstate();

	lua_pushcfunction(Lua_state, L_func<0>);
	lua_setglobal(Lua_state, "func0");
	lua_pushcfunction(Lua_state, L_func<1>);
	lua_setglobal(Lua_state, "func1");

	luaL_loadstring(Lua_state, "func0(); func1();");
	lua_pcall(Lua_state, 0, 0, 0);

	lua_close(Lua_state);
	*/

}
