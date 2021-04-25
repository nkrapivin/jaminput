// Приведенный ниже блок ifdef - это стандартный метод создания макросов, упрощающий процедуру 
// экспорта из библиотек DLL. Все файлы данной DLL скомпилированы с использованием символа JAMINPUT_EXPORTS,
// в командной строке. Этот символ не должен быть определен в каком-либо проекте
// использующем данную DLL. Благодаря этому любой другой проект, чьи исходные файлы включают данный файл, видит 
// функции JAMINPUT_API как импортированные из DLL, тогда как данная DLL видит символы,
// определяемые данным макросом, как экспортированные.
#include "stdafx.h"
#ifdef JAMINPUT_EXPORTS
#define JAMINPUT_API __declspec(dllexport)
#else
#define JAMINPUT_API __declspec(dllimport)
#endif

#include "lua\lua.hpp"

int sendinput(lua_State* _pL);
void lua_jaminput_constants(lua_State* _pL);
void lua_jaminput_lib(lua_State* _pL);
EXTERN_C JAMINPUT_API int CDECL luaopen_jaminput(lua_State* _pL);