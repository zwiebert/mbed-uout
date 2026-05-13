#pragma once

#include "uout_writer_raw.hh"
#include "so_target_bits.h"
#include "so_out.h"
#include "uout_builder_json.hh"
#include "uout_builder_plaintext.hh"
#include <assert.h>

/**
 * \brief  Abstract class which contains various data builders
 *
 *        The builders are passed a *this reference, so they can call our write methods to output the build data.
 *        Subclasses will implement the abstract priv_write() method, so the data has a sink to go.
 *
 */
class UoutWriter: public UoutRawWriter {
public:
  /**
   * \param tgt    Flags describing the requested format(s) and/or target
   *               only one of the formats ist possible at the same time
   */
  UoutWriter(so_target_bits tgt = SO_TGT_NONE) :
      myTgt(tgt) {
    assert(!((tgt & SO_TGT_FLAG_TXT) && (tgt & SO_TGT_FLAG_JSON)));
  }

  UoutWriter(const UoutWriter&) = delete;
  UoutWriter& operator=(const UoutWriter&) = delete;

public:

  /// \brief Get target bit flags
  so_target_bits tgt() const {
    return myTgt;
  }
  /// \brief Add a target bit flag
  void add_tgt_flag(so_target_bits flag) {
    myTgt = static_cast<so_target_bits>(myTgt | flag);
    assert(!((myTgt & SO_TGT_FLAG_TXT) && (myTgt & SO_TGT_FLAG_JSON)));
  }

  /// \brief  Get the related UoutBuilderJson object
  UoutBuilderJson& sj() const {
    return mySj;
  }
  /// \brief  Get the related UoutBuilderPlaintext object
  UoutBuilderPlaintext& st() const {
    return myStxt;
  }
  /// \brief  Get the related UoutPrinter object
  const class UoutPrinter& so() const {
    return mySo;
  }

protected:
  so_target_bits myTgt = SO_TGT_NONE; ///< target to write to and format to output
  ///////////////////////////////
  mutable UoutBuilderJson mySj = { this };  ///< builder for JSON format
  mutable UoutBuilderPlaintext myStxt = { *this }; ///< builder for plain text format
  const UoutPrinter mySo = { *this }; ///< builder which selects format by content of \ref myTgt
};
