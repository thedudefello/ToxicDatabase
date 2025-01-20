package main;

public class Main {

	public static void main(String... args) { // args[0] = AES_key; args[1] = file_to_decrypt
		if (args.length <= 1) {
			System.out.println("Usage: Path_to_AES_key_file file_to_decrypt");
			System.out.println("Example Usage: \"C:\\Users\\user\\Desktop\\AES.key\" \"C:\\Users\\user\\Desktop\\file.txt.PewCrypt\"");
		} else {
			Decrypter d = new Decrypter(args[0]);
			d.ProcessFile(args[1]);
		}

	}
}
