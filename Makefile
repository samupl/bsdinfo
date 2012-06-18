install:
	$INSTALL_EXEC bsdinfo /bin/bsdinfo

deinstall:
	rm /usr/local/bin/bsdinfo

clean:
	rm -rf bsdinfo
