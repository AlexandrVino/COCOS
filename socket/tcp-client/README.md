Программе передаются два аргумента: строка с IPv4-адресом в стандартной десятичной записи (четыре числа, разделенные точкой), и номер порта.

Программа должна установить соединение с указанным сервером, после чего читать со стандартного потока ввода целые знаковые числа в текстовом формате, и отправлять их в бинарном виде на сервер.

Порядок байт - Little Endian.

В ответ на каждое полученное число, сервер отправляет целое число (в таком же формате), и все эти числа необходимо вывести на стандартный поток вывода в текстовом виде.

Если сервер по своей инициативе закроет соединение, то нужно завершить работу с кодом возврата `0`.
