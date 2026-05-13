#pragma once

#include "uout_writer_base.hh"

/**
 * \brief Build data and write output to a file in chunks while building
 */
class UoutWriterFile final : public UoutWriter {
  typedef int (*writeReq_fnT)(void* req, const char* s, ssize_t len, bool last);

 public:
  /**
   * \param file_name       Named file to write to
   * \param fmt             Specify the data format (e.g. JSON)
   */
  UoutWriterFile(const char* file_name, so_target_bits fmt = SO_TGT_FLAG_JSON);
  UoutWriterFile(const UoutWriterFile&) = delete;
  virtual ~UoutWriterFile();

 public:
 private:
  virtual int priv_write(const char* s, ssize_t len, bool last) override;

 private:
  int myFd = STDOUT_FILENO;
  int m_ofd = -1;
};