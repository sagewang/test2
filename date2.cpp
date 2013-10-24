#include "date2.h"
#include<iostream>
#include<fstream>
#include"month.h"
#include"date.h"

using namespace std;
const int DAYSINMONTH[2][13]={{0,31,59,90,120,151,181,212,243,273,304,334,365},
                              {0,31,60,91,121,152,182,213,244,274,305,335,366}};
Date2::Date2()
{
    dayno=0;
}
Date2::Date2(int day)
{
    dayno=day;
}

Date2::Date2(int d,int m,int y)
{
    int year=y-2000;
    dayno=year*365+year/4-year/100+year/400+DAYSINMONTH[Month(m).IsLeap(y)][m-1]+d;
}
void Date2::SetDate(int n)
{
    dayno=n;
}
void Date2::SetDate(int d, int m, int y)
{
    int year=y-2000;
    dayno=year*365+year/4-year/100+year/400+DAYSINMONTH[Month(m).IsLeap(y)][m-1]+d;
}
void Date2::GetDate(int &d,int &m,int &y)
{
    y=dayno*400/146097;
    dayno-=y*365+y/4-y/100+y/400;
    y+=2000;

    int i=0;
    while (dayno>DAYSINMONTH[IsLeap(y)][i]){
        i++;}
    m=i;

    dayno-=DAYSINMONTH[IsLeap(y)][m-1];
    d=dayno;
}
int Date2::GetDayno()
{
    return dayno;
}

void Date2::Show(ostream& out)
{
    out<<":"<<dayno;
}

bool Date2::IsLeap(int year)
{
    if (year%400==0){
       return true;}
    else if (year%100==0){
       return false;}
    else if (year%4==0){
       return true;}
    else{
       return false;}
}

Date2 operator+ (Date2 A, int n)
{
    int after=A.dayno+n;
    return Date2(after);
}

Date2 operator- (Date2 A, int n)
{
    int after=A.dayno-n;
    return Date2(after);
}
int operator- (Date2 A, Date2 B)
{
    return (A.dayno-B.dayno);
}

bool operator== (Date2 A, Date2 B)
{
    return (A.dayno==B.dayno);
}

ostream& operator<< (ostream& out, Date2 A)
{
    int d=0,m=0,y=0;
    A.GetDate(d,m,y);
    out<<"d/m/y:"<<d<<"/"<<m<<"/"<<y;
    return out;
}

istream& operator >> (istream& in, Date2& A)
{
    char junk1, junk2;
    int d=0,m=0,y=0;
    in>>d>>junk1>>m>>junk2>>y;
    A.SetDate(d,m,y);
    return in;
}

Date2 operator++ (Date2& A, int)//A++
{
    Date2 B(A);
    A.dayno++;
    return B;
}

Date2 operator++ (Date2& A)//++A
{
    A.dayno++;
    return A;
}
