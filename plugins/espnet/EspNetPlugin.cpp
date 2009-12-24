/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 *
 * EspNetPlugin.cpp
 * The EspNet plugin for ola
 * Copyright (C) 2005-2009 Simon Newton
 */

#include <string>
#include "olad/Preferences.h"
#include "plugins/espnet/EspNetPlugin.h"
#include "plugins/espnet/EspNetDevice.h"

/*
 * Entry point to this plugin
 */
extern "C" ola::AbstractPlugin* create(
    const ola::PluginAdaptor *plugin_adaptor) {
  return new ola::plugin::espnet::EspNetPlugin(plugin_adaptor);
}

namespace ola {
namespace plugin {
namespace espnet {

const char EspNetPlugin::ESPNET_NODE_NAME[] = "ola-EspNet";
const char EspNetPlugin::ESPNET_DEVICE_NAME[] = "EspNet Device";
const char EspNetPlugin::PLUGIN_NAME[] = "EspNet Plugin";
const char EspNetPlugin::PLUGIN_PREFIX[] = "espnet";


/*
 * Start the plugin
 * For now we just have one device.
 */
bool EspNetPlugin::StartHook() {
  m_device = new EspNetDevice(this,
                              ESPNET_DEVICE_NAME,
                              m_preferences,
                              m_plugin_adaptor);

  if (!m_device)
    return false;

  if (!m_device->Start()) {
    delete m_device;
    return false;
  }
  m_plugin_adaptor->RegisterDevice(m_device);
  return true;
}


/*
 * Stop the plugin
 *
 * @return 0 on sucess, -1 on failure
 */
bool EspNetPlugin::StopHook() {
  m_plugin_adaptor->UnregisterDevice(m_device);
  m_device->Stop();
  delete m_device;
  return true;
}


/*
 * Return the description for this plugin
 */
string EspNetPlugin::Description() const {
  return
"EspNet Plugin\n"
"----------------------------\n"
"\n"
"This plugin creates a single device with five input and five output ports.\n"
"\n"
"Esp supports up to 255 universes. As ESP has no notion of ports, we provide "
"a fixed number of ports which can be patched to any universe. When sending "
"data from a port, the data is addressed to the universe the port is patched "
"to. For example if port 0 is patched to universe 10, the data will be sent to "
"ESP universe 10.\n"
"\n"
"--- Config file : ola-espnet.conf ---\n"
"\n"
"ip = a.b.c.d\n"
"The ip address to bind to. If not specified it will use the first "
"non-loopback ip.\n"
"\n"
"name = ola-EspNet\n"
"The name of the node.\n";
}

/*
 * Set the default preferences.
 */
bool EspNetPlugin::SetDefaultPreferences() {
  if (!m_preferences)
    return false;

  if (m_preferences->SetDefaultValue("name", ESPNET_NODE_NAME))
    m_preferences->Save();

  if (m_preferences->GetValue("name").empty())
    return false;

  return true;
}
}  // espnet
}  // plugin
}  // ola
