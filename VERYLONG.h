#pragma warning(disable : 4996)
#pragma once
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;

namespace chapter13
{
	namespace verylong
	{
		const unsigned int SZ = 1000;
		
		class verylong
		{
			int size = 0;
			char vlstr[SZ];
			verylong multiDigit(const int digit) const;
			verylong multi10(const verylong vl) const;
			verylong(const char s[SZ])
			{
				strcpy(vlstr, s);
				//strrev(vlstr);
				size = strlen(s);
			}
		public:
			verylong() : size(0)
			{
				vlstr[0] = '\0';
			}
			verylong(const unsigned long number)
			{
				itoa(number, vlstr, 10);
				strrev(vlstr);
				size = strlen(vlstr);
			}

			void putvl() const;
			void getvl();
			verylong operator +(const verylong) const;
			verylong operator *(const verylong) const;
		};
		void verylong::putvl() const
		{
			char temp[SZ];
			strcpy(temp, vlstr);
			cout << strrev(temp);
		}
		void verylong::getvl()
		{
			cout << "Enter very long number: "; cin >> vlstr;
			strrev(vlstr);
			size = strlen(vlstr);
		}
		verylong verylong::multi10(const verylong vl) const
		{
			char temp[SZ];
			int i = vl.size;
			for (i; i >= 0; i--)
			{
				temp[i + 1] = vl.vlstr[i];
			}
			temp[0] = '0';
			temp[vl.size+1] = '\0';
			return verylong(temp);
		}

		verylong verylong::multiDigit(const int d) const
		{
			char temp[SZ];
			int carry = 0;
			int i = 0;
			for (i; i < size; i++)
			{
				int prod = d * (vlstr[i] - '0') + carry;
				if (prod >= 10) {
					carry = prod / 10;
					prod %= 10;
				}
				else carry = 0;
				temp[i] = prod + '0';
			}
			if (carry != 0)
				temp[i++] = carry + '0';
			temp[i] = '\0';
			return verylong(temp);
		}
		verylong verylong::operator*(const verylong vl) const
		{
			verylong temp;
			verylong prod;
			/*const verylong* smallervl = NULL;
			const verylong* greatervl = NULL;

			if (vl.size >= this->size)
			{
				smallervl = this;
				greatervl = &vl;
			}
			else
			{
				smallervl = &vl;
				greatervl = this;
			}*/
			int i = 0;
			for (i; i < vl.size; i++)
			{
				int d1 = vl.vlstr[i] - '0';
				prod = multiDigit(d1);
				for (int k = 0; k < i; k++)
					prod = multi10(prod);
				temp = temp + prod;
			}
			return temp;
		}
		verylong verylong::operator+(const verylong vl) const
		{
			char temp[SZ];

			int gl = strlen(vl.vlstr) < strlen(this->vlstr) ? strlen(this->vlstr) : strlen(vl.vlstr);
			int carry = 0;
			int i = 0;
			for (i; i < gl; i++)
			{
				int d1 = i > vl.size - 1 ? 0 : vl.vlstr[i] - '0';
				int d2 = i > this->size - 1 ? 0 : this->vlstr[i] - '0';
				int sum = d1 + d2 + carry;
				if (sum >= 10)
				{
					carry = 1;
					sum -= 10;
				}
				else
					carry = 0;
				temp[i] = sum + '0';
			}
			if (carry == 1)
				temp[i++] = '1';
			temp[i] = '\0';
			return verylong(temp);
		}

		void main()
		{
			verylong vl1;
			verylong vl2;
			vl1.getvl();
			vl2.getvl();
			verylong res = vl1 * vl2;

			res.putvl();
		}

		void vl_app()
		{
			unsigned long numb, j;
			cout << "Ener a number to find it's factorial: "; cin >> numb;

			verylong factorial = 1;

			for (j = numb; j > 0; j--)
			{
				factorial = factorial * j;
			}

			factorial.putvl(); cout << endl;
		}
	}

	namespace projects
	{
		namespace one
		{
			const unsigned int SZ = 1000;

