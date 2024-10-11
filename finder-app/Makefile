writer: writer.c
	@echo Building writer app
ifdef CROSS_COMPILE
	@echo Using ${"CROSS_COMPILE"} toolchain to compile writer app
	aarch64-none-linux-gnu-gcc writer.c -o writer
	@echo DONE
else
	@echo Compiling writer app with native tools
	gcc writer.c -o writer
	@echo DONE
endif


clean:
	rm writer

