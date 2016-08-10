#include <node.h>
#include <windows.h>

using namespace v8;

namespace checker {
  int lastInputTime() {
    LASTINPUTINFO li;
    li.cbSize = sizeof(LASTINPUTINFO);
    ::GetLastInputInfo(&li);

    return ::GetTickCount() - li.dwTime;
  }

  /**
   * @param { int } args[0] время простоя
   * @param { function } args[1] js callback
   */
  void method(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    bool userActive = true;
    int delay = Integer::New(args[0]);
    Local<Function> callback = Local<Function>::Cast(args[1]);

    do {
      userActive = delay <= lastInputTime();
      if(!userActive) {
        callback->Call(Null(isolate));
      }
    } while(userActive);

    // args.GetReturnValue().Set(Integer::New(isolate, checker::lastInputTime()));    
  }

  void init(Local<Object> exports) {
    NODE_SET_METHOD(exports, "checkDwTime",  method);
  }

  NODE_MODULE(checker, init)
}
