#include <iostream>
#include <array>
#include <vector>

class Month
{
public:
  enum MonthID : int // Int because int type was requested. I would use unsigned or signed char.
  { JANUARY = 1, FEBRUARY, MARCH, APRIL, MAY, JUNE, JULY, AUGUST, SEPTEMBER, OCTOBER, NOVEMBER, DECEMBER };
private:
  static MonthID month_from_String(const std::array<char,3>&);
  static MonthID month_from_string(const std::array<char,3>&);
  static MonthID month_from_number(const int);

  static int number_from_month(const MonthID);
  static std::string string_from_month(const MonthID);
  static std::string String_from_month(const MonthID);
  static std::string str_from_month(const MonthID);
  static std::string Str_from_month(const MonthID);
public:
  Month(char c1, char c2, char c3);
  Month(int monthNumber);
  Month(const MonthID monthID);
  Month();

  void getMonthByNumber(std::istream&);
  void getMonthByName(std::istream&);
  void outputMonthNumber(std::ostream&);
  void outputMonthName(std::ostream&);
  Month nextMonth();
  int monthNumber();

  std::string to_string() const;
public:
  bool operator==(const Month&) const;
  bool operator>(const Month&) const;

  Month operator+(const Month&);
  Month operator-(const Month&);

  Month& operator+=(const Month&);
  Month& operator-=(const Month&);

  Month& operator++();
  Month& operator--();
  Month operator++(int);
  Month operator--(int);
private:
  MonthID mnth;
};

int main()
{
  Month month;
  while(true)
  {
    std::cout << "> ";
    std::string command;
    std::cin >> command;

    // Split string by spaces
    std::vector<std::string> tokens;
    std::string token;
    for (char c : command)
    {
      if (c == ' ')
      {
        tokens.push_back(token);
        token = "";
      }
      else
      {
        token += c;
      }
    }

    // Define token pop
    const auto pop_token = [&tokens]() -> std::string
    {
      std::string token = tokens[0];
      tokens.erase(tokens.begin());
      return token;
    };

    std::string commandName = pop_token();
    /**
     * Interface:
     * - set <month string> : Set the month
     * - next : Get the next month
     * - prev : Get the previous month
     * - string : Get the month as a string
     * - number : Get the month as a number
     * - quit : Quit the program
     * 
     * Hash with function ([2] | 16):
     * - set 116 - 114 = 2
     * - next 120 - 114 = 6
     * - prev 117 - 114 = 3
     * - string 114 - 114 = 0
     * - number 125 - 114 = 11
     * - quit 121 - 114 = 7
     */
    enum class CommandID
    {
      SET = 2,
      NEXT = 6,
      PREV = 3,
      STRING = 0,
      NUMBER = 11,
      QUIT = 7
    } commandID = static_cast<CommandID>((commandName[0] | 16) - 114);

    switch (commandID)
    {
      case CommandID::SET:
      {
        std::string monthString = pop_token();
        Month newMonth(monthString[0], monthString[1], monthString[2]);
        month = newMonth;
      } // case CommandID::SET
      case CommandID::NEXT:
      {
        month++;
      } // case CommandID::NEXT
      case CommandID::PREV:
      {
        month--;
      } // case CommandID::PREV
      case CommandID::STRING:
      {
        month.outputMonthName(std::cout);
        std::cout << "\n";
      } // case CommandID::STRING
      case CommandID::NUMBER:
      {
        month.outputMonthNumber(std::cout);
        std::cout << "\n";
      } // case CommandID::NUMBER
      case CommandID::QUIT:
      {
        return 0;
      } // case CommandID::QUIT
    } // switch (commandID)
  }
}

Month::Month(char c1, char c2, char c3) :
  mnth(month_from_String({c1, c2, c3}))
{
}
Month::Month(int monthNumber) :
  mnth(month_from_number(monthNumber))
{
}
Month::Month(const MonthID monthID) :
  mnth(monthID)
{
}
Month::Month() :
  mnth(MonthID::JANUARY)
{
}

