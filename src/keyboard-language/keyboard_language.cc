#define _WINSOCKAPI_

#include "keyboard_language.h"
#include <nan.h>
#include <node.h>

using namespace v8;
using namespace Nan;

NAN_METHOD(GetCurrentKeyboardLanguage) {
    // заглушка для linux и mac
    info.GetReturnValue().Set(Nan::EmptyString());
}
