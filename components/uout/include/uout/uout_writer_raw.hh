#pragma once

#include <unistd.h>
#include <utils_misc/itoa.h>

#include <utility>

/**
 * \brief   Abstract class which implements public write methods and operators
 * which then call an abstract private write method.
 *
 */
class UoutRawWriter {
 protected:
  virtual ~UoutRawWriter() = default;

 public:
  /**
   * \brief        write output
   * \param s      output string
   * \param len    length of output string, or -1 for a null terminated string
   * \param last   On subsequent writes, mark the last write as final (required
   * for e.g. web-socket target)
   * \return       Number of bytes written.  On error returns -1.
   */
  int write(const char* s, ssize_t len = -1, bool last = false);

  /**
   * \brief        write output line
   * \param s      output string (a line-feed will be appended)
   * \param len    length of output string, or -1 for a null terminated string
   * \param last  On subsequent writes, mark the last write as final (required
   * for e.g. web-socket target)
   * \return       Number of bytes written.  On error returns -1.
   */

  int writeln(const char* s, ssize_t len = -1, bool last = false);

  /**
   * \brief   write a single character (non final)
   */
  int write(const char c);

 public:
  /// \brief  write to output (non-final)
  friend UoutRawWriter& operator<<(UoutRawWriter& lhs, const char* s) {
    lhs.write(s);
    return lhs;
  }
  /// \brief  write to output (non-final)
  friend UoutRawWriter& operator<<(UoutRawWriter& lhs, char c) {
    lhs.write(c);
    return lhs;
  }
  /// \brief  write to output (non-final)
  friend UoutRawWriter& operator<<(UoutRawWriter& lhs, int n) {
    char buf[20];
    itoa(n, buf, 10);
    lhs.write(buf);
    return lhs;
  }
  /// \brief  modifier for << operator (final, line-feed)  XXX: currently
  /// unused/untested
  struct mod {
    bool fin : 1 = false;
    bool lf : 1 = false;
  };
  /// \brief  write to output with modifiers XXX: currently unused/untested
  friend UoutRawWriter& operator<<(
      UoutRawWriter& lhs,
      const std::pair<UoutRawWriter::mod, const char*>& mod_s) {
    if (mod_s.first.lf)
      lhs.writeln(mod_s.second, -1, mod_s.first.fin);
    else
      lhs.write(mod_s.second, -1, mod_s.first.fin);
    return lhs;
  }

 private:
  /**
   * \brief        do-nothing-stub for a write function to be overridden
   * \param s,len  string and string length to write
   * \param last  On subsequent writes, mark the last write as final (required
   * for e.g. web-socket target)
   * \return   -1
   */

  virtual int priv_write(const char* s, ssize_t len, bool last) = 0;
};
