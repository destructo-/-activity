#include <node.h>
#include <windows.h>

using namespace v8;

namespace checker {
  void spyActiveUser(const FunctionCallbackInfo<Value>& args);
  void spyUnactiveUser(const FunctionCallbackInfo<Value>& args);

  int64_t lastInputTime() {
    LASTINPUTINFO li;
    li.cbSize = sizeof(LASTINPUTINFO);
    ::GetLastInputInfo(&li);

    return ::GetTickCount() - li.dwTime;
  }

  bool isUserActive(int64_t delay, int64_t lit) {
    if (delay >= lit) {
      return true;
    }
    return false;
  }

  bool checkArguments(const FunctionCallbackInfo<Value>& args) {
    if (args.Length() == 3 && args[0]->IsNumber() &&
        args[1]->IsFunction() && args[2]->IsFunction()) {
      return true;
    }
    return false;
  }

  void spyUnactiveUser(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    bool userActive = false;
    int64_t delay = args[0]->IntegerValue();
    Local<Function> callback = Local<Function>::Cast(args[2]);

    do {
      userActive = isUserActive(delay, lastInputTime());
      if(userActive) {
        const unsigned argc = 1;
        Local<Value> argv[argc] = { String::NewFromUtf8(isolate, "user back") };
        callback->Call(Null(isolate), argc, argv);
      }
    } while(!userActive);

    spyActiveUser(args);
  }

  void spyActiveUser(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    bool userActive = true;
    int64_t delay = args[0]->IntegerValue();
    Local<Function> callback = Local<Function>::Cast(args[1]);

    do {
      userActive = isUserActive(delay, lastInputTime());
      if(!userActive) {
        const unsigned argc = 1;
        Local<Value> argv[argc] = { String::NewFromUtf8(isolate, "user gone") };
        callback->Call(Null(isolate), argc, argv);
      }
    } while(userActive);

    spyUnactiveUser(args);
  }

  /**
   * @param { int } args[0] время простоя
   * @param { function } args[1] js callback
   */
  void method(const FunctionCallbackInfo<Value>& args) {
    if (checkArguments(args)) {
      spyActiveUser(args);
    } else {
      Isolate* isolate = args.GetIsolate();
      isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Wrong arguments")));
    }
  }

  void init(Local<Object> exports) {
    NODE_SET_METHOD(exports, "userActivitySpy",  method);
  }

  NODE_MODULE(checker, init)
}
