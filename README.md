<h1>bsdinfo</h1>

<h2>Description</h2>
<p>This is my FreeBSD attempt to implement archey-like terminal system information display utility. It is just an esthetic way to display system information. Right now it doesn't have any configurable options (different themes, switches to change behaviour, etc), but I will add such features in the future, perhaps.</p>

<br />
<h2>Installation</h2>

<p>To install the script, simply run:</p>

<pre>
    make
</pre>

<p>To build xterm-256 color version, type:</p>

<pre>
    make xterm-256
</pre>

<p>To install the binary:</p>

<pre>
	make install
</pre>

<p>You will need to have root permissions, to run `make install`, as it requires write access to /usr/local/bin. The binary will be installed at /usr/local/bin/bsdinfo.</p>

<p>Please remember, that you should have the TERM environment variable set to 'xterm-256color', and you should have a 256-color capable terminal emulator to run the 256 color version, which is also a bit wider than the standard version.</p>

<h2>Screenshot</h2>

<p>Normal build:</p>

<img src="https://github.com/samaelszafran/bsdinfo/raw/master/screenshot.png" />

<p>And the xterm-256 version:</p>

<img src="https://github.com/samaelszafran/bsdinfo/raw/master/screenshot256.png" />
