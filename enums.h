#ifndef ENUMS_H
#define ENUMS_H

struct Sprzedaz {
  enum eData {
    Id,
    FirmaId,
    KontrahentId,
    DowodSprzedazy,
    DataSprzedazy,
    DataWystawienia

  };
};

struct Zakup {
  enum eData { Id, FirmaId, KontrahentId, DowodZakupu, DataZakupu, DataWplywu };
};

struct MojaFirma {
  enum eData { Id, Skrot, Nazwa, NIP, Adres, Email };
};

struct Kontrahent {
  enum eData { Id, Nazwa, NIP, Pesel };
};

#endif // ENUMS_H
