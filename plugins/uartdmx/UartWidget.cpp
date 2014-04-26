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
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 * This class is based on QLCFTDI class from
 *
 * Q Light Controller
 * qlcftdi-libftdi.cpp
 *
 * Copyright (C) Heikki Junnila
 *
 * Only standard CPP conversion was changed and function name changed
 * to follow OLA coding standards.
 *
 * by Rui Barreiros
 * Copyright (C) 2014 Richard Ash
 */

#include <strings.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

#include <string>
#include <algorithm>
#include <vector>

#include "ola/Logging.h"
#include "ola/BaseTypes.h"
#include "plugins/uartdmx/UartWidget.h"
#include "plugins/uartdmx/UartLinuxHelper.h"

namespace ola {
namespace plugin {
namespace uartdmx {

using std::string;
using std::vector;

UartWidget::UartWidget(const string& path, int device_id)
    : m_path(path),
      m_device_id(device_id) {
  m_filed = -2;
}

UartWidget::~UartWidget() {
  if (IsOpen())
    Close();
}


bool UartWidget::Open() {
  OLA_DEBUG << "Opened serial port " << Name();
  m_filed = open(m_path.c_str(), O_WRONLY);
  if (m_filed == -1) {
    OLA_WARN << Name() << " failed to open";
    return false;
  } else {
    return true;
  }
}

bool UartWidget::Close() {
  if (close(m_filed) > 0) {
    OLA_WARN << Name() << " error closing";
    m_filed = -2;
    return false;
  } else {
    m_filed = -2;
    return true;
  }
}

bool UartWidget::IsOpen() const {
  return (m_filed > 0) ? true : false;
}

bool UartWidget::SetBreak(bool on) {
  unsigned long request;
  if (on == true)
    request = TIOCSBRK;
  else
    request = TIOCCBRK;

  if (ioctl(m_filed, request, NULL) < 0) {
    OLA_WARN << Name() << " ioctl() failed";
    return false;
  } else {
    return true;
  }
}

bool UartWidget::Write(const ola::DmxBuffer& data) {
  unsigned char buffer[DMX_UNIVERSE_SIZE + 1];
  int unsigned length = DMX_UNIVERSE_SIZE;
  buffer[0] = 0x00;  // start code of 0 for dimmer control messages

  data.Get(buffer + 1, &length);

  if (write(m_filed, buffer, length + 1) <= 0) {
    // TODO(richardash1981): handle errors better as per the test code,
    // especially if we alter the scheduling!
    OLA_WARN << Name() << " Short or failed write!";
    return false;
  } else {
    return true;
  }
}

bool UartWidget::Read(unsigned char *buff, int size) {
  int readb = read(m_filed, buff, size);
  if (readb <= 0) {
    OLA_WARN << Name() << " read error";
    return false;
  } else {
    return true;
  }
}

/**
 * Setup our device for DMX send
 * Also used to test if device is working correctly
 * before AddDevice()
 */
bool UartWidget::SetupOutput() {
  struct termios my_tios;
  // Setup the Uart for DMX
  if (Open() == false) {
    OLA_WARN << "Error Opening widget";
    return false;
  }
  /* do the port settings */

  if (tcgetattr(m_filed, &my_tios) < 0) {  // get current settings
    OLA_WARN << "Failed to get POSIX port settings";
    return false;
  }
  cfmakeraw(&my_tios);  // make it a binary data port

  my_tios.c_cflag |= CLOCAL;    // port is local, no flow control
  my_tios.c_cflag &= ~CSIZE;
  my_tios.c_cflag |= CS8;       // 8 bit chars
  my_tios.c_cflag &= ~PARENB;   // no parity
  my_tios.c_cflag |= CSTOPB;    // 2 stop bit for DMX
  my_tios.c_cflag &= ~CRTSCTS;  // no CTS/RTS flow control

  if (tcsetattr(m_filed, TCSANOW, &my_tios) < 0) {  // apply settings
    OLA_WARN << "Failed to get POSIX port settings";
    return false;
  }

  /* Do the platform-specific initialisation of the Uart to 250kbaud */
  if (!LinuxHelper::SetDmxBaud(m_filed)) {
    OLA_WARN << "Failed to set baud rate to 250k";
    return false;
  }
  /* everything must have worked to get here */
  return true;
}

}  // namespace uartdmx
}  // namespace plugin
}  // namespace ola
