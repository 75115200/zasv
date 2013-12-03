CXX := clang++
CXXFLAGS :=  
LDFLAGS :=

TARGET := dm
SOURCES := main.cpp
OBJS := main.o
HEADS := Sector.h Block.h DiskManager.h

TARGET: $(OBJS)
	$(CXX) $^ -o $(TARGET) $(CXXFLAGS)

$(OBJS): $(HEADS) $(SOURCES)

clean:
	$(RM) $(OBJS) $(TARGET)

test:
	./$(TARGET)

.PHONY: clean
