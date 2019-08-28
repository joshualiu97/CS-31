#include <iostream>
#include <cctype>
#include <cassert>
#include <string>
using namespace std;

// Return true if the argument is a two-uppercase-letter state code, or
// false otherwise.

bool isValidUppercaseStateCode(string stateCode)
{
	const string codes =
		"AL.AK.AZ.AR.CA.CO.CT.DE.FL.GA.HI.ID.IL.IN.IA.KS.KY."
		"LA.ME.MD.MA.MI.MN.MS.MO.MT.NE.NV.NH.NJ.NM.NY.NC.ND."
		"OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
	return (stateCode.size() == 2 &&
		stateCode.find('.') == string::npos  &&  // no '.' in stateCode
		codes.find(stateCode) != string::npos);  // match found
}

// Determines whether or not the poll data has proper syntax

bool hasProperSyntax(string pollData)
{
	for (string::size_type i = 0; i != pollData.size(); i++) // Makes all letters uppercase
	{
		if (islower(pollData[i]))
		{
			pollData[i] = toupper(pollData[i]);
		}
	}
	for (string::size_type j = 0; j != pollData.size(); j++) // Checks for spaces
	{
		if (pollData[j] == ' ')
		{
			return false;
		}
	}
	if (pollData == "")
	{
		return true;
	}

	int count = 0;
	string newTemp = pollData;

	// Begin to check string

	do {
		if (newTemp.size() >= 2) // If string size is less than two, that means there cannot be a state code, so return false
		{
			string temp1(1, newTemp[count]);
			string temp2(1, newTemp[count + 1]);
			string tempCode = temp1 + temp2;
			if (!isValidUppercaseStateCode(tempCode))
			{
				return false;
			}
			newTemp = newTemp.substr(2, newTemp.size() - 2); // Cut state code from string

			// After checking for the state code, check the number of seats and party codes to see if they are valid

			do {
				if (newTemp == "")
				{
					return true;
				}

				if (newTemp[0] == ',')
				{
					break;
				}

				if (!isdigit(newTemp[0])) // Ensure the next char is a digit
				{
					return false;
				}

				int numOfDigits = 0;
				for (string::size_type k = 0; isdigit(newTemp[k]); k++)
				{
					if (isdigit(newTemp[k]))
					{
						numOfDigits++;
					}
					if (numOfDigits > 2)
					{
						return false;
					}
				}

				newTemp = newTemp.substr(numOfDigits, newTemp.size() - numOfDigits); // Cut digits from string

				if (!isalpha(newTemp[0])) // Ensure there is a party code after the digit(single alphabet)
				{
					return false;
				}
				else
				{
					newTemp = newTemp.substr(1, newTemp.size() - 1); // Cut party code from string
				}

				if (newTemp == "")
				{
					return true;
				}

				if (isalpha(newTemp[0])) // Invalid syntax if party code is more than one letter
				{
					return false;
				}
			} while (newTemp[0] != ',');

			newTemp = newTemp.substr(1, newTemp.size() - 1); // Cut ',' from string
		}
		else
		{
			return false;
		}
	} while (newTemp.size() >= 2);
	return false;
}

// Determines the amount of seats predicted for a given party

