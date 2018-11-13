#pragma once
#ifndef LUA_TYPE_HPP
#define LUA_TYPE_HPP

#include "Lua/lua.hpp"
#include <string>

#include "Lua_type_functions.cpp" // .cpp because of templates.
#include "Lua_type_information.h"



namespace lua_types {



	namespace impl {
		namespace func_register_type {


			template<typename T_type, typename T_member_function_info, typename... T_tail>
			struct register_member_function {
				static void do_for_state(lua_State* Lua_state) {
					lua_pushcfunction(Lua_state, T_member_function_info::function);
					lua_setfield(Lua_state, -2, (lua_member_function_call<T_type, T_member_function_info::name>));
					register_member_function<T_tail...>::do_for_state(Lua_state);
				}
			};

			template<typename T_type, typename T_member_function_info>
			struct register_member_function<T_type, T_member_function_info> {
				static void do_for_state(lua_State* Lua_state) {
					lua_pushcfunction(Lua_state, (lua_member_function_call<T_type, T_member_function_info::function>));
					lua_setfield(Lua_state, -2, T_member_function_info::name);
				}
			};

			/*
			template<typename T_member_function_info, typename... T_tail>
			void register_member_function(lua_State* Lua_state) {
				lua_pushcfunction(Lua_state, T_member_function_info::function);
				lua_setfield(Lua_state, -2, T_member_function_info::name);
				register_member_function<T_tail...>(Lua_state);
			}
			*/


		}
	}



	template<typename T_type, lua_constructor<T_type> constructor = default_constructor<T_type>, lua_destructor<T_type> destructor = default_destructor<T_type>, typename... T_member_function_info>
	void register_type(lua_State* Lua_state) {
		// Create the meta table if the meta table does not yet exist.
		if (!luaL_getmetatable(Lua_state, T_type::Lua_type_info::name)) {

			// Create global table to enable "Type.new()" as constructor.
			{
				lua_newtable(Lua_state);
				lua_pushcfunction(Lua_state, (lua_create_object<T_type, constructor>));
				lua_setfield(Lua_state, -2, "new");
				lua_setglobal(Lua_state, T_type::Lua_type_info::name);
			}

			// Destructor
			{
				luaL_newmetatable(Lua_state, T_type::Lua_type_info::name);
				lua_pushcfunction(Lua_state, (lua_delete_object<T_type, destructor>));
				lua_setfield(Lua_state, -2, "__gc");
			}

			lua_pushvalue(Lua_state, -1);
			lua_setfield(Lua_state, -2, "__index");

			//member functions
			{
				impl::func_register_type::register_member_function<T_type, T_member_function_info...>::do_for_state(Lua_state);
				/*
				for (auto mem_func& : member_functions) {
					lua_pushcfunction(Lua_state, mem_func.function);
					lua_setfield(Lua_state, -2, mem_func.function_name);
				}
				*/
			}

			lua_pop(Lua_state, 1);

		}
	}



}

#endif // !LUA_TYPE_H