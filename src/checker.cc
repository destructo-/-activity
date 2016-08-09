#include <node.h>
#include <windows.h>

using namespace v8;

namespace checker {
  void method(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    args.GetReturnValue().Set(NanNew::Number(isolate, lastInputTime()));
  }

  int lastInputTime() {
    LASTINPUTINFO li;
    li.cbSize = sizeof(LASTINPUTINFO);
    ::GetLastInputInfo(&li);

    return li.dwTime;
  }

  void init(Local<Object> exports) {
    NODE_SET_METHOD(exports, "checkFreeTime",  method);
  }

  NODE_MODULE(checker, init)
}
