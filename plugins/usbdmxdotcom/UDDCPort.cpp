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

bool UDDCPortHelper::PreSetUniverse(Universe *old_universe,
                                    Universe *new_universe) {
  if (new_universe && (new_universe->UniverseId() == 0 ||
                       new_universe->UniverseId() > MAX_UDDC_UNIVERSE)) {
    OLA_WARN << "Universe id " << new_universe->UniverseId() << " is 0 or > "
      << MAX_UDDC_UNIVERSE;
    return false;
  }
  (void) old_universe;
  return true;
}


string UDDCPortHelper::Description(Universe *universe) const {
  std::ostringstream str;
  if (universe)
    str << "UDDC Universe " << universe->UniverseId();
  return str.str();
}



/*
 * Set the universe for an input port.
 */
void UDDCInputPort::PostSetUniverse(Universe *old_universe,
                                    Universe *new_universe) {
  if (old_universe)
    //m_node->RemoveHandler(old_universe->UniverseId());

  if (new_universe)
    /*
    m_node->SetHandler(
        new_universe->UniverseId(),
        &m_buffer,
        &m_priority,
        NewCallback<UDDCInputPort, void>(this, &UDDCInputPort::DmxChanged));
    */
    new_universe = new_universe;
}

UDDCOutputPort::~UDDCOutputPort() {
  Universe *universe = GetUniverse();
  if (universe) {
    //m_node->TerminateStream(universe->UniverseId(), m_last_priority);
  }
}

/*
 * Set the universe for an output port.
 */
void UDDCOutputPort::PostSetUniverse(Universe *old_universe,
                                     Universe *new_universe) {
  if (old_universe) {
    //m_node->TerminateStream(old_universe->UniverseId(), m_last_priority);
  }
  if (new_universe) {
    //m_node->StartStream(new_universe->UniverseId());
  }
}


/*
 * Write data to this port.
 */
bool UDDCOutputPort::WriteDMX(const DmxBuffer &buffer, uint8_t priority) {
  Universe *universe = GetUniverse();
  if (!universe)
    return false;
  
  if (false) {
    string aa;
    aa = buffer.Get();
  }

  m_last_priority = (GetPriorityMode() == PRIORITY_MODE_STATIC) ?
      GetPriority() : priority;
  return true;
  //m_node->SendDMX(universe->UniverseId(), buffer, m_last_priority,
    //                     m_preview_on);
}
}  // namespace usbdmxdotcom
}  // namespace plugin
}  // namespace ola
