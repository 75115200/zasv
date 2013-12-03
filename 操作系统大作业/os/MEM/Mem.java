/*************************************************************************
    > File Name:     Mem.java
    > Author:        Landerl Young
    > Mail:          LanderlYoung@gmail.com 
    > Created Time:  2013/5/13 6:4
 ************************************************************************/
import java.util.*;

public class Mem implements Iterable {
	private LinkedList<Block> ll = new LinkedList<Block>();
	private int capacity; 

	public Mem(int size) {
		capacity = size;
		Block b = new Block(0, size);
		ll.add(b);
	}

	public boolean malloc(int size) {
		return malloc(size,null);
	}

	public boolean malloc(int size,String processName) {
		int index = findAvailableBlock(size);
		if(index == -1)
			return false;

		Block tmp = ll.get(index);
		int originalSize = tmp.getSize();
		int originalAddress = tmp.getAddress();
		ll.remove(index);
		ll.add(index, new Block(
				originalAddress, size, processName));
		if (originalSize - size > 0)
			ll.add(index +  1, new Block(
						originalAddress + size, originalSize - size));
		return true;
	}

	public boolean free(int pid) {
		if(pid < 0)
			return false;
		int index = findByPid(pid);
		if(index == -1)
			return false;

		int totalSize = ll.get(index).getSize();

		if(index + 1 < ll.size()) {
			Block b = ll.get(index + 1);
			if(b.isBlank()){
				totalSize += b.getSize();
				ll.remove(index + 1);
			}
		}

		ll.remove(index);

		if (index - 1 >= 0) {
			Block b = ll.get(index -1 );
			if (b.isBlank()) {
				totalSize += b.getSize();
				ll.remove(index -1);
				index--;
			}
		} 

		int address;
		if (index - 1 >= 0){
			Block tmp = ll.get(index - 1);
			address = tmp.getAddress() + tmp.getSize() + 1;
		} else 
			address = 0;

		ll.add(index,new Block(address, totalSize));
		return true;
	}

	private int findByPid(int pid) {
		Iterator<Block> it = ll.iterator();
		Block tmp;
		int index = 0;
		while(it.hasNext()) {
			tmp = it.next();
			if(tmp.getPid() == pid)
				return index;
			index++;
		}
		return -1;
	}


	private int findAvailableBlock(int size) {
		Iterator<Block> it = ll.iterator();
		Block tmp;
		int index = 0;
		while(it.hasNext()) {
			tmp = it.next();
			if(tmp.isBlank() && tmp.getSize() >= size)
				return index;
			index++;
		}
		return -1;
	}

	public String getStatue() {
		String statue = "addr  size  pid name\n";
		Iterator<Block> it = ll.iterator();
		Block tmp;
		while(it.hasNext()){
			tmp = it.next();
		statue += tmp.getAddress() + "  " + tmp.getSize() +"  " +
						tmp.getPid() + "  " + tmp.getName() + "\n";
		}
		return statue;
	}


	public void showStatue() {
		System.out.printf(getStatue());
	}

	public Iterator<Block> iterator() {
		return ll.iterator();
	}

	public Block getBlockByPid(int pid) {
		Block b;
		Iterator<Block> it = ll.iterator();
		while(it.hasNext()) {
			b = it.next();
			if (b.getPid() == pid)
				return b;
		}

		return null;
	}

	public Block getBlockByIndex(int index) {
		try {
			return ll.get(index);
		} catch(IndexOutOfBoundsException e) {
			return null;
		}
	}

	public int getCapacity() {
		return capacity;
	}

	public static void main(String[] args) {
	}
}