			class verylong
			{
				int size = 0;
				char vlstr[SZ];
				bool minus = false;
				verylong multiDigit(const int digit) const;
				verylong multi10(const verylong vl) const;
				verylong(const char s[SZ], bool Minus = false)
				{
					minus = Minus;
					strcpy(vlstr, s);
					//strrev(vlstr);
					size = strlen(s);
				}
			public:
				verylong() : size(0)
				{
					vlstr[0] = '\0';
				}
				verylong(long number, bool minus = false)
				{
					if (number < 0)
						minus = true;
					number = number * 1;
					itoa(number, vlstr, 10);
					strrev(vlstr);
					size = strlen(vlstr);
				}

				void putvl() const;
				void getvl();
				verylong operator +(const verylong) const;
				verylong operator *(const verylong) const;
				verylong operator -(const verylong) const;
				verylong operator /(const verylong) const;
				bool operator <(const verylong) const;
				bool operator >(const verylong) const;
				bool UpdateQuotientWhenCurrentDividendLessThanDivisor(char quotient[SZ], int &qs, verylong &id, const verylong &vl) const;
				int EstimateNextQuotient(const verylong &dividend, const verylong& dvisor) const;
			};
			void verylong::putvl() const
			{
				char temp[SZ];
				strcpy(temp, vlstr);
				if (minus)
					cout << "-";
				cout << strrev(temp);
			}
			void verylong::getvl()
			{
				cin >> vlstr;
				if (strchr(vlstr, '-'))
				{
					minus = true;
					// Instead of manually removing '-'
				    *std::remove(vlstr, vlstr + strlen(vlstr), '-') = '\0';
				}
				strrev(vlstr);
				size = strlen(vlstr);
			}
			verylong verylong::multi10(const verylong vl) const
			{
				char temp[SZ];
				int i = vl.size;
				for (i; i >= 0; i--)
				{
					temp[i + 1] = vl.vlstr[i];
				}
				temp[0] = '0';
				temp[vl.size + 1] = '\0';
				return verylong(temp);
			}

			// todo: this should be static
			verylong verylong::multiDigit(const int d) const
			{
				char temp[SZ];
				int carry = 0;
				int i = 0;
				for (i; i < size; i++)
				{
					int prod = d * (vlstr[i] - '0') + carry;
					if (prod >= 10) {
						carry = prod / 10;
						prod %= 10;
					}
					else carry = 0;
					temp[i] = prod + '0';
				}
				if (carry != 0)
					temp[i++] = carry + '0';
				temp[i] = '\0';

				while (i > 1 && temp[i - 1] == '0')
				{
					temp[--i] = '\0';
				}
				return verylong(temp);
			}

			verylong verylong::operator*(const verylong vl) const
			{
				verylong temp;
				verylong prod;
				if (vl.minus || this->minus)
					temp.minus = 1;
				/*const verylong* smallervl = NULL;
				const verylong* greatervl = NULL;

				if (vl.size >= this->size)
				{
					smallervl = this;
					greatervl = &vl;
				}
				else
				{
					smallervl = &vl;
					greatervl = this;
				}*/
				int i = 0;
				for (i; i < vl.size; i++)
				{
					int d1 = vl.vlstr[i] - '0';
					prod = multiDigit(d1);
					for (int k = 0; k < i; k++)
						prod = multi10(prod);
					temp = temp + prod;
				}
				return temp;
			}

			verylong verylong::operator+(const verylong vl) const
			{
				verylong temp;
				if (minus && vl.minus)
					temp.minus = true;
				else if (minus && !vl.minus)
				{
					if (vl > *this)
						return verylong((verylong(vlstr) - verylong(vl.vlstr)).vlstr, true);
					else
						return verylong(vl.vlstr) - verylong(vlstr);
				}
				else if(!minus && vl.minus)
				{
					if (*this > vl)
						return verylong(vlstr) - verylong(vl.vlstr);
					else
						return verylong((verylong(vl.vlstr) - verylong(vlstr)).vlstr, true);
				}

				// This may not be needed
				int gl = strlen(vl.vlstr) < strlen(this->vlstr) ? strlen(this->vlstr) : strlen(vl.vlstr);
				int carry = 0;
				int i = 0;
				for (i; i < gl; i++)
				{
					int d1 = i > vl.size - 1 ? 0 : vl.vlstr[i] - '0';
					int d2 = i > this->size - 1 ? 0 : this->vlstr[i] - '0';
					int sum = d1 + d2 + carry;
					if (sum >= 10)
					{
						carry = 1;
						sum -= 10;
					}
					else
						carry = 0;
					temp.vlstr[i] = sum + '0';
				}
				if (carry == 1)
					temp.vlstr[i++] = '1';
				temp.vlstr[i] = '\0';
				temp.size = strlen(temp.vlstr);
				return temp;
			}

