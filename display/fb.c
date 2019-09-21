#include <config.h>
#include <display_manager.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/fb.h>
#include <string.h>

static int FBDeviceInit(void);
static int FBShowPixel(int iX, int iY, unsigned int dwColor);
static int FBCleanScreen(void);

static int g_fd;
static struct fb_var_screeninfo g_tFBVar;
static struct fb_fix_screeninfo g_tFBFix;
static unsigned char *g_pucFBMem;
static unsigned int g_dwScreenSize;

static unsigned int g_dwLineWidth;
static unsigned int g_dwPixelWidth;

static T_DispOpr g_tFBOpration = {
    .name = "fb",
    .DeviceInit = FBDeviceInit,
    .ShowPixel = FBShowPixel,
    .CleanScreen = FBCleanScreen,
};

static int FBDeviceInit(void)
{
    int ret;
    g_fd = open(FB_DEVICE_NAME, O_RDWR);
    if (0 > g_fd)
    {
        DBG_PRINTF("can't open %s\n", FB_DEVICE_NAME);
        return -1;
    }
    ret = ioctl(g_fd, FBIOGET_VSCREENINFO, &g_tFBVar);
    if (0 > ret)
    {
        DBG_PRINTF("can't get fs's var\n");
        return -1;
    }
    ret = ioctl(g_fd, FBIOGET_FSCREENINFO, &g_tFBFix);
    if (0 > ret)
    {
        DBG_PRINTF("can't get fb's fix\n");
        return -1;
    }
    g_dwScreenSize = g_tFBVar.xres*g_tFBVar.yres*g_tFBVar.bits_per_pixel/8;
    g_pucFBMem = (unsigned char *)mmap(NULL , g_dwScreenSize, PROT_WRITE | PROT_READ,MAP_SHARED, g_fd, 0 );
    if(g_pucFBMem < 0)
    {
        DBG_PRINTF("can't mmap framebuff\n");
        return -1;
    }
    g_tFBOpration.iXres = g_tFBVar.xres;
    g_tFBOpration.iYres = g_tFBVar.yres;
    /* 一个像素多少位 */
    g_tFBOpration.iBpp = g_tFBVar.bits_per_pixel;

    /* 一行的数据大小 */
    g_dwLineWidth = g_tFBVar.xres*g_tFBVar.bits_per_pixel/8;
    /* 一个像素的大小 */
    g_dwPixelWidth = g_tFBVar.bits_per_pixel/8;

    
}
static int FBShowPixel(int iX, int iY, unsigned int dwColor)
{
    unsigned char * pucFB;
    unsigned short * pwFB16bpp;
    unsigned int * pdwFB32bpp;
    unsigned short wColor16bpp;
    int iRed;
    int iGreen;
    int iBlue;
    if((iX >= g_tFBVar.xres) || (iY >= g_tFBVar.yres))
    {
        DBG_PRINTF("out of region\n");
        return -1;
    }
    pucFB = g_pucFBMem + g_dwLineWidth * iY + g_dwPixelWidth * iX;
    pwFB16bpp = (unsigned short *)pucFB;
    pdwFB32bpp = (unsigned int *)pucFB;
    switch( g_tFBVar.bits_per_pixel )
    {
        case 8:{
            *pucFB = dwColor;
        }break;
        case 16:{

        }break;
        case 32:{

        }break;
    }

}
/* 清屏 */
static int FBCleanScreen(void)
{
    memset(g_pucFBMem, 0 ,g_dwScreenSize);
    return 0;
}

/* 初始化Framebuff */
int FBInit(void)
{
    return RegisterDispOpr(&g_tFBOpration);
}