#include "Calculator.h"

Calculator::Calculator() {
	m_ResultNum = 0.0;
	m_Num1 = 0.0;
	m_Num2 = 0.0;

	m_State = FirstNumber;	
	m_Method = None;

	m_Update = true;
}

void Calculator::Return() {
	if (m_Method == Addition) {
		m_ResultNum = m_Num1 + m_Num2;
	}
	else if (m_Method == Subtraction) {
		m_ResultNum = m_Num1 - m_Num2;
	}
	else if (m_Method == Multiplication) {
		m_ResultNum = m_Num1 * m_Num2;
	}
	else if (m_Method == Division) {
		m_ResultNum = m_Num1 / m_Num2;
	}

	m_Num1 = 0.0;
	m_Num2 = 0.0;
	m_State = Done;
	m_Method = None;
}

void Calculator::ReturnToNum1() {
	if (m_Method == Addition) {
		m_Num1 = m_Num1 + m_Num2;
	}
	else if (m_Method == Subtraction) {
		m_Num1 = m_Num1 - m_Num2;
	}
	else if (m_Method == Multiplication) {
		m_Num1 = m_Num1 * m_Num2;
	}
	else if (m_Method == Division) {

	}
}

void Calculator::AddNewNum(int _Num_Ascii) {
	int num = 0;

	switch (_Num_Ascii)
	{
	case 48:// Number 0
		num = 0;
		break;
	case 49:// Number 1
		num = 1;
		break;
	case 50:// Number 2
		num = 2;
		break;
	case 51:// Number 3
		num = 3;
		break;
	case 52:// Number 4
		num = 4;
		break;
	case 53:// Number 5
		num = 5;
		break;
	case 54:// Number 6
		num = 6;
		break;
	case 55:// Number 7
		num = 7;
		break;
	case 56:// Number 8
		num = 8;
		break;
	case 57:// Number 9
		num = 9;
		break;
	default:
		break;
	}

	if (m_State == FirstNumber) {
		m_Num1 = m_Num1 * 10 + num;
	}
	else if (m_State == SecondNumber) {
		m_Num2 = m_Num2 * 10 + num;
	}
}

void Calculator::RemoveNum() {
	double num;
	double remainder = 0.0;

	if (m_Method == FirstNumber) {
		num = m_Num1;

		if (num < 10 && num > 0) {
			m_Num1 = m_Num1 - num;
		}
		else {
			remainder = (int)num % 10;
			m_Num1 = (m_Num1 - remainder) / 10;
		}
	}
	else if (m_Method == SecondNumber) {
		num = m_Num2;

		if (num < 10 && num >0) {
			m_Num2 = m_Num2 - num;
		}
		else {
			remainder = (int)num % 10;
			m_Num2 = (m_Num2 - remainder) / 10;
		}
	}		
}

void Calculator::ClearNum() {
	if (m_Method == FirstNumber) {
		m_Num1 = 0.0;
	}
	else if (m_Method == SecondNumber) {
		m_Num2 = 0.0;
	}
}

void Calculator::ClearAll() {
	m_ResultNum = 0.0;
	m_Num1 = 0.0;
	m_Num2 = 0.0;

	m_Method = None;
	m_State = FirstNumber;
}

double Calculator::GetResultNum() {
	return m_ResultNum;
}

double Calculator::GetNum1() {
	return m_Num1;
}

double Calculator::GetNum2() {
	return m_Num2;
}

void Calculator::SetUpdate(bool _update) {
	m_Update = _update;
}

bool Calculator::GetUpdate() {
	return m_Update;
}

CalculatorState Calculator::GetCalculatorState() {
	return m_State;
}

MathMethod Calculator::GetMathMethod() {
	return m_Method;
}

void Calculator::KeyPressCB(int key) {
	if (m_State == FirstNumber) {
		if (key > 47 && key < 58) {
			AddNewNum(key);
		}
		else {
			switch (key)
			{
			case 8:// BackSpace Key Press
				RemoveNum();
				break;
			case 13:// Enter(Return) Key Press
				Return();
				break;
			case 27:// Esc Key Press
				ClearAll();
				break;
			case 42:// * Key Press
				m_Method = Multiplication;
				m_State = SecondNumber;
				break;
			case 43:// + Key Press
				m_Method = Addition;
				m_State = SecondNumber;
				break;
			case 45:// - Key Press
				m_Method = Subtraction;
				m_State = SecondNumber;
				break;
			case 47:// / Key Press
				m_Method = Division;
				m_State = SecondNumber;
				break;
			case 224:// Delete Key Press
				ClearNum();
				break;
			default:
				break;
			}
		}
	}
	else if (m_State == SecondNumber) {
		if (key > 47 && key < 58) {
			AddNewNum(key);
		}
		else {
			switch (key)
			{
			case 8:// BackSpace Key Press
				RemoveNum();
				break;
			case 13:// Enter(Return) Key Press
				Return();
				break;
			case 27:// Esc Key Press
				ClearAll();
				break;
			case 42:// * Key Press
				m_Method = Multiplication;
				ReturnToNum1();
				break;
			case 43:// + Key Press
				m_Method = Addition;
				ReturnToNum1();
				break;
			case 45:// - Key Press
				m_Method = Subtraction;
				ReturnToNum1();
				break;
			case 47:// / Key Press
				m_Method = Division;
				ReturnToNum1();
				break;
			case 224:
				ClearNum();
				break;
			default:
				break;
			}
		}
	}
	else if (m_State == Done) {
		if (key > 47 && key < 58) {
			m_State = FirstNumber;
			AddNewNum(key);
		}
		switch (key)
		{
		case 27:// Esc Key Press
			ClearAll();
			break;
		default:
			break;
		}
	}
}