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
#include <fcntl.h>

#include "ola/Logging.h"
#include "ola/io/IOUtils.h"
#include "ola/io/SelectServerInterface.h"
#include "plugins/usbdmxdotcom/UDDCPort.h"
#include "plugins/usbdmxdotcom/UDDCDevice.h"

namespace ola {
namespace plugin {
namespace usbdmxdotcom {

using std::string;
using std::vector;

const char UDDCDevice::DEVICE_NAME[] = "usbdmx.com device";

/**
 * Constructor for the UDDCDevice
 * @param owner the plugin which created this device
 * @param plugin_adaptor a pointer to a PluginAdaptor object

 * @param addresses a list of strings to use as UDDC addresses for the input
 *   ports.
 * @param port_configs config to use for the ports
 */
UDDCDevice::UDDCDevice(AbstractPlugin *owner,
                       class Preferences *preferences,
		       PluginAdaptor *plugin_adaptor,
                       const string &dev_path)
    : Device(owner, DEVICE_NAME),
      m_plugin_adaptor(plugin_adaptor),
      m_preferences(preferences),
      m_dev_path(dev_path) {

  OLA_INFO << "Create device " << m_dev_path;
}

UDDCDevice::~UDDCDevice() {
  if (m_socket) {
    m_socket->Close();
    delete m_socket;
  }
}

/*
 * Start this device.
 * @returns true if the device started successfully, false otherwise.
 */
bool UDDCDevice::StartHook() {
  UDDCInputPort *input_port = new UDDCInputPort(this, 0, m_plugin_adaptor);
  AddPort(input_port);

  UDDCOutputPort *output_port = new UDDCOutputPort(this, 0);
  AddPort(output_port);

  OLA_WARN << "TODO: the 'open()' will be there..";

  return true;
}

bool UDDCDevice::Connect() {
  OLA_DEBUG << "Connecting to " << m_dev_path;
  int fd;
  if (!ola::io::Open(m_dev_path, O_RDWR | O_NONBLOCK | O_NOCTTY, &fd)) {
    return false;
  }
  
  m_socket = new ola::io::DeviceDescriptor(fd);
  
  OLA_DEBUG << "Connected to " << m_dev_path;
  return true;
}

void UDDCDevice::Disconnect() {
  m_socket->Close();
}

}  // namespace uddc
}  // namespace plugin
}  // namespace ola
