#define _WINSOCKAPI_

#include "activate_window.h"
#include <nan.h>
#include <windows.h>
#include <node.h>

using namespace v8;
using namespace Nan;

bool ActivateWindow(HWND windowHandler, bool isMaximize) {
  DWORD dwThreadID, dwCurThreadID, OldTimeOut;

  if (windowHandler == NULL || !IsWindow(windowHandler)) return false;
  if (GetForegroundWindow() == windowHandler) return true;

  SystemParametersInfo(SPI_GETFOREGROUNDLOCKTIMEOUT, 0, &OldTimeOut, 0);
  SystemParametersInfo(SPI_SETFOREGROUNDLOCKTIMEOUT, 0, NULL, 0);
  SetWindowPos(windowHandler, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

  HWND hCurWnd = GetForegroundWindow();
  bool isZoom = (IsZoomed(windowHandler) != 0);
  
  while(true) {
    dwThreadID = GetCurrentThreadId();
    dwCurThreadID = GetWindowThreadProcessId(hCurWnd, NULL);
    AttachThreadInput(dwThreadID, dwCurThreadID, true);
	
    SetFocus(windowHandler);
    ShowWindow(windowHandler, SW_RESTORE);
    
    if (SetForegroundWindow(windowHandler)) break;

    AttachThreadInput(dwThreadID, dwCurThreadID, false);
    Sleep(250);
  }

  SetWindowPos(windowHandler, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
  SystemParametersInfo(SPI_SETFOREGROUNDLOCKTIMEOUT, 0, &OldTimeOut, 0);

  if (isMaximize) {
    SendMessage(windowHandler, WM_SYSCOMMAND, SC_MAXIMIZE, 0);
  }
  return true;
}

class ActivateWorker : public AsyncWorker {
  public:
    ActivateWorker(HWND window, bool isMaximize, Callback *callback)
        : AsyncWorker(callback), window(window), 
			isMaximize(isMaximize), isSuccess(false)  {}
    ~ActivateWorker() {}

    // Executed inside the worker-thread.
    // It is not safe to access V8, or V8 data structures
    // here, so everything we need for input and output
    // should go on `this`.
    void Execute () {
      isSuccess = ActivateWindow(window, isMaximize);
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
    bool isMaximize;
    bool isSuccess;
};

NAN_METHOD(ActivateWindow) {
  std::string windowName = *Nan::Utf8String(info[0]);
  HWND windowHandler = ::FindWindow(NULL, (LPCSTR)windowName.c_str());
  bool isMaximize = To<bool>(info[1]).FromJust();
  ActivateWindow(windowHandler, isMaximize);
}

NAN_METHOD(SetActiveWindow) {
  std::string windowName = *Nan::Utf8String(info[0]);
  HWND windowHandler = ::FindWindow(NULL, (LPCSTR)windowName.c_str());
  bool isMaximize = To<bool>(info[1]).FromJust();
  Callback *callback = new Callback(info[2].As<Function>());

  AsyncQueueWorker(new ActivateWorker(windowHandler, isMaximize, callback));
}
