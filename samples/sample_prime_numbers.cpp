// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// sample_prime_numbers.cpp - Copyright (c) Гергель В.П. 20.08.2000
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Тестирование битового поля и множества

#include <iomanip>

// #define USE_SET // Использовать класс TSet,
                // закоментировать, чтобы использовать битовое поле

#ifndef USE_SET // Использовать класс TBitField

#include "tbitfield.h"

int main()
{
  int n, m, k, count;

  setlocale(LC_ALL, "Russian");
  cout << "Тестирование программ поддержки битового поля" << endl;
  cout << "             Решето Эратосфена" << endl;
  cout << "Введите верхнюю границу целых значений - ";
  cin  >> n;
  TBitField s(n + 1);
  // заполнение множества
  for (m = 2; m <= n; m++)
    s.SetBit(m);
  // проверка до sqrt(n) и удаление кратных
  for (m = 2; m * m <= n; m++)
    // если m в s, удаление кратных
    if (s.GetBit(m))
      for (k = 2 * m; k <= n; k += m)
        if (s.GetBit(k))
          s.ClrBit(k);
  // оставшиеся в s элементы - простые числа
  cout << endl << "Печать множества некратных чисел" << endl << s << endl;
  cout << endl << "Печать простых чисел" << endl;
  count = 0;
  k = 1;
  for (m = 2; m <= n; m++)
    if (s.GetBit(m))
    {
      count++;
      cout << setw(3) << m << " ";
      if (k++ % 10 == 0)
        cout << endl;
    }
  cout << endl;
  cout << "В первых " << n << " числах " << count << " простых" << endl;
}
#else

#include "tset.h"

int main()
{
  int n, m, k, count;

  setlocale(LC_ALL, "Russian");
  cout << "Тестирование программ поддержки множества" << endl;
  cout << "              Решето Эратосфена" << endl;
  cout << "Введите верхнюю границу целых значений - ";
  cin  >> n;
  TSet s(n + 1);
  // заполнение множества
  for (m = 2; m <= n; m++)
    s.InsElem(m);
  // проверка до sqrt(n) и удаление кратных
  for (m = 2; m * m <= n; m++)
    // если м в s, удаление кратных
    if (s.IsMember(m))
      for (k = 2 * m; k <= n; k += m)
       if (s.IsMember(k))
         s.DelElem(k);
  // оставшиеся в s элементы - простые числа
  cout << endl << "Печать множества некратных чисел" << endl << s << endl;
  cout << endl << "Печать простых чисел" << endl;
  count = 0;
  k = 1;
  for (m = 2; m <= n; m++)
    if (s.IsMember(m))
    {
      count++;
      cout << setw(3) << m << " ";
      if (k++ % 10 == 0)
        cout << endl;
    }
  cout << endl;
  cout << "В первых " << n << " числах " << count << " простых" << endl;
}

#endif

/*
using namespace std;

int main()
{

    TBitField bf(10);
    cout << "Length = " << bf.GetLength() << endl;

    bf.SetBit(0);
    bf.SetBit(3);
    bf.SetBit(9);
    cout << "GetBit(0) = " << bf.GetBit(0) << endl;
    cout << "GetBit(1) = " << bf.GetBit(1) << endl;
    cout << "GetBit(3) = " << bf.GetBit(3) << endl;
    cout << "GetBit(9) = " << bf.GetBit(9) << endl;
    cout << "bf:" << bf << endl;

    bf.ClrBit(3);
    cout << "bf(3) = " << bf.GetBit(3) << endl;

    TBitField copy(bf);
    cout << "copy == bf : " << (copy == bf) << endl;

    TBitField bf2(5);
    bf2 = bf;
    cout << "bf2 == bf : " << (bf2 == bf) << endl;
    cout << "bf2 length = " << bf2.GetLength() << endl;

    TBitField bf3(10);
    bf3.SetBit(1);
    cout << "bf3 != bf : " << (bf3 != bf) << endl;

    cout << bf;
    return 0;
}
*/