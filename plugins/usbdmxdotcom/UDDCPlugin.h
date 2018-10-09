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
 * UDDCPlugin.h
 */

#ifndef PLUGINS_UDDC_UDDCPLUGIN_H_
#define PLUGINS_UDDC_UDDCPLUGIN_H_

#include <string>
#include <vector>

//#include "olad/Plugin.h"
//#include "ola/plugin_id.h"
#include "ola/io/Descriptor.h"
#include "olad/Plugin.h"

namespace ola {
namespace plugin {
namespace usbdmxdotcom {

class UDDCDevice;

class UDDCPlugin: public Plugin {
 public:
    explicit UDDCPlugin(PluginAdaptor *plugin_adaptor)
      : Plugin(plugin_adaptor) {}
    ~UDDCPlugin() {}

    std::string Name() const { return PLUGIN_NAME; }
    ola_plugin_id Id() const { return OLA_PLUGIN_EXPERIMENTAL; }
    std::string Description() const;
    int SocketClosed(ola::io::ConnectedDescriptor *socket);
    std::string PluginPrefix() const { return PLUGIN_PREFIX; }

 private:
    bool StartHook();
    bool StopHook();
    bool SetDefaultPreferences();
    void DeleteDevice(UDDCDevice *device);

    std::vector<UDDCDevice*> m_devices;  // list of our devices

    static const char USBDMX_DEVICE_PATH[];
    static const char USBDMX_BASE_DEVICE_NAME[];
    static const char USBDMX_SS_DEVICE_NAME[];
    static const char PLUGIN_NAME[];
    static const char DEVICE_KEY[];
    static const char PLUGIN_PREFIX[];
};
}  // namespace uddc
}  // namespace plugin
}  // namespace ola
#endif  // PLUGINS_UDDC_UDDCPLUGIN_H_
