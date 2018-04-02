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
 * UDDCDevice.cpp
 */

#include <string>
#include <vector>

#include "ola/Logging.h"
#include "ola/io/SelectServerInterface.h"
#include "plugins/usbdmxdotcom/UDDCDevice.h"

namespace ola {
namespace plugin {
namespace uddc {

using std::string;
using std::vector;

const char UDDCDevice::DEVICE_NAME[] = "UDDC Device";

/**
 * Constructor for the UDDCDevice
 * @param owner the plugin which created this device
 * @param plugin_adaptor a pointer to a PluginAdaptor object
 * @param udp_port the UDP port to listen on
 * @param addresses a list of strings to use as UDDC addresses for the input
 *   ports.
 * @param port_configs config to use for the ports
 */
UDDCDevice::UDDCDevice(AbstractPlugin *owner,
                     PluginAdaptor *plugin_adaptor,
                     uint16_t udp_port,
                     const vector<string> &addresses,
                     const PortConfigs &port_configs)
    : Device(owner, DEVICE_NAME),
      m_plugin_adaptor(plugin_adaptor),
      m_port_addresses(addresses),
      m_port_configs(port_configs) {
	
  if (udp_port == 0) return;
}

/*
 * Start this device.
 * @returns true if the device started successfully, false otherwise.
 */
bool UDDCDevice::StartHook() {
  bool ok = true;
  return ok;
}
}  // namespace uddc
}  // namespace plugin
}  // namespace ola
