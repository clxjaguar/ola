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

//#define __STDC_LIMIT_MACROS  // for UINT8_MAX & friends
//#include <stdint.h>
//#include <stdlib.h>
//#include <stdio.h>
//#include <memory>
//#include <set>
#include <string>
#include <vector>

#include "ola/StringUtils.h"
#include "olad/PluginAdaptor.h"
#include "olad/Preferences.h"
#include "plugins/usbdmxdotcom/UDDCDevice.h"
#include "plugins/usbdmxdotcom/UDDCPlugin.h"
#include "plugins/usbdmxdotcom/UDDCPluginDescription.h"

namespace ola {
namespace plugin {
namespace usbdmxdotcom {

using ola::network::IPV4SocketAddress;
using std::set;
using std::string;
using std::vector;

const char UDDCPlugin::PLUGIN_NAME[] = "USBDMX.com";
const char UDDCPlugin::PLUGIN_PREFIX[] = "usbdmxdotcom";
const char UDDCPlugin::DEVICE_KEY[] = "device";
const char UDDCPlugin::USBDMX_DEVICE_PATH[] = "";

/*
 * Start the plugin.
 */
bool UDDCPlugin::StartHook() {
    UDDCDevice *device;

    device = new UDDCDevice(this, m_preferences, m_plugin_adaptor);

    if (!device->Start()) {
      delete device;
      return false;
    }

    m_plugin_adaptor->RegisterDevice(device);

    return true;
}


/*
 * Stop the plugin
 * @return true on success, false on failure
 */
bool UDDCPlugin::StopHook() {
  //UDDCDevice *device;
  //m_devices.clear();
  return true;
}

/*
 * Return the description for this plugin
 */
string UDDCPlugin::Description() const {
    return plugin_description;
}

/*
 * load the plugin prefs and default to sensible values
 *
 */
bool UDDCPlugin::SetDefaultPreferences() {
  if (!m_preferences) {
    return false;
  }

  bool save = false;

  save |= m_preferences->SetDefaultValue(DEVICE_KEY, StringValidator(),
                                         USBDMX_DEVICE_PATH);

  if (save) {
    m_preferences->Save();
  }

  // Just check key exists, as we've set it to ""
  if (!m_preferences->HasKey(DEVICE_KEY)) {
    return false;
  }
  return true;
}

}  // namespace uddc
}  // namespace plugin
}  // namespace ola
