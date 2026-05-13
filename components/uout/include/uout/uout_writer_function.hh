#pragma once

#include "uout_writer_base.hh"
#include <functional>

/**
 * \brief  Build data and, while building, write them in chunks using a user provided callback function object (for http req, web-socket, ...)
 *
 *        The function object may be created using std::bind or closures to provide data like file handles/descriptors, http requests, ...
 */
class UoutWriterFunction final: public UoutWriter {
public:
  /**
   * \brief  callback function object
   *  \param      src             Data to be written
   *  \param      src_len         Data length or -1 for zero terminated strings
   *  \param      chunk_status    Chunk number of data, to control output (e.g. 4 chunk sequence: -1,-2,-3,+4)
   *                                 - 0 for a single (first and final) "chunk"
   *                                 - -1 is the first chunk
   *                                 - -2 ... -n   are in-between chunks
   *                                 - +n          is the final chunk
   *  \return    number of bytes written.  If zero, the builder will just grow its buffer and may call again later.
   */
  using write_callback_type = std::function<int(const char *src,
      ssize_t src_len, int chunk_status)>;
public:

  /**
   * \param write_callback  Callback function object for writing out our data
   * \param fmt             specify which data formats should be build by mySo()
   */
  UoutWriterFunction(write_callback_type write_callback, so_target_bits fmt = SO_TGT_FLAG_JSON) :
      UoutWriter(fmt), m_write_callback(write_callback) {
  }

  UoutWriterFunction(const UoutWriterFunction&) = delete;
  virtual ~UoutWriterFunction() {
    mySj.write_json(true); // write all remaining json
  }

private:
  virtual int priv_write(const char *src, ssize_t src_len, bool is_final) override {
    bool no_fragments = is_final && !nmb_chunks_written;

    int chunk_status = no_fragments ? 0 : (is_final ? (nmb_chunks_written + 1) : (nmb_chunks_written + 1) * -1);

    int n = m_write_callback(src, src_len, chunk_status);

    if (n > 0)
      ++nmb_chunks_written;

    if (is_final)
      nmb_chunks_written = 0;

    return n;
  }

private:
  write_callback_type m_write_callback;
  int nmb_chunks_written = 0;
};
