import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;

public class LoadLibrary
{
	public static boolean loadLibraryInJar(InputStream paramInputStream)
	{
		try
		{
			File localFile = File.createTempFile("ENC_YOUNG", ".lib");
			FileOutputStream localFileOutputStream = new FileOutputStream(localFile);

			byte[] arrayOfByte = new byte[1024];
			int i;
			while ((i = paramInputStream.read(arrayOfByte)) != -1) {
				localFileOutputStream.write(arrayOfByte, 0, i);
			}

			paramInputStream.close();
			localFileOutputStream.close();
			localFile.deleteOnExit();
			System.load(localFile.getAbsolutePath());
			return true;
		} catch (IOException localIOException) {
			return false;
		}
	}
}
