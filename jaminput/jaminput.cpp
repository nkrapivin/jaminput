// jaminput.cpp: определяет экспортированные функции для приложения DLL.
// а некита дебил

#include "stdafx.h"
#include "jaminput.h"

int sendinput(lua_State* _pL) {
	lua_Integer tablelen = 0;
	lua_Integer i = 0;
	INPUT* inputs = nullptr;

	// должен быть минимум один аргумент, и он должен быть таблицей
	// если не так, луа вызовет ошибку.
	luaL_checktype(_pL, 1, LUA_TTABLE);

	// #arg
	lua_len(_pL, 1);
	tablelen = lua_tointeger(_pL, -1);
	lua_pop(_pL, 1);

	if (tablelen <= 0) {
		lua_pushinteger(_pL, -1); // SendInput возвращает UINT, то есть код ошибки -1 значит что у тебя даже данных то и нет.
		return 1; // даже не пытаться.
	}

	inputs = static_cast<INPUT*>(_malloca(static_cast<size_t>(tablelen * sizeof(INPUT))));
	ZeroMemory(inputs, static_cast<size_t>(tablelen * sizeof(INPUT)));

	for (i = 0; i < tablelen; i++) {
		// arg[i]
		// если аргумент не таблица то бросить ошибку что не тот тип.
		if (lua_geti(_pL, 1, 1 + i) != LUA_TTABLE) {
			return luaL_typeerror(_pL, -1, lua_typename(_pL, LUA_TTABLE));
		}

		// arr[i].type
		if (lua_getfield(_pL, -1, "type") != LUA_TNUMBER) {
			return luaL_typeerror(_pL, -1, lua_typename(_pL, LUA_TNUMBER));
		}

		inputs[i].type = static_cast<DWORD>(lua_tointeger(_pL, -1));
		lua_pop(_pL, 1);

		// а дальше мне руками тип проверять лень, луа и так ошибку вызовет если что-то не так.
		switch (inputs[i].type) {
			case INPUT_MOUSE: {
				if (lua_getfield(_pL, -1, "dx") != LUA_TNIL)
					inputs[i].mi.dx = static_cast<LONG>(lua_tointeger(_pL, -1));
				lua_pop(_pL, 1);

				if (lua_getfield(_pL, -1, "dy") != LUA_TNIL)
					inputs[i].mi.dy = static_cast<LONG>(lua_tointeger(_pL, -1));
				lua_pop(_pL, 1);

				if (lua_getfield(_pL, -1, "mouseData") != LUA_TNIL)
					inputs[i].mi.mouseData = static_cast<DWORD>(lua_tointeger(_pL, -1));
				lua_pop(_pL, 1);

				if (lua_getfield(_pL, -1, "dwFlags") != LUA_TNIL)
					inputs[i].mi.dwFlags = static_cast<DWORD>(lua_tointeger(_pL, -1));
				lua_pop(_pL, 1);

				if (lua_getfield(_pL, -1, "time") != LUA_TNIL)
					inputs[i].mi.time = static_cast<DWORD>(lua_tointeger(_pL, -1));
				lua_pop(_pL, 1);

				if (lua_getfield(_pL, -1, "dwExtraInfo") != LUA_TNIL)
					inputs[i].mi.dwExtraInfo = static_cast<ULONG_PTR>(lua_tointeger(_pL, -1));
				lua_pop(_pL, 1);

				break;
			}

			case INPUT_KEYBOARD: {
				if (lua_getfield(_pL, -1, "wVk") != LUA_TNIL)
					inputs[i].ki.wVk = static_cast<WORD>(lua_tointeger(_pL, -1));
				lua_pop(_pL, 1);

				if (lua_getfield(_pL, -1, "wScan") != LUA_TNIL)
					inputs[i].ki.wScan = static_cast<WORD>(lua_tointeger(_pL, -1));
				lua_pop(_pL, 1);

				if (lua_getfield(_pL, -1, "dwFlags") != LUA_TNIL)
					inputs[i].ki.dwFlags = static_cast<DWORD>(lua_tointeger(_pL, -1));
				lua_pop(_pL, 1);

				if (lua_getfield(_pL, -1, "time") != LUA_TNIL)
					inputs[i].ki.time = static_cast<DWORD>(lua_tointeger(_pL, -1));
				lua_pop(_pL, 1);

				if (lua_getfield(_pL, -1, "dwExtraInfo") != LUA_TNIL)
					inputs[i].ki.dwExtraInfo = static_cast<ULONG_PTR>(lua_tointeger(_pL, -1));
				lua_pop(_pL, 1);

				break;
			}

			case INPUT_HARDWARE: {
				if (lua_getfield(_pL, -1, "uMsg") != LUA_TNIL)
					inputs[i].hi.uMsg = static_cast<DWORD>(lua_tointeger(_pL, -1));
				lua_pop(_pL, 1);

				if (lua_getfield(_pL, -1, "wParamL") != LUA_TNIL)
					inputs[i].hi.wParamL = static_cast<WORD>(lua_tointeger(_pL, -1));
				lua_pop(_pL, 1);

				if (lua_getfield(_pL, -1, "wParamH") != LUA_TNIL)
					inputs[i].hi.wParamH = static_cast<WORD>(lua_tointeger(_pL, -1));
				lua_pop(_pL, 1);

				break;
			}

			default: {
				lua_pop(_pL, 1);

				return luaL_error(_pL, "Invalid input type, expected KEYBOARD, MOUSE or HARDWARE, got %d.", static_cast<int>(inputs[i].type));
			}
		}

		lua_pop(_pL, 1);
	}

	// наконец
	lua_pushinteger(_pL, SendInput(static_cast<UINT>(tablelen), inputs, sizeof(INPUT)));
	return 1; // один элемент - код ошибки (или успеха), я обычно надеюсь на ошибку.
}

