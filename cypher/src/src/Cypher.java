/*************************************************************************
  > File Name:     Cypher.java
  > Author:        Landerl Young
  > Mail:          LanderlYoung@gmail.com 
  > Created Time:  2013/6/15 23:24:59
 ************************************************************************/
import java.io.*;
import java.util.Arrays;
import javax.swing.*;

public class Cypher {
	private static final String desString = "Des";
	private static final String aesString = "Aes";
	private static final String rc4String = "Rc4";
	private static final String doneString =
		"<html><font color=\"red\">完成</font></html>";

	static {
		System.loadLibrary("Cypher");
	}

	/**Des*/
	public static native void desKeySetUp(byte[] key);
	public static native void desEncryption(byte[] message,
			byte[] cypher);

	public static native void desDecryption(byte[] message,
			byte[] cypher);

	/**AES*/
	public static native void aesKeySetUp(byte[] key);
	public static native void aesEncryption(byte[] message, byte[] cypher);
	public static native void aesDecryption(byte[] message, byte[] cypher);

	/**RC4*/
	public static native void rc4KeySetup(byte[] key);
	public static native byte rc4GenKey();

	private static void desEncryptFile(File src, File dst, 
			byte[] key, JProgressBar jpb) {

		byte[] realKey = new byte[8];
		if(key.length > 8) 
			realKey = Arrays.copyOf(realKey, 8);
		else if(key.length < 8) {
			for(int i = 0;i < 8; i++) {
				realKey[i] = key[i % key.length];
			}
		} else {
			realKey = key;
		}

		try {
			jpb.setMaximum((int)src.length());
			jpb.setMinimum(0);
			jpb.setValue(0);

			desKeySetUp(realKey);
			FileInputStream inFile = new FileInputStream(src);
			FileOutputStream outFile = new FileOutputStream(dst);
			int readSize;
			byte[] buf = new byte[8];
			byte[] cyp = new byte[8];

			while((readSize = inFile.read(buf)) != -1) {
				if(readSize == 8) {
					desEncryption(buf, cyp);
					outFile.write(cyp, 0, 8);
				} else {
					for(int i = 0; i < readSize; i++) {
						cyp[i] = (byte)(realKey[i] ^ buf[i]);
					}
					outFile.write(cyp, 0, readSize);
				}
				jpb.setValue(jpb.getValue() + readSize);
			}

			jpb.setValue((int)src.length());
			inFile.close();
			outFile.close();
		}catch (IOException e) {
			System.err.println(e);
		}
	}

	private static void desDecryptFile(File src, File dst, 
			byte[] key, JProgressBar jpb) {

		byte[] realKey = new byte[8];
		if(key.length > 8) 
			realKey = Arrays.copyOf(realKey, 8);
		else {
			for(int i = 0;i < 8; i++) {
				realKey[i] = key[i % key.length];
			}
		}

		try {
			jpb.setMaximum((int)src.length());
			jpb.setMinimum(0);
			jpb.setValue(0);
			desKeySetUp(realKey);
			FileInputStream inFile = new FileInputStream(src);
			FileOutputStream outFile = new FileOutputStream(dst);
			int readSize;
			byte[] buf = new byte[8];
			int bufSwitch = 0;
			byte[] msg = new byte[8];
			while((readSize = inFile.read(buf)) != -1) {
				if(readSize == 8) {
					desDecryption(msg, buf);
					outFile.write(msg, 0, 8);
				} else {
					for(int i = 0; i < readSize; i++) {
						msg[i] = (byte)(realKey[i] ^ buf[i]);
					}
					outFile.write(msg, 0, readSize);
				}
				jpb.setValue(jpb.getValue() + readSize);
			}
			jpb.setValue((int)src.length());
			inFile.close();
			outFile.close();
		}catch (IOException e) {
			System.err.println(e);
		}

	}

