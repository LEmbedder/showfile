CROSSCOMPILE := arm-linux-

CFLAGS 	:= -Wall -O2 -c
CFLAGS  += -I$(PWD)/include \
		   -I /work/platform-335x/tools/freetype-2.4.10/tmp/usr/local/include


LIBS += -L /work/platform-335x/tools/freetype-2.4.10/tmp/usr/local/lib

LDFLAGS := -lm -lfreetype

CC 	:= $(CROSSCOMPILE)gcc
LD 	:= $(CROSSCOMPILE)ld

OBJS := main.o


all: $(OBJS)
	$(CC) $(LDFLAGS) $(LIBS) -o show_file $^ 

clean:
	rm -f show_file
	rm -f $(OBJS)

%.o:%.c
	$(CC) $(CFLAGS) -o $@ $<