			verylong verylong::operator-(const verylong vl) const
			{
				verylong temp;
				const verylong* subtractee = this;
				const verylong* subtrahend = &vl;

				if (minus && vl.minus)
				{
					if (*this > vl)
					{
						subtractee = this;
						subtrahend = &vl;
						temp.minus = true;
					}
					else if (*this < vl)
					{
						subtractee = &vl;
						subtrahend = this;
					}
				}
				else if (!minus && vl.minus)
				{
					return verylong(vlstr) + verylong(vl.vlstr);
				}
				else if (minus && !vl.minus)
				{
					return verylong((verylong(vlstr) + verylong(vl.vlstr)).vlstr, true);
				}
				else if (vl > *this) // If substrahend is bigger than subtractee, swap
				{
					subtrahend = this;
					subtractee = &vl;
					temp.minus = true;
				}
				short i;
				short carry = 0;
				short d1;
				short d2;
				for (i = 0; i < subtractee->size; i++)
				{
					// when d1 is 2
					d1 = i >= subtractee->size ? 0 : subtractee->vlstr[i] - '0' - carry;
					if (d1 < 0)
						d1 = 9;
					else {
						carry = 0;
					}
					d2 = i >= subtrahend->size ? 0 : subtrahend->vlstr[i] - '0';
					if (d1 < d2)
					{
						d1 += 10;
						if (carry && d1 == 10)
							d1--;
						carry = 1;
					}
					temp.vlstr[temp.size++] = d1 - d2 + '0';
					//temp.size++;
				}
				temp.vlstr[temp.size] = '\0';
				// trimming leading 0s
				while (temp.size > 1 && temp.vlstr[temp.size - 1] == '0')
				{
					temp.vlstr[--temp.size] = '\0';
				}
				return temp;
			}

			bool verylong:: operator< (const verylong other) const
			{
				return other > *this;
			}

			// Don't pass verylongs with leading 0s
			bool verylong:: operator> (const verylong other) const
			{
				// todo: preceeding 0s should not be accounted as length
				if (other.minus && !minus) return true;
				if (!other.minus && minus) return false;

				// if number of places is not greater or equals vl, return true
				verylong left = *this;
				verylong right = other;
				short lesserLen = right.size < left.size ? right.size : left.size;
				/*if (this->vlstr[this->size - 1] == '0')
				{
					throw 1;
				}
				if (other.vlstr[other.size - 1] == '0')
				{
					throw 1;
				}*/

				if (left.minus && right.minus)
				{
					verylong temp = right;
					right = left;
					left = temp;
				}

				if (left.size > right.size)
					return true;
				else if (left.size < right.size)
					return false;

				for (short i = 0; i < lesserLen; i++)
				{
					if (this->vlstr[left.size - 1 - i] - '0' > other.vlstr[left.size - 1 - i] - '0')
						return true;
					else if(this->vlstr[left.size - 1 - i] - '0' < other.vlstr[left.size - 1 - i] - '0')
						return false;
				}
				return false;
			}

