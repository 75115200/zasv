/*************************************************************************
  > File Name:     UI.java
  > Author:        Landerl Young
  > Mail:          LanderlYoung@gmail.com 
  > Created Time:  2013/6/16 18:13:05
 ************************************************************************/
import javax.swing.*;
import javax.swing.border.*;
import java.awt.*;
import java.awt.event.*;
import java.io.File;


public class UI extends JFrame {

	public static final int ENCRYPT = 0;
	public static final int DESCERPT = 1;

	//Constence Strings
	private static final String desString = "Des";
	private static final String aesString = "Aes";
	private static final String rc4String = "Rc4";
	private static final String srcFileString = 
		"源文件";
	private static final String dstFileString =
		"目的文件";
	private static final String radioButtonPanelString = 
		"选择加密算法";
	private static final String passwordString = 
		" 密码";
	private static final String encryButtonString = 
		"加密";
	private static final String descryButtonString =
		"解密";
	private static final String fileSelectPanelTitleString = 
		"选择文件";
	private static final String srcFileChooserDialogTitle = 
		"选择源文件";
	private static final String dstFileChooserDialogString = 
		"选择密文";
	private static final String srcFileNotFoundMessageString = 
		"源文件为空";
	private static final String dstFileNotFoundMessageString = 
		"密文为空";
	private static final String passwordNullMessageString = 
		"密码为空";
	private static final String errTitle =
		"错误";

	private static final String titleString =
		"密码学课程设计___杨超";

	private final static String imageFileString = 
		"images/file.png";
	private static final String imageFileFocusedString =
		"images/fileFocused.png";

	//Cryption Algorithm 
	//default is des
	private String cryptionAlgorithm = desString;

	//components
	private JPanel radioButtonPanel = new JPanel();
	private JPanel fileSelectPanel = new JPanel();
	private JPanel passwordPanel = new JPanel();
	private JTextField passwordField = new JTextField(20);

	private JButton encryButton =  new JButton(encryButtonString);
	private JButton descryButton = new JButton(descryButtonString);
	private JLabel srcFileLabel = new JLabel();
	private JLabel dstFileLabel = new JLabel();


	private final JProgressBar progressBar = 
		new JProgressBar();

	//
	private File srcFile;
	private File dstFile;

	public UI() {
		//Do something Here
		initComponments();
		initLayout();

		//
		pack();
		setTitle(titleString);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setSize(600, 400);
		setLocationRelativeTo(null);
		setVisible(true);
	}

	private void initComponments() {
		initRadioButtonPanel();
		initFileSelectPanel();
		initPasswordPanel();
	}

	private void initRadioButtonPanel() {
		TitledBorder border = new TitledBorder(radioButtonPanelString);
		border.setTitleColor(Color.BLUE);
		radioButtonPanel.setBorder(border);
		radioButtonPanel.setLayout(new GridBagLayout());
		GridBagConstraints gbc = new GridBagConstraints();

		gbc.gridx = 0;
		gbc.gridy = 0;
		gbc.weighty = 0.4;
		gbc.ipady = 70;
		//gbc.fill = GridBagConstraints.VERTICAL;
		radioButtonPanel.add(new RadioButtonPanel(), gbc);

		gbc.gridx = 0;
		gbc.gridy = 1;
		gbc.weighty = 0.1;
		gbc.ipady = 0;
		gbc.insets = new Insets(0, 0, 10, 0);
		gbc.fill = GridBagConstraints.NONE;
		//
		JButton tb = new JButton("Test");
		tb.setEnabled(false);
		tb.setText("false");
		//TODO
		//Reserved
		//radioButtonPanel.add(tb, gbc);
	}

