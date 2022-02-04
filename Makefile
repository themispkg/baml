define build_baml
	gcc main.c -o baml
endef

define test_baml
	/usr/bin/baml --bash ./example.baml
endef

define clean
	rm ./baml
endef

build:
	$(build_baml)
	@cp libbaml/baml.h /usr/include/
	

install:
	$(build_baml)
	install -m 755 ./baml /usr/bin/baml
	@$(test_baml)
	@cp libbaml/baml.h /usr/include/

uninstall:
	rm /usr/bin/baml

reinstall:
	$(clean)
	$(build_baml)
	install -m 755 ./baml /usr/bin/baml
	@$(test_baml)

clean:
	$(clean)

test:
	@$(test_baml)