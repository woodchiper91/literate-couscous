
Mark Young <woodchiper98@gmail.com>
Apr 29, 2021, 12:29 AM (2 days ago)
to wodchiper98

/*
Mark Young_Assignment17.cpp

Mark Young
COSC-3000
4-23-2021
I believe I finally worked out all issues. Thanks for your patience. I hope you had a fun trip! My older brother lives in Tokyo, I hope you enjoyed!
*/
#include <iostream>
#include <iomanip>


using namespace std;

//global constants
const int secondsInAMinute = 60;
const int minutesInAnHour = 60;
const int hoursInOneEntireCycle = 24;

//enumerate "comp" type for "compare" function
enum comp { GREATER = 1, LESS = -1, EQUAL = 0 };

//class representing a wall clock
class WallClockTime
{
public:

    //friend ImperialWeight operator +(const ImperialWeight& clock1, const ImperialWeight& clock2);
    //
    //friend ImperialWeight add(const ImperialWeight& clock1, const ImperialWeight& clock2);
    //friend comp compare(const ImperialWeight& clock1, const ImperialWeight& clock2);

    friend WallClockTime add(const WallClockTime& clock1, const WallClockTime& clock2); //function declaration for add function - friend function
    friend comp compare(const WallClockTime& clock1, const WallClockTime& clock2); //declaration for compare function - friend function

    WallClockTime(); //default constructor
    WallClockTime(const int hours, const int minutes, const int seconds);
    WallClockTime(const int minutes, const int seconds);
    WallClockTime(const int seconds);
    int get_hours() const; //Add “const” modifier to member functions if they do not change member variables! This function is a getter for private variable clockHours.
    int get_minutes() const; //This function is a getter for private variable clockMinutes n(add const modifier to this member function because it doesn't change any member variables either. Only returns or 'gets' them.
    int get_seconds() const;


    //void set_minutes(int z);

    //void set_hours(int z);
    //void setter(int new_hours, int new_minutes, int new_seconds);
    void showTime24(std::ostream& osObj);
    void showTime12(std::ostream& osObj);
    // friend bool operator +(const WallClockTime& clock1, const WallClockTime& clock2);

    friend WallClockTime operator + (const WallClockTime& clock1, const WallClockTime& clock2);
    friend WallClockTime operator - (const WallClockTime& clock1, const WallClockTime& clock2);
    friend WallClockTime operator *(const WallClockTime& clock1, const int n);
    friend WallClockTime operator *(const int n, const WallClockTime& clock1);
    friend WallClockTime operator /(const WallClockTime& clock1, const int n);
    //operator + to compute (WallClockTime object) + (WallClockTime object)
    //operator += to compute(WallClockTime object) += (WallClockTime object)
    /*WallClockTime operator -=(WallClockTime& clock1, const WallClockTime& clock2)
    WallClockTime operator -(const WallClockTime& clock1, const WallClockTime& clock2)*/
    friend WallClockTime operator +=(WallClockTime& clock1, const WallClockTime& clock2); //don't use const for first argument 'clock1' because we are changing it (it is on left of += operator)
    friend WallClockTime operator -=(WallClockTime& clock1, const WallClockTime& clock2); //again don't use const for first argument 'clock1' because we are changing it (it is on left side of -= operator)
    friend WallClockTime operator *=(WallClockTime& clock1, const int n);


    //operator /= to compute(WallClockTime object) /= (int)
    friend WallClockTime operator /=(WallClockTime& clock1, const int n);

    friend bool operator <(const WallClockTime& clock1, const WallClockTime& clock2);
    friend bool operator <=(const WallClockTime& clock1, const WallClockTime& clock2);
    friend bool operator >(const WallClockTime& clock1, const WallClockTime& clock2);
    friend bool operator >=(const WallClockTime& clock1, const WallClockTime& clock2);

    friend bool operator ==(const WallClockTime& clock1, const WallClockTime& clock2);

    bool is12hourNotation() const; // getter for bool notation12hours returns true if 12-hours notation is set
    void set12hourNotation(bool flag); // set 12-hours notation true or false - setter for bool notation12hours
    friend std::ostream& operator << (std::ostream& strm, const WallClockTime& clock1);
    //
    //friend std::istream& operator >> (std::istream &strm, ImperialWeight& w1);
    friend std::istream& operator >> (std::istream& strm, const WallClockTime& clock1);
    //friend void setter(int new_hours, int new_minutes, int new_seconds);
    void setter(const int new_hours, const int new_minutes, const int new_seconds);
    void set_seconds(const int z);
    void set_minutes(const int z);
    void set_hours(const int z);
private:
    int clockHours;
    int clockMinutes;
    int clockSeconds;
    bool notation12hours;  // Flag for 12 hours notation. To be used by the '<<' operator to perform (ostream object) << (WallClockTime object). If 'notation12hours' is true, export the time with 12 - hours notation, if false, export the time with 24 - hours notation.
    //void setter(int new_hours, int new_minutes, int new_seconds); //Already present in the public: portion above.
    /*void set_seconds(const int z);
    void set_minutes(int z);
    void set_hours(int z);*/
    //
    void seconds_helper(void);
    void minutes_helper(void);
    void hours_helper(void);
    //void setter(int new_hours, int new_minutes, int new_seconds);
    /*These helper functions must be private member:
    void seconds_helper(void); void minutes_helper(void); void hours_helper(void);*/
};


