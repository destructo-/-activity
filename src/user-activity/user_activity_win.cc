#define _WINSOCKAPI_

#include <nan.h>
#include <windows.h>
#include <node.h>

int LastInputTime(void) {
  LASTINPUTINFO li;
  li.cbSize = sizeof(LASTINPUTINFO);
  ::GetLastInputInfo(&li);
  return ::GetTickCount() - li.dwTime;
}
