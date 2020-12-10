#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "not.h"

int sayiOku() {
    /*Sistemde kaç tane öğrenci kayıtlı olduğunu sayi.txt dosyasından okuyoruz.*/
    int sayi1;
    FILE* sayiPtr = NULL;
    sayiPtr = fopen("sayi.txt","r");
    if(sayiPtr==NULL) {
        printf("\nSayi listesine ulaşılamadı!\n");
        return 0;
    }
    fscanf(sayiPtr, "%d", &sayi1);
    fclose(sayiPtr);
    
    return sayi1;
}
void ogrenciOku(Ogrenci ogrenci[],int sayi) {
    /*Sistemde kayıtlı olan öğrencilerin listesini ogrenci.txt dosyasından ogrenci dizisine aktarıyoruz.*/
    FILE* filePtr = NULL;
    filePtr = fopen("ogrenci.txt","r");
    if(filePtr==NULL) {
        printf("\nÖğrenci listesine ulaşılamadı!\n");
        return;
    }
    int i;
    for(i=0; i<sayi; i++) {
        fscanf(filePtr, "%s %s %s %s %s %d %d %d",ogrenci[i].num,ogrenci[i].tc,ogrenci[i].ad,ogrenci[i].soyad,ogrenci[i].sinif,&ogrenci[i].sinav1,
                &ogrenci[i].sinav2,&ogrenci[i].sinav3);
    }
    fclose(filePtr);
}
void notEkle(Ogrenci ogrenci[],int sayi) {
    printf("\n[NOT EKLEME EKRANI]\n");
    char num[12];
    char secim;
    int ara,vize,finnal;
    int sira = sorgu(ogrenci,sayi);
    
    if(sira>-1) {
        /*Hangi sınavın notu girileceğini belirliyoruz.*/
    printf("\n1. Ara Sınav\n");
    printf("2. Vize\n");
    printf("3. Final\n");
    printf("Yapmak istediğiniz işlemi seçiniz : ");
    scanf("%c",&secim);
    switch(secim) {
        case '1':
            printf("Sınav notunu giriniz : ");
            scanf("%d",&ara);
            ogrenci[sira].sinav1 = ara;
            break;
        case '2':
            printf("Vize notunu giriniz : ");
            scanf("%d",&vize);
            ogrenci[sira].sinav2 = vize;
            break;
        case '3':
            printf("Final notunu giriniz : ");
            scanf("%d",&finnal);
            ogrenci[sira].sinav3 = finnal;
            break;
        default:
            printf("Lütfen geçerli bir işlem seçiniz!\n");
            break;
    }    
    } else
        printf("\nÖğrenci bulunamadı.\n");
}
void notGoruntule(Ogrenci ogrenci[],int sayi) {
    printf("\n[NOT SORGULAMA EKRANI]\n");
    int sira = sorgu(ogrenci,sayi);
    if(sira>-1) {
        printf("Öğrenci Adi : %s\n",ogrenci[sira].ad);
        printf("Öğrenci Soyadi : %s\n",ogrenci[sira].soyad);
        printf("Öğrenci Numarasi : %s\n",ogrenci[sira].num);
        printf("Ara Sinav : %d Vize : %d Final : %d\n",ogrenci[sira].sinav1,ogrenci[sira].sinav2,ogrenci[sira].sinav3);
    } else
         printf("Kayit bulunamadi.\n");    
}
void ekle(Ogrenci ogrenci[],int sayi) {
    printf("\n[ÖĞRENCİ KAYIT EKRANI]\n");
    sayi++;
    Ogrenci* ptr = ogrenci;
    ptr = realloc(ptr, sayi * sizeof(Ogrenci));
    
    printf("Öğrencinin adını giriniz : ");
    scanf("%s",ogrenci[sayi-1].ad);
    printf("Öğrencinin soyadını giriniz : ");
    scanf("%s",ogrenci[sayi-1].soyad);
    printf("Öğrencinin TC sini giriniz : ");
    scanf("%s",ogrenci[sayi-1].tc);
    printf("Öğrencinin numarasını giriniz : ");
    scanf("%s",ogrenci[sayi-1].num);
    printf("Öğrencinin sınıfını giriniz : ");
    scanf("%s",ogrenci[sayi-1].sinif);
    ogrenci[sayi-1].sinav1,ogrenci[sayi-1].sinav2,ogrenci[sayi-1].sinav3 = 0;
    printf("Kayit başarıyla oluşturulmuştur.\n");
    free(ptr);
    sayiGuncelle(sayi);
    ogrGuncelle(ogrenci,sayi);
}
void sil(Ogrenci ogrenci[],int sayi) {
    printf("\n[KAYIT SİLME EKRANI]\n");
    Ogrenci* filePtr;
    int sira = sorgu(ogrenci,sayi);
    if(sira>-1) {
        /*Pointer'ın adresine silinecek öğrencinin olduğu indise kadar atıyoruz. Sonra atanan kısmı bir azaltıyoruz.*/
        filePtr = &ogrenci[sira];
        *filePtr = ogrenci[sayi-1];
        sayi--;
        printf("Kayıt silme işlemi başarıyla gerçekleştirildi.\n");
    } else
        printf("Geçerli bir öğrenci numarası giriniz!\n");
    sayiGuncelle(sayi);
    ogrGuncelle(ogrenci,sayi);
}
int sorgu(Ogrenci ogrenci[],int sayi) {
    /*Kullanıcıdan öğrenci numarasını okuyup ogrenci dizisindeki öğrenci numaralarıyla karşılaştırıyoruz.Girilen numara sistemde kayıtlıysa
     numaranın bulunduğu indisi döndürüyoruz.Kayıtlı değilse -1 değerini döndürüyoruz.*/
    int i;
    char num[12];
    
    printf("Öğrencinin numarasını giriniz : ");
    scanf("%s",num);
    for(i=0; i<sayi; i++) {
        if(strcmp(ogrenci[i].num,num)==0) {
            return i;
        }
    }
    return -1;
}
void sayiGuncelle(int sayi) {
    /*Tüm işlemler sonrasında sayi.txt dosyasındaki değeri güncelliyoruz.*/
    FILE* filePtr = NULL;
    filePtr = fopen("sayi.txt","w+");
    if(filePtr==NULL) {
        printf("Sayi listesi bulunamadi.");
        return;
    }
    fprintf(filePtr,"%d",sayi);
    fclose(filePtr);
}
void ogrGuncelle(Ogrenci ogrenci[],int sayi) {
    /*Tüm işlemler sonrasında ogrenci.txt dosyasındaki öğrenci listesini güncelliyoruz.*/
    FILE* filePtr = NULL;
    filePtr = fopen("ogrenci.txt","w+");
    if(filePtr==NULL) {
        printf("Öğrenci listesi bulunamadi.");
        return;
    }
    int i;
    for(i=0; i<sayi; i++) {
        fprintf(filePtr,"%s %s %s %s %s %d %d %d",ogrenci[i].num,ogrenci[i].tc,ogrenci[i].ad,ogrenci[i].soyad,ogrenci[i].sinif,ogrenci[i].sinav1,
                ogrenci[i].sinav2,ogrenci[i].sinav3);
    }
    fclose(filePtr);
}
