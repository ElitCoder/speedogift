NAME			:= speedogift

CLIENT_SRCS		:= $(wildcard client/src/*.cpp) $(wildcard shared/src/*.cpp)
SERVER_SRCS		:= $(wildcard server/src/*.cpp) $(wildcard shared/src/*.cpp)
CLIENT_OBJS		:= $(CLIENT_SRCS:.cpp=.o)
SERVER_OBJS		:= $(SERVER_SRCS:.cpp=.o)

CXXFLAGS		+= -std=c++11 -Wall -Wextra -pedantic-errors
CXXFLAGS		+= -g

TARGET_CLIENT	:= client/bin/$(NAME)-client
TARGET_SERVER	:= server/bin/$(NAME)-server

.PHONY: all
all: $(TARGET_SERVER) $(TARGET_CLIENT)

.PHONY: clean
clean:
	rm -f $(CLIENT_OBJS) $(TARGET_CLIENT) $(CLIENT_OBJS:.o=.d)
	rm -f $(SERVER_OBJS) $(TARGET_SERVER) $(SERVER_OBJS:.o=.d)

$(TARGET_SERVER): $(SERVER_OBJS)
	$(CXX) $(LDFLAGS) -o $(TARGET_SERVER) $^ $(LDLIBS)

$(TARGET_CLIENT): $(CLIENT_OBJS)
	$(CXX) $(LDFLAGS) -o $(TARGET_CLIENT) $^ $(LDLIBS)

CXXFLAGS		+= -MMD
-include $(CLIENT_OBJS:.o=.d)
-include $(SERVER_OBJS:.o=.d)