int tallySeats(string pollData, char party, int& seatTally)
{
	if (!hasProperSyntax(pollData))
	{
		return 1;
	}

	if (!isalpha(party))
	{
		return 2;
	}

	for (string::size_type aa = 0; aa != pollData.size(); aa++) // Makes all letters uppercase
	{
		if (islower(pollData[aa]))
		{
			pollData[aa] = toupper(pollData[aa]);
		}
	}

	// Initialize all letters as ints to store number of tallies in each one

	int a = 0, b = 0, c = 0, d = 0, e = 0, f = 0, g = 0, h = 0, i = 0, j = 0, k = 0, l = 0, m = 0;
	int n = 0, o = 0, p = 0, q = 0, r = 0, s = 0, t = 0, u = 0, v = 0, w = 0, x = 0, y = 0, z = 0;
	int count = 0;
	string newTemp = pollData;

	if (newTemp == "" && isalpha(party)) // Check for empty string and valid party char
	{
		seatTally = 0;
		return 0;
	}

	do {
		string temp1(1, newTemp[count]);
		string temp2(1, newTemp[count + 1]);
		string tempCode = temp1 + temp2;

		newTemp = newTemp.substr(2, newTemp.size() - 2); // Cut state code from string

		do {
			if (newTemp == "")
			{
				break;
			}

			if (newTemp[0] == ',') // If there is a comma, break out of this loop to evaluate next state poll info
			{
				break;
			}

			int numOfDigits = 0;

			string numOfVotes = "";

			for (string::size_type bb = 0; isdigit(newTemp[bb]); bb++)
			{
				if (isdigit(newTemp[bb]))
				{
					numOfDigits++;
					numOfVotes += newTemp[bb];
				}
			}

			// Convert the digits into an integer

			int convertedDigits = 0;
			int len = numOfVotes.size();
			int multiplier = 1;

			for (string::size_type cc = 0; cc < numOfVotes.size(); cc++)
			{
				char tempDigit = numOfVotes[len - (cc + 1)];
				int digit = tempDigit - '0';
				convertedDigits += digit * multiplier;
				multiplier *= 10;
			}

			newTemp = newTemp.substr(numOfDigits, newTemp.size() - numOfDigits); // Cut digits from string

			char partyCode = newTemp[0];

			// Adds the number of seats together

			switch (partyCode)
			{
			case 'A':
				a += convertedDigits;
				break;
			case 'B':
				b += convertedDigits;
				break;
			case 'C':
				c += convertedDigits;
				break;
			case 'D':
				d += convertedDigits;
				break;
			case 'E':
				e += convertedDigits;
				break;
			case 'F':
				f += convertedDigits;
				break;
			case 'G':
				g += convertedDigits;
				break;
			case 'H':
				h += convertedDigits;
				break;
			case 'I':
				i += convertedDigits;
				break;
			case 'J':
				j += convertedDigits;
				break;
			case 'K':
				k += convertedDigits;
				break;
			case 'L':
				l += convertedDigits;
				break;
			case 'M':
				m += convertedDigits;
				break;
			case 'N':
				n += convertedDigits;
				break;
			case 'O':
				o += convertedDigits;
				break;
			case 'P':
				p += convertedDigits;
				break;
			case 'Q':
				q += convertedDigits;
				break;
			case 'R':
				r += convertedDigits;
				break;
			case 'S':
				s += convertedDigits;
				break;
			case 'T':
				t += convertedDigits;
				break;
			case 'U':
				u += convertedDigits;
				break;
			case 'V':
				v += convertedDigits;
				break;
			case 'W':
				w += convertedDigits;
				break;
			case 'X':
				x += convertedDigits;
				break;
			case 'Y':
				y += convertedDigits;
				break;
			case 'Z':
				z += convertedDigits;
				break;
			}

			newTemp = newTemp.substr(1, newTemp.size() - 1); // Cut party code from string

			if (newTemp == "")
			{
				break;
			}

		} while (newTemp[0] != ',');

		if (newTemp == "")
		{
			break;
		}

		newTemp = newTemp.substr(1, newTemp.size() - 1); // Cut ',' from string
	} while (newTemp.size() >= 2);

	if (islower(party))
	{
		party = toupper(party);
	}

	switch (party) // Change value of seat to correspond to given seat char
	{
	case 'A':
		seatTally = a;
		break;
	case 'B':
		seatTally = b;
		break;
	case 'C':
		seatTally = c;
		break;
	case 'D':
		seatTally = d;
		break;
	case 'E':
		seatTally = e;
		break;
	case 'F':
		seatTally = f;
		break;
	case 'G':
		seatTally = g;
		break;
	case 'H':
		seatTally = h;
		break;
	case 'I':
		seatTally = i;
		break;
	case 'J':
		seatTally = j;
		break;
	case 'K':
		seatTally = k;
		break;
	case 'L':
		seatTally = l;
		break;
	case 'M':
		seatTally = m;
		break;
	case 'N':
		seatTally = n;
		break;
	case 'O':
		seatTally = o;
		break;
	case 'P':
		seatTally = p;
		break;
	case 'Q':
		seatTally = q;
		break;
	case 'R':
		seatTally = r;
		break;
	case 'S':
		seatTally = s;
		break;
	case 'T':
		seatTally = t;
		break;
	case 'U':
		seatTally = u;
		break;
	case 'V':
		seatTally = v;
		break;
	case 'W':
		seatTally = w;
		break;
	case 'X':
		seatTally = x;
		break;
	case 'Y':
		seatTally = y;
		break;
	case 'Z':
		seatTally = z;
		break;
	}

	return 0;
}

int main()
{
	assert(hasProperSyntax("AZ"));
	assert(hasProperSyntax("aZ"));
	assert(hasProperSyntax("az"));
	assert(hasProperSyntax("tX12r6m"));
	assert(hasProperSyntax("ut10u"));
	assert(hasProperSyntax("IA3r7y9q,Wv6q2s9k"));
	assert(hasProperSyntax("Ca4r6d9i"));
	assert(hasProperSyntax(""));
	assert(hasProperSyntax("ga07t,ne0d02k"));
	
	assert(!hasProperSyntax("ZA"));
	assert(!hasProperSyntax("Za"));
	assert(!hasProperSyntax("za"));
	assert(!hasProperSyntax("gA5%i$"));
	assert(!hasProperSyntax("gA5k1l,HIe3*i"));
	assert(!hasProperSyntax("f l2k"));
	assert(!hasProperSyntax("Cor4,WI4 w"));
	assert(!hasProperSyntax(" OH"));
	assert(!hasProperSyntax("OH "));
	assert(!hasProperSyntax(" "));
	assert(!hasProperSyntax("La4j,,ky1e"));

	int seats;
	seats = -999;    // so we can detect whether tallySeats sets seats
	assert(tallySeats("CT7d,NY1t18z1I,vT,Ne07r00z04z", 'z', seats) == 0 && seats == 22);
	seats = -999;
	assert(tallySeats("de8i4f,nc5y8v", '%', seats) == 2 && seats == -999);
	seats = -999;
	assert(tallySeats("", 'E', seats) == 0 && seats == 0);
	seats = -999;
	assert(tallySeats("pa4#", 'E', seats) == 1 && seats == -999);
	seats = -999;
	assert(tallySeats("ne4^", '(', seats) == 1 && seats == -999);
	seats = -999;
	assert(tallySeats("ca9R16D1I,IA,ks3d7r4D,NJ7r", 'r', seats) == 0 && seats == 23);
	seats = -999;
	assert(tallySeats("ca9R16D1I,IA,ks3d7r4D,NJ7r", 'd', seats) == 0 && seats == 23);
	seats = -999;
	assert(tallySeats("ca9R16D1I,IA,ks3d7r4D,NJ7r", 'i', seats) == 0 && seats == 1);
	seats = -999;
	assert(tallySeats("ca4l,md8f,nc7y", 'z', seats) == 0 && seats == 0);
	seats = -999;
	assert(tallySeats("mn1a1b1c1d1e1f1g1h,ia1i1j1k1l1m1n1o,pa1p1q1r1s,wy1t1u1v1w1x1y1z", 't', seats) == 0 && seats == 1);

	cout << "All tests succeeded" << endl;
}