	private void initFileSelectPanel() {
		//init fileSelectPanel
		srcFileLabel.setHorizontalAlignment(SwingConstants.CENTER);
		dstFileLabel.setHorizontalAlignment(SwingConstants.CENTER);

		progressBar.setStringPainted(true);
		fileSelectPanel.setBorder(new TitledBorder(fileSelectPanelTitleString));

		fileSelectPanel.setLayout(new GridBagLayout());
		GridBagConstraints gbc = new GridBagConstraints();
		//Global Setting
		gbc.fill = GridBagConstraints.HORIZONTAL;


		final ImageIcon fileIcon = new ImageIcon(imageFileString);
		if(fileIcon == null)
			System.err.println("Image File " + imageFileString + " not found.");
		ImageIcon fileIconFocused_tmp = new ImageIcon(imageFileFocusedString);
		if(fileIconFocused_tmp == null) {
			System.err.println("Image File " + imageFileFocusedString
					+ " not found.");
			fileIconFocused_tmp = fileIcon;
		}
		final ImageIcon fileIconFocused = fileIconFocused_tmp;

		  JLabel srcFileIconLabel = new JLabel(fileIcon);
		  JLabel dstFileIconLabel = new JLabel(fileIcon);
		//Add actionListener
		//
		srcFileIconLabel.addMouseListener(new MouseListener() {
			public void mouseClicked(MouseEvent e) {
				//Call FileCHooser
				JFileChooser fc = new JFileChooser(new File("."));
				fc.setDialogTitle(srcFileChooserDialogTitle);
				if(fc.showOpenDialog(((JLabel)e.getSource()).getRootPane())
					== JFileChooser.APPROVE_OPTION) {
					srcFile = fc.getSelectedFile();
					srcFileLabel.setText(srcFile.getName());
				}
			}
			public void mouseEntered(MouseEvent e) {
				if(srcFile == null) {
					((JLabel)e.getSource()).setIcon(fileIconFocused);
				}


			}
			public void mouseExited(MouseEvent e) {
				if(srcFile == null) {
					((JLabel)e.getSource()).setIcon(fileIcon);
				}

			}
			public void mousePressed(MouseEvent E) {
			}
			public void mouseReleased(MouseEvent e) {
			}
		});

		dstFileIconLabel.addMouseListener(new MouseListener() {
			public void mouseClicked(MouseEvent e) {
				//Call FileCHooser
				JFileChooser fc = new JFileChooser(new File("."));
				fc.setDialogTitle(dstFileChooserDialogString);
				if(fc.showOpenDialog(((JLabel)e.getSource()).getRootPane())
					== JFileChooser.APPROVE_OPTION) {
					dstFile = fc.getSelectedFile();
					dstFileLabel.setText(dstFile.getName());
				}
			}
			public void mouseEntered(MouseEvent e) {
				if(dstFile == null) {
					((JLabel)e.getSource()).setIcon(fileIconFocused);
				}


			}
			public void mouseExited(MouseEvent e) {
				if(dstFile == null) {
					((JLabel)e.getSource()).setIcon(fileIcon);
				}
			}
			public void mousePressed(MouseEvent E) {
			}
			public void mouseReleased(MouseEvent e) {
			}
		});

		gbc.gridx = 0;
		gbc.gridy = 0;
		gbc.gridwidth = 1;
		gbc.gridheight = 1;
		gbc.weightx = 0.1;
		gbc.weighty = 0.5;
		//gbc.insets = new Insets(40, 10, 0, 10);
		fileSelectPanel.add(srcFileIconLabel, gbc);
		//fileSelectPanel.add(new JButton("Test"), gbc);

		gbc.gridx = 1;
		gbc.gridy = 0;
		gbc.gridwidth = 1;
		gbc.gridheight = 1;
		gbc.weightx = 0.2;
		gbc.weighty = 0.5;
		fileSelectPanel.add(progressBar, gbc);

		gbc.gridx = 2;
		gbc.gridy = 0;
		gbc.gridwidth = 1;
		gbc.gridheight = 1;
		gbc.weightx = 0.1;
		gbc.weighty = 0.5;
		fileSelectPanel.add(dstFileIconLabel, gbc);

		gbc.gridx = 0;
		gbc.gridy = 1;
		gbc.gridwidth = 1;
		gbc.gridheight = 1;
		gbc.weightx = 0.1;
		gbc.weighty = 0.05;
		//gbc.insets = new Insets(0, 0, 40, 0);
		JLabel srcFileLabel_inner = new JLabel(srcFileString);
		srcFileLabel_inner.setHorizontalAlignment(SwingConstants.CENTER);
		fileSelectPanel.add(srcFileLabel_inner, gbc);

		gbc.gridx = 2;
		gbc.gridy = 1;
		gbc.gridwidth = 1;
		gbc.gridheight = 1;
		gbc.weightx = 0.1;
		gbc.weighty = 0.05;
		JLabel dstFileLabel_Inner = new JLabel(dstFileString);
		dstFileLabel_Inner.setHorizontalAlignment(SwingConstants.CENTER);
		fileSelectPanel.add(dstFileLabel_Inner, gbc);

		gbc.gridx = 0;
		gbc.gridy = 2;
		fileSelectPanel.add(srcFileLabel, gbc);

		gbc.gridx = 2;
		fileSelectPanel.add(dstFileLabel, gbc);


	}

	private void initPasswordPanel() {
		//init passwordPanel
		passwordPanel.setBorder(new TitledBorder(passwordString));


		//init encryButton
		RunButtonActionListener ale =
			new RunButtonActionListener(UI.ENCRYPT);
		encryButton.addActionListener(ale);

		RunButtonActionListener ald =
			new RunButtonActionListener(UI.DESCERPT);
		descryButton.addActionListener(ald);

		passwordPanel.setLayout(new GridBagLayout());
		GridBagConstraints gbc = new GridBagConstraints();

		JPanel buttonPanel = new JPanel();
		buttonPanel.setLayout(new GridBagLayout());
		gbc.insets = new Insets(5, 0, 5, 0);
		gbc.gridx = 0;
		gbc.gridy = 0;
		buttonPanel.add(encryButton, gbc);
		gbc.gridy = 1;
		buttonPanel.add(descryButton, gbc);


		gbc.insets = new Insets(0, 10, 0, 10);
		gbc.gridx = 0;
		gbc.gridy = 0;
		gbc.weightx = 0.1;
		passwordPanel.add(new JLabel(passwordString), gbc);
		
		gbc.gridx = 1;
		gbc.gridy = 0;
		gbc.weightx = 0.3;
		passwordPanel.add(passwordField, gbc);

		gbc.gridx = 2;
		gbc.gridy = 0;
		gbc.weightx = 0.1;
		//passwordPanel.add(encryButton, gbc);
		passwordPanel.add(buttonPanel, gbc);

		
	}


