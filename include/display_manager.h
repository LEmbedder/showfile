#ifndef _DISPLAY_MANAGER_H_
#define _DISPLAY_MANAGER_H_

typedef struct DispOpr {
	char *name;
	int iXres;
	int iYres;
	int iBpp;
	int (*DeviceInit)(void);
	int (*ShowPixel)(int iPenX, int iPenY, unsigned int dwColor);
	int (*CleanScreen)(void);
}T_DispOpr, *PT_DispOpr;

int RegisterDispOpr(PT_DispOpr ptDispOpr);
void ShowDispOpr(void);
int SelectDispOpr(char *pcName);
int DisplayInit(void);
int FBInit(void);

#endif