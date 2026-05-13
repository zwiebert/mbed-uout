#include <string.h>

#include <uout_writer_raw.hh>


int UoutRawWriter::write(const char *s, ssize_t len, bool last)  {
  if (len < 0) {
    len = strlen(s);
  }

  return priv_write(s, len, last);
}


int UoutRawWriter::writeln(const char *s, ssize_t len, bool last)  {
  if (len < 0) {
    len = strlen(s);
  }

  if (ssize_t n = priv_write(s, len, false); n == len)
    if (write("\n", 1, last) == 1)
      return n + 1;
  return -1;
}

int UoutRawWriter::write(const char c) {
  return write(&c, 1);
}