	private void initLayout() {
		setLayout(new GridBagLayout());
		GridBagConstraints gbc = new GridBagConstraints();
		//Global Setting
		gbc.insets = new Insets(20, 10, 20, 10);
		gbc.fill = GridBagConstraints.BOTH;

		gbc.gridx = 0;
		gbc.gridy = 0;
		gbc.gridwidth = 1;
		gbc.gridheight = 2;
		gbc.weightx = 0.1;
		gbc.weighty = 0.1;
		gbc.ipadx = 10;
		//gbc.ipady = 150;
		add(radioButtonPanel, gbc);

		gbc.gridx = 1;
		gbc.gridy = 0;
		gbc.gridwidth = 1;
		gbc.gridheight = 1;
		gbc.weightx = 0.2;
		gbc.weighty = 0.1;
		//gbc.ipadx = 100;
		//gbc.ipady = 100;
		add(fileSelectPanel, gbc);

		gbc.gridx = 1;
		gbc.gridy = 1;
		gbc.gridwidth = 1;
		gbc.gridheight = 1;
		gbc.weightx = 0.2;
		gbc.weighty = 0.1;
		//gbc.ipadx = 100;
		//gbc.ipady = 40;
		add(passwordPanel, gbc);
	}

	private class RadioButtonPanel extends JPanel {
		RadioButtonPanel() {
			//init Radio Buttons
			JRadioButton desButton =
				new JRadioButton(desString);
			desButton.setMnemonic(KeyEvent.VK_D);
			desButton.setActionCommand(desString);
			desButton.setSelected(true);

			JRadioButton aesButton = 
				new JRadioButton(aesString);
			aesButton.setMnemonic(KeyEvent.VK_A);
			aesButton.setActionCommand(aesString);

			JRadioButton rc4Button = 
				new JRadioButton(rc4String);
			rc4Button.setMnemonic(KeyEvent.VK_R);
			rc4Button.setActionCommand(rc4String);

			//Group the radion Buttons
			ButtonGroup group = new ButtonGroup();
			group.add(desButton);
			group.add(aesButton);
			group.add(rc4Button);

			//create Action Listener;
			ActionListener al = new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					cryptionAlgorithm = e.getActionCommand();
					//TODO
					//Reserved to do some other thing
				}
			};

			//Register listeners
			desButton.addActionListener(al);
			aesButton.addActionListener(al);
			rc4Button.addActionListener(al);

			//SetLayout
			setLayout(new GridLayout(0, 1));
			add(desButton);
			add(aesButton);
			add(rc4Button);
		}
	}

	private class RunButtonActionListener implements ActionListener {
		private int type;
		public RunButtonActionListener(int type) {
			super();
			this.type = type;
		}

		@Override
			public void actionPerformed(ActionEvent e) {
				if(srcFile == null) {
					JOptionPane.showMessageDialog(
							((JButton)e.getSource()).getRootPane(),
							srcFileNotFoundMessageString,
							errTitle, 
							JOptionPane.ERROR_MESSAGE);
				} else if(dstFile == null) {
					JOptionPane.showMessageDialog(
							((JButton)e.getSource()).getRootPane(), 
							dstFileNotFoundMessageString,
							errTitle, 
							JOptionPane.ERROR_MESSAGE);
				} else if(passwordField.getText().length() == 0) {
					JOptionPane.showMessageDialog(null,
							passwordNullMessageString,
							errTitle, 
							JOptionPane.ERROR_MESSAGE);
				} else {

					EncryptRunnable encry =
						new EncryptRunnable(srcFile, dstFile, 
								passwordField.getText().getBytes(), 
								cryptionAlgorithm, 
								progressBar, 
								type);
					Thread encryThread = new Thread(encry);
					encryThread.start();
				}
			}
	}

	private class EncryptRunnable implements Runnable {
		private File src, dst;
		private byte[] key;
		private String algorithm;
		private JProgressBar jpb;
		private int type;

		EncryptRunnable(File src, File dst, byte[] key,
				String algorithm, JProgressBar progressBar, int type) {
			this.src = src;
			this.dst = dst;
			this.key = key;
			this.algorithm = algorithm;
			this.jpb = progressBar;
			this.type = type;
		}

		public void run() {
			//TODO
			if(type == 0) {
				//Encrypt
				Cypher.encry(src, dst, key, algorithm, jpb);
			} else {
				Cypher.descry(src, dst, key, algorithm, jpb);
			}
		}
	};


	public static void main(String[] args) { 
		new UI();
	}
}
