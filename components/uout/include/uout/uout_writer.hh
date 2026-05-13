/**
 * \file   uout/uout_writer.hh
 * \brief  A virtual class hierarchy to create types which build data and do
 * chunked output to keep the build-buffer from overflowing.
 *
 * the build data will be formatted either as JSON or as plain text. The
 * user has to pass the format he wants to the contructor when creating the
 * object. the output stream is determined by the subclass.
 *
 */

#pragma once
#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

#include <utility>

#include "uout_writer_builder.hh"
#include "uout_writer_console.hh"
#include "uout_writer_file.hh"
#include "uout_writer_function.hh"