// ����������� ���� ���� ifdef - ��� ����������� ����� �������� ��������, ���������� ��������� 
// �������� �� ��������� DLL. ��� ����� ������ DLL �������������� � �������������� ������� JAMINPUT_EXPORTS,
// � ��������� ������. ���� ������ �� ������ ���� ��������� � �����-���� �������
// ������������ ������ DLL. ��������� ����� ����� ������ ������, ��� �������� ����� �������� ������ ����, ����� 
// ������� JAMINPUT_API ��� ��������������� �� DLL, ����� ��� ������ DLL ����� �������,
// ������������ ������ ��������, ��� ����������������.
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