void Month::getMonthByNumber(std::istream& stream)
{
  int monthNumber;
  stream >> monthNumber;
  mnth = month_from_number(monthNumber);
}
void Month::getMonthByName(std::istream& stream)
{
  std::array<char, 3> monthName;
  stream >> monthName[0] >> monthName[1] >> monthName[2];
  mnth = month_from_string(monthName);
}
void Month::outputMonthNumber(std::ostream& stream)
{
  stream << number_from_month(mnth);
}
void Month::outputMonthName(std::ostream& stream)
{
  stream << String_from_month(mnth);
}
Month Month::nextMonth()
{
  Month nextMonth = *this;
  ++nextMonth;
  return nextMonth;
}
int Month::monthNumber()
{
  return number_from_month(mnth);
}

Month::MonthID Month::month_from_String(const std::array<char, 3> &input_string)
{
  /**
   * Hash Function (([0] ^ 15) ^ ([1] | [2])):
   * - January 42
   * - February 46
   * - March 49
   * - April 60
   * - May 59
   * - June 58
   * - July 56
   * - August 57
   * - September 41
   * - October 55
   * - November 62
   * - December 44
   */

  switch ((input_string[0] ^ 15) ^ (input_string[1] | input_string[2]))
  {
  case 42:
    return MonthID::JANUARY;
  case 46:
    return MonthID::FEBRUARY;
  case 49:
    return MonthID::MARCH;
  case 60:
    return MonthID::APRIL;
  case 59:
    return MonthID::MAY;
  case 58:
    return MonthID::JUNE;
  case 56:
    return MonthID::JULY;
  case 57:
    return MonthID::AUGUST;
  case 41:
    return MonthID::SEPTEMBER;
  case 55:
    return MonthID::OCTOBER;
  case 62:
    return MonthID::NOVEMBER;
  case 44:
    return MonthID::DECEMBER;
  }
}
Month::MonthID Month::month_from_string(const std::array<char, 3> &input_string)
{
  /**
   * Hash Function (([0] ^ 15) ^ ([1] | [2])):
   *  - january 10
   *  - february 14
   *  - march 17
   *  - april 28
   *  - may 27
   *  - june 26
   *  - july 24
   *  - august 25
   *  - september 9
   *  - october 23
   *  - november 30
   *  - december 12
   */

  switch ((input_string[0] ^ 15) ^ (input_string[1] | input_string[2]))
  {
  case 10:
    return MonthID::JANUARY;
  case 14:
    return MonthID::FEBRUARY;
  case 17:
    return MonthID::MARCH;
  case 28:
    return MonthID::APRIL;
  case 27:
    return MonthID::MAY;
  case 26:
    return MonthID::JUNE;
  case 24:
    return MonthID::JULY;
  case 25:
    return MonthID::AUGUST;
  case 9:
    return MonthID::SEPTEMBER;
  case 23:
    return MonthID::OCTOBER;
  case 30:
    return MonthID::NOVEMBER;
  case 12:
    return MonthID::DECEMBER;
  }
}
Month::MonthID Month::month_from_number(const int number)
{
  return static_cast<MonthID>(number);
}

std::string Month::to_string() const
{
  return string_from_month(mnth);
}


