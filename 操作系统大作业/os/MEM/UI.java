/*************************************************************************
  > File Name:     UI.java
  > Author:        Landerl Young
  > Mail:          LanderlYoung@gmail.com 
  > Created Time:  2013/54 18:42:31
 ************************************************************************/
import javax.swing.*;
import javax.swing.border.*;
import java.awt.*;
import java.awt.event.*;

public class UI extends JFrame {
	private int size = -1;
	private Mem m;
	private MyCanvas canvas;

	private JPanel jp = new JPanel();
	private JButton mallocB = new JButton("Malloc");
	private JButton freeB = new JButton("Free");
	private JLabel mallocL = new JLabel("Size");
	private JLabel mallocNL = new JLabel("Name");
	private JTextField mallocNT = new JTextField(8);
	private JLabel freeL = new JLabel("PID");
	private JTextField mallocT = new JTextField(8);
	private JTextField freeT = new JTextField(8);
	private JTextArea log = new JTextArea(9, 18);



	public UI() {
		new GetSize();
	}

	private void initUI() {
		//Initialize conmonents
		initComponents();
		//JPanel
		jp.setSize(200, 500);
		jp.setLayout(new BorderLayout());
		
		//MyCanvas
		canvas.setSize(180, 500);

		//JFrame
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setSize(400,500);
		setTitle("Memery Allocation");
		add(BorderLayout.WEST, canvas);
		add(BorderLayout.EAST, jp);
		setLocationRelativeTo(null);
		setVisible(true);

		//Layout
		add(BorderLayout.WEST, canvas);
		JPanel bigJP = new JPanel();
		bigJP.setPreferredSize(new Dimension(200,500));
		add(BorderLayout.EAST, bigJP);
		bigJP.setLayout(new BorderLayout());

		JPanel mallocJP = new JPanel();
		mallocJP.setPreferredSize(new Dimension(200, 150));
		mallocJP.setBorder(new TitledBorder("Malloc"));
		JPanel freeJP = new JPanel();
		freeJP.setPreferredSize(new Dimension(200,150));
		freeJP.setBorder(new TitledBorder("Free"));
		JPanel logJP = new JPanel();
		logJP.setPreferredSize(new Dimension(200,200));
		logJP.setBorder(new TitledBorder("Statue"));

		bigJP.add(BorderLayout.NORTH, mallocJP);
		bigJP.add(BorderLayout.CENTER, freeJP);
		bigJP.add(BorderLayout.SOUTH, logJP);

		mallocJP.setLayout(new GridBagLayout());
		GridBagConstraints gbc = new GridBagConstraints();
		Insets tabInsets = new Insets(0, 0, 10, 7);
		Insets txtInsets = new Insets(0, 0, 10, 0);
		gbc.gridx = 0;
		gbc.gridy = 0;
		gbc.gridwidth = 1;
		gbc.gridheight = 1;
		gbc.weightx = 0;
		gbc.weighty = 0;
		gbc.anchor = GridBagConstraints.CENTER;
		gbc.fill = GridBagConstraints.NONE;
		gbc.insets = tabInsets;
		gbc.ipadx = 0;
		gbc.ipady = 0;
		mallocJP.add(mallocL,gbc);

		gbc.gridx = 1;
		gbc.gridy = 0;
		gbc.gridwidth = 1;
		gbc.gridheight = 1;
		gbc.weightx = 0;
		gbc.weighty = 0;
		gbc.anchor = GridBagConstraints.CENTER;
		gbc.fill = GridBagConstraints.NONE;
		gbc.insets = txtInsets;
		gbc.ipadx = 0;
		gbc.ipady = 0;
		mallocJP.add(mallocT, gbc);

		gbc.gridx = 0;
		gbc.gridy = 1;
		gbc.gridwidth = 1;
		gbc.gridheight = 1;
		gbc.weightx = 0;
		gbc.weighty = 0;
		gbc.anchor = GridBagConstraints.CENTER;
		gbc.fill = GridBagConstraints.NONE;
		gbc.insets = tabInsets;
		gbc.ipadx = 0;
		gbc.ipady = 0;
		mallocJP.add(mallocNL, gbc);

		gbc.gridx = 1;
		gbc.gridy = 1;
		gbc.gridwidth = 1;
		gbc.gridheight = 1;
		gbc.weightx = 0;
		gbc.weighty = 0;
		gbc.anchor = GridBagConstraints.CENTER;
		gbc.fill = GridBagConstraints.NONE;
		gbc.insets = txtInsets;
		gbc.ipadx = 0;
		gbc.ipady = 0;
		mallocJP.add(mallocNT, gbc);

		gbc.gridx = 0;
		gbc.gridy = 2;
		gbc.gridwidth = 2;
		gbc.gridheight = 1;
		gbc.weightx = 0;
		gbc.weighty = 0;
		gbc.anchor = GridBagConstraints.CENTER;
		gbc.fill = GridBagConstraints.HORIZONTAL;
		gbc.ipadx = 0;
		gbc.ipady = 0;
		mallocJP.add(mallocB, gbc);

		freeJP.setLayout(new GridBagLayout());

		gbc.gridx = 0;
		gbc.gridy = 0;
		gbc.gridwidth = 1;
		gbc.gridheight = 1;
		gbc.weightx = 0;
		gbc.weighty = 0;
		gbc.anchor = GridBagConstraints.CENTER;
		gbc.fill = GridBagConstraints.NONE;
		gbc.insets = tabInsets;
		gbc.ipadx = 0;
		gbc.ipady = 0;
		freeJP.add(freeL, gbc);

		gbc.gridx = 1;
		gbc.gridy = 0;
		gbc.gridwidth = 1;
		gbc.gridheight = 1;
		gbc.weightx = 0;
		gbc.weighty = 0;
		gbc.anchor = GridBagConstraints.CENTER;
		gbc.fill = GridBagConstraints.NONE;
		gbc.insets = txtInsets;
		gbc.ipadx = 0;
		gbc.ipady = 0;
		freeJP.add(freeT, gbc);

		gbc.gridx = 0;
		gbc.gridy = 1;
		gbc.gridwidth = 2;
		gbc.gridheight = 1;
		gbc.weightx = 0;
		gbc.weighty = 0;
		gbc.anchor = GridBagConstraints.CENTER;
		gbc.fill = GridBagConstraints.HORIZONTAL;
		gbc.insets = txtInsets;
		gbc.ipadx = 0;
		gbc.ipady = 0;
		freeJP.add(freeB, gbc);

		logJP.add(new JScrollPane(log));
		log.setText(m.getStatue());
	}

