#define _WINSOCKAPI_

#include <nan.h>
#include <windows.h>
#include <node.h>
#include "user-activity/user_activity.h"
#include "activate-window/activate_window.h"

using namespace v8;
using namespace Nan;

NAN_MODULE_INIT(InitAll) {
  Nan::Set(target, New<String>("spyActiveUser").ToLocalChecked(),
    GetFunction(New<FunctionTemplate>(AsyncSpyActive)).ToLocalChecked());

  Nan::Set(target, New<String>("spyUnactiveUser").ToLocalChecked(),
    GetFunction(New<FunctionTemplate>(AsyncSpyUnactive)).ToLocalChecked());

  Nan::Set(target, New<String>("setActiveWindow").ToLocalChecked(),
    GetFunction(New<FunctionTemplate>(SetActiveWindow)).ToLocalChecked());
	
  Nan::Set(target, New<String>("getLastInputTime").ToLocalChecked(),
    GetFunction(New<FunctionTemplate>(GetLastInputTime)).ToLocalChecked());
	
  Nan::Set(target, New<String>("activateWindow").ToLocalChecked(),
    GetFunction(New<FunctionTemplate>(ActivateWindow)).ToLocalChecked());
}

NODE_MODULE(addon, InitAll)
