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
 * UDDCPort.cpp
 * The E1.31 plugin for ola
 * Copyright (C) 2007 Simon Newton
 */

#include <string>
#include "ola/Logging.h"
#include "olad/Universe.h"
#include "plugins/usbdmxdotcom/UDDCPort.h"
#include "plugins/usbdmxdotcom/UDDCDevice.h"

namespace ola {
namespace plugin {
namespace usbdmxdotcom {

using std::string;

std::string UDDCInputPort::Description() const {
	return "USB-DMX input";
}

std::string UDDCOutputPort::Description() const {
	return (std::string)"USB-DMX "+(std::string)"output";
}

/*
 * Write data to this port.
 */
bool UDDCOutputPort::WriteDMX(const DmxBuffer &buffer, OLA_UNUSED uint8_t priority) {
  if (false) {
    string aa;
    aa = buffer.Get();
  }

  return true;
}

}  // namespace usbdmxdotcom
}  // namespace plugin
}  // namespace ola
