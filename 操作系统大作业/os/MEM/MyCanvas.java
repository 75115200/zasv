/*************************************************************************
    > File Name:     MyCanvas.java
    > Author:        Landerl Young
    > Mail:          LanderlYoung@gmail.com 
    > Created Time:  2013/5/4 21:56:22
 ************************************************************************/
import java.awt.Canvas;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Color;
import java.util.Iterator;

class MyCanvas extends Canvas {
	Mem m;
	private double transFactor;
	private int height;
	private int width;
	private final int space = 0;
	private static final int PPI = 80;
	private static final
	Color borderColor = Color.white,
		  stringColor = Color.white,
		  blankBg = Color.blue,
		  processBg = Color.red;

	public MyCanvas(Mem mem) {
		super();
		m = mem;
	}

	@Override
		public void setSize(int width, int height) {
			super.setSize(width, height);
			this.width = width;
			this.height = height;
			transFactor = (double)(height - space) / (double)m.getCapacity();
			//System.out.println("C setS:" + height + " " + width + " " +
					//transFactor + " capacity " + m.getCapacity());
		}

	@Override
		public void paint(Graphics g) {
			g.setColor(Color.white);
			g.fillRect(0, 0, width, height);
			Iterator<Block> it = m.iterator();
			Block b;
			while(it.hasNext()) {
				b = it.next();
				drawBlock(b, g);
			}
		}

	private void drawBlock(Block b,Graphics g) {
		int size = b.getSize();
		String sign = Integer.toString(b.getPid()) + " " +
			Integer.toString(size) + " " +
			b.getName();
		int rectPosX = 0;
		int rectPosY = (int)(b.getAddress() * transFactor);
		int rectWidth = width;
		int rectHeight = (int)(size * transFactor);
		//rectHeight = rectHeight < 4 ? 4 : rectHeight;
		int stringPosX = (int)(width -
			g.getFont().getSize()/72*PPI*sign.length()*transFactor)/2;
		//stringPosX = stringPosX > 0 ? stringPosX : 0;
		int stringPosY = (int)(rectPosY + rectHeight/2 + 
			g.getFont().getSize()/72*PPI*transFactor/2);

		g.setColor(borderColor);
		g.drawRect(rectPosX, rectPosY, rectWidth, rectHeight);
		if (b.isBlank()) 
			g.setColor(blankBg);
		else 
			g.setColor(processBg);
		g.fillRect(rectPosX+1, rectPosY+1, rectWidth-2, rectHeight-2);
		g.setColor(stringColor);
		g.drawString(sign, stringPosX, stringPosY);
	}
}
