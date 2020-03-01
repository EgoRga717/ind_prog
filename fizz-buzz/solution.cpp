// FizzBuzzV2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <string>

#define MAX_NUMBER 100000000
#define MAX_LONG_LONG_SIZE 9223372036854775807
#define MIN_LONG_LONG_SIZE (- MAX_LONG_LONG_SIZE - 1)

//Макрос, который уведомляет об ошибке в случае, если isError == 1
#define ERR(isError)				\
	if (isError)					\
	{ 								\
		std::cout << "\nERROR\n";	\
		return 1;					\
	}


//bool isError;

bool cinInt(long long &something, const long long &inf, const long long &sup)	//Функция ввода числа типа int. Проверяет, ввел ли пользователь корректные данные, и просит переввести в случае некорректности
{
	bool isCorrect = 0; //Своего рода флаг корректности или некорректности ввода. Изначально считаем ввод некорректным
	while (isCorrect == 0)
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
			return 1;
		}
	}
	return 0;
}

bool isFizz(const long long &number)	//Проверка делимости на 3
{
	std::string inStr;
	int inStrLength;
	int numSum = 0;
	inStr = std::to_string(number);		//Конвертация в строку
	inStrLength = inStr.length();	//Чтобы в цикле постоянно не приходилось считать длину строки, которая остается постоянной в этом цикле
	if (inStr[0] != '-')	//Суммирую цифры
		numSum += inStr[0] - '0';
	for (int i = 1; i < inStrLength; ++i)
	{
		numSum += inStr[i] - '0';
		if (numSum > 9)		//В делимости на 3 главное, чтобы сумма цифр делилась на 3, а значит не имеет смысла хранить сумму больше 9
			numSum -= 9;
	}
	if (numSum == 0 || numSum == 3 || numSum == 6 || numSum == 9)	//Проверяю делимость на 3
	{
		std::cout << "fizz";
		return 1;
	}
	else
		return 0;
}

bool isBuzz(const long long &number)	//Проверка делимости на 5. Логика похожа на isFizz, только проще, проверятся лишь последний символ
{
	std::string inStr;
	int inStrLength;
	int last;
	inStr = std::to_string(number);
	inStrLength = inStr.length();
	last = inStr[inStrLength - 1] - '0';
	if (last == 0 || last == 5)
	{
		std::cout << "buzz";
		return 1;
	}
	else
		return 0;
}

int main()
{
	long long M;
	long long number;
	bool isF, isB;	//Позже объясню, зачем они
	std::cout << "Enter M:\n";
	ERR(cinInt(M, 1, MAX_LONG_LONG_SIZE))

	std::cout << "Enter " << M << " numbers:\n";
	for (int i = 0; i < M; ++i)
	{
		ERR(cinInt(number, MIN_LONG_LONG_SIZE, MAX_LONG_LONG_SIZE));
		isF = isFizz(number);
		isB = isBuzz(number);
		if (!(isF || isB))	//Если сразу подставить isFizz и isBuzz вместо isF и isB, то в случае, когда isFizz == 1, isBuzz не выполнится
			std::cout << number;
		std::cout << ' ';		
	}

	return 0;
}
