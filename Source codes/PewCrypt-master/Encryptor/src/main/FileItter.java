package main;

import java.io.File;
import java.util.ArrayList;

public class FileItter {

	/*
	 * Class constructor will iterate though target paths Function itterFiles
	 * recursively walks directory finding files Function getPaths to access paths
	 * found and encrypt-able
	 */

	private ArrayList<String> paths;
	private ArrayList<File> directory_paths;

	public FileItter(String[] paths) {

		this.paths = new ArrayList<String>();
		this.directory_paths = new ArrayList<File>();

		for (String path : paths) {
			System.out.println(path);
			File file = new File(path);

			if (file.isDirectory()) {
				// directory needs walking
				directory_paths.add(file);

			} else {

				// must be a file
				this.paths.add(path);
			}
		}

		this.itterFiles(this.directory_paths.toArray(new File[this.directory_paths.size()]));
	}

	private void itterFiles(File[] files) {
		try {
			for (File file : files) {
				//System.out.println(file.getPath());
				if (file.isDirectory()) {
					
					itterFiles(file.listFiles()); // recursion 

				} else {
					
					//if a file
					this.paths.add(file.getPath());
					
					
				}
			}

		} catch (NullPointerException e) {
			// when a folder is empty
			System.out.println(e);
		}
	}

	public ArrayList<String> getPaths() {
		return this.paths;
	}
}
