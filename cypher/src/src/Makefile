TARGET:=Cypher.dll

#mingw
CC:=gcc
CFLAGS:=-I"${JAVA_HOME}\include" -I"${JAVA_HOME}\include\win32" -shared  -Wl,--kill-at

CLASS_NAME:=Cypher

JSOURCE:=$(CLASS_NAME).java
CLASS:=$(CLASS_NAME).class

SOURCES:=$(CLASS_NAME).c des.c aes.c rc4.c
HEADERS:=$(CLASS_NAME).h des.h aes.h rc4.h
OBJECTS:=$(CLASS_NAME).o des.o aes.o rc4.o

UI.class:$(CLASS) UI.java
	javac UI.java

$(CLASS):$(TARGET) $(JSOURCE)
	javac $(JSOURCE)

$(TARGET):$(OBJECTS) $(HEADERS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET) 

$(OBJECTS):$(SOURCES) $(HEADERS)
	gcc $(CFLAGS) -c $(SOURCES)

.PHONY:clean r e c

clean:
	$(RM) $(TARGET) $(CLASS) $(OBJECTS) *.class

r:$(TARGET)
	java UI

e:
	vim $(CLASS_NAME).java 

c:
	vim $(CLASS_NAME).c
