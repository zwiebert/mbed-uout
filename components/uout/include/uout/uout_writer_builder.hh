#pragma once

#include "uout_writer_base.hh"

/**
 * \brief  Build data without an actual data sink for passing to external builder functions expecting a UoutWriter reference.
 *
 *         We implement the priv_write() method with a dummy. This should cause the internal builders to use (growing) internal buffers for building.
 *
 *
 */
class UoutWriterBuilder final: public UoutWriter {
public:
  UoutWriterBuilder(so_target_bits tgt = SO_TGT_NONE) :
      UoutWriter(tgt) {
  }
private:
  /*
   * \brief does nothing. This should cause the builder to grow its buffer
   * \return  returns bytes written, which is always zero.
   */
  virtual int priv_write(const char *, ssize_t, bool) override {
    return 0;
  }
};