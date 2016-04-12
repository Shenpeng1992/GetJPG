#include <QCoreApplication>
#include "stdio.h"
#include "gdal_priv.h"
#include "math.h"
#include "iostream"
#include "fstream"
#include <QImage>
#include <QDebug>

using namespace std;

void transfrom(int longitude, int latitude,
    int dx, int dy,
    float *memdata)
{
    FILE *fp;
    if ((fp = fopen("transform.txt", "w+")) == NULL)
    {
        printf("打开文件失败!");
        exit(1);
    }
    printf("%d\t", longitude);
    printf("%d\t", latitude);
    printf("%d", *memdata);
    printf("\n");
    /*int X, Y, Z;
    X = sin(longitude)*(25000 + *memdata);
    putc(X, fp);
    Z = sin(latitude)*(25000 + *memdata);
    putc(Z, fp);
    Y = cos(longitude)*(25000 + *memdata);
    putc(Y, fp);*/

}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    printf("Process running.");
    ofstream outfile("transform.txt",ios::out);
    if (!outfile)

    {
        cerr << "open error!" << endl;
        exit(1);
    }

    GDALAllRegister();
    const char *pszFile = "E:/Study/863apporach/terrian/Vesta_Dawn_HAMO_DTM_DLR_Global_48ppd_s16bit.tif";//打开图像
    GDALDataset *poDataset = (GDALDataset*)GDALOpen(pszFile, GA_ReadOnly);
    if (poDataset == NULL)
    {
        printf("File:%s不能打开！\n", pszFile);
        return 0;
    }
    GDALDataType dataType = poDataset->GetRasterBand(1)->GetRasterDataType();//图像数据格式
    GDALRasterBand *poBand = poDataset->GetRasterBand(1);


    int nImgSizeX, nImgSizeY;
    int nBufferSizeX, nBufferSizeY;
    double *memdata;
    nImgSizeX = poDataset->GetRasterXSize();//获得图像长度
    nImgSizeY = poDataset->GetRasterYSize();//获得图像宽度
    printf("%d\t", nImgSizeX);
    printf("%d\n", nImgSizeY);
    double geotransform[6];
    poDataset->GetGeoTransform(geotransform);
    double  Imgdx = geotransform[1];//像元宽度
    double  Imgdy = geotransform[5];//像元高度
    printf("%lf\t", Imgdx);
    printf("%lf\n", Imgdy);

    int X = 100;
    int Y = 100;

    QImage img(X,Y,QImage::Format_RGB888);

    int temp = 0, MAX = 30767, MIN = 15848;

    for (int j = 0; j < Y; j++)
    for (int i = 0; i < X; i++)
    {
        short int * memdata = new short int[1];
        unsigned char imedata;

        poBand->RasterIO(GF_Read, 8000+i, 3500+j, 1 , 1, memdata, 1, 1, dataType, 0, 0);
        outfile << *memdata << "\t";

        imedata = ((double(*memdata - MIN+1) / (MAX - MIN)) * 255);
        qDebug()<<QStringLiteral("行")<<j<<QStringLiteral("列")<<i<<"gray"<<imedata;

        img.setPixel(i,j,qRgb(imedata,200,0));
    }

    img.save("temp.jpg","JPG");

    printf("%d\t", MAX);
    printf("%d", MIN);

    printf("完！\n");
    getchar();
    GDALClose((GDALDatasetH)poDataset);
    return a.exec();
}
