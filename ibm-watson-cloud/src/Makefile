BIN:=ibm-watson-cloud
LDFLAGS:=-liotp-as-device -lpaho-mqtt3as -lblobmsg_json -lubox -lubus -largp
CPPFLAGS:=-I$(CURDIR)
SRC:=$(wildcard *.c)
OBJS:=$(SRC:.c=.o)

.PHONY: all clean

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(BIN) $(OBJS)