/***************************************************************************************
* Copyright (C) 2018 Tinashe Mutandagayi                                               *
*                                                                                      *
* This file is part of the MT-Operating System source code. The author(s) of this file *
* is/are not liable for any damages, loss or loss of information, deaths, sicknesses   *
* or other bad things resulting from use of this file or software, either direct or    *
* indirect.                                                                            *
* Terms and conditions for use and distribution can be found in the license file named *
* LICENSE.TXT. If you distribute this file or continue using it,                       *
* it means you understand and agree with the terms and conditions in the license file. *
* binding this file.                                                                   *
*                                                                                      *
* Happy Coding :)                                                                      *
****************************************************************************************/

#include <stdio.h>

char filename[128];
char rdbuffer[4097];
char input[16];
char xtmpfile[135];


char *cmtstr = "\
/***************************************************************************************\n\
* Copyright (C) 2018 Tinashe Mutandagayi                                               *\n\
*                                                                                      *\n\
* This file is part of the MT-Operating System source code. The author(s) of this file *\n\
* is/are not liable for any damages, loss or loss of information, deaths, sicknesses   *\n\
* or other bad things resulting from use of this file or software, either direct or    *\n\
* indirect.                                                                            *\n\
* Terms and conditions for use and distribution can be found in the license file named *\n\
* LICENSE.TXT. If you distribute this file or continue using it,                       *\n\
* it means you understand and agree with the terms and conditions in the license file. *\n\
* binding this file.                                                                   *\n\
*                                                                                      *\n\
* Happy Coding :)                                                                      *\n\
****************************************************************************************/\n\n";


char *asmstr = "\
;****************************************************************************************\n\
;* Copyright (C) 2018 Tinashe Mutandagayi                                               *\n\
;*                                                                                      *\n\
;* This file is part of the MT-Operating System source code. The author(s) of this file *\n\
;* is/are not liable for any damages, loss or loss of information, deaths, sicknesses   *\n\
;* or other bad things resulting from use of this file or software, either direct or    *\n\
;* indirect.                                                                            *\n\
;* Terms and conditions for use and distribution can be found in the license file named *\n\
;* LICENSE.TXT. If you distribute this file or continue using it,                       *\n\
;* it means you understand and agree with the terms and conditions in the license file. *\n\
;* binding this file.                                                                   *\n\
;*                                                                                      *\n\
;* Happy Coding :)                                                                      *\n\
;****************************************************************************************\n\n";


char *asmextensions[] = {".asm", ".inc", ".as", ".8", ".s", ".hpp"};

void comment(char *filename) {

	int bDotH = 0;

	strcpy(xtmpfile, filename);
	strcat(xtmpfile,".tmp");
	
	printf("%s", xtmpfile);
	rename(filename, xtmpfile);
		
	char *cmtSrc = cmtstr;
	for (int c = 0; c < 6; c++) {
		if (strstr(filename, asmextensions[c]) == 0) continue;
		cmtSrc = asmstr;
	}
		
	
	FILE *newout = fopen(filename, "w+");
	FILE *tmpf = fopen(xtmpfile, "r");

	char *period = strchr(filename, '.');
	if (period && period[1] == 'h') {
		if ( (period[2] == 'x' && period[3] == 'x') || period[2] == 0) {
			fwrite("#pragma once\n\n", 1, strlen("#pragma once\n\n"), newout);
			bDotH = 1;
		}
		
	}
	
	if (strstr(filename, ".php\0") != 0) {
		fwrite("<?php\n\n", 1, strlen("<?php\n\n"), newout ); 
	}

	fwrite(cmtSrc, strlen(cmtSrc),1, newout);

	if (strstr(filename, ".php\0") != 0) {
		fwrite("?>\n\n", 1, strlen("?>\n\n"), newout ); 
	}
	
	while (!feof(tmpf)) {
		rdbuffer[0] = 0;
		if (0==fgets(rdbuffer, 4095, tmpf)) break;
		char *prag = strstr(rdbuffer, "#pragma once");
		if ( ( prag!= 0) && bDotH > 0) {
//			printf("PRAGFIX!:%s",prag);
			continue;
		}
		else {
//			printf("--%s", rdbuffer);
			fputs(rdbuffer, newout);
		}
	}
	
	fclose(tmpf);
	fclose(newout);
}

int main(int args, char *argv[]) {

	FILE *finput = fopen("comments.txt","r");
	int bDontPrompt = 0;
	
	rdbuffer[4096] = 0;
	printf("\n\Hello World!\r\n");
	printf("Comy (C) 2018, Tinashe Mutandagayi\r\n");
	printf("Add copyright or comments to source code\n\n");
	
	if (strcmpi(argv[1], "/y") == 0) bDontPrompt = 1;
	
	printf("Automode:%s\n", bDontPrompt ? "yes":"no");
//	return 0;
	while (!feof(finput)) {
		int n = fgets(&filename[0], 128, finput);
		FILE *fout;
		int e = 0;

		while (filename[e] != 0) {

			if (filename[e] < 32) {
				filename[e] = 0;
				break;
			}
			e++;

		}


		if (n > 0) {
			
			printf("FILE: {{%s}}", filename);

			if (!bDontPrompt) {

				fout = fopen(&filename[0], "a+");
				
				if (fout == 0) continue;

				printf("Dump:\n===========================================\n\n");
				
				fseek(fout, 0, SEEK_SET);

				for (int c=0;c < 10; c++) {

					int nb = fgets(rdbuffer, 4096, fout);
					if (nb == 0) break;
					printf("%s", rdbuffer);

				}

				printf("==================================================================== \n\nDo you want to patch? Y/N ESC = Exit :");
				gets(input);
				input[0] = toupper(input[0]);
				input[1] = 0;
	//			printf("%s\n",input);

				fclose(fout);
			}
			if (bDontPrompt || input[0] == 'Y') {
				printf("  Commenting....");
				comment(filename);
				printf("Done!\n");
			}

		}
	}
}