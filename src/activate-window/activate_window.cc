#define _WINSOCKAPI_

#include "user_activity.h"
#include <nan.h>
#include <windows.h>
#include <node.h>

using namespace v8;
using namespace Nan;

bool ActivateWindow(HWND windowHandler) {
  HWND hCurWnd;
  DWORD dwThreadID, dwCurThreadID, OldTimeOut;

  if (windowHandler == NULL || !IsWindow(windowHandler)) return false;

  SystemParametersInfo(SPI_GETFOREGROUNDLOCKTIMEOUT, 0, &OldTimeOut, 0);
  SystemParametersInfo(SPI_SETFOREGROUNDLOCKTIMEOUT, 0, NULL, 0);
  SetWindowPos(windowHandler, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

  hCurWnd = GetForegroundWindow();

  while(true) {
    dwThreadID = GetCurrentThreadId();
    dwCurThreadID = GetWindowThreadProcessId(hCurWnd, NULL);
    AttachThreadInput(dwThreadID, dwCurThreadID, true);
    if (SetForegroundWindow(windowHandler)) break;
    AttachThreadInput(dwThreadID, dwCurThreadID, false);
  }

  SetWindowPos(windowHandler, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
  SystemParametersInfo(SPI_SETFOREGROUNDLOCKTIMEOUT, 0, &OldTimeOut, 0);
  return true;
}

class ActivateWorker : public AsyncWorker {
  public:
    ActivateWorker(HWND window, Callback *callback)
        : AsyncWorker(callback), window(window), isSuccess(false)  {}
    ~ActivateWorker() {}

    // Executed inside the worker-thread.
    // It is not safe to access V8, or V8 data structures
    // here, so everything we need for input and output
    // should go on `this`.
    void Execute () {
        isSuccess = ActivateWindow(window);
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
    HWND window;
    bool isSuccess;
};

NAN_METHOD(SetActiveWindow) {
  std::string windowName = *Nan::Utf8String(info[0]);
  HWND windowHandler = ::FindWindow(NULL, (LPCSTR)windowName.c_str()), hCurWnd;
  Callback *callback = new Callback(info[1].As<Function>());

  AsyncQueueWorker(new ActivateWorker(windowHandler, callback));
}