int Month::number_from_month(const Month::MonthID month_id)
{
  return static_cast<int>(month_id);
}
std::string Month::string_from_month(const Month::MonthID month_id)
{
  switch (month_id)
  {
  case MonthID::JANUARY:
    return "january";
  case MonthID::FEBRUARY:
    return "february";
  case MonthID::MARCH:
    return "march";
    case MonthID::APRIL:
      return "april";
    case MonthID::MAY:
      return "may";
    case MonthID::JUNE:
      return "june";
    case MonthID::JULY:
      return "july";
    case MonthID::AUGUST:
      return "august";
    case MonthID::SEPTEMBER:
      return "september";
    case MonthID::OCTOBER:
      return "october";
    case MonthID::NOVEMBER:
      return "november";
    case MonthID::DECEMBER:
      return "december";
  }
}
std::string Month::String_from_month(const Month::MonthID month_id)
{
  switch (month_id)
  {
  case MonthID::JANUARY:
    return "January";
  case MonthID::FEBRUARY:
    return "February";
  case MonthID::MARCH:
    return "March";
  case MonthID::APRIL:
    return "April";
  case MonthID::MAY:
    return "May";
  case MonthID::JUNE:
    return "June";
  case MonthID::JULY:
    return "July";
  case MonthID::AUGUST:
    return "August";
  case MonthID::SEPTEMBER:
    return "September";
  case MonthID::OCTOBER:
    return "October";
  case MonthID::NOVEMBER:
    return "November";
  case MonthID::DECEMBER:
    return "December";
  }
}
std::string Month::str_from_month(const Month::MonthID month_id)
{
  switch (month_id)
  {
  case MonthID::JANUARY:
    return "jan";
  case MonthID::FEBRUARY:
    return "feb";
  case MonthID::MARCH:
    return "mar";
  case MonthID::APRIL:
    return "apr";
  case MonthID::MAY:
    return "may";
  case MonthID::JUNE:
    return "jun";
  case MonthID::JULY:
    return "jul";
  case MonthID::AUGUST:
    return "aug";
  case MonthID::SEPTEMBER:
    return "sep";
  case MonthID::OCTOBER:
    return "oct";
  case MonthID::NOVEMBER:
    return "nov";
  case MonthID::DECEMBER:
    return "dec";
  }
}
std::string Month::Str_from_month(const Month::MonthID month_id)
{
  switch (month_id)
  {
  case MonthID::JANUARY:
    return "Jan";
  case MonthID::FEBRUARY:
    return "Feb";
  case MonthID::MARCH:
    return "Mar";
  case MonthID::APRIL:
    return "Apr";
  case MonthID::MAY:
    return "May";
  case MonthID::JUNE:
    return "Jun";
  case MonthID::JULY:
    return "Jul";
  case MonthID::AUGUST:
    return "Aug";
  case MonthID::SEPTEMBER:
    return "Sep";
  case MonthID::OCTOBER:
    return "Oct";
  case MonthID::NOVEMBER:
    return "Nov";
  case MonthID::DECEMBER:
    return "Dec";
  }
}


bool Month::operator==(const Month& rhs) const
{
  return mnth == rhs.mnth;
}
bool Month::operator>(const Month& rhs) const
{
  return mnth > rhs.mnth;
}

Month Month::operator+(const Month& rhs)
{
  int result = number_from_month(mnth) + number_from_month(rhs.mnth);
  if (result > 12)
  {
    return Month(result - 12);
  }
  return Month(result);
}
Month Month::operator-(const Month& rhs)
{
  int result = number_from_month(mnth) - number_from_month(rhs.mnth);
  if (result < 1)
  {
    return Month(result + 12);
  }
  return Month(result);
}

Month& Month::operator+=(const Month& rhs)
{
  int result = number_from_month(mnth) + number_from_month(rhs.mnth);
  if (result > 12)
  {
    mnth = MonthID(result - 12);
  }
  else
  {
    mnth = MonthID(result);
  }
  return *this;
}
Month& Month::operator-=(const Month& rhs)
{
  int result = number_from_month(mnth) - number_from_month(rhs.mnth);
  if (result < 1)
  {
    mnth = MonthID(result + 12);
  }
  else
  {
    mnth = MonthID(result);
  }
  return *this;
}

Month& Month::operator++()
{
  if (mnth == MonthID::DECEMBER)
  {
    mnth = MonthID::JANUARY;
  }
  else
  {
    mnth = MonthID(number_from_month(mnth) + 1);
  }
  return *this;
}
Month& Month::operator--()
{
  if (mnth == MonthID::JANUARY)
  {
    mnth = MonthID::DECEMBER;
  }
  else
  {
    mnth = MonthID(number_from_month(mnth) - 1);
  }
  return *this;
}
Month Month::operator++(int)
{
  if (mnth == MonthID::DECEMBER)
  {
    return Month(MonthID::JANUARY);
  }
  else
  {
    return Month(number_from_month(mnth) + 1);
  }
}
Month Month::operator--(int)
{
  if (mnth == MonthID::JANUARY)
  {
    return Month(MonthID::DECEMBER);
  }
  else
  {
    return Month(number_from_month(mnth) - 1);
  }
}
