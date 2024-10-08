# A. Длиннейшая чередующаяся подпоследовательность

Требование | Значение
--- | ---
Ограничение времени | 0.5 секунд
Ограничение памяти | 64Mb
Ввод | стандартный ввод или input.txt
Вывод | стандартный вывод или output.txt

Найдите наибольшую чередующуюся подпоследовательность ai1, ai2, …, aik последовательности , то есть такую подпоследовательность, для которой i1 < i2 < … < ik, любые два соседних элемента различны, и для любых трех соседних элементов ail - 1, ail, ail + 1 либо ail - 1 < ail, ail > ail + 1, либо ail - 1 > ail, ail < ail + 1, при этом k — наибольшее возможное.

## Формат ввода

В первой строке входного потока записано число n. Во второй строке записаны n (1 ≤ n ≤ 1000) целых чисел a1, a2, a3, …, an (|ai| ≤ 109).

## Формат вывода

В выходной поток выведите саму подпоследовательность . Если таких последовательностей несколько, то следует выбрать ту, для которой i1 минимально. Из всех максимальных с одинаковым i1 — ту, у которой значение i2 минимально и так далее.

## Примеры

Пример 1

```
Ввод
10
1 4 2 3 5 8 6 7 9 10
---
Вывод
1 4 2 8 6 7
```

Пример 2

```
Ввод
5
1 2 3 4 5
---
Вывод
1 2
```

Пример 3

```
Ввод
1
100
---
Вывод
100
```


# B. Правильная скобочная последовательность

Требование | Значение
--- | ---
Ограничение времени | 0.5 секунд
Ограничение памяти | 64Mb
Ввод | стандартный ввод или input.txt
Вывод | стандартный вывод или output.txt

Правильной скобочной последовательностью называется строка, состоящая только из скобок, в которой все скобки можно разбить на пары таким образом, что:

* в каждой паре есть левая и правая скобка, причем левая скобка расположена левее правой;
для любых двух пар скобок либо одна из них полностью внутри другой пары, либо промежутки между скобками в парах не пересекаются
* в паре с круглой скобкой может быть только круглая скобка, с квадратной — квадратная, с фигурной — фигурная

Примеры:

* Если разрешены только круглые скобки:
  * правильные последовательности: `(), (()), ()(), ()()(), (())(), ((()))`
  * неправильные последовательности: `)(, )), ((, ())()(, ()), ))((`
* Если разрешены круглые и квадратные скобки:
  * правильные последовательности: `[],(), [()], [[([])]()]`
  * неправильные последовательности: `[), ([)], (())()[]][`
* Если разрешены еще и фигурные скобки:
  * правильные последовательности: `[{(())}({})], []{}(), {}, (), []`
  * неправильные последовательности: `[{(})], [(]())]{}`

## Формат ввода

Во входе задана непустая строка  длины не более 1 000 000, состоящая только из скобок (круглых, квадратных и/или фигурных).

## Формат вывода

Требуется определить, является ли она правильной скобочной последовательностью. Если да, выведите слово CORRECT Если нет, выведите длину максимального префикса , который либо сам является правильной скобочной последовательностью, либо может быть продолжен до таковой.

## Примеры

Пример 1

```
Ввод
(())
---
Вывод
CORRECT
```

Пример 2

```
Ввод
([)]
---
Вывод
2
```

Пример 3

```
Ввод
(([{
---
Вывод
4
```

## Примечания

Например, для строки `(())))` ответ 4, так как строка `(())` является правильной скобочной последовательностью, а строку `(()))` уже нельзя никаким образом продолжить вправо, чтобы получить правильную скобочную последовательность. Для строки `]())(` ответ 0, поскольку строку ] нельзя продолжить вправо, чтобы получить правильную скобочную последовательность. Для строки `(()){()()}` ответ CORRECT.


# C. Минимальный максимум

Требование | Значение
--- | ---
Ограничение времени | 2 секунды
Ограничение памяти | 256Mb
Ввод | стандартный ввод или input.txt
Вывод | стандартный вывод или output.txt

Даны n нестрого возрастающих массивов Ai и m нестрого убывающих массивов Bj. Все массивы имеют одну и ту же длину l. Далее даны q запросов вида (i, j), ответ на запрос — такое k, что  минимален. Если таких k несколько, можно вернуть любое.

## Формат ввода

На первой строке числа n, m, l (1 ≤ n, m ≤ 900; 1 ≤ l ≤ 3 000). Следующие n строк содержат описания массивов Ai. Каждый массив описывается перечислением l элементов. Элементы массива — целые числа от 0 до 105 - 1. Следующие m строк описывают массивы Bj в таком же формате. Массивы и элементы внутри массива нумеруются с 1. На следюущей строке число запросов q (1 ≤ q ≤ n ⋅ m). Следующие q строк содержат пары чисел i, j (1 ≤ i ≤ n, 1 ≤ j ≤ m).

## Формат вывода

Выведите q чисел от 1 до l — ответы на запросы.

## Пример

```
Ввод
4 3 5
1 2 3 4 5
1 1 1 1 1
0 99999 99999 99999 99999
0 0 0 0 99999
5 4 3 2 1
99999 99999 99999 0 0
99999 99999 0 0 0
12
1 1
1 2
1 3
2 1
2 2
2 3
3 1
3 2
3 3
4 1
4 2
4 3
---
Вывод
3
4
3
5
4
3
1
4
3
4
4
4
```


# D. Минимальный накрывающий круг

Требование | Значение
--- | ---
Ограничение времени | 0.5 секунд
Ограничение памяти | 64Mb
Ввод | стандартный ввод или input.txt
Вывод | стандартный вывод или output.txt

На плоскости даны n точек с координатами (x1, y1), (x2, y2), …, (xn, yn). Необходимо накрыть по крайней мере k из них кругом с центром на оси Ox. Найдите наименьший возможный радиус такого круга с точностью до 10-3.

## Формат ввода

В первой строке входа даны числа n и k, 1 <= k <= n <= 10000. В следующих n строках — по два целых числа, координаты соотетствующей точки. Координаты не превосходят по модулю 1000.

## Формат вывода

Выведите радиус круга ровно с 6 знаками после запятой. Ваш ответ должен отличаться от правильного не более, чем на 10-3, вывести нужно при этом 6 знаков, чтобы избежать ошибок из-за округления.

## Примеры

Пример 1

```
Ввод
3 3
0 5
3 4
-4 -3
---
Вывод
5.000000
```

Пример 2

```
Ввод
3 2
0 1
2 1
1 100
---
Вывод
1.414246
```
