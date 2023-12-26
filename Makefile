TARGET_EXEC := final_program

BUILD_DIR := ./build
SRC_DIRS := ./

SRCS := $(shell find $(SRC_DIRS) -name '*.cpp' -or -name '*.s' -not -path './test/*')
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)
INC_DIRS := $(shell find $(SRC_DIRS) -type d) 
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

SDL_CFLAGS := $(shell sdl2-config --cflags)
SDL_LDFLAGS := $(shell sdl2-config --libs)

SDL_IMAGE_CFLAGS := $(shell pkg-config SDL2_image --cflags)
SDL_IMAGE_LDFLAGS := $(shell pkg-config SDL2_image --libs)

SDL_TTF_CFLAGS := $(shell pkg-config SDL2_ttf --cflags)
SDL_TTF_LDFLAGS := $(shell pkg-config SDL2_ttf --libs)

CPPFLAGS := $(INC_FLAGS) $(SDL_CFLAGS) $(SDL_IMAGE_CFLAGS) $(SDL_TTF_CFLAGS) -MMD -MP
LDFLAGS := $(SDL_LDFLAGS) $(SDL_IMAGE_LDFLAGS) $(SDL_TTF_LDFLAGS)

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -r $(BUILD_DIR)

install:
	@if [ -w "/usr/local/bin/" ]; then \
	install ./build/final_program /usr/local/bin/scheduler; \
	echo "Installation successful!"; \
	else \
	echo "Error: Insufficient privileges to install in /usr/local/bin/. Please run 'make install' with elevated privileges (sudo)."; \
	exit 0; \
    fi

-include $(DEPS)