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
 * UDDCPort.h
 * The E1.31 port for OLA
 * Copyright (C) 2007 Simon Newton
 */

#ifndef PLUGINS_UDDC_UDDCPORT_H_
#define PLUGINS_UDDC_UDDCPORT_H_

#include <string>
#include "olad/Port.h"
#include "plugins/usbdmxdotcom/UDDCDevice.h"

namespace ola {
namespace plugin {
namespace usbdmxdotcom {

class UDDCInputPort: public BasicInputPort {
 public:
  UDDCInputPort(UDDCDevice *parent, int id,
                class PluginAdaptor *plugin_adaptor)
      : BasicInputPort(parent, id, plugin_adaptor) {
  }

  const ola::DmxBuffer &ReadDMX() const { return m_buffer; }

  std::string Description() const;

 private:
  ola::DmxBuffer m_buffer;
};


class UDDCOutputPort: public BasicOutputPort {
 public:
  UDDCOutputPort(UDDCDevice *parent, int id)
      : BasicOutputPort(parent, id) {
  }

  std::string Description() const;
  bool WriteDMX(const ola::DmxBuffer &buffer, uint8_t priority);

 private:
  ola::DmxBuffer m_buffer;
};
}  // namespace usbdmxdotcom
}  // namespace plugin
}  // namespace ola
#endif  // PLUGINS_UDDC_UDDCPORT_H_
