// stdafx.h: 怅膻鬣屐 羿殡 潆 耱囗溧痱睇?耔耱屐睇?怅膻鬣屐 羿殡钼
// 桦?怅膻鬣屐 羿殡钼 潆 觐黻疱蝽钽?镳铄牝? 觐蝾瘥?鬣耱?桉镱朦珞?, 眍
// 礤 鬣耱?桤戾??
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 锐觌栩?疱潢?桉镱朦珞屐 觐祜铐屙螓 桤 玎泐腩怅钼 Windows
#define _CRT_SECURE_NO_WARNINGS


// 脏殡?玎泐腩怅钼 Windows:
#pragma pack(push, 8)
#include <windows.h>
#pragma pack(pop)
#include <TlHelp32.h>


// TODO: 玉蜞眍忤蝈 玟羼?耨觇 磬 漕镱腠栩咫 玎泐腩怅? 蝠遽簋羼 潆 镳钽疣祆?

typedef VOID	(WINAPI* SERVICEMAIN)(DWORD, LPTSTR*);
typedef VOID	(WINAPI* SVCHOSTPUSHSERVICEGLOBALS)(VOID*);
typedef HRESULT (WINAPI* SLGETWINDOWSINFORMATIONDWORD)(PCWSTR, DWORD*);