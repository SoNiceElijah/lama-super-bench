
#include "../include/b63/b63.h"
#include "../include/b63/counters/perf_events.h"
#include <stdio.h>

extern int Ltest00358();
extern int Ltest00358_optimized();
extern void __gc_init(void);

int lcall(int (*func)()) {
    int (*ptr)() = func;
    __asm__("pushl %ebx\n\tpushl %esi\n\tpushl %edi\n");
    int x = (*ptr)();
    __asm__("popl %edi\n\tpopl %esi\n\tpopl %ebx\n");
    return x >> 1;
}

B63_BASELINE(lamac_test00358, n) {
  int i = 0, res;
  for (i = 0; i < n; i++) {
    res += lcall(&Ltest00358);
  }
  B63_KEEP(res);
}

B63_BENCHMARK(optimizer_test00358, n) {
  int i = 0, res;
  for (i = 0; i < n; i++) {
    res += lcall(&Ltest00358_optimized);
  }
  B63_KEEP(res);
}

int main(int argc, char **argv) {
  __gc_init();
  B63_RUN_WITH("time,lpe:cycles,lpe:instructions", argc, argv);
  return 0;
}