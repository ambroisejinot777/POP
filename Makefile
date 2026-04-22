OUT      := project
CXX      := g++
CXXFLAGS := -Wall -std=c++17
PKGS     := gtkmm-4.0
LINKING  := $(shell pkg-config --cflags $(PKGS))
LDLIBS   := $(shell pkg-config --libs $(PKGS))

BUILD_DIR := build

CXXFILES := tools.cc message.cc paddle.cc brick.cc ball.cc graphic.cc \
												gui.cc game.cc project.cc
OFILES   := $(addprefix $(BUILD_DIR)/, $(CXXFILES:.cc=.o))

.PHONY: all clean tests

all: $(OUT)

$(BUILD_DIR)/%.o: %.cc
	@mkdir -p $(dir $@)
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@

$(OUT): $(OFILES)
	@$(CXX) $(CXXFLAGS) $(LINKING) $^ -o $@ $(LDLIBS)

clean:
	@echo "Cleaning project..."
	@rm -rf $(BUILD_DIR) $(OUT)

tests: $(OUT)
	@for test in $$(ls tests); do \
		echo "Running $$test..."; \
		./$(OUT) tests/$$test; \
	done

depend:
	@echo " *** MISE A JOUR DES DEPENDANCES ***"
	@(sed '/^# DO NOT DELETE THIS LINE/q' Makefile && \
	  $(CXX) -MM $(CXXFLAGS) $(CXXFILES) | \
	  egrep -v "/usr/include" \
	 ) >Makefile.new
	@mv Makefile.new Makefile
