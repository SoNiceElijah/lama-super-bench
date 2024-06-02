
#include "../include/b63/b63.h"
#include "../include/b63/counters/perf_events.h"
#include <stdio.h>

extern int Ltest08254();
extern int Ltest08254_optimized();
extern void __gc_init(void);

int lcall(int (*func)()) {
    int (*ptr)() = func;
    __asm__("pushl %ebx\n\tpushl %esi\n\tpushl %edi\n");
    int x = (*ptr)();
    __asm__("popl %edi\n\tpopl %esi\n\tpopl %ebx\n");
    return x >> 1;
}

B63_BASELINE(lamac_test08254, n) {
  int i = 0, res;
  for (i = 0; i < n; i++) {
    res += lcall(&Ltest08254);
  }
  B63_KEEP(res);
}

B63_BENCHMARK(optimizer_test08254, n) {
  int i = 0, res;
  for (i = 0; i < n; i++) {
    res += lcall(&Ltest08254_optimized);
  }
  B63_KEEP(res);
}

int main(int argc, char **argv) {
  __gc_init();
  B63_RUN_WITH("time,lpe:cycles,lpe:instructions", argc, argv);
  return 0;
}
