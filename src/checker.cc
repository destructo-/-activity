#define _WINSOCKAPI_

#include <nan.h>
#include <windows.h>
#include <node.h>

using namespace v8;
using namespace Nan;

int lastInputTime() {
    LASTINPUTINFO li;
    li.cbSize = sizeof(LASTINPUTINFO);
    ::GetLastInputInfo(&li);

    return ::GetTickCount() - li.dwTime;
  }

bool isUserActive(int delay, int lit) {
  if (delay >= lit) {
    return true;
  }
  return false;
}

bool spyActiveUser(int delay) {
    bool userActive = true;

    do {
      userActive = isUserActive(delay, lastInputTime());
      if(!userActive) {
        return true;
      }
    } while(userActive);
    return false;
}

bool spyUnactiveUser(int delay) {
    bool userActive = false;

    do {
      userActive = isUserActive(delay, lastInputTime());
      if(userActive) {
        return true;
      }
    } while(!userActive);
    return false;
}

class SpyWorker : public AsyncWorker {
 public:
  SpyWorker(int delay, Callback *callback, bool (*asyncMethod)(int))
    : AsyncWorker(callback), delay(delay), isSuccess(false), asyncMethod(asyncMethod)  {}
  ~SpyWorker() {}

  // Executed inside the worker-thread.
  // It is not safe to access V8, or V8 data structures
  // here, so everything we need for input and output
  // should go on `this`.
  void Execute () {
    isSuccess = asyncMethod(delay);
  }

  // Executed when the async work is complete
  // this function will be run inside the main event loop
  // so it is safe to use V8 again
  void HandleOKCallback () {
    Nan::HandleScope scope;
    Local<Value> argv[1] = { New<Boolean>(isSuccess) };
    callback->Call(2, argv);
  }

 private:
  int delay;
  bool isSuccess;
  bool (*asyncMethod)(int);
};

NAN_METHOD(AsyncSpyActive) {
  int delay = To<int>(info[0]).FromJust();
  Callback *callback = new Callback(info[1].As<Function>());

  AsyncQueueWorker(new SpyWorker(delay, callback, &spyActiveUser));
}

NAN_METHOD(AsyncSpyUnactive) {
  int delay = To<int>(info[0]).FromJust();
  Callback *callback = new Callback(info[1].As<Function>());

  AsyncQueueWorker(new SpyWorker(delay, callback, &spyUnactiveUser));
}

NAN_METHOD(SetActiveWindow) {
  HWND hwnd = (HWND)info[0]->IntegerValue();
  ::SetForegroundWindow(hwnd);
}

NAN_MODULE_INIT(InitAll) {
  Nan::Set(target, New<String>("spyActiveUser").ToLocalChecked(),
    GetFunction(New<FunctionTemplate>(AsyncSpyActive)).ToLocalChecked());

  Nan::Set(target, New<String>("spyUnactiveUser").ToLocalChecked(),
    GetFunction(New<FunctionTemplate>(AsyncSpyUnactive)).ToLocalChecked());

  Nan::Set(target, New<String>("setActiveWindow").ToLocalChecked(),
    GetFunction(New<FunctionTemplate>(SetActiveWindow)).ToLocalChecked());
}

NODE_MODULE(addon, InitAll)
