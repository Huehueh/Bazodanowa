#ifndef COLUMNNAMES_H
#define COLUMNNAMES_H

#include "enums.h"
#include <QString>
#include <map>

namespace ColumnNames {
std::map<Sprzedaz::eData, QString> sale{
    {Sprzedaz::KontrahentId, "Kontrahent"},
    {Sprzedaz::DowodSprzedazy, "Dowód sprzadaży"},
    {Sprzedaz::DataSprzedazy, "Data sprzadaży"},
    {Sprzedaz::DataWystawienia, "Data wystawienia"}};

std::map<Zakup::eData, QString> purchase{{Zakup::KontrahentId, "Kontrahent"},
                                         {Zakup::DowodZakupu, "Dowód zakupu"},
                                         {Zakup::DataZakupu, "Data zakupu"},
                                         {Zakup::DataWplywu, "Data wplywu"}};

std::map<MojaFirma::eData, QString> my_companies{
    {MojaFirma::Skrot, "Skrócona nazwa"},
    {MojaFirma::Nazwa, "Nazwa firmy"},
    {MojaFirma::NIP, "NIP"},
    {MojaFirma::Adres, "Adres firmy"},
    {MojaFirma::Email, "Adres mailowy"}};

std::map<Kontrahent::eData, QString> contractors{
    {Kontrahent::Nazwa, "Nazwa kontrahenta"},
    {Kontrahent::NIP, "NIP"},
    {Kontrahent::Pesel, "PESEL"}};
}; // namespace ColumnNames

#endif // COLUMNNAMES_H