//default constructor
//precondition: this is a constructor to initialize a WallClockTime object
//postcondition: after being called a WallClockTime will be initialized with hours, minutes, and seconds equal to 0
WallClockTime::WallClockTime(void)
{
    notation12hours = false;
    clockHours = 0;
    clockMinutes = 0;
    clockSeconds = 0;
    seconds_helper();
    minutes_helper();
    hours_helper();
}

//constructor that takes 3 arguments/parameters: int hours, int minutes and int seconds
//precondition: takes 3 arguments/parameters of data type int with the intention to set the hours, minutes, and seconds of the WallClockTime object equal to them
//postcondition: the wallclock on which this function was called has changed its stored values for hours, minutes, and seconds to those passed to the function
WallClockTime::WallClockTime(const int hours, const int minutes, const int seconds) //initializes clockHours to int 'hours', clockMinutes to int 'minutes', clockSeconds to int 'seconds'
{
    notation12hours = false;
    clockHours = hours;
    clockMinutes = minutes;
    clockSeconds = seconds;
    seconds_helper();
    minutes_helper();
    hours_helper();
}

//constructor that takes only 2 arguments: int minutes, and int seconds
//precondition: takes 2 variables of data type int - minutes, and seconds
//postcondition: creates a WallClockTime object with clockHours set to 0 and with minutes and seconds set to the 2 variables of data type int passed to the function
WallClockTime::WallClockTime(const int minutes, const int seconds) //initializes clockHours to 0, clockMinutes to int minutes, and clockSeconds to int seconds
{
    notation12hours = false;
    clockHours = 0;
    clockMinutes = minutes;
    clockSeconds = seconds;
    seconds_helper();
    minutes_helper();
    hours_helper();
}

//constructor that takes only 1 argument, int seconds
//precondition: takes one parameter/argument, seconds, of data type int
//postcondition: constructs a new WallClockTime object with hours and minutes equal to 0, and with seconds equal to the parameter of data type int passed to the function
WallClockTime::WallClockTime(const int seconds) //initializes clockSeconds to equal int seconds, and initializes clockHours and clockMinutes to equal 0
{
    notation12hours = false;
    clockHours = 0;
    clockMinutes = 0;
    clockSeconds = seconds;
    seconds_helper();
    minutes_helper();
    hours_helper();
}

//precondition: takes no parameters
//postcondition: adjusts the number of seconds and minutes until the number of seconds is between 0 and 59 inclusive, then returns this number as data type int
int WallClockTime::get_seconds() const
{
    /*while (clockSeconds < 0)
    {
        clockSeconds += secondsInAMinute;
        clockMinutes--;
    }
    while (clockSeconds >= secondsInAMinute)
    {
        clockSeconds -= secondsInAMinute;
        clockMinutes++;
    }*/
    return clockSeconds;
}
void WallClockTime::setter(const int new_hours, const int new_minutes, const int new_seconds)
{
    clockHours = new_hours;
    clockMinutes = new_minutes;
    clockSeconds = new_seconds;
}
void WallClockTime::set_seconds(const int z)
{
    clockSeconds = z;
}
void WallClockTime::set_minutes(const int z)
{
    clockMinutes = z;
}
void WallClockTime::set_hours(const int z)
{
    clockHours = z;
}

