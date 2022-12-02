# Defines

MKDIR=mkdir -p

PATHS = 			src
PATHI =				include
PATHU =				unittest
PATHC = 			clients
PATHB = 			build
PATHLB = 			lib$(PATHB)
PATHD =				depend
PATHUB =			unittestBuild
SRCS =				$(wildcard $(PATHS)/*.cpp)
USRCS =				$(wildcard $(PATHU)/*.cpp)
LIBRARY =			libaoc.a
CXX = 				g++
LINK = 				$(CXX)
AR = 				ar
CXX_STD =			c++17
DEF =				-g
CXXFLAGS =			-I$(PATHI) -Wall -Wextra -Werror $(ARCH) -O3 -std=$(CXX_STD) -D_POSIX_C_SOURCE=200809L $(DEF)
CLIENT_CFLAGS = 	-I$(PATHI) -Wall -Wextra -Werror -pedantic $(ARCH) -std=$(CXX_STD) -D_POSIX_C_SOURCE=200809L $(DEF)

LDFLAGS =			$(ARCH) $(DEF)

COMPILE =			$(CXX) $(CXXFLAGS) -MT $@ -MP -MMD -MF $(PATHD)/$*.Td
OBJS =				$(addprefix $(PATHLB)/, $(notdir $(SRCS:.cpp=.o)))
POSTCOMPILE =		@mv -f $(PATHD)/$*.Td $(PATHD)/$*.d && touch $@
UBINS =				$(addprefix $(PATHUB)/, $(notdir $(basename $(USRCS))))

.PHONY: all clean unittest

.PRECIOUS: $(PATHD)/%.d
.PRECIOUS: $(PATHB)/%.o
.PRECIOUS: $(PATHB)/%.a
.PRECIOUS: $(PATHLB)/%.o
.PRECIOUS: $(PATHUB)/%


# Rules

all:aoc 


./$(PATHB):
	$(MKDIR) $@

$(PATHLB):
	$(MKDIR) $@

$(PATHD):
	$(MKDIR) $@

$(PATHUB):
	$(MKDIR) $@


aoc: $(PATHB)/aoc | $(PATHB)
	ln -sf $^ $@

$(PATHB)/%: $(PATHB)/%.o $(PATHLB)/$(LIBRARY) | $(PATHB) $(PATHLB)
	$(LINK) $(LDFLAGS) -o $@ $^ $(LDLIBS)

$(PATHLB)/$(LIBRARY): $(OBJS)
	# $(MAKE) DEF="$(DEF)" PATHB="$(PATHB)" unittest
	$(RM) $@
	$(AR) rcs $@ $^

$(PATHB)/%.o: $(PATHC)/%.cpp | $(PATHB) $(PATHD)
	$(CXX) $(CLIENT_CFLAGS) -MT $@ -MP -MMD -MF $(PATHD)/$*.Td -c $< -o $@
	$(POSTCOMPILE)

$(PATHLB)/%.o: $(PATHS)/%.cpp | $(PATHLB) $(PATHD)
	$(COMPILE) -c $< -o $@
	$(POSTCOMPILE)

$(PATHUB)/%.o: $(PATHU)/%.cpp | $(PATHUB) $(PATHD)
	$(COMPILE) -c $< -o $@
	$(POSTCOMPILE)

$(PATHUB)/%: $(PATHUB)/%.o $(PATHLB)/$(LIBRARY) | $(PATHB)
	$(LINK) $(LDFLAGS) -o $@ $^ $(LDLIBS)
	$@

unittest: $(UBINS)

clean:
	$(RM) $(PATHD)/*.d
	$(RM) $(PATHD)/*.Td
	$(RM) $(PATHUB)/*
	$(RM) $(PATHLB)/*
	$(RM) $(PATHB)/*
	$(RM) ./aoc

include $(wildcard $(PATHD)/*.d)
