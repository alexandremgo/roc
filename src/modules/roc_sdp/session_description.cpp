/*
 * Copyright (c) 2019 Roc authors
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "roc_sdp/session_description.h"
#include "roc_sdp/enums.h"

namespace roc {
namespace sdp {

SessionDescription::SessionDescription(core::IAllocator& allocator)
    : guid_(allocator) {
    clear();
}

void SessionDescription::clear() {
    guid_.resize(0);
}

const char* SessionDescription::guid() const {
    return &guid_[0];
}

bool SessionDescription::set_guid(const char* start_p_origin_username,
                                  const char* end_p_origin_sess_id,
                                  const char* start_p_origin_nettype,
                                  const char* end_p_origin_addr) {

    const size_t len_part_1 = end_p_origin_sess_id - start_p_origin_username + 1;
    const size_t len_part_2 = end_p_origin_addr - start_p_origin_nettype + 1;
    // + 1 because of the space between the 2 parts
    // + 1 for guid's null-terminator
    const int guid_len = len_part_1 + len_part_2 + 2;

    guid_.resize(guid_len);

    if(!core::append_str(&guid_[0], len_part_1, start_p_origin_username, end_p_origin_sess_id)) {
        roc_panic("1st part of origin guid could not be appended");
        return false;
    }

    guid_[len_part_1 - 1] = ' ';

    if(!core::append_str(&guid_[len_part_1], len_part_2, start_p_origin_nettype, end_p_origin_addr)) {
        roc_panic("2nd part of origin guid could not be appended");
        return false;
    }

    roc_log(LogInfo, "parsed guid: %s of len %d", &guid_[0], guid_len);

    return true;
}

bool SessionDescription::set_origin_addrtype(AddrType addrtype) {
    origin_addrtype_ = addrtype;
    return true;
}

bool SessionDescription::set_origin_unicast_address(const char* str, size_t str_len) {
    char addr_buffer[address::SocketAddr::MaxStrLen];
    if (!core::copy_str(addr_buffer, 45, str, str + str_len)) {
        roc_panic("Origin unicast address could not be copy in buffer");
        return false;
    }

    roc_log(LogInfo, "Unicast address: %s", &addr_buffer[0]);
    switch (origin_addrtype_) {
    case IP4:
        if (!origin_unicast_address_.set_host_port_ipv4(addr_buffer, 0)) {
            roc_log(LogError, "Origin unicast address: invalid IPv4 address");
            return false;
        }
        return true;
    case IP6:
        if (!origin_unicast_address_.set_host_port_ipv6(addr_buffer, 0)) {
            roc_log(LogError, "Origin unicast address: invalid IPv6 address");
            return false;
        }
        return true;
    }
    return false;
}

} // namespace roc
} // namespace sdp
