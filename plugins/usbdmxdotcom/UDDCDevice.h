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
 * UDDCDevice.h
 */

#ifndef PLUGINS_UDDC_UDDCDEVICE_H_
#define PLUGINS_UDDC_UDDCDEVICE_H_

#include <memory>
#include <string>
#include <vector>
#include "ola/io/SelectServerInterface.h"
#include "ola/network/SocketAddress.h"
#include "olad/Device.h"

namespace ola {

class AbstractPlugin;

namespace plugin {
namespace usbdmxdotcom {

class UDDCDevice: public ola::Device {
 public:
    UDDCDevice(AbstractPlugin *owner,
               class Preferences *preferences,
	       PluginAdaptor *plugin_adaptor,
               const std::string &dev_path);

//    ~UDDCDevice();
    std::string DeviceId() const { return m_dev_path; }
//    ola::io::ConnectedDescriptor *GetSocket() const;
/*
    bool AllowLooping() const { return true; }
    bool AllowMultiPortPatching() const { return true; }
*/
 protected:
    PluginAdaptor *m_plugin_adaptor;
    const std::vector<std::string> m_port_addresses;
    std::auto_ptr<class UDDCNode> m_uddc_node;

    bool StartHook();

    static const char DEVICE_NAME[];

  private:
	class Preferences *m_preferences;
	std::string const m_dev_path;
};
}  // namespace uddc
}  // namespace plugin
}  // namespace ola
#endif  // PLUGINS_UDDC_UDDCDEVICE_H_