//precondition: takes no parameters
//postcondition: returns number of minutes
int WallClockTime::get_minutes() const //getter for private variable clockMinutes
{
    return clockMinutes;
}
//precondition: takes no arguments
//postcondition: returns bool value of private variable notation12hours
bool WallClockTime::is12hourNotation() const //getter for private variable notation12hours
{
    return notation12hours; //returns value of notation12hours - returns true if output should be 12hr format, returns false if output should be 24hr format
}
//precondition: takes an argument 'flag' of data type bool
//postcondition: private variavle notation12hours has been set to equal variable 'flag'
void WallClockTime::set12hourNotation(bool flag) //setter for private variable 'notation12hours' of data type bool
{
    notation12hours = flag;
}
//precondition: takes no parameters
//postcondition: returns the number of hours (after adjusting the amount of hours until between 0 and 24 inclusive if it is not already in that range)
int WallClockTime::get_hours() const //getter for private variable clockHours
{
    return clockHours;
}
//precondition: takes an ostream object as an argument via call-by-reference
//postcondition: outputs the time in 24-hour format to the output stream passed to the function
void WallClockTime::showTime24(std::ostream& osObj) //displays the time on 24-hr clocks (no a.m. or p.m.
{
    seconds_helper();
    minutes_helper();
    hours_helper();
    int seconds = get_seconds(); //calling this function here first ensures that seconds is within the allowable range of [0,60)    - brackets for inclusive, parenthesis for exclusive (60 isn't in set; 0 is in set)

    int minutes = get_minutes(); //calling this function here after get_seconds() has been called ensures that both are within their allowable ranges of [0,60) for int variables clockMinutes and clockSeconds

    int hours = get_hours(); //calling this function here after get_seconds() and get_minutes() ensures that Hours if in it's acceptable range of 0 to 24 inclusive, or [0,24]
    osObj << std::setw(2) << std::setfill('0') << get_hours() << ':' << std::setw(2) << std::setfill('0') << get_minutes() << ':' << std::setw(2) << std::setfill('0') << get_seconds() << std::endl; //use setw and setfill to ensure leading zeroes are present when necessary
}
//precondition: helper function to fix seconds
//postcondition: seconds is within its acceptable range
void WallClockTime::seconds_helper(void)
{
    while (clockSeconds < 0)
    {
        clockSeconds += secondsInAMinute;
        clockMinutes--;
    }
    while (clockSeconds >= secondsInAMinute)
    {
        clockSeconds -= secondsInAMinute;
        clockMinutes++;
    }
}
//precondition:helper function to fix minutes
//postcondition: minutes is within its acceptable range
void WallClockTime::minutes_helper(void)
{
    while (clockMinutes < 0) //loop adds 60 to minutes and subtracts 1 from hours until clockMinutes is above 0 if it was less than 0
    {
        clockMinutes += minutesInAnHour;
        clockHours--;
    }
    while (clockMinutes >= minutesInAnHour)//if clockMinutes is greater than or equal to 60, this loop subtracts 60 from minutes and adds 1 to hours until clockMinutes is below 60
    {
        clockMinutes -= minutesInAnHour;
        clockHours++;
    }
}
//precondition: helper function to fix hours
//postcondition: hours is within the its acceptable range
void WallClockTime::hours_helper(void)
{
    while (clockHours < 0) //adds 24 to clockHours until it is no longer less than 0
    {
        clockHours += hoursInOneEntireCycle;
    }
    while (clockHours >= hoursInOneEntireCycle) //subtracts 24 to clockHours until it is no longer greater than 24
    {
        clockHours -= hoursInOneEntireCycle;
    }
}
//precondition: takes an ostream object as a parameter via call-by-reference
//postcondition: outputs the time in 12 hour format (including am or pm) to the ostream object passed to the function
void WallClockTime::showTime12(std::ostream& osObj)
{
    seconds_helper();
    minutes_helper();
    hours_helper();
    std::string AMorPM("am"); //set string to "am" by default and test if it is after noon ("pm")
    std::string testAMorPM2("am");
    int testAMorPM = get_hours() % hoursInOneEntireCycle;
    if (testAMorPM >= hoursInOneEntireCycle / 2)
    {
        AMorPM = "pm";
        testAMorPM -= 12;
    }

    else
        AMorPM = "am";

    int seconds = get_seconds(); //calling this function here first ensures that seconds is within the allowable range of [0,60)    - brackets for inclusive, parenthesis for exclusive (60 isn't in set; 0 is in set)

    int minutes = get_minutes(); //calling this function here after get_seconds() has been called ensures that both are within their allowable ranges of [0,60) for int variables clockMinutes and clockSeconds

    int hours = get_hours(); //calling this function here after get_seconds() and get_minutes() ensures that Hours if in it's acceptable range of 0 to 24 inclusive, or [0,24]
    if ((AMorPM == "am") && (get_hours() == 0))
        hours += hoursInOneEntireCycle / 2;
    if ((AMorPM == "pm") && (get_hours() > hoursInOneEntireCycle / 2))
        hours -= hoursInOneEntireCycle / 2;
    //osObj << std::setw(2)<<std::setfill('0');
   // if (get_hours() > hoursInOneEntireCycle / 2)
       // set_hours(get_hours() - hoursInOneEntireCycle / 2);
    if ((get_hours() > (hoursInOneEntireCycle / 2) && (AMorPM == "pm")))
    {
        int outputHours = get_hours() - hoursInOneEntireCycle / 2;

        osObj << std::setw(2) << std::setfill('0') << outputHours;
    }
    else
        osObj << std::setw(2) << std::setfill('0') << get_hours();
    osObj << ':' << std::setw(2) << std::setfill('0') << get_minutes();
    osObj << ':' << std::setw(2) << std::setfill('0') << get_seconds() << AMorPM << std::endl; //use setw and setfill to ensure leading zeroes are present when necessary

}
//precondition: function takes two WallClockTime objects as arguments/parameters via call-by-reference
//postcondition: returns a comp type (enum type) variable of GREATER, LESS, OR EQUAL if time of clock1 is greater than, less than, or equal to time of clock 2. For clarity, I am stating that one clock is considered to be greater than another clock if its time is later in a day than the other clock, and a clock is considered to be less than another clock if its time is earlier in the day than the second clock.
comp compare(const WallClockTime& clock1, const WallClockTime& clock2) //friend function to compare 2 WallClockTime objects
{

    if (clock1.clockHours > clock2.clockHours)
        return GREATER;
    else if (clock1.clockHours == clock2.clockHours)
        if (clock1.clockMinutes > clock2.clockMinutes)
            return GREATER;
        else if (clock1.clockMinutes == clock2.clockMinutes)
            if (clock1.clockSeconds > clock2.clockSeconds)
                return GREATER;
            else if (clock1.clockSeconds == clock2.clockSeconds)
                return EQUAL;
    return LESS; //if the code has reached this line, it means that clock 1 is not greater than clock 2, and that clock 1 is not equal to clock 2, so clock1 must be less than clock2, and that is what is returned
}
//precondition: takes 2 WallClockTime objects as arguments/variables
//postcondition: adds the times of the two wall clock objects in initialization of a new sum WallClockObject, and this new WallClockObject is returned
WallClockTime add(const WallClockTime& clock1, const WallClockTime& clock2) //function definition for friend function add that adds 2 WallClockTime object and returns the summed WallClockTime object
{
    //double check this constructor to be sure on order of hours, minutes, and seconds
    //WallClockTime newSumObject = WallClockTime(clock1.get_hours() + clock2.get_hours(), clock1.get_minutes() + clock2.get_minutes(), clock1.get_seconds() + clock2.get_seconds());
    WallClockTime sum(clock1.clockHours + clock2.clockHours, clock1.clockMinutes + clock2.clockMinutes, clock1.clockSeconds + clock2.clockSeconds);
    //run functions of new clock to organize seconds, minutes, and hours properly
    return sum;
}
//precondition: takes 2 WallClockTime objects as arguments/variables on either side of the addition operator '+'
//postcondition: adds the times of the two wall clock objects in initialization of a new sum WallClockObject, and this new WallClockObject is returned
WallClockTime operator + (const WallClockTime& clock1, const WallClockTime& clock2) //function definition for friend operator +
{
    //double check this constructor to be sure on order of hours, minutes, and seconds
    WallClockTime sum(clock1.clockHours + clock2.clockHours, clock1.clockMinutes + clock2.clockMinutes, clock1.clockSeconds + clock2.clockSeconds);
    //run functions of new clock to organize seconds, minutes, and hours properly
    return sum;
}
//precondition: takes a WallClockTime object and an integer in that order
//postcondition: returns a new WallClockTime object that is the product of the integer and the WallClockTime object sent to the function
WallClockTime operator *(const WallClockTime& clock1, const int n) //definition for overloaded * operator with parameters of one WallClockTime and an integer in that order as shown on the left
{
    WallClockTime ClockScaledByFactorOf_N(n * clock1.get_hours(), n * clock1.get_minutes(), n * clock1.get_seconds());
    return ClockScaledByFactorOf_N;
}
//precondition: takes an integer in that order and a WallClockTime object
//postcondition: returns a new WallClockTime object that is the product of the WallClockTime object and the integer sent to the function
WallClockTime operator *(const int n, const WallClockTime& clock1) //definition for overloaded * operator with parameters of one integer and one WallClockTime object in that order as shown on the left
{
    WallClockTime ClockScaledByFactorOf_N(n * clock1.get_hours(), n * clock1.get_minutes(), n * clock1.get_seconds());
    return ClockScaledByFactorOf_N;
}
//precondition: takes a WallClockTime object and an int as the 2 parameters, in that order
//postconditon: returns a WallClockTime object that has been divided by integer n - that is to say the total
WallClockTime operator /(const WallClockTime& clock1, const int n) {
    WallClockTime dividedClock(clock1.get_hours() / n, clock1.get_minutes() / n, clock1.get_seconds() / n);
    return dividedClock;
}
//precondition: takes 2 WallClockTime objects as arguments 'clock1' and 'clock2'
//postcondition: returns true if clock1 is less than clock2, otherwise returns false
bool operator <(const WallClockTime& clock1, const WallClockTime& clock2) {
    return compare(clock1, clock2) == LESS; //if clock1 < clock2 (clock1 less than clock2), returns true, else returns false
}
//precondition: takes 2 WallClockTime objects as arguments, 'clock1' and 'clock2'
//postcondition: returns true if clock1 is less than or equal to clock2. returns false otherwise
bool operator <=(const WallClockTime& clock1, const WallClockTime& clock2) {
    comp cmp = compare(clock1, clock2);
    return (cmp == LESS) || (cmp == EQUAL); //returns true if clock1 is less than clock2 or if clock1 is equal to clock2
}
//precondition: takes 2 WallClockTime objects as arguments 'clock1' and 'clock2'
//postcondition: returns true if clock1 is greater than clock2, otherwise returns false
bool operator >(const WallClockTime& clock1, const WallClockTime& clock2) {
    comp cmp = compare(clock1, clock2); //if clock1 > clock2 (clock1 is greater than clock2) returns true, returns false if not the case
    return (cmp == GREATER);
}
//precondition: takes 2 WallClockTime objects as arguments 'clock1' and 'clock2'
//postcondition: returns true if clock1 is greater than or equal to clock2, otherwise returns false
bool operator >=(const WallClockTime& clock1, const WallClockTime& clock2) {
    comp cmp = compare(clock1, clock2);
    return (cmp == GREATER) || (cmp == EQUAL);
}
//precondition: takes 2 WallClockTime objects as arguments 'clock1' and 'clock2'
//postcondition: returns true if clock1 is equal to clock2, otherwise returns false
bool operator ==(const WallClockTime& clock1, const WallClockTime& clock2) {
    comp cmp = compare(clock1, clock2);
    return (cmp == EQUAL); //Returns true when clock1 equals clock2, returns false when clock1 and clock2 are not equivalent
}
//precondition: takes 2 WallClockTime objects as arguments, using const on the second argument 'clock2' because its value is not changed. const is not used on clock1 because it is changed. call-by-reference is used for both arguments because they are WallClockTime objects
//postcondition: creates and returns a new clock that is the sum of clock1 and clock2, and changes clock1 to equal this new clock (clock1 was on left of += operator and clock2 was on right of += operator, so clock2 is to be added to the current value of clock1)
WallClockTime operator +=(WallClockTime& clock1, const WallClockTime& clock2) //creates a new clock that is the sum of clock1 and clock2 and sets clock1 equal to this new clock
{
    //WallClockTime clock1_plus_clock2 = add(clock1, clock2);
    WallClockTime clock1_plus_clock2 = clock1 + clock2;
    clock1 = clock1_plus_clock2; //stores the WallClockTime object sum of clock1 and clock2 at the location where clock1 was formerly stored in memory
    return clock1_plus_clock2;
}
//precondition: takes 2 WallClockTime objects as arguments, using const on both as they are not changed
//postcondition: creates and returns a new clock that is the sum of clock1 and negative clock2, and changes clock1 to equal this new clock (clock1 was on left of -= operator and clock2 was on right of += operator, so clock2 is to be subtracted from the current value of clock1 with the new clock stored in clock1 at end of function)
WallClockTime operator -(const WallClockTime& clock1, const WallClockTime& clock2)
{
    WallClockTime negative_clock2 = -1 * clock2;
    WallClockTime clock1_minus_clock2 = clock1 + negative_clock2;

    return clock1_minus_clock2;
}
//precondition: takes 2 WallClockTime objects as arguments (call-by-reference used for both because they are WallClockTime objects), using const on the second argument 'clock2' because its value is not changed. const is not used on clock1 because it is changed. again, call-by-reference is used for both arguments because they are WallClockTime objects.
//postcondition: creates a new clock that is equal to clock1 minus clock2, which is equal to the sum of clock1 and negative clock2. (the sum of clock1 and negative clock2 is... clock1 + (-1 * clock2)) (clock1 was on left of -= operator and clock2 was on right of -= operator, so clock2 is to be subtracted from current value of clock1 with the result stored in clock1 before end of function)
WallClockTime operator -=(WallClockTime& clock1, const WallClockTime& clock2)
{
    WallClockTime negative_clock2 = -1 * clock2;
    WallClockTime clock1_minus_clock2 = add(clock1, negative_clock2);
    clock1 = clock1_minus_clock2;
    return clock1_minus_clock2;
}
//precondition: first argument is a WallClockTime object 'clock1' that uses call-by-reference since the argument is a WallClockTime object. const modifier is not used on first argument because this WallClockTime object argument is going to be altered. 'clock2' because its value is not changed. const is not used on clock1 because it is changed. call-by-reference is used for both arguments because they are WallClockTime objects
//postcondition: creates a new clock that is equal to clock1 * n, and stores this clock where clock1 formerly was in memory which is equal to the sum of clock1 and negative clock2. (the sum of clock1 and negative clock2 is... clock1 + (-1 * clock2)) (clock1 was on left of -= operator and clock2 was on right of -= operator, so clock2 is to be subtracted from current value of clock1 with the result stored in clock1 before end of function)
WallClockTime operator *=(WallClockTime& clock1, const int n)
{
    WallClockTime productClock = clock1 * n;
    clock1 = productClock;
    return productClock;
}
//precondition: takes 2 arguments - the first arguments is a WallClockTime object, so it is passed using call-by-reference, but it is modified by the '/=' operation, so we do not use the 'const' modifier. second argument 'n' of data type int is the amount that the first argument clock is divided by
//postcondition: clock1 has been altered - it has been divided by the value of argument int 'n'
WallClockTime operator /=(WallClockTime& clock1, const int n)
{
    WallClockTime quotientClock = clock1 / n;
    clock1 = quotientClock;
    return quotientClock;
}
std::ostream& operator << (std::ostream& strm, WallClockTime& clock1)
{
    if (clock1.is12hourNotation())
    {
        clock1.showTime12(strm);
        return strm;
    }
    else
        clock1.showTime24(strm);
    return strm;
}
//////operator >> to perform(istream object) >> (WallClockTime object)
//////Obtain integers of hours, minutes, and seconds in 24 - hours notation from a stream object.
std::istream& operator >> (std::istream& strm, WallClockTime& clock1)
{
    int new_clockHours = 0;
    int new_clockMinutes = 0;
    int new_clockSeconds = 0;
    new_clockHours = clock1.get_hours();
    new_clockMinutes = clock1.get_minutes();
    new_clockSeconds = clock1.get_seconds();
    WallClockTime newClock2 = WallClockTime(new_clockHours, new_clockMinutes, new_clockSeconds);
    strm >> new_clockHours >> new_clockMinutes >> new_clockSeconds; // // // // // //
    clock1.setter(new_clockHours, new_clockMinutes, new_clockSeconds);

    return strm;
}
/*    //int main(int argc, const char* argv[]) {
    //const WallClockTime noon(12, 0, 0);
    //// test << and >>
    //std::cout << "What time is it now?\n";
    //std::cout << "(hour) (minute) (second) separated by space :";
    //WallClockTime time1;
    //std::cin >> time1;
    //time1.set12hourNotation(true);
    //std::cout << "Current time is " << time1 << std::endl;
    //if (time1.is12hourNotation()) {
    //    time1.set12hourNotation(false);
    //    std::cout << "Current time is " << time1 << std::endl;
    //}
    //// test comparition operators
    //std::cout << "Lunch is " << noon - time1 << " ahead.\n";
    //if (time1 == noon) {
    //    std::cout << "It's lunch time.\n";
    //}
    //if (time1 <= noon && time1 >= noon) {
    //    std::cout << "Yes! It's lunch time.\n";
    //}
    //if (time1 < noon) {
    //    std::cout << noon - time1 << " to lunch time.\n";
    //}
    //if (time1 > noon) {
    //    std::cout << time1 - noon << " past lunch time.\n";
    //}
    //// test /
    //const WallClockTime oneHour(3600);
    //WallClockTime twentyMin = oneHour / 3;
    //// test +
    //std::cout << "20 minutes from now is " << time1 + twentyMin << std::endl;
    //// test /=
    //twentyMin = oneHour;
    //twentyMin /= 3;
    //// test +=
    //time1 += twentyMin;
    //std::cout << "20 minutes from now is " << time1 << std::endl;
    //// test -=
    //time1 -= twentyMin;
    //std::cout << "Current time is " << time1 << std::endl;
    //// test *
    //if (twentyMin * 3 == oneHour) {
    //    std::cout << "20 min x 3 = 1 hour\n";
    //}
    //if (3 * twentyMin == oneHour) {
    //    std::cout << "3 x 20 min = 1 hour\n";
    //}
    //// test *=
    //twentyMin *= 24 * 3 + 1; // = 20 min
    //std::cout << twentyMin << std::endl;
    //   return 0;
    //}
    //
    //
*/
//std::ostream& operator << (std::ostream& strm, const WallClockTime& clock1) {
//    //*********2308452448206846028406248608268205
//    if (clock1.is12hourNotation() == true)
//    {
//        clock1.showTime12(strm);
//    }
//    else
//        strm << clock1.showTime24(std::cout);
//    strm << clock1.pounds << "(lb) " << clock1.ounces << "(oz)";
//    return strm;
//}
//delete
void test_add_function(void);

