#include <uout/so_target_desc.hh>
#include <stdio.h>

int UoutRawWriter::write(const char *s, ssize_t len, bool final) const {
  if (len < 0) {
    len = strlen(s);
  }

  return priv_write(s, len, final);
}

int UoutRawWriter::writeln(const char *s, ssize_t len, bool final) const {
  if (len < 0) {
    len = strlen(s);
  }

  if (ssize_t n = priv_write(s, len, false); n == len)
    if (write("\n", 1, final) == 1)
      return n + 1;
  return -1;
}

int UoutRawWriter::write(const char c) const {
  return write(&c, 1);
}

int UoutWriterConsole::priv_write(const char *s, ssize_t len, bool final) const {
  const size_t size = len;
  assert(size < 2046);

  const char crlf[] = "\r\n";
  const unsigned crlf_len = sizeof crlf - 1;
  char prev_c = 0;
  int last_chunk = 0;

  for (size_t i = 0; i < size; ++i) {
    const char c = s[i];
    if (c == '\r' || (c == '\n' && prev_c == '\r'))
      continue;

    if (c == '\n') {
      const int chunk_len = i - last_chunk;
      if (chunk_len > 0 && ::write(myFd, s + last_chunk, chunk_len) < 1)
        return -1;
      last_chunk = i + 1;
      if (::write(myFd, crlf, crlf_len) < 1)
        return -1;
    } else if (i + 1 == size) {
      const int chunk_len = i - last_chunk + 1;
      if (chunk_len > 0 && ::write(myFd, s + last_chunk, chunk_len) < 1)
        return -1;
      break;
    }
    prev_c = c;
  }

  return len;
}

int UoutWriterWebsocket::priv_write(const char *s, ssize_t len, bool final) const {
  if (myReq && myWriteReqFn) {
    return myWriteReqFn(myReq, s, len, final);
  }
  return -1;
}

