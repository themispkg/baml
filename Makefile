install:
	install -m 755 ./baml.sh /usr/bin/baml

uninstall:
	rm /usr/bin/baml

reinstall:
	rm /usr/bin/baml
	install -m 755 ./baml.sh /usr/bin/baml