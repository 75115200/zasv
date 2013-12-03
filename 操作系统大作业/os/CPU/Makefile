CC := gcc 
TARGET = "cpu"

HEADERS := dataStruct.h
SOURCES := dataStruct.c \
	main.c 
OBJECTS := dataStruct.o \
	main.o

$(TARGET):$(OBJECTS)
	$(CC) $^ -o $@

$(OBJECTS):$(HEADERS) $(SOURCES)
#$(CXX) -c $(SOURCES)

clean:
	$(RM) $(OBJECTS) $(TARGET)

e:
	vim main.c

r:
	./$(TARGET)
