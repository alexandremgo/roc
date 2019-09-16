/*
 * Copyright (c) 2015 Roc authors
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

//! @file roc_pipeline/target_stdio/roc_pipeline/parse_address.h
//! @brief Parse port from string.

#ifndef ROC_PIPELINE_PARSE_ADDRESS_H_
#define ROC_PIPELINE_PARSE_ADDRESS_H_

#include "roc_packet/address.h"

namespace roc {
namespace pipeline {

//! Set multicast interface adress on which to join the multicast group.
//!
//! @remarks
//!  The input string should be in one of the following forms:
//!   - "IPv4"    e.g. "1.2.3.4"
//!   - "[IPv6]"  e.g. "[::1]"
//!
//! @returns
//!  false if @p input can't be parsed;
//!  false if @p addr is not multicast.
//!  false if @p miface represents IP address with a version other than
//!  IP version of @p addr.
bool set_miface_from_string(const char* input, packet::Address& addr);

} // namespace pipeline
} // namespace roc

#endif // ROC_PIPELINE_PARSE_ADDRESS_H_
