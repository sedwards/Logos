CC = gcc
CFLAGS = -Iinclude -Iinclude/connectors -I/opt/homebrew/include/cjson
LIBS = -L/opt/homebrew/lib -lcurl -lcjson

# List of object files
OBJS = src/main.o src/engine.o src/connectors/chatgpt_driver.o

# Target for the final executable
all: Logos

# Rule for linking the executable
Logos: $(OBJS)
	$(CC) -o $@ $^ $(LIBS)

# Rule for compiling source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files and the executable
clean:
	rm -f $(OBJS) Logos

