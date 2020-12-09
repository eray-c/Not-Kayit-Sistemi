#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

typedef struct {
    char num[12];
    char tc[12];
    char ad[20];
    char soyad[20];
    char sinif;
    int sinav1;
    int sinav2;
    int sinav3;
}Ogrenci;

void menuYazdir();
int sayiOku();
void ogrenciOku(Ogrenci[] ,int );
void notEkle(Ogrenci[] ,int );
void notGoruntule(Ogrenci[] ,int );
void ekle(Ogrenci[] ,int );
void sil(Ogrenci[] ,int );
int sorgu(Ogrenci[] , int);
void sayiGuncelle(int );
void ogrGuncelle(Ogrenci[] ,int );

int main(int argc, char** argv) {
    setlocale(LC_ALL, "Turkish");
    printf("---------------------------------------------\n");
    printf("           NOT KAYIT SİSTEMİ          \n");
    printf("---------------------------------------------\n");
    
    int sayi = sayiOku();
    Ogrenci ogrenci[sayi];
    ogrenciOku(ogrenci,sayi); 
    
    while(1) {
        char secim;
        menuYazdir();
        scanf("%c",&secim);
        switch(secim) {
            case '1':
                notEkle(ogrenci,sayi);
                break;
            case '2':
                notGoruntule(ogrenci,sayi);
                break;
            case '3':
                ekle(ogrenci,sayi);
                break;
            case '4':
                sil(ogrenci,sayi);
                break;
            case '0':
                free(ogrenci);
                printf("Çıkış yapılıyor...");
                exit(0);
            default:
                printf("Lütfen geçerli bir işlem seçiniz!\n");
                break;
        }        
    }
    sayiGuncelle(sayi);
    ogrGuncelle(ogrenci,sayi);
    
    return (EXIT_SUCCESS);
}
void menuYazdir() {
    printf("\n[ANA MENÜ]\n");
    printf("1. SINAV NOTU EKLE\n");
    printf("2. SINAV NOTU GÖRÜNTÜLE\n");
    printf("3. ÖĞRENCİ KAYIT EKLE\n");
    printf("4. ÖĞRENCİ KAYIT SİL\n");
    printf("0. ÇIKIŞ\n");
    printf("Yapmak istediğiniz işlemi seçiniz : ");
}
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
    ogrenci = realloc(ogrenci, sayi * sizeof(Ogrenci));
    
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
    filePtr = fopen("sayi.txt","w");
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
    filePtr = fopen("ogrenci.txt","w");
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