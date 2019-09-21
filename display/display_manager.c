#include <config.h>
#include <display_manager.h>
#include <string.h>

static PT_DispOpr g_aptDispOprs[DISP_OPR_NUM];

/* 注册显示设备 */
int RegisterDispOpr(PT_DispOpr ptDispOpr)
{
    int i;
    for(i = 0;i < DISP_OPR_NUM;i++)
    {
        if(g_aptDispOprs[i] == NULL)
        {
            break;
        }
    }
    if(i >= DISP_OPR_NUM)
    {
        printf("can't registerDispOpr, it is full\n");
        return -1;
    }
    else{
        g_aptDispOprs[i] = ptDispOpr;
    }
    return 0;

}
/* 打印所有显示设备 */
void ShowDispOpr(void)
{
    int i;
    for(i = 0;i < DISP_OPR_NUM ;i++ )
    {
        if(g_aptDispOprs[i] != NULL)
        {
            printf("%02d %s\n", i, g_aptDispOprs[i]->name );
        }
    }

}
int SelectDispOpr(char *pcName)
{
    int i;
    for(i = 0;i < DISP_OPR_NUM; i++)
    {
        
    }
}
int FBInit(void)
{
    int i_Error;

    return i_Error;
}