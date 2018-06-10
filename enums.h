#ifndef ENUMS_H
#define ENUMS_H

struct Sprzedaz {
  enum eData {
    Id,
    FirmaId,
    KontrahentId,
    DowodSprzedazy,
    DataSprzedazy,
    DataWystawienia,
    LiczbaKolumn

  };
};

struct Zakup {
  enum eData {
    Id,
    FirmaId,
    KontrahentId,
    DowodZakupu,
    DataZakupu,
    DataWplywu,
    LiczbaKolumn
  };
};

struct MojaFirma {
  enum eData { Id, Skrot, Nazwa, NIP, Adres, Email, LiczbaKolumn };
};

struct Kontrahent {
  enum eData { Id, Nazwa, NIP, Pesel, LiczbaKolumn };
};

#endif // ENUMS_H
