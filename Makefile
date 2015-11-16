.PHONY: flash docs clean

flash:
	sudo xfer9860 -u ARMLET.G1A ARMLET.G1A

docs:
	doxygen ./Doxyfile

clean:
	rm -rf doxygen/ Debug/ SDCard/ Init/ *.G1A
