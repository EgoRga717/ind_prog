// Find Number.cpp Вроде не крашится, если вводить че попало. Программа пытается убедить пользователя вводить нормальные данные
//Сложность алгоритма О(n). Память 1 массив int размера N

#include <iostream>

#define MAX_NUMBER 100000000	//Максимально возможное M. C++ ругается в случае, если число элементов массива больше, чем int

bool isError = 0;	//Глобальная переменная, проверяет наличие ошибки

void cinInt(int &something, const int &inf, const int &sup)	//Функция ввода числа типа int. Проверяет, ввел ли пользователь корректные данные, и просит переввести в случае некорректности
{
	bool isCorrect = 0; //Своего рода флаг корректности или некорректности ввода. Изначально считаем ввод некорректным
	while (isCorrect == 0 && isError == 0)
	{
		std::cin >> something;
		if ((inf <= something) && (something <= sup) && (std::cin))	//Проверка соответсятвия допустимому интервалу и корректности ввода
			isCorrect = 1;	//все норм, можно вылезать из цикла
		else
		{
			std::cout << "Wrong input.\n";
			if (!std::cin) //Заклинание украл со STACKOVERFLOW. Фишка в очистке буфера ввода в случае, если пользователь вводит не число, а какую-то ерунду
			{
				std::cin.clear();  //Убираем флаг ошибки. Теперь состояние потока снова good
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Выкидываем все что ввел пользователь до конца строки
			}
			isError = 1;
		}
	}
}

void arrayInit(int& M, int array[])	//обнуляет элементы массива
{
	for (int i = 0; i < M; ++i)	//создаем последовательный массив от 0 до M
		array[i] = i;
}

void readNumbers(int& M, int& arraySize, int array[])  //ввод чисел массива array. В случае, если пользователь вводит ерунду, просто игнорируем
{
	int tmp;	//буферная переменная
	for (int i = 0; i < arraySize; ++i)
	{
		cinInt(tmp, 0, M - 1);
		array[tmp] = -1;	//число -1 будет своего роа индикатором, что это число есть во входной последовательности
	}
}

void writeNumbers(int& M, int array[])	//Вывод оставшихся чисел
{
	for (int i = 0; i < M; ++i)
		if (array[i] != -1)
			std::cout << array[i] << ' ';
}

int main()
{
	int M;
	int arraySize;
	int array[MAX_NUMBER];
	std::cout << "Enter numbers only. If you enter something other, the programm will ignore all after it in this string:\n";
	std::cout << "Enter M:\n";	//Вводим М
	cinInt(M, 1, MAX_NUMBER);
	
	std::cout << "Enter input array size:\n";	//Вводим arraySize
	cinInt(arraySize, 0, M);

	arrayInit(M, array);

	std::cout << "Enter numbers of array:\n";
	readNumbers(M, arraySize, array);

	std::cout << "Remaining numbers:\n";
	writeNumbers(M, array);
	if (isError)
	{
		std::cout << "\nERROR\n";
		return 1;
	}
	return 0;
}