	private void initComponents() {
		mallocB.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				String str;
				String name;
				int size;
				str = mallocT.getText();
				name = mallocNT.getText();
				try {
					size = Integer.parseInt(str);
				} catch (NumberFormatException ex) {
					size = -1;
				}
				if(size <= 0) {
					showErrorMsg((((JButton)e.getSource()).getParent()),
						"Number Format Error.Please input again.");
					mallocT.setText(null);
				} else if (!m.malloc(size, name)) {
					showErrorMsg((((JButton)e.getSource()).getParent()),
						"Allocation memory failed");
				} else {
					log.setText(m.getStatue());
					canvas.repaint();
				}
			}
		});

		freeB.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				String str;
				int pid;
				str = freeT.getText();
				try {
					pid = Integer.parseInt(str);
				} catch (NumberFormatException ex) {
					pid = -1;
				}
				if(pid < 0) {
					showErrorMsg((((JButton)e.getSource()).getParent()),
						"Number Format Error.Please input again.");
					freeT.setText(null);
				} else if(!m.free(pid)) {
					showErrorMsg((((JButton)e.getSource()).getParent()),
						"Free memory failed");
				} else {
					freeT.setText(String.valueOf(pid + 1));
					log.setText(m.getStatue());
					canvas.repaint();
				}
			}
		});
	}

	public void showErrorMsg(Component cpn, String msg) {
		JOptionPane.showConfirmDialog(cpn, msg,
				"Error",JOptionPane.DEFAULT_OPTION,
				JOptionPane.ERROR_MESSAGE);
	}


	class GetSize {
		JDialog f = new JDialog();
		JTextField txt = new JTextField(10);
		JButton jb = new JButton("OK");
		public GetSize() {
			jb.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					int s;
					try {
						s = Integer.parseInt(txt.getText());
					} catch (NumberFormatException ex) {
						s = -1;
					}

					if( s > 0) {
						size = s;
						m = new Mem(size);
						canvas = new MyCanvas(m);
						initUI();
						f.dispose();
					} else {
						txt.setText("");
						//show Help Msg
						//
						showErrorMsg(f,
							"Number Formate Error.Please input again.");
					}
				}
			});
			f.setDefaultCloseOperation(JDialog.DISPOSE_ON_CLOSE);
			f.setTitle("Enter Memory Size");
			f.setSize(300,60);
			f.add(BorderLayout.WEST, new JLabel("Enter Size"));
			f.add(BorderLayout.CENTER, txt);
			f.add(BorderLayout.EAST, jb);
			f.setLocationRelativeTo(null);
			f.setVisible(true);
		}
	}

	public static void main(String[] args){
		UI ui = new UI();
		System.out.println(ui.size);
	}
}
