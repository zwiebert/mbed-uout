#pragma once

#include "uout_writer_base.hh"

/**
 * \brief build data and write to local or remote console (file or socket
 * descriptor)
 */
class UoutWriterConsole final : public UoutWriter {

 public:
  /**
   * \brief      construct for local console (fd = STDOUT_FILENO)
   * \param tgt   target to write to (XXX:?) and data format
   */
  UoutWriterConsole(so_target_bits tgt = SO_TGT_NONE) : UoutWriter(tgt) {}
  /**
   * \brief construct for remote console
   * \param fd     file/socket descriptor
   * \param tgt   target to write to (XXX:?) and data format
   */
  UoutWriterConsole(int fd, so_target_bits tgt = SO_TGT_NONE)
      : UoutWriter(tgt), myFd(fd) {}
  UoutWriterConsole(const UoutWriterConsole&) = delete;

 public:
 private:
  virtual int priv_write(const char* s, ssize_t len, bool last) override;

 private:
  int myFd = STDOUT_FILENO;
};
