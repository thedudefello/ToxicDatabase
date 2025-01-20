package main;

import java.util.Base64;

import javax.crypto.BadPaddingException;
import javax.crypto.Cipher;
import javax.crypto.IllegalBlockSizeException;
import javax.crypto.NoSuchPaddingException;
import javax.crypto.spec.SecretKeySpec;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.security.InvalidKeyException;
import java.security.Key;
import java.security.KeyFactory;
import java.security.NoSuchAlgorithmException;
import java.security.PrivateKey;
import java.security.spec.InvalidKeySpecException;
import java.security.spec.PKCS8EncodedKeySpec;

public class Decrypter {
	private String DEFAULT_RSA_KEY = "MIIEvQIBADANBgkqhkiG9w0BAQEFAASCBKcwggSjAgEAAoIBAQDThEl/fSuUgIAGJCfcLzmhk4/KmxhKqBCkVqAECRWii5DfGDI2Skkp7TrWMljBUwd4dnKjBlle0UFaOBAmq1GZLZmvfaEQfhm1qyMNkPkY+T6RuanZ5Y509I2Usxpy/ZKiwqX6Us5mCSMvPhHIf7dNk1pOtvS61Ds22frZ/esf6/jiLNo1MhlDBSEmRytr6hpoWgIEkEg12e4wmhlNVlruRZydrvVCa7dbSDfEo315wLbNniTJTB/aUifBn0JsTg56iem/bsZ7otuaC99Yd9Alnbs8T0C46jRoOJ7mRhn+VA5Jto1O+Qu7M4tMKp3VX1hVKggOh5P4vTJ1mRcAJp4/AgMBAAECggEAd16/A/4mLCbhGZYqEK9uPOvESLmC2g9DZRumLuDZnuRZHC7Rl6YQ6GKDxAKh6GjtXGSsiai5ozNBSKM/KjOhV2tOwqWJ0n74D3jHzY41poxzbVZ0rw5IeWTSykrR8Hd+2/AyL7Wv2hHqE21aJ+c8EcHJQ4cpUo8X4/rdAU219kr1R6BLhrwhW6kxc9lPr+J/CWAdclxJXcvapuRXx0ipPm9Jut5xETCq8GnrMjdysSFXPMA5aJP52hm9RvjzCIPGKR/nm2jJVMsbD2x0CV6HJByT6MfzTluSEf309vCKM2stEOoC/wrXBfBtc7TUfZ4ntS1vhwyJTkZUcFz4ZKhhsQKBgQDym3lNydsxj5TTKsFRuurgDXKLcYZcIiLlm+pefxSB7HTqXJsVfpLjp0NGiUmY1PVVVCGLZRC09KMSLN6qB1VBuEBnebsiIKSuGadAy4uiIzd4cORmDyj+DyCW5k4pnJ28tnYPYkvJoPjkZNkEf3n9HWFjxOMkOuZnfa1oCch+ewKBgQDfMXD7p7YlEZhxG+kNlK/GsnQhfdVATDbGOcy9euCYr0BeBJwhxXfsrrYi6ehqR+EnQ4e2zXGYrPxKm+TPCWh+tJiMOu3Y1mMUuAEJNm1Yjv3ewVAb1YxUK0XqF7Z7JRyL4bFztwIhMSu/R8Lx2FWykoRng2GgmhzR7TzlQer2DQKBgA7PoRM3rJMVAe/2X0D/GVG+YGzU7G/5gYnk/+Tu+zCHYAfiyXEBfjQ5xOisfvq+nY+tCDM7Y0641K/KX3mf4vuVJRFsJBmMRqF+XXCePJMUdVF8CuWULVt9Tu8HdmQh9JtNxF1iEeBoXGmNIpactbTXM1fk8D0I/4H38Ts1xbC7AoGAbXkhsr27MIll3SzUbc3dPbdwELFYtNXtE+Nr0hCAM0PabYMTVdk2jkfPnGZgkii5ffm4imhQbJOEl8/JNeemcmeAX1/UI8RcCuCJ2YvxrDtOuEDXWx+uWeZzv3NsFRDJ5K6JzHkaOU+V5pd7PgZfWlxVRzSA4TZWJn2XnddsOM0CgYEA2lv2ITPwzf+h9/WZdz0Cfi9ir/yAcOf81tqLY1Qfub6scU1tALA/fjQijuRgqBHkH2OXoxrYl4BREW4wUObBi6Hro2JlAhR1TmO3clRRsZ8DneKBAWnX044mtKzm3kMKSy5tZYqNNBYPejh/px3ka+MjCLMk4B0A9SWg8HObrAg=";
	private PrivateKey RSAKey;
	private Key AESKey;
	private Cipher cipher;

	public Decrypter(String AESKeyFile) {
		try {
			this.RSAKey = this.generateRSAKey(Base64.getDecoder().decode(DEFAULT_RSA_KEY));
			this.AESKey = decryptAESKey(Files.readAllBytes(new File(AESKeyFile).toPath()), this.RSAKey);

			this.cipher = Cipher.getInstance("AES");

			this.cipher.init(Cipher.DECRYPT_MODE, this.AESKey);

		} catch (NoSuchAlgorithmException | NoSuchPaddingException | InvalidKeyException | IllegalBlockSizeException
				| BadPaddingException | IOException | InvalidKeySpecException e) {
			e.printStackTrace();
			System.exit(-1);

		}
	}

	private static Key decryptAESKey(byte[] AESKey, Key RSAKey) throws InvalidKeyException, NoSuchAlgorithmException,
			NoSuchPaddingException, IllegalBlockSizeException, BadPaddingException {
		Cipher cipher = Cipher.getInstance("RSA");
		cipher.init(Cipher.DECRYPT_MODE, RSAKey);
		return (Key) new SecretKeySpec(cipher.doFinal(AESKey), "AES");

	}

	private PrivateKey generateRSAKey(byte[] rawKey) throws NoSuchAlgorithmException, InvalidKeySpecException {

		KeyFactory kf = KeyFactory.getInstance("RSA");
		return kf.generatePrivate(new PKCS8EncodedKeySpec(rawKey));

	}

	public boolean ProcessFile(String path) {
		try {
			// get handles
			File file = new File(path);

			// file checks
			if (!file.exists()) {
				System.out.println("File not found: " + path);
				return false;

			} else if (!file.canRead() | !file.canWrite() | (file.length() > 20000000)) {
				System.out.println("File conditions not satifified");
				return false;
			}

			// file content buffer
			byte[] fileContent = Files.readAllBytes(file.toPath());

			// encrypted data buffer
			byte[] outputBytes = this.cipher.doFinal(fileContent);

			// write encrypted data back to file
			Files.write(file.toPath(), outputBytes);

			String outPath = path.replace(".PewCrypt", "");

			file.renameTo(new File(outPath));

			System.out.println("Decryption Complete, Out: " + outPath);
			return true;

		} catch (IOException | BadPaddingException | IllegalBlockSizeException e) {

			e.printStackTrace();
			return false;
		}
	}

}
