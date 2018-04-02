/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Library General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * UDDCPlugin.cpp
 */

#define __STDC_LIMIT_MACROS  // for UINT8_MAX & friends
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <memory>
#include <set>
#include <string>
#include <vector>

#include "ola/StringUtils.h"
#include "olad/PluginAdaptor.h"
#include "olad/Preferences.h"
#include "plugins/usbdmxdotcom/UDDCDevice.h"
#include "plugins/usbdmxdotcom/UDDCPlugin.h"

namespace ola {
namespace plugin {
namespace uddc {

using ola::network::IPV4SocketAddress;
using std::set;
using std::string;
using std::vector;

const char UDDCPlugin::DEFAULT_ADDRESS_TEMPLATE[] = "/dmx/universe/%d";
const char UDDCPlugin::DEFAULT_TARGETS_TEMPLATE[] = "";
const char UDDCPlugin::INPUT_PORT_COUNT_KEY[] = "input_ports";
const char UDDCPlugin::OUTPUT_PORT_COUNT_KEY[] = "output_ports";
const char UDDCPlugin::PLUGIN_NAME[] = "UDDC";
const char UDDCPlugin::PLUGIN_PREFIX[] = "uddc";
const char UDDCPlugin::PORT_ADDRESS_TEMPLATE[] = "port_%d_address";
const char UDDCPlugin::PORT_TARGETS_TEMPLATE[] = "port_%d_targets";
const char UDDCPlugin::PORT_FORMAT_TEMPLATE[] = "port_%d_output_format";
const char UDDCPlugin::UDP_PORT_KEY[] = "udp_listen_port";

const char UDDCPlugin::BLOB_FORMAT[] = "blob";
const char UDDCPlugin::FLOAT_ARRAY_FORMAT[] = "float_array";
const char UDDCPlugin::FLOAT_INDIVIDUAL_FORMAT[] = "individual_float";
const char UDDCPlugin::INT_ARRAY_FORMAT[] = "int_array";
const char UDDCPlugin::INT_INDIVIDUAL_FORMAT[] = "individual_int";

/*
 * Start the plugin.
 */
bool UDDCPlugin::StartHook() {
  return true;
}


/*
 * Stop the plugin
 * @return true on success, false on failure
 */
bool UDDCPlugin::StopHook() {
  return true;
}


string UDDCPlugin::Description() const {
  return "";
}


/**
 * Set the default preferences for the UDDC plugin.
 */
bool UDDCPlugin::SetDefaultPreferences() {
  return true;
}

}  // namespace uddc
}  // namespace plugin
}  // namespace ola