void test_add_function(void)
{
    WallClockTime toBeAdded_Clock1(27, 0, 30); //initializes a clock to the time of 03:00:30 (on 24 hour scale; 3:00:30am on 12 hour scale)
    WallClockTime toBeAdded_Clock2(13, 0, 32); //initializes a clock to the time of 13:00:32 (on 24 hour scale; 1:00:32pm on 12 hour scale)
    std::cout << std::endl << "The following lines demonstrate usage of the 'add' friend function. \nClock 1 to be added has a time of ";
    toBeAdded_Clock1.showTime24(std::cout);
    std::cout << endl << "Clock 2 to be added has a time of ";
    toBeAdded_Clock2.showTime24(std::cout);
    std::cout << endl;

    //creates a new WallClockTime object 'addedClock' using the function 'add' that takes 2 WallClockTime objects as parameters and returns the summed WallClockTime object
    WallClockTime addedClock = add(toBeAdded_Clock1, toBeAdded_Clock2);

    // cout << "\n\nThe new clock that is the sum of the 2 clocks has a time of ";
     //add(toBeAdded_Clock1, toBeAdded_Clock2).showTime12(cout);
     //addedClock.showTime24(cout);
    std::cout << "In 12-hour format the new clock that is the sum of the 2 clocks shown the time is ";
    addedClock.showTime12(std::cout);
    std::cout << "In 24-hour format the new clock that is the sum of the 2 clocks shown the time is ";
    addedClock.showTime24(std::cout);
    //cout << "\n";
}
void do_things(void);

