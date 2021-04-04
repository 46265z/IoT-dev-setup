If `last connection` value is negative (e.g. _-10 seconds_) it is very likely that your clock is not synced

_for manjaro/arch linux_

Run the following:

`$ sudo systemctl enable --now systemd-timesyncd`

then

`$ sudo timedatectl set-ntp true`
