#include <ZPC.h>
int main() {
  ZPC_MainInit();
  do {ZPC_MainLoop();} while (0x1);
  return 0x0;
}