#define lua_setconstant(_lua_state, _constant) lua_pushinteger((_lua_state), (_constant)); lua_setglobal((_lua_state), (#_constant))
void lua_jaminput_constants(lua_State* _pL) {
	// ох этот винапи по утрам
	// ммммм.... а пахне як

	// input type
	lua_setconstant(_pL, INPUT_MOUSE);
	lua_setconstant(_pL, INPUT_KEYBOARD);
	lua_setconstant(_pL, INPUT_HARDWARE);

	// keyboard event
	lua_setconstant(_pL, KEYEVENTF_KEYUP);
	lua_setconstant(_pL, KEYEVENTF_EXTENDEDKEY);
	lua_setconstant(_pL, KEYEVENTF_UNICODE);
	lua_setconstant(_pL, KEYEVENTF_SCANCODE);

	// mouse event
	lua_setconstant(_pL, MOUSEEVENTF_MOVE);
	lua_setconstant(_pL, MOUSEEVENTF_LEFTDOWN);
	lua_setconstant(_pL, MOUSEEVENTF_LEFTUP);
	lua_setconstant(_pL, MOUSEEVENTF_RIGHTDOWN);
	lua_setconstant(_pL, MOUSEEVENTF_RIGHTUP);
	lua_setconstant(_pL, MOUSEEVENTF_MIDDLEDOWN);
	lua_setconstant(_pL, MOUSEEVENTF_MIDDLEUP);
	lua_setconstant(_pL, MOUSEEVENTF_XDOWN);
	lua_setconstant(_pL, MOUSEEVENTF_XUP);
	lua_setconstant(_pL, MOUSEEVENTF_WHEEL);
	lua_setconstant(_pL, MOUSEEVENTF_HWHEEL);
	lua_setconstant(_pL, MOUSEEVENTF_MOVE_NOCOALESCE);
	lua_setconstant(_pL, MOUSEEVENTF_VIRTUALDESK);
	lua_setconstant(_pL, MOUSEEVENTF_ABSOLUTE);

	// TODO: добавить сюда больше говна из винапи (keycode?)
}

void lua_jaminput_lib(lua_State* _pL) {
	const luaL_Reg jamtable[] = {
		{ "sendinput", sendinput },
		{ nullptr, nullptr }
	};

	luaL_newlib(_pL, jamtable);
}

// jam = require("jaminput") вызовет в дллке функцию luaopen_jaminput
// по этому важно, что она экспортируется через JAMINPUT_API
// а sendinput похуй так-то.
EXTERN_C JAMINPUT_API int CDECL luaopen_jaminput(lua_State* _pL) {
	lua_jaminput_constants(_pL);
	lua_jaminput_lib(_pL);
	return 1;
	// jam.sendinput() будет вызывать sendinput
}