void do_things(void)
{
    WallClockTime noon(12, 0, 0);

    // test << and >>
    std::cout << "What time is it now?\n";
    std::cout << "(hour) (minute) (second) separated by space :";
    WallClockTime time1;
    //std::cin >> time1;
    //time1.set12hourNotation(true);
    //std::cout << "Current time is " << time1 << std::endl;

    //if (time1.is12hourNotation()) {
    //    time1.set12hourNotation(false);
    //    std::cout << "Current time is " << time1 << std::endl;
    //}

    //// test comparition operators
    //std::cout << "Lunch is " << noon - time1 << " ahead.\n";
    //if (time1 == noon) {
    //    std::cout << "It's lunch time.\n";
    //}
    //if (time1 <= noon && time1 >= noon) {
    //    std::cout << "Yes! It's lunch time.\n";
    //}
    //if (time1 < noon) {
    //    std::cout << noon - time1 << " to lunch time.\n";
    //}
    //if (time1 > noon) {
    //    std::cout << time1 - noon << " past lunch time.\n";
    //}

    //// test /
    //const WallClockTime oneHour(3600);
    //WallClockTime twentyMin = oneHour / 3;

    //// test +
    //std::cout << "20 minutes from now is " << time1 + twentyMin << std::endl;
    //// test /=
    //twentyMin = oneHour;
    //twentyMin /= 3;
    //// test +=
    //time1 += twentyMin;
    //std::cout << "20 minutes from now is " << time1 << std::endl;
    //// test -=
    //time1 -= twentyMin;
    //std::cout << "Current time is " << time1 << std::endl;

    //// test *
    //if (twentyMin * 3 == oneHour) {
    //    std::cout << "20 min x 3 = 1 hour\n";
    //}
    //if (3 * twentyMin == oneHour) {
    //    std::cout << "3 x 20 min = 1 hour\n";
    //}

    //// test *=
    //twentyMin *= 24 * 3 + 1; // = 20 min
    //std::cout << twentyMin << std::endl;

}