	private static void aesEncryptFile(File src, File dst, 
			byte[] key, JProgressBar jpb) {

		byte[] realKey = new byte[16];
		if(key.length > 16) 
			realKey = Arrays.copyOf(realKey, 16);
		else {
			for(int i = 0;i < 16; i++) {
				realKey[i] = key[i % key.length];
			}
		}

		try {
			jpb.setMaximum((int)src.length());
			jpb.setMinimum(0);
			jpb.setValue(0);
			aesKeySetUp(realKey);
			FileInputStream inFile = new FileInputStream(src);
			FileOutputStream outFile = new FileOutputStream(dst);
			int readSize;
			byte[] buf = new byte[16];
			byte[] cyp = new byte[16];
			while((readSize = inFile.read(buf)) != -1) {
				if(readSize == 16) {
					aesEncryption(buf, cyp);
					outFile.write(cyp, 0, 16);
				} else {
					for(int i = 0; i < readSize; i++) {
						cyp[i] = (byte)(buf[i] ^ realKey[i]);
					}
					outFile.write(cyp, 0, readSize);
				}
				jpb.setValue(jpb.getValue() + readSize);
			}
			jpb.setValue((int)src.length());
			inFile.close();
			outFile.close();
		}catch (IOException e) {
			System.err.println(e);
		}
	}
	private static void aesDecryptFile(File src, File dst, 
			byte[] key, JProgressBar jpb) {
		byte[] realKey = new byte[16];
		if(key.length > 16) 
			realKey = Arrays.copyOf(realKey, 16);
		else {
			for(int i = 0;i < 16; i++) {
				realKey[i] = key[i % key.length];
			}
		}

		try {
			jpb.setMaximum((int)src.length());
			jpb.setMinimum(0);
			jpb.setValue(0);
			aesKeySetUp(realKey);
			FileInputStream inFile = new FileInputStream(src);
			FileOutputStream outFile = new FileOutputStream(dst);
			int readSize;
			byte[] buf = new byte[16];
			int bufSwitch = 0;
			byte[] msg = new byte[16];
			while((readSize = inFile.read(buf)) != -1) {
				if(readSize == 16) {
					aesDecryption(msg , buf);
					outFile.write(msg, 0, 16);
				} else {
					for(int i = 0; i < readSize; i++) {
						msg[i] = (byte)(buf[i] ^ realKey[i]);
					}
					outFile.write(msg, 0, readSize);
				}
				jpb.setValue(jpb.getValue() + readSize);
			}
			jpb.setValue((int)src.length());
			inFile.close();
			outFile.close();
		}catch (IOException e) {
			System.err.println(e);
		}
	}

	private static void rc4EncANDDecFile(File src, File dst,
			byte[] key, JProgressBar jpb) {
		rc4KeySetup(key);
		try {
			jpb.setMaximum((int)src.length());
			jpb.setMinimum(0);
			jpb.setValue(0);
			FileInputStream inFile = new FileInputStream(src);
			FileOutputStream outFile = new FileOutputStream(dst);
			int readSize;
			byte[] buf = new byte[1024];
			byte[] cyp = new byte[1024];

			while((readSize = inFile.read(buf)) != -1) {
				for (int i = 0; i < readSize; i++) {
					cyp[i] = (byte)(buf[i] ^ rc4GenKey());
				}
				outFile.write(cyp, 0, readSize);
				jpb.setValue(jpb.getValue() + readSize);
			}
			jpb.setValue((int)src.length());
			inFile.close();
			outFile.close();
		} catch (IOException e) {
			System.err.println(e);
		}
	}


	public static void encry(File src, File dst, byte[] key, String algorithm, 
			JProgressBar jpb) {
		switch(algorithm) {
			case aesString:
				aesEncryptFile(src, dst, key, jpb);
				break;

			case desString:
				desEncryptFile(src, dst, key, jpb);
				break;

			case rc4String:
				rc4EncANDDecFile(src, dst, key, jpb);
				break;
		}
	}

	public static void descry(File src, File dst, byte[] key, String algorithm, 
			JProgressBar jpb) {
		switch(algorithm) {
			case aesString:
				aesDecryptFile(src, dst, key, jpb);
				break;

			case desString:
				desDecryptFile(src, dst, key, jpb);
				break;

			case rc4String:
				rc4EncANDDecFile(src, dst, key, jpb);
				break;
		}
	}

	public static void main(String[] args) { 

		/*
		 * test DES
		 */
		//byte[] m = new byte[]{
		byte[] m = new byte[]{0, 9, 8, 7, 6, 5, 4, 3,};
		byte[] c = new byte[8];
		byte[] k = new byte[]{8, 7, 3, 2, 1,43, 65, 76 };

		desKeySetUp(k);
		show(m, c, k);
		desEncryption(m, c);
		show(m, c, k);
		Arrays.fill(m, (byte)0);
		desKeySetUp(k);
		desDecryption(m, c);
		show(m, c, k);


		/*

		 *
		 * Test Aes
		 byte[] m = new byte[]{1, 2, 3, 4, 5,
		 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 15};
		 byte[] c;
		 byte[] k = new byte[]{0, 1, 2, 3,
		 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 1, 5};
		 show(m, null, k);
		 c = aesEncryption(m, k);
		 show(m, c, k);
		 m = aesDecryption(c, k);
		 show(m, c, k);
		 *

		 *
		 * Test Rc4
		 *
		 byte[] key = new byte[]{1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
		 rc4KeySetup(key);
		 long now = System.currentTimeMillis();
		 for(int i = 0; i < 100000; i ++) {
		 rc4GenKey();
		//System.out.print(rc4GenKey() + " ");
		 }
		 System.out.println(System.currentTimeMillis() - now);
		 */
		}
		static void show(byte[] m, byte[] c, byte[] k) {
			System.out.println("_________________________");
			System.out.println("M: " + Arrays.toString(m));
			System.out.println("C: " + Arrays.toString(c));
			System.out.println("K: " + Arrays.toString(k));
		}
	}

