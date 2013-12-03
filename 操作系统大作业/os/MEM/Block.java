/*************************************************************************
    > File Name:     Block.java
    > Author:        Landerl Young
    > Mail:          LanderlYoung@gmail.com 
    > Created Time: 
 ************************************************************************/

public class Block {
	public static final boolean BLANK = true;
	public static final boolean PROCESS = false;
	private static int SPid = 0;
	private  final boolean type;
	private final int size;
	private final int address;
	private final int pid;
	private String name = null;

	//Given only size means this is a 
	//blank block.
	public Block(int address, int size) {
		this.address = address;
		this.type = BLANK;
		this.size = size;
		this.pid = -1;
		this.name = "Blank";
	}

	//Given name means this is a process
	//Block;
	public Block(int address, int size,String name) {
		this.address = address;
		this.pid = SPid++;
		this.type = PROCESS;
		this.size = size;
		this.name = name;
	}

	public boolean isBlank() {
		return type;
	}
	
	public void setName(String name) {
		this.name = name;
	}

	public int getPid() {
		return pid;
	}
	public int getSize() {
		return size;
	}
	public int getAddress() {
		return address;
	}
	public String getName() {
		return name;
	}
	public String toString() {
		return name;
	}
}