int main(int argc, const char* argv[]) {
    // time1
    WallClockTime wctime1;
    std::cout << "Time1 is " << wctime1.get_hours() << 'h'
        << wctime1.get_minutes() << 'm'
        << wctime1.get_seconds() << 's' << std::endl;
    wctime1.showTime24(std::cout);
    wctime1.showTime12(std::cout);

    // time2
    WallClockTime wctime2(12, 0, 0);
    std::cout << "Time2 is " << wctime2.get_hours() << 'h'
        << wctime2.get_minutes() << 'm'
        << wctime2.get_seconds() << 's' << std::endl;
    wctime2.showTime24(std::cout);
    wctime2.showTime12(std::cout);

    // time3
    WallClockTime wctime3(780, 0);
    std::cout << "Time3 is " << wctime3.get_hours() << 'h'
        << wctime3.get_minutes() << 'm'
        << wctime3.get_seconds() << 's' << std::endl;
    wctime3.showTime24(std::cout);
    wctime3.showTime12(std::cout);

    // time4
    WallClockTime wctime4(-86401);
    std::cout << "Time4 is " << wctime4.get_hours() << 'h'
        << wctime4.get_minutes() << 'm'
        << wctime4.get_seconds() << 's' << std::endl;
    wctime4.showTime24(std::cout);
    wctime4.showTime12(std::cout);

    // BEGIN TEST CODE FOR ADDITIONS OF HOMEWORK17 - ADD AND COMPARE FRIEND FUNCTIONS
    //WallClockTime toBeAdded_Clock1(27, 0, 30); //initializes a clock to the time of 03:00:30 (on 24 hour scale; 3:00:30am on 12 hour scale)
    //WallClockTime toBeAdded_Clock2(13, 0, 32); //initializes a clock to the time of 13:00:32 (on 24 hour scale; 1:00:32pm on 12 hour scale)
    //std::cout << std::endl << "The following lines demonstrate usage of the 'add' friend function. \nClock 1 to be added has a time of ";
    //toBeAdded_Clock1.showTime24(std::cout);
    //std::cout << endl << "Clock 2 to be added has a time of ";
    //toBeAdded_Clock2.showTime24(std::cout);
    //std::cout << endl;

    ////creates a new WallClockTime object 'addedClock' using the function 'add' that takes 2 WallClockTime objects as parameters and returns the summed WallClockTime object
    //WallClockTime addedClock = add(toBeAdded_Clock1, toBeAdded_Clock2);

    //// cout << "\n\nThe new clock that is the sum of the 2 clocks has a time of ";
    // //add(toBeAdded_Clock1, toBeAdded_Clock2).showTime12(cout);
    // //addedClock.showTime24(cout);
    //std::cout << "In 12-hour format the new clock that is the sum of the 2 clocks shown the time is ";
    //addedClock.showTime12(std::cout);
    //std::cout << "In 24-hour format the new clock that is the sum of the 2 clocks shown the time is ";
    //addedClock.showTime24(std::cout);
    ////cout << "\n";
    ////
    test_add_function();
    //// END TEST CODE FOR ADD FUNCTION
    //
    //
    // // // // // // // // // // // // // //
    /////////////////////////////////////////
    // // // // // // // // // // // // // //
    // BEGIN TEST CODE FOR COMPARE FUNCTION
    WallClockTime toBeCompared_Clock1(27, 0, 30);
    WallClockTime toBeCompared_Clock2(13, 0, 32);
    comp comparison = compare(toBeCompared_Clock1, toBeCompared_Clock2);
    std::cout << std::endl << "The following lines demonstrate usage of the 'compare' friend function. \n   Clock 1 to be compared has a time of ";
    toBeCompared_Clock1.showTime24(std::cout);
    std::cout << endl << "   Clock 2 to be compared has a time of ";
    toBeCompared_Clock2.showTime24(std::cout);
    if (comparison == LESS)
        cout << "Clock 1 is less than Clock 2\n";
    else if (comparison == EQUAL)
        cout << "Clock 1 is equal to Clock 2\n";
    else if (comparison == GREATER)
        cout << "Clock 1 is greater than Clock 2\n";
    //cout << compare(toBeAdded_Clock1, toBeAdded_Clock2) << endl;
    toBeCompared_Clock1 = WallClockTime(18, 3, 2);
    toBeCompared_Clock2 = WallClockTime(7, 1, 3);
    comparison = compare(toBeCompared_Clock1, toBeCompared_Clock2);
    std::cout << std::endl << "\n   Clock 1 to be compared has a time of ";
    toBeCompared_Clock1.showTime24(std::cout);
    std::cout << endl << "   Clock 2 to be compared has a time of ";
    toBeCompared_Clock2.showTime24(std::cout);
    if (comparison == -1)
        std::cout << "Clock 1 is less than Clock 2\n";
    else if (comparison == 0)
        std::cout << "Clock 1 is equal to Clock 2\n";
    else if (comparison == 1)
        std::cout << "Clock 1 is greater than Clock 2\n";
    //
    //cout << compare(toBeAdded_Clock1, toBeAdded_Clock2) << endl;
    toBeCompared_Clock1 = WallClockTime(15, 40, 21);
    toBeCompared_Clock2 = WallClockTime(15, 40, 21);

    comparison = compare(toBeCompared_Clock1, toBeCompared_Clock2);
    std::cout << std::endl << "\n   Clock 1 to be compared has a time of ";
    toBeCompared_Clock1.showTime24(std::cout);
    std::cout << endl << "   Clock 2 to be compared has a time of ";
    toBeCompared_Clock2.showTime24(std::cout);
    if (comparison == -1)
        std::cout << "Clock 1 is less than Clock 2\n";
    else if (comparison == 0)
        std::cout << "Clock 1 is equal to Clock 2\n";
    else if (comparison == 1)
        std::cout << "Clock 1 is greater than Clock 2\n";


    // END TEST CODE FOR COMPARE FUNCTION
    // // // // // // // // // // // // // //
    /////////////////////////////////////////
    WallClockTime test1(9, 5, 3); //clock set to 9:05:03am
    std::cout << endl << test1 << endl;
    test1.set12hourNotation(true);
    std::cout << test1 << endl;
    test1.set12hourNotation(false);
    std::cout << test1 << endl;
    WallClockTime test2(18, 5, 3); //clock set to 6:05:03pm
    std::cout << test2 << endl;
    test2.set12hourNotation(true);
    std::cout << "The current test time is: (test2 put into stream now) " << test2 << endl;
    std::cout << "Now enter 3 integers for hours, minutes, seconds of new WallClockTime object\n (Overloaded << operator for WallClockTime objects creates a 24-hour clock, not 12-hr clock):\n";
    WallClockTime testClock4;
    WallClockTime testClock3;

    std::cin >> testClock4;

    //testClock4.set12hourNotation(false);

    std::cout << std::endl << "Clock testClock4 - after used as an object within cin istream and >> operator overloaded - has a 24hr-time of " << testClock4 << endl << "This time was output in default 24-hour format as set by constructors\n\n";

    //now test output using overloaded << operator when flag of data type bool equals true - that is, when time is 12hr format (am/pm!)
    testClock4.set12hourNotation(true);
    std::cout << std::endl << "Clock testClock4 - after used as an object within cin istream and >> operator overloaded (then setting flag for 12hr-format equal to true using setter for that variable) - has a 12hr-time of " << testClock4 << endl << "This time was output in 12-hour format since the flag is true\n\n";

    //test2.showTime24(std::cout);

    //
    //

    ////WallClockTime noon(12,0,0);

    ////// test << and >>
    ////std::cout << "What time is it now?\n";
    ////std::cout << "(hour) (minute) (second) separated by space :";
    ////WallClockTime time1;
    ////std::cin >> time1;
    ////time1.set12hourNotation(true);
    ////std::cout << "Current time is " << time1 << std::endl;
    ////
    ////if (time1.is12hourNotation()){
    ////    time1.set12hourNotation(false);
    ////    std::cout << "Current time is " << time1 << std::endl;
    ////}
    ////
    ////// test comparition operators
    ////std::cout << "Lunch is " << noon - time1 << " ahead.\n";
    ////if (time1 == noon){
    ////    std::cout << "It's lunch time.\n";
    ////}
    ////if (time1 <= noon && time1 >= noon){
    ////    std::cout << "Yes! It's lunch time.\n";
    ////}
    ////if (time1 < noon){
    ////    std::cout << noon - time1 << " to lunch time.\n";
    ////}
    ////if (time1 > noon){
    ////    std::cout << time1 - noon << " past lunch time.\n";
    ////}
    ////
    ////// test /
    ////const WallClockTime oneHour(3600);
    ////WallClockTime twentyMin = oneHour / 3;
    ////
    ////// test +
    ////std::cout << "20 minutes from now is " << time1 + twentyMin << std::endl;
    ////// test /=
    ////twentyMin = oneHour;
    ////twentyMin /= 3;
    ////// test +=
    ////time1 += twentyMin;
    ////std::cout << "20 minutes from now is " << time1 << std::endl;
    ////// test -=
    ////time1 -= twentyMin;
    ////std::cout << "Current time is " << time1 << std::endl;
    ////
    ////// test *
    ////if (twentyMin * 3 == oneHour){
    ////    std::cout << "20 min x 3 = 1 hour\n";
    ////}
    ////if (3 * twentyMin == oneHour){
    ////    std::cout << "3 x 20 min = 1 hour\n";
    ////}
    ////
    ////// test *=
    ////twentyMin *= 24 * 3 + 1; // = 20 min
    ////std::cout << twentyMin << std::endl;
    //

    //
 //   //
 WallClockTime noon(12,0,0);

    // test << and >>
    std::cout << "What time is it now?\n";
    std::cout << "(hour) (minute) (second) separated by space :";
    //WallClockTime time8(1,0,0);
    std::cin >> test2;
    test2.set12hourNotation(true);
    std::cout << "Current time is " << test2 << std::endl;
    if (test2.is12hourNotation()){
        test2.set12hourNotation(false);
        std::cout << "Current time is " << test2 << std::endl;
    }
    //
    //// test comparition operators
    //std::cout << "Lunch is " << noon - time8 << " ahead.\n";
    //if (time8 == noon){
    //    std::cout << "It's lunch time.\n";
    //}
    //if (time8 <= noon && time8 >= noon){
    //    std::cout << "Yes! It's lunch time.\n";
    //}
    //if (time8 < noon){
    //    std::cout << noon - time8 << " to lunch time.\n";
    //}
    //if (time8 > noon){
    //    std::cout << time8 - noon << " past lunch time.\n";
    //}
 //  
 //   // test /
 //   const WallClockTime oneHour(3600);
 //   WallClockTime twentyMin = oneHour / 3;
 //  
 //   // test +
 //   std::cout << "20 minutes from now is " << time1 + twentyMin << std::endl;
 //   // test /=
 //   twentyMin = oneHour;
 //   twentyMin /= 3;
 //   // test +=
 //   time1 += twentyMin;
 //   std::cout << "20 minutes from now is " << time1 << std::endl;
 //   // test -=
 //   time1 -= twentyMin;
 //   std::cout << "Current time is " << time1 << std::endl;
 //  
 //   // test *
 //   if (twentyMin * 3 == oneHour){
 //       std::cout << "20 min x 3 = 1 hour\n";
 //   }
 //   if (3 * twentyMin == oneHour){
 //       std::cout << "3 x 20 min = 1 hour\n";
 //   }
 //  
 //   // test *=
 //   twentyMin *= 24 * 3 + 1; // = 20 min
 //   std::cout << twentyMin << std::endl;
 //  

    return 0;
}
