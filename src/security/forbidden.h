/*
 * security/forbidden.h — Compile-time ban of dangerous / Win32-only APIs
 *
 * Include this file via -include in CMakeLists.txt so that every
 * translation unit is covered automatically.
 *
 * Any use of a poisoned identifier will cause a hard compiler error,
 * preventing accidental introduction of Win32 dependencies or
 * unsafe C functions into the cross-platform Qt codebase.
 */

#pragma once

#ifdef __GNUC__

/* ---- Win32 registry / INI helpers (replaced by QSettings) ---- */
#pragma GCC poison GetPrivateProfileString
#pragma GCC poison GetPrivateProfileInt
#pragma GCC poison WritePrivateProfileString

/* ---- Win32 string APIs (use QString / std::string) ---- */
#pragma GCC poison _tcslen
#pragma GCC poison _tcscpy
#pragma GCC poison _tcsncpy
#pragma GCC poison _tcscat
#pragma GCC poison _tcscmp
#pragma GCC poison _tcsicmp
#pragma GCC poison lstrcpy
#pragma GCC poison lstrcat
#pragma GCC poison lstrlen
#pragma GCC poison lstrcmp
#pragma GCC poison lstrcmpi
#pragma GCC poison wsprintf
#pragma GCC poison wvsprintf

/* ---- Unsafe C string functions (use bounded variants) ---- */
#pragma GCC poison gets

/*
 * NOTE: sprintf, vsprintf, strcpy, strcat, strtok are intentionally
 * NOT poisoned because they appear in <cstdio>/<cstring> standard
 * library headers.  The -Wformat=2 and _FORTIFY_SOURCE=2 flags
 * already catch misuse at compile/link time.
 */

/* ---- Win32 threading (use QThread / QMutex / std::thread) ---- */
#pragma GCC poison CreateThread
#pragma GCC poison _beginthread
#pragma GCC poison _beginthreadex
#pragma GCC poison InitializeCriticalSection
#pragma GCC poison EnterCriticalSection
#pragma GCC poison LeaveCriticalSection
#pragma GCC poison DeleteCriticalSection

/* ---- Win32 message loop (use Qt signal/slot) ---- */
#pragma GCC poison PostMessage
#pragma GCC poison SendMessage
#pragma GCC poison PeekMessage
#pragma GCC poison GetMessage
#pragma GCC poison DispatchMessage
#pragma GCC poison TranslateMessage

/* ---- Win32 memory (use new/delete, smart pointers, containers) ---- */
#pragma GCC poison GlobalAlloc
#pragma GCC poison GlobalFree
#pragma GCC poison LocalAlloc
#pragma GCC poison LocalFree
#pragma GCC poison HeapAlloc
#pragma GCC poison HeapFree

/* ---- MFC types that must not leak into Qt code ---- */
#pragma GCC poison CString
#pragma GCC poison CWnd
#pragma GCC poison CDialog
#pragma GCC poison CWinApp
#pragma GCC poison AfxMessageBox

#endif /* __GNUC__ */
