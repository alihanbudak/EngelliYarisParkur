#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct
{
    int engelsayisi;
    int *engeldizi;
    int Parkurmetresi;
}
Parkur;
Parkur parkurbilgi;
int parkurUzunlukBelirle();
int parkurEngelSayisiBelirle();
void engelAtavesirala();
void XurvivorYarismasi_DosyayaYazma(Parkur parkurbilgileri);
int asalmi(int hp,int *engel);
int main()
{
    srand(time(NULL));
    parkurbilgi.Parkurmetresi = parkurUzunlukBelirle();
    parkurbilgi.engelsayisi = parkurEngelSayisiBelirle();
    parkurbilgi.engeldizi = (int*)malloc(sizeof(int)*parkurbilgi.engelsayisi);
    engelAtavesirala();
    XurvivorYarismasi_DosyayaYazma(parkurbilgi);
    return 0;
}
int parkurUzunlukBelirle()
{
    return 50+rand()%51;
}
int parkurEngelSayisiBelirle()
{
    return 2+rand()%4;
}
void engelAtavesirala()
{
    int i,j,gecici;
    for(i=0;i<parkurbilgi.engelsayisi;i++)
    {
        parkurbilgi.engeldizi[i] = 5 + rand()%(parkurbilgi.Parkurmetresi-4);
    }
    for(i=0;i<parkurbilgi.engelsayisi-1;i++)
        for(j=0;j<parkurbilgi.engelsayisi-1;j++)
            if(parkurbilgi.engeldizi[j] > parkurbilgi.engeldizi[j+1])
            {
                gecici=parkurbilgi.engeldizi[j];
                parkurbilgi.engeldizi[j]=parkurbilgi.engeldizi[j+1];
                parkurbilgi.engeldizi[j+1]=gecici;
            }
}
void XurvivorYarismasi_DosyayaYazma(Parkur parkurbilgileri)
{
    int k=0,hp=100;
    FILE *YarismaDosyasi;
    if((YarismaDosyasi=fopen("log.txt","w")) == NULL)
    {
        printf("Dosya acma hatasi!!! Dosya acilamadi\n");
        exit(1);
    }
    fputs("Yarisma Basladi !!!\n",YarismaDosyasi);
    fprintf(YarismaDosyasi,"Yarismaci HP = %d\n",hp);
    while(k < parkurbilgileri.engelsayisi)
    {
        if(asalmi(hp,&parkurbilgileri.engeldizi[k]) == 1)
        {
            fprintf(YarismaDosyasi,"Yarismaci %d. metreye kadar bir engel ile karsilasmadi\n",parkurbilgileri.engeldizi[k]);
            fprintf(YarismaDosyasi,"%d. metrede bir engel var.    %d ve %d aralarinda asaldir\n",parkurbilgileri.engeldizi[k],hp,parkurbilgileri.engeldizi[k]);
            hp = hp - parkurbilgileri.engeldizi[k];
            fprintf(YarismaDosyasi,"Yarismaci HP = %d\n",hp);
            if(hp<=0){
            fputs("Uzgunum!!! yarismayi tamamlayamadin\n",YarismaDosyasi);
            fclose(YarismaDosyasi);
            free(parkurbilgileri.engeldizi);
            exit(1);
            }
        }
        else
        {
            fprintf(YarismaDosyasi,"Yarismaci %d. metreye kadar bir engel ile karsilasmadi\n",parkurbilgileri.engeldizi[k]);
            fprintf(YarismaDosyasi,"%d. metrede bir engel var    %d ve %d aralarinda asal degildir\n",parkurbilgileri.engeldizi[k],hp,parkurbilgileri.engeldizi[k]);
            fprintf(YarismaDosyasi,"Yarismaci HP = %d\n",hp);
        }
      k++;
    }
    fprintf(YarismaDosyasi,"Yarismaci %d. metreye kadar bir engel ile karsilasmadi\n",parkurbilgileri.Parkurmetresi);
    fprintf(YarismaDosyasi,"Tebrikler!!! Yarismayi %d HP ile bitirdiniz",hp);
    free(parkurbilgileri.engeldizi);
    fclose(YarismaDosyasi);
}
int asalmi(int hp, int *engel)
{
    int j;
    int asallikdurumu = 1;
    for(j=2; j <=(*engel); j++)
    {
        if( (hp%j == 0) && (*engel%j == 0) )
        {
            asallikdurumu = 0;
        }
    }
    return asallikdurumu;
}
