#Ant is so egg-fucked
.PHONY: r e c clean

UI.class:UI.java Mem.class MyCanvas.class
	javac $<

MyCanvas.class:MyCanvas.java
	javac $<

Mem.class:Mem.java Block.class
	javac $< 

Block.class:Block.java
	javac $<

clean:
	rm -f *.class
