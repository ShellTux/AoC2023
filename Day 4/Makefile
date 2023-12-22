SRC_DIR = src
OBJ_DIR = obj

EXTENSION = java

SOURCES := $(wildcard $(SRC_DIR)/*.$(EXTENSION))
OBJECTS := $(patsubst $(SRC_DIR)/%.$(EXTENSION),$(OBJ_DIR)/%.class,$(SOURCES))

$(OBJ_DIR)/%.class: $(SRC_DIR)/%.$(EXTENSION)
	@mkdir -p $(@D)
	javac -d $(OBJ_DIR) $<

.PHONY: all
all: $(OBJECTS)

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR)
