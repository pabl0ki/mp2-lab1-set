// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);

TBitField::TBitField(int len)
{
    if (len <= 0) throw len;
    BitLen = len;
    MemLen = (BitLen-1) / (8 * sizeof(TELEM)) + 1; // подумать над размером
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
    BitLen = 0;
    MemLen = 0;
    delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    if (n < 0 || n >= BitLen) throw 55;
    return n/(sizeof(TELEM)*8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    if (n < 0 || n >= BitLen) throw 55;
    TELEM res = 1;
    int idBit = n % (sizeof(TELEM) * 8);
    res <<= idBit;
    return res;   
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n >= BitLen || n < 0) throw 55;
    int ind = GetMemIndex(n);
    TELEM mask = GetMemMask(n);
    pMem[ind] |= mask;
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n >= BitLen || n < 0) throw 55;
    int ind = GetMemIndex(n);
    TELEM mask = GetMemMask(n);
    pMem[ind] &= ~mask;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n >= BitLen || n < 0) throw 55;
    int ind = GetMemIndex(n);
    TELEM mask = GetMemMask(n);
    int res = mask & pMem[ind];
    if (res) return 1;
    return 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if (this != &bf) {
        BitLen = bf.BitLen;
        if (MemLen != bf.MemLen) {
            MemLen = bf.MemLen;
            delete[] pMem;
            pMem = new TELEM[MemLen];
        }
        for (int i = 0; i < MemLen; i++) pMem[i] = bf.pMem[i];
    }
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (BitLen != bf.BitLen) return 0;
    for (int i = 0; i < MemLen-1; i++) {
        if (pMem[i] != bf.pMem[i]) return 0;
    }
    for (int i = (MemLen - 1) * sizeof(TELEM) * 8; i < BitLen; i++) {
        if (GetBit(i) != bf.GetBit(i)) return false;
    }
    return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    return !(*this == bf);
}

TBitField TBitField::operator|(TBitField& bf)
{
    int maxlen = (BitLen > bf.BitLen) ? BitLen : bf.BitLen;
    TBitField res(maxlen);

    int minMem = (MemLen < bf.MemLen) ? MemLen : bf.MemLen;
    for (int i = 0; i < minMem; i++)
        res.pMem[i] = pMem[i] | bf.pMem[i];

    const TBitField& longer = (MemLen > bf.MemLen) ? *this : bf;
    for (int i = minMem; i < longer.MemLen; i++)
        res.pMem[i] = longer.pMem[i];

    return res;
}

TBitField TBitField::operator&(TBitField &bf) // операция "и"
{
    int maxlen = (BitLen > bf.BitLen) ? BitLen : bf.BitLen;
    TBitField res(maxlen);

    int minMem = (MemLen < bf.MemLen) ? MemLen : bf.MemLen;
    for (int i = 0; i < minMem; i++)
        res.pMem[i] = pMem[i] & bf.pMem[i];
    return res;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField res(BitLen);
    for (int i = 0; i < MemLen - 1; i++) {
        res.pMem[i] = ~pMem[i];
    }
    for (int i = (MemLen - 1) * sizeof(TELEM) * 8; i < BitLen; i++) {
        if (GetBit(i)) res.ClrBit(i);
        else res.SetBit(i);
    }
    return res;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    char bit;
    int i = 0;
    istr >> bit;
    while (bit == '0' || bit == '1') {
        if (bit == '0') bf.ClrBit(i);
        else bf.SetBit(i);
        i++;
        istr >> bit;
    }
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for (size_t i = 0; i < bf.BitLen; i++)
    {
        ostr << bf.GetBit(i);
    }
    return ostr;
}
