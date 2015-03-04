all: Utils HWDescription HWInterface System tools src GUI

libs: Utils HWDescription HWInterface System

gui: Utils HWDescription HWInterface System tools src GUI
	
HWDescription::
	$(MAKE) -C $@
Utils::
	$(MAKE) -C $@
HWInterface::
	$(MAKE) -C $@
System::
	$(MAKE) -C $@
tools::
	$(MAKE) -C $@
src::
	$(MAKE) -C $@
GUI::
	$(MAKE) -C GUI/Macros
	$(MAKE) -C $@
doc::
	$(MAKE) -C $@


clean:
	(cd System; make clean)
	(cd Utils; make clean)
	(cd HWInterface; make clean)
	(cd HWDescription; make clean)
	(cd tools; make clean)
	(cd GUI; make clean)
	(cd GUI; make clean; cd GUI/Macros; make clean)
	(cd doc; make clean)
	(rm -f lib/* bin/*)

