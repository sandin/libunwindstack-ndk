// https://cs.android.com/android/platform/superproject/main/+/main:bionic/libc/platform/bionic/pac.h;drc=2c73f5abdf31943e12c68e75f8148c10d2abbf6a;l=33
#ifndef UNWINDINGDEMO_APP_SRC_MAIN_CPP_LIBUNWINDSTACK_NDK_PAC_H_
#define UNWINDINGDEMO_APP_SRC_MAIN_CPP_LIBUNWINDSTACK_NDK_PAC_H_

#include <stddef.h>

inline uintptr_t __unwinding_bionic_clear_pac_bits(uintptr_t ptr) {
#if defined(__aarch64__)
  register uintptr_t x30 __asm("x30") = ptr;
  // This is a NOP on pre-Armv8.3-A architectures.
  asm("xpaclri" : "+r"(x30));
  return x30;
#else
  return ptr;
#endif
}

#endif //UNWINDINGDEMO_APP_SRC_MAIN_CPP_LIBUNWINDSTACK_NDK_PAC_H_
