#include <config.h>
#include <display_manager.h>
#include <string.h>

static PT_DispOpr g_aptDispOprs[DISP_OPR_NUM];
static int g_iDispOprUsing;
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
/*  选择显示设备 */
int SelectDispOpr(char *pcName)
{
    int i;
    g_iDispOprUsing = -1;
    for(i = 0;i < DISP_OPR_NUM; i++)
    {
        if(g_aptDispOprs[i] && (strcmp(g_aptDispOprs[i]->name,pcName)== 0))
        {
            g_iDispOprUsing = i;
            return 0;
        }
    }
}
/* 获取设备 */
PT_DispOpr GetDispOpr(char *pcName)
{
    int i;
    for(i = 0;i < DISP_OPR_NUM; i++)
    {
        if(g_aptDispOprs[i] && (strcmp(g_aptDispOprs[i]->name,pcName)== 0))
        {
            return g_aptDispOprs[i];
        }
    }
    return NULL;
}
/**
 * 初始化显示设备
*/
int DisplayInit(void)
{
    int iError;
	
	iError = FBInit();

	return iError;
}