			verylong verylong:: operator/ (const verylong vl) const
			{
				bool isMinus = false;
				isMinus = vl.minus || this->minus;

				if (*this < vl)
					return verylong();

				if (strlen(this->vlstr) <= 9)
				{
					char* temp = new char[vl.size + 1];
					strncpy(temp, vl.vlstr, vl.size);
					temp[vl.size] = '\0';
					int divisor = atoi(strrev(temp));
					delete[] temp;
					temp = new char[this->size + 1];
					strcpy(temp, this->vlstr);
					int dividant = atoi(strrev(temp));
					delete[]temp;
					return verylong(dividant / divisor, isMinus);
				}
				// divisor size
				// bi Is not buffer index, it is nextDividentDigit idex
#pragma region correct sol with functions
				verylong id;

				strcpy(id.vlstr, this->vlstr + this->size - vl.size);
				id.size = vl.size;

				char quotient[SZ];
				int qs = 0;
				quotient[qs] = '\0';
				int i = this->size - id.size;
				for (i; i >= 0; i--)
				{
					if (i != this->size - vl.size && !(id.size == 1 && id.vlstr[0] == '0'))
					{
						// I can use id.multi10 and modifies at index 0
						memmove(id.vlstr + 1, id.vlstr, id.size);
						id.size++;
						id.vlstr[id.size] = '\0';
						id.vlstr[0] = this->vlstr[i];
					}
					else if (i != this->size - vl.size)
					{
						id.vlstr[0] = this->vlstr[i];
						id.size = 1;
					}

					if (UpdateQuotientWhenCurrentDividendLessThanDivisor(quotient, qs, id, vl))
						continue;
					
					int iq = EstimateNextQuotient(id, vl);
					
					verylong ip = vl.multiDigit(iq);

					verylong ir = id - ip;

					while (!(ir < vl) && !ir.minus)
					{
						iq++;
						ip = vl.multiDigit(iq);
						ir = id - ip;
					}
					while (ir.minus)
					{
						iq--;
						ip = vl.multiDigit(iq);
						ir = id - ip;
					}

					quotient[qs++] = iq + '0';
					quotient[qs] = '\0';

					id = ir;
				}
				char* cleanQuotient = quotient;
				while (*cleanQuotient == '0' && *(cleanQuotient + 1) != '\0')
					cleanQuotient++;
				return verylong(strrev(cleanQuotient), isMinus);
#pragma endregion

#pragma region Correct solution
				//verylong id;

				//strcpy(id.vlstr, this->vlstr + this->size - vl.size);
				//id.size = vl.size;

				//char quotient[SZ];
				//short qs = 0;
				//quotient[qs] = '\0';
				//int i = this->size - id.size;
				//for (i; i >= 0; i--)
				//{


				//	if (i != this->size - vl.size && !(id.size == 1 && id.vlstr[0] == '0'))
				//	{
				//		// I can use id.multi10 and modifies at index 0
				//		memmove(id.vlstr + 1, id.vlstr, id.size);
				//		id.size++;
				//		id.vlstr[id.size] = '\0';
				//		id.vlstr[0] = this->vlstr[i];
				//	}
				//	else if (i != this->size - vl.size)
				//	{
				//		id.vlstr[0] = this->vlstr[i];
				//		id.size = 1;
				//	}

				//	if (id < vl)
				//	{
				//		quotient[qs++] = '0';
				//		quotient[qs] = '\0';
				//		continue;
				//	}
				//	short n = id.vlstr[id.size - 1] - '0';
				//	short d = vl.vlstr[vl.size - 1] - '0';
				//	if (id.size > vl.size && id.size > 1)
				//		n = n * 10 + id.vlstr[id.size - 2] - '0';

				//	int iq = n / d;
				//	if (iq > 9) iq = 9;

				//	verylong ip = vl.multiDigit(iq);

				//	verylong ir = id - ip;

				//	while (!(ir < vl) && !ir.minus)
				//	{
				//		iq++;
				//		ip = vl.multiDigit(iq);
				//		ir = id - ip;
				//	}
				//	while (ir.minus)
				//	{
				//		iq--;
				//		ip = vl.multiDigit(iq);
				//		ir = id - ip;
				//	}

				//	quotient[qs++] = iq + '0';
				//	quotient[qs] = '\0';

				//	id = ir;
				//}
				//char *cleanQuotient = quotient;
				//while (*cleanQuotient == '0' && *(cleanQuotient + 1) != '\0')
				//	cleanQuotient++;
				//return verylong(strrev(cleanQuotient), isMinus);
#pragma endregion

#pragma region Fallacious sol - attempt 2


				//int iq;
				//verylong id;
				//strcpy(id.vlstr, this->vlstr + (this->size - vl.size));
				//id.size = vl.size;

				//bool skip = false;
				//verylong ip; 
				//verylong ir;
				//char quotient[SZ];
				//int qs = 0;
				//quotient[qs] = '\0';
				//for (int i = id.size; i <= this->size; i++)
				//{
				//	// this is find next iq function
				//	short n = id.vlstr[id.size - 1] - '0';
				//	short d = vl.vlstr[vl.size - 1] - '0';
				//	if (n < d) {
				//		n *= 10;
				//		n += id.vlstr[id.size - 2] - '0';
				//	}
				//	if (!skip)
				//		iq = n / d;

				//	ip = vl.multiDigit(iq);

				//	ir = id - ip;

				//	while (ir > vl)
				//	{
				//		iq++;

				//		ip = vl.multiDigit(iq);

				//		ir = id - ip;
				//	}
				//	while (ir.minus)
				//	{
				//		iq--;

				//		ip = vl.multiDigit(iq);


				//		ir = id - ip;

				//		if (iq == 0)
				//			break;
				//	}
				//	// This is append iq function
				//	quotient[qs++] = iq + '0';
				//	quotient[qs] = '\0';
				//	// this is (update id function)
				//	id = verylong(this->vlstr[this->size - i - 1] - '0'); 
				//	
				//	if (id.vlstr[0] - '0' != 0)
				//	{
				//		id.size = 1;
				//		strcpy(id.vlstr + 1, ir.vlstr);
				//		id.size += ir.size;
				//	}
				//	else {
				//		strcpy(id.vlstr, ir.vlstr);
				//		id.size = ir.size;
				//	}
				//	// if new id is less than vl
				//	if (id < vl)
				//	{
				//		iq = 0;
				//		skip = 1;
				//	}
				//}
				//return verylong(strrev(quotient), isMinus);
#pragma endregion

#pragma region Fallacious Sol  - attempt 1
				//// todo: resolve step 4
				//char *currentDividantBuffer = new char[this->size];
				//strcpy(currentDividantBuffer, this->vlstr);
				//strrev(currentDividantBuffer);
				//char *divisorBuffer = new char[vl.size];
				//strcpy(divisorBuffer, vl.vlstr);
				//strrev(divisorBuffer);

				//char quotient[SZ];
				//short aqi = 0;
				//quotient[aqi] = '\0';
				//short nextDividantDigitIndex = vl.size;
				//verylong currentDividant;
				//short currentDivisorFirstPart = divisorBuffer[0] - '0';
				//currentDividant = currentDividantBuffer;
				//strrev(currentDividant.vlstr);
				//do {
				//	short currentDividantFirstPart = currentDividantBuffer[0] - '0';
				//	// WROOOOOOOOOOOOOOONG
				//	short q = currentDividantFirstPart / currentDivisorFirstPart;
				//	if (q == 0) {
				//		char buffer[3];
				//		buffer[0] = currentDividantBuffer[0];
				//		buffer[1] = currentDividantBuffer[1];
				//		buffer[2] = '\0';
				//		currentDividantFirstPart = atoi(buffer);
				//	}
				//	q = currentDividantFirstPart / currentDivisorFirstPart;
				//	// Todo: make sure we only need to subtract q by 1
				//	verylong remainder = vl.multiDigit(q);
				//	if (remainder > currentDividant)
				//	{
				//		q--;
				//		remainder = vl.multiDigit(q);
				//	}
				//	currentDividant = currentDividant - remainder;
				//	currentDividant.vlstr[currentDividant.size++] = this->vlstr[--nextDividantDigitIndex];
				//	currentDividant.vlstr[currentDividant.size] = '\0';
				//	quotient[aqi++] = q + '0';
				//	quotient[aqi] = '\0';
				//} while (currentDividant > vl);
				//return verylong(quotient, isMinus);
#pragma endregion
			}

			bool verylong::UpdateQuotientWhenCurrentDividendLessThanDivisor(char quotient[SZ], int& qs, verylong& id, const verylong& vl) const
			{
				if (id < vl)
				{
					quotient[qs++] = '0';
					quotient[qs] = '\0';
					true;
				}
				return false;
			}

			int verylong::EstimateNextQuotient(const verylong& dividend, const verylong& divisor) const
			{
				short n = dividend.vlstr[dividend.size - 1] - '0';
				short d = divisor.vlstr[divisor.size - 1] - '0';
				if (dividend.size > divisor.size && dividend.size > 1)
					n = n * 10 + dividend.vlstr[dividend.size - 2] - '0';

				int iq = n / d;
				if (iq > 9) iq = 9;
				
				return iq;
			}

			void main()
			{
				verylong vl1;
				verylong vl2;
				cout << "Dividend: ";
				vl1.getvl();
				cout << "Divisor: ";
				vl2.getvl();
				verylong res = vl1 / vl2;
				res.putvl();
			}

			void vl_app()
			{
				unsigned long numb, j;
				cout << "Ener a number to find it's factorial: "; cin >> numb;

				verylong factorial = 1;

				for (j = numb; j > 0; j--)
				{
					factorial = factorial * j;
				}

				factorial.putvl(); cout << endl;
			}
		}
	}
}