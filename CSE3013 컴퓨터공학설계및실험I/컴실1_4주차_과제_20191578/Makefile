.SURFFIXES : .cpp .o
CXX = g++

CPPFLAGS = -g

HEDRS = Array.h GrowableArray.h
SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)

TARGET = growablearray

all : $(TARGET)

$(TARGET) : $(OBJS) $(HDRS)
	$(CXX) -o $@ $(OBJS)

clean :
	rm -rf $(OBJS) $(TARGET)
