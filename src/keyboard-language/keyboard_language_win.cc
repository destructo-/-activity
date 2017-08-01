#define _WINSOCKAPI_

#include "keyboard_language.h"
#include "LanguageProfileNotifySink.h"
#include <nan.h>
#include <windows.h>
#include <node.h>

using namespace v8;
using namespace Nan;

NAN_METHOD(GetCurrentKeyboardLanguage) {
  Local<Function> callbackHandle = info[0].As<Function>();
  Nan::Callback *callback = new Nan::Callback(callbackHandle);
  HRESULT CLanguageProfileNotifySink::OnLanguageChanged() {
    callback();
    return S_OK;
  }
}
