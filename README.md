ping-icon-qt
=======

System tray icon for a remote host.

Copyright (C) 2021-2022  Konrad Kosmatka

![Screenshot](/ping-icon.png?raw=true)

This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

# Usage
```sh
$ ping-icon -h
Usage: ping-icon-qt [-r name] [-u name] [-i interval] [-t timeout] hostname

Options:
  -r  icon name for reachable state
  -u  icon name for unreachable state
  -i  interval (default: 60 s)
  -t  timeout  (default: 5 s)

If both icons are unspecified, only reachable icon "computer" is used.
```

# What's it?
Sometimes I forgot to turn off my desktop computer after powering it on remotely. As the price of electricity is getting higher and higher, I wrote this small app to display an icon in the system tray when the host is up. Just to make sure to power it off, when it is no longer needed.

To make it more versatile, three modes are implemented:
- `-r` only – the icon is visible only when the host is reachable (default)
- `-u` only – the icon is visible only when the host is unreachable
- `-r` & `-u` – both icons are used, one when host is reachable and another one when it is unreachable
