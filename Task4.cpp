/*
Аэропорт (управление вылетом пассажирских авиарейсов):
пункт назначения, номер рейса, дата вылета, время вылета,
время прибытия в пункт назначения, количество свободных мест,
информация о задержке вылета в часах. Количество строк на табло отображения 10.
Операции
    1) Вставить информацию по новому рейсу в таблицу перед рейсом с большим номером.
    2) Удалить информацию об вылетевшем рейсе и сохранить ее в архивной таблице.
    3) Вывести рейсы, готовые к вылету по расписанию (за 2 часа до времени вылета).
    4) Сформировать список номеров рейсов, вылетающих в заданный пункт назначения.
*/
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>

using std::cout;
using std::cin;
using std::vector;
using std::string;
using std::setw;
using std::left;
using std::endl;
using std::to_string;

struct Date {
    unsigned short day;
    unsigned short month;
    unsigned short year;
    bool operator == (const Date &other)
    {
        return day == other.day && month == other.month && year == other.year;
    }
};

struct Time {
    unsigned short hours;
    unsigned short minutes;
    unsigned short seconds;
    bool operator == (const Time &other)
    {
        return hours == other.hours && minutes == other.minutes && seconds == other.seconds;
    }
    int operator - (const Time &other)
    {
        return (hours - other.hours) + (minutes - other.minutes) - (seconds - other.seconds);
    }
};

string Format2Digits(string value)
{
    return value.length() == 1 ? '0' + value : value;
}

string DateToString(Date& date)
{
    string day = Format2Digits(to_string(date.day));
    string month = Format2Digits(to_string(date.month));
    string year = Format2Digits(to_string(date.year));
    return day + '/' + month + '/' + year;
}

string TimeToString(Time& time)
{
    string hours = Format2Digits(to_string(time.hours));
    string minutes = Format2Digits(to_string(time.minutes));
    string seconds = Format2Digits(to_string(time.seconds));
    return hours + ':' + minutes + ':' + seconds;
}

struct Flight {
    string destination;
    unsigned int number;
    unsigned short emptySeats;
    Date departureDate;
    Time departureTime;
    Time arrivalTime;
    int hoursDelay;
    bool operator < (const Flight &other) const {
        return number < other.number;
    }
};

vector<Flight> table;
vector<Flight> archive;

void AddFlight(vector<Flight>& table, string destination, unsigned int number,
               unsigned short emptySeats, Date departureDate, Time departureTime,
               Time arrivalTime, int hoursDelay)
{
    Flight flight = { destination, number, emptySeats, departureDate,
                      departureTime, arrivalTime, hoursDelay };
    table.push_back(flight);
    std::sort(table.begin(), table.end());
}

void PrintFlights(vector<Flight>& table)
{
    cout << setw(5) << left << "NUM" << " ";
    cout << setw(10) << left << "DEST" << " ";
    cout << setw(5) << left << "SEATS" << " ";
    cout << setw(10) << left << "DEP_DATE" << " ";
    cout << setw(8) << left << "DEP_TIME" << " ";
    cout << setw(8) << left << "ARR_TIME" << " ";
    cout << setw(5) << left << "DELAY" << endl;
    for (auto el : table)
    {
        cout << setw(5) << left << el.number << " ";
        cout << setw(10) << left << el.destination << " ";
        cout << setw(5) << left << el.emptySeats << " ";
        cout << setw(10) << left << DateToString(el.departureDate) << " ";
        cout << setw(8) << left << TimeToString(el.departureTime) << " ";
        cout << setw(8) << left << TimeToString(el.arrivalTime) << " ";
        cout << setw(2) << left << el.hoursDelay << endl;
    }
}

vector<Flight> FlightsWithDestination(vector<Flight>& table, string destination)
{
    vector<Flight> output;
    for (Flight el : table)
        if (el.destination == destination)
            output.push_back(el);
    return output;
}

void DeleteFlight(vector<Flight>& table, unsigned int number)
{
    for (size_t i = 0; i < table.size(); i++)
    {
        if (table[i].number == number)
        {
            archive.push_back(table[i]);
            table.erase(table.begin() + i);
            return;
        }
    }
    cout << "Рейс с номером " << number << " не найден";
}

void DeleteDepartedFlight(vector<Flight>& table, Date dateNow, Time timeNow)
{
    vector<Flight> output;
    for (Flight el: table)
        if (el.departureDate.year == dateNow.year && el.departureTime - timeNow < 0)
            DeleteFlight(table, el.number);
}

void PrintReadyFlights(vector<Flight>& table, Date dateNow, Time timeNow) {
    vector<Flight> output;
    int offsetTime = 60 * 60 * 2;
    for (Flight el: table)
        if (el.departureDate.year == dateNow.year && el.departureTime - timeNow <= offsetTime)
            output.push_back(el);
    PrintFlights(output);
}

int main()
{
    AddFlight(
            table,"Kaluga",103,21,
            Date {21, 1, 2022},
            Time {15, 25, 12},
            Time {17, 4, 23},
            0);
    AddFlight(
            table,"Kostroma",56,9,
            Date {23, 01, 2022},
            Time {13, 50, 21},
            Time {14, 22, 43},
            1);
    PrintFlights(table);
    return 0;
}