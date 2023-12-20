CC = g++
CFLAGS = -Wall -Wextra -Werror
CFLAGS += -Wno-error=unused-parameter
CFLAGS += -Wno-error=unused-variable
CFLAGS += -Wno-error=unused-but-set-variable
LINKS = 


SRCDIR = src
OBJDIR = obj

# C Source Files
SOURCES  = $(shell find $(SRCDIR) -name "*.cpp" -o -name "*.s" -o -name "*.asm" | tr '\n' ' ')
# Remove SRCDIR
SOURCES := $(SOURCES:$(SRCDIR)/%=%)

# C Object Files
OBJECTS := $(SOURCES:%.cpp=%.o)
OBJECTS := $(OBJECTS:%.s=%.o)
OBJECTS := $(OBJECTS:%.asm=%.o)

# Header files
HEADERS  = $(wildcard $(SRCDIR)/*.h)

TARGET = gear-ratios
TARDIR = build

.PHONY: all
all: $(TARGET)

debug-flags: CFLAGS += -g
debug-flags: clean $(TARGET)

debug: CFLAGS += -DDEBUG=1
debug: run

$(SRCDIR) $(OBJDIR) $(TARDIR) $(TESTDIR):
	mkdir --parents --verbose $@

.PHONY: clean
clean:
	@printf "Cleaning\n"
	rm -f $(TARDIR)/$(TARGET) $(TARGET) $(TEST)
	rm -rf $(OBJDIR)

.PHONY: run
run: $(TARGET)
	@printf "\n\033[32m"
	@printf "###############\n"
	@printf "#   Running   #\n"
	@printf "###############\n"
	@printf "\033[0m\n"
	./$(TARGET)

$(TARGET): $(OBJECTS:%=$(OBJDIR)/%) | $(TARDIR)
	$(CC) $(CFLAGS) -o $(TARDIR)/$@ $^ $(LINKS)
	cp $(TARDIR)/$@ .

# Object rule for C files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(HEADERS) | $(OBJDIR)
	@printf "\n\033[31m"
	@printf "########################\n"
	@printf "Building %s\n" $@
	@printf "########################\n"
	@printf "\033[0m\n"
	mkdir -p `dirname $@`
	$(CC) $(CFLAGS) -c -o $@ $<

# Object rule for Assembly files
$(OBJDIR)/%.o: $(SRCDIR)/%.s $(HEADERS) | $(OBJDIR)
	@printf "\n\033[31m"
	@printf "########################\n"
	@printf "Building %s\n" $@
	@printf "########################\n"
	@printf "\033[0m\n"
	mkdir -p `dirname $@`
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/%.o: $(SRCDIR)/%.asm $(HEADERS) | $(OBJDIR)
	@printf "\n\033[31m"
	@printf "########################\n"
	@printf "Building %s\n" $@
	@printf "########################\n"
	@printf "\033[0m\n"
	mkdir -p `dirname $@`
	$(CC) $(CFLAGS) -c -o $@ $<

