
# https://46265z.github.io/IoT-dev-setup/

## Description

Za vsqko pycom ustroistvo ima otdelen branch koito sudurja nujnite za nego failove.

directory structure overview

<pre>
.
└── IoT-dev-setup/
    ├── docs/                       # contains markdown documentation
    │   └── ...
    ├── devices/                    # contains project folder for each device
    │   └── <device_name>/
    │       ├── py-workspace/       # holds micropython code (if available)
    │       │   └── ...
    │       └── ino-workspace/      # holds Arduino code (if available)
    │           └── ...
    └── ...    
</pre>

### Time sync problem

If `last connection` value is negative (e.g. _-10 seconds_) it is very likely that your clock is not synced

_for manjaro/arch linux_

Run the following:

`$ sudo systemctl enable --now systemd-timesyncd`

then

`$ sudo timedatectl set-ntp true`
