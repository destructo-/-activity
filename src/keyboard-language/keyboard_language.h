#ifndef KEYBOARD_LANGUAGE_NATIVE_NODE_NODULE
#define KEYBOARD_LANGUAGE_NATIVE_NODE_NODULE
/*
#ifdef WINVER
#undef WINVER
!~!#endif
#define WINVER 0x500
*/

#include <nan.h>
#include <windows.h>
#include <node.h>
#include <iostream>
#include <string.h>

NAN_METHOD(GetCurrentKeyboardLanguage);

#endif // KEYBOARD_LANGUAGE_NATIVE_NODE_NODULE
