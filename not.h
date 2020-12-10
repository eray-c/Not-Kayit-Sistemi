#ifndef NOT_H
#define NOT_H

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

extern int sayi;
extern Ogrenci ogrenci[];

int sayiOku();
void ogrenciOku(Ogrenci[] ,int );
void notEkle(Ogrenci[] ,int );
void notGoruntule(Ogrenci[] ,int );
void ekle(Ogrenci[] ,int );
void sil(Ogrenci[] ,int );
int sorgu(Ogrenci[] , int);
void sayiGuncelle(int );
void ogrGuncelle(Ogrenci[] ,int );

#endif /* NOT_H */

