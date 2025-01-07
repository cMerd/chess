CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++23 -I./inc/
SRCDIR := src
BUILDDIR := build
LIBS := -lm -lraylib

# List of source files
SRCS := $(wildcard $(SRCDIR)/*.cpp)

# Generate object file names from source file names
OBJS := $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SRCS))

# Default target
all: $(BUILDDIR)/chess

# Rule to link object files into executable
$(BUILDDIR)/chess: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) $(LIBS) -o $@

# Rule to compile each source file into object files
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean target to remove all files in build directory
clean:
	rm -f $(BUILDDIR)/*
