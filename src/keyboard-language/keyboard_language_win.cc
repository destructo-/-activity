#define _WINSOCKAPI_

#include "keyboard_language.h"
#include <nan.h>
#include <windows.h>
#include <node.h>
#include <iostream>

using namespace v8;
using namespace Nan;
using namespace std;

void currentKeyboardLanguage(void) {
  GUITHREADINFO Gti;
  ::ZeroMemory ( &Gti,sizeof(GUITHREADINFO));
  Gti.cbSize = sizeof(GUITHREADINFO);
  ::GetGUIThreadInfo(0, &Gti);
  DWORD dwThread = ::GetWindowThreadProcessId(Gti.hwndActive, 0);
  //CString strName;
  //cout << strName.Format(_T("&#37;08X"), ::GetKeyboardLayout(dwThread));
  cout << "!!!!!!!!!!!!!!";
  cout << ::GetKeyboardLayout(dwThread);

}
