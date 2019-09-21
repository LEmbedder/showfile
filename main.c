#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(int argc,char *argv[])
{
    int i_Error = -1;
    unsigned int font_size = 16;
    char acHzkFile[128];
	char acFreetypeFile[128];
	char acTextFile[128];

    while((i_Error = getopt(argc,argv,"s:f:h:") != -1))
    {
        switch(i_Error)
        {
            case 's':
            {
                font_size = strtoul(optarg,NULL,0);
            }break;

            case 'f':
            {
                strncpy(acHzkFile,optarg,128);
                acHzkFile[127] = '\0';
            }break;

            case 'h':
            {
                strncpy(acFreetypeFile,optarg,128);
                acFreetypeFile[127] = '\0';
            }break;

            default:
            {
                printf("Usage: %s [-s size] [-f font_file] [-h HZK] <text_file>\n",argv[0]);
                return -1;
            }break;

        }
    }
    if(optind >= argc )
    {
        printf("Usage: %s [-s size] [-f font_file] [-h HZK] <text_file>\n",argv[0]);
        return -1;
    }
    /*文件名称*/
    strncpy(acTextFile,argv[optind],128);
    acTextFile[127] = '\0';
    /*显示初始化*/
    

    return 0;

}