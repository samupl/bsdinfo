bsdinfo
=======

Description
-----------

This is my FreeBSD attempt to implement archey-like terminal system information display utility. It is just an esthetic way to display system information. Right now it doesn't have any configurable options (different themes, switches to change behaviour, etc), but I will add such features in the future, perhaps.

Installation
------------

To install the script, simply run

	make

To build xterm-256 color version, type:

        make xterm-256

To install the binary:

	make install


You will need to have root permissions, to run `make install`, as it requires write access to /usr/local/bin. The binary will be installed at /usr/local/bin/bsdinfo.

Please remember, that you should have the TERM environment variable set to 'xterm-256color', and you should have a 256-color capable terminal emulator to run the 256 color version, which is also a bit wider than the standard version.

Screenshot
----------

You can see a screenshot in the repository. I don't know how to attach it on github README, so if you wan't to view it, simply visit the link below.

https://github.com/samaelszafran/bsdinfo/raw/master/screenshot.png

And the xterm-256 version:

https://github.com/samaelszafran/bsdinfo/raw/master/screenshot256.png
