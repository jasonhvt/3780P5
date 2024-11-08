# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++11

# Executable names
RECEIVER_EXEC = receiver
SENDER_EXEC = sender

# Source files
RECEIVER_SRC = 3-receiver.cc
SENDER_SRC = 2-send.cc

# Default target to build both executables
all: $(RECEIVER_EXEC) $(SENDER_EXEC)

# Build receiver
$(RECEIVER_EXEC): $(RECEIVER_SRC)
	$(CXX) $(CXXFLAGS) -o $(RECEIVER_EXEC) $(RECEIVER_SRC)

# Build sender
$(SENDER_EXEC): $(SENDER_SRC)
	$(CXX) $(CXXFLAGS) -o $(SENDER_EXEC) $(SENDER_SRC)

# Run receiver with default port 3000 and optional protocol (-4 or -6)
run-receiver: $(RECEIVER_EXEC)
	./$(RECEIVER_EXEC) 3000 $(PROTOCOL)

# Run sender with default arguments (localhost and port 3000)
run-sender: $(SENDER_EXEC)
	./$(SENDER_EXEC) localhost 3000

# Clean up executables
clean:
	rm -f $(RECEIVER_EXEC) $(SENDER_EXEC)

# Phony targets to avoid conflicts with files named "all", "clean", etc.
.PHONY: all clean run-receiver run-sender
