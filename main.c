#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "not.h"

void menuYazdir();

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
                printf("Çıkış yapılıyor...");
                exit(0);
            default:
                printf("Lütfen geçerli bir işlem seçiniz!\n");
                break;
        }        
    }
    
    return 0;
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
