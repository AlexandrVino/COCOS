# Find substrings in file

Программе передаются два аргумента: имя файла, и строка для поиска.

Необходимо найти все вхождения строки в текстовом файле, используя отображение на память с помощью системного вызова mmap.

На стандартный поток вывода вывести список всех позиций (с нуля) в файле, где втречаются строка.