#define _WINSOCKAPI_

#include <nan.h>
#include <windows.h>
#include <node.h>
#include "user-activity/user_activity.h"
#include "activate-window/activate_window.h"
#include "checker.h"

using namespace v8;
using namespace Nan;

NAN_METHOD(GetLastInputTime) {
  int lastInputTime;
  lastInputTime = LastInputTime();
  info.GetReturnValue().Set(lastInputTime);
}

NAN_MODULE_INIT(InitAll) {
  Nan::Set(target, New<String>("setActiveWindow").ToLocalChecked(),
    GetFunction(New<FunctionTemplate>(SetActiveWindow)).ToLocalChecked());

  Nan::Set(target, New<String>("getLastInputTime").ToLocalChecked(),
    GetFunction(New<FunctionTemplate>(GetLastInputTime)).ToLocalChecked());

  Nan::Set(target, New<String>("activateWindow").ToLocalChecked(),
    GetFunction(New<FunctionTemplate>(ActivateWindow)).ToLocalChecked());
}

NODE_MODULE(checker, InitAll)
