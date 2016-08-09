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

  void method(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    args.GetReturnValue().Set(Integer::New(isolate, checker::lastInputTime()));
  }

  void init(Local<Object> exports) {
    NODE_SET_METHOD(exports, "checkFreeTime",  method);
  }

  NODE_MODULE(checker, init)
}

