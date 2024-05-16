#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>


#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

int printf(const char *fmt, ...) {
  va_list ap; // args pointer
  va_start(ap, fmt);
  while (*fmt) {
    if (*fmt == '%') {
      fmt += 1;
      switch (*fmt)
      {
      case 's': /* string */
        char *s = va_arg(ap, char *);
        putstr(s);
        break;
      case 'd': /* int */
        int d = va_arg(ap, int);
        putch('0' + d); // only print 0~9
        break;
      case 'c': /* char */
        /* need a cast here since va_arg only
           takes fully promoted types */
        char c = (char)va_arg(ap, int);
        putch(c);
        break;
      }
    } else {
      putch(*fmt);
    }
    fmt += 1;
  }

  va_end(ap);
  return 0;
}

int vsprintf(char *out, const char *fmt, va_list ap) {
  panic("Not implemented");
}

int sprintf(char *out, const char *fmt, ...) {
  panic("Not implemented");
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  panic("Not implemented");
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  panic("Not implemented");
}

#endif
