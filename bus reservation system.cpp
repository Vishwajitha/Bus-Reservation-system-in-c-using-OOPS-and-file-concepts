#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <iomanip>
using namespace std;
class Student;
class Bus
{
protected:
int fare,routeNo;
string route[10],nameOfBus,startTime,reachTime;
public:
void viewBusDetails();
void read();
void search(string); //search bus via boarding pnt
bool search(int,string);  //check whether entered pnt is available in selected route
int booked,capacity;
static int bcnt;
};

int Bus::bcnt;

class Admin: public Bus
{
private:
string username,password;
public:
void ViewBusBookings();
void ViewBusPasses(Student []);
void loginCheck();
void AddNewBus();
}b[30],a;

class Student
{
protected:
string rollNo,branch,bloodGrp,boardingPt,name;
int routeNo,year,sno;
public:
void book();
void downloadBusPass(int);
void downloadBusPass();
void read();
friend void Admin :: ViewBusPasses(Student []);
        static int cnt;
}s[300];

int Student ::cnt ;

void Bus :: read()
{
ifstream BusCnt("C:\\Users\\Admin\\Downloads\\BusCount.txt");
BusCnt>>bcnt;
BusCnt.close();
ifstream file("C:\\Users\\Admin\\Downloads\\buses.txt");
ifstream capfile("C:\\Users\\Admin\\Downloads\\capacity.txt");
for(int i=0;i<bcnt;i++)
{
file>>b[i].routeNo>>b[i].nameOfBus>>b[i].fare>>b[i].startTime>>b[i].reachTime;
for(int j=0;j<10;j++)
file>>b[i].route[j];
b[i].capacity=10;
capfile>>b[i].booked;
}
file.close();
capfile.close();
}

void Bus :: viewBusDetails()
{
system("cls");
cout<<"\n\n\t\t\t\tBus Details - VNRVJIET"<<endl;
for(int i=0;i<bcnt;i++)
{
cout<<"\n\n"<<i+1<<"> Route Number "<<b[i].routeNo<<" : "<<b[i].nameOfBus<<" Fare : Rs."<<b[i].fare<<"/-\nBus Timings: Departure : "<<b[i].startTime<<" Arrival : "<<b[i].reachTime<<"\nRoute : ";
for(int j=0;j<10;j++)
{
cout<<b[i].route[j]<<" ";
}
cout<<"\nCapacity : "<<b[i].capacity<<"\nBooked : "<<b[i].booked;
}
}
bool Bus::search(int rno,string stop)
{
bool flag=false;
for(int i=0;i<10;i++)
{
if(b[rno-1].route[i]==stop)
{
flag=true;
break;
}
}
return flag;
}
void Bus :: search(string stop)
{
int found=0;
for(int i=0;i<bcnt;i++)
{
int flag=0;
for(int j=0;j<10;j++)
{
if(b[i].route[j]==stop)
{
flag=1;
break;
}
}
if(flag)
{
cout<<"\n\n"<<i+1<<">\tRoute Number "<<b[i].routeNo<<"\t:"<<b[i].nameOfBus
<<"\tFare : Rs.\t"<<b[i].fare<<"/-\nBus Timings: Departure : "<<
b[i].startTime<<"\tArrival : "<<b[i].reachTime
<<"\nRoute : ";
for(int j=0;j<10;j++)
{
cout<<b[i].route[j]<<" ";
}
cout<<"\nCapacity : "<<b[i].capacity<<"\nBooked : "<<b[i].booked<<"\n";
found=1;
}
}
if(!found)
cout<<"No buses available for searched stop!!"<<endl;
}


void Student :: read()
{
ifstream studentCnt("C:\\Users\\Admin\\Downloads\\StudentCount.txt");
studentCnt>>cnt;
studentCnt.close();
ifstream student("C:\\Users\\Admin\\Downloads\\student.txt");
for(int i=0;i<cnt;i++)
{
student>>s[i].sno>>s[i].name>>s[i].rollNo>>s[i].branch>>s[i].year>>s[i].bloodGrp;
student>>s[i].boardingPt>>s[i].routeNo;
}
student.close();
}
void Student :: book()
{
system("cls");
cout<<"\n\n\t\tBus Booking Application form - VNRVJIET"<<endl;
s[cnt].sno=cnt+1;
cout<<"\nEnter your name : ";
cin>>s[cnt].name;
cout<<"\nEnter your roll number : ";
cin>>s[cnt].rollNo;
cout<<"\nEnter your branch : ";
cin>>s[cnt].branch;
cout<<"\nEnter your year : ";
cin>>s[cnt].year;
cout<<"\nEnter your blood group : ";
cin>>s[cnt].bloodGrp;
cout<<"\nEnter your boarding point : ";
cin>>s[cnt].boardingPt;
cout<<"\nEnter route number you wish to travel in : ";
cin>>s[cnt].routeNo;
//bool flag= search(b,s[cnt].routeNo,s[cnt].boardingPt);
bool flag= b[0].search(s[cnt].routeNo,s[cnt].boardingPt);
if(flag)
{
if(b[routeNo-1].booked+1<=b[routeNo-1].capacity)
{
char choice;
cout<<"\nDo you want to proceed for payment : (y/n) "<<endl;
cin>>choice;
if(choice=='y')
{
cout<<"\nBooking confirmed";
cnt++;
b[routeNo-1].booked++;
ofstream cntfile("C:\\Users\\Admin\\Downloads\\StudentCount.txt");
cntfile<<cnt;
cntfile.close();
ofstream capfile("C:\\Users\\Admin\\Downloads\\capacity.txt");
for(int i=0;i<Bus::bcnt;i++)
capfile<<b[i].booked<<" ";
capfile.close();
ofstream stufile("C:\\Users\\Admin\\Downloads\\student.txt",ios::app);
stufile<<s[cnt-1].sno<<" "<<s[cnt-1].name<<" "<<s[cnt-1].rollNo;
stufile<<" "<<s[cnt-1].branch<<" "<<s[cnt-1].year<<" "<<s[cnt-1].bloodGrp;
stufile<<" "<<s[cnt-1].boardingPt<<" "<<s[cnt-1].routeNo;
stufile<<"\n";
stufile.close();
cout<<"\nPress y to download your bus pass : (y/n) ";
cin>>choice;
if(choice=='y')
downloadBusPass(cnt-1);
}
else
{
cout<<"\nBooking cancelled";
}
}
else
{
cout<<"\nRoute number requested is full or unavailable";
}
}
else
{
cout<<"\nThe boarding point you selected is unavailable in the requested route"<<endl;
}

}

void Student :: downloadBusPass(int stu)
{
cout<<"\n\t\t\tYour Bus Pass"<<endl;
for(int i=1;i<=20;i++)
cout<<"_";
cout<<"\n|";
for(int i=1;i<59;i++)
cout<<" ";
cout<<"|\n|";
cout<<"  Name : "<<s[stu].name<<"\tSno : "<<s[stu].sno<<"\tRoll No. : "<<s[stu].rollNo<<"\t   |\n|  Branch : "<<s[stu].branch;
cout<<"\tYear : "<<s[stu].year<<"\t\t\t   |\n|  Blood Group : "<<s[stu].bloodGrp<<"\t\t\t\t\t   |\n|  ";
cout<<"Boarding point : "<<s[stu].boardingPt<<"\tRoute No."<<s[stu].routeNo;
cout<<"\t\t   |\n|";
for(int i=1;i<59;i++)
cout<<" ";
cout<<"|\n";
cout<<"|";
for(int i=1;i<=20;i++)
cout<<"_";
}
void Student :: downloadBusPass()
{
cout<<"\nEnter your roll number : ";
string rno;
int flag=0;
cin>>rno;
cout<<"\n\n\t\tYour Bus Pass"<<endl;
for(int j=0;j<cnt;j++)
{
if(s[j].rollNo==rno)
{
flag=1;
for(int i=1;i<=20;i++)
cout<<"_";
cout<<"\n|";
for(int i=1;i<59;i++)
cout<<" ";
cout<<"|\n|";
cout<<"  Name : "<<s[j].name<<"\tSno : "<<s[j].sno<<"\tRoll No. : "<<s[j].rollNo<<"\t   |\n|  Branch : "<<s[j].branch;
cout<<"\tYear : "<<s[j].year<<"\t\t\t   |\n|  Blood Group : "<<s[j].bloodGrp<<"\t\t\t\t\t   |\n|  ";
cout<<"Boarding point : "<<s[j].boardingPt<<"\tRoute No."<<s[j].routeNo;
cout<<"\t\t   |\n|";
for(int i=1;i<59;i++)
cout<<" ";
cout<<"|\n";
cout<<"|";
for(int i=1;i<=20;i++)
cout<<"_";
break;
}
}
if(!flag)
cout<<"\nNo match found!! You might have not booked your bus";

}

void Admin::loginCheck()
{
while(1)
{
system("cls");
cout<<"\n\n\n\n\n\t\t\t\t\t";
cout<<"Enter your login details : "<<"\n\n\t\t\t";
cout<<"Enter username : ";
cin>>username;
cout<<"\n\t\t\t"<<"Enter password : ";
cin>>password;
if(username!="admin" || password!="admin")
{
cout<<"\n\t\t\tInvalid credentials\n\t\t\tDo u want to exit(0) / retry(1)";
int choice;
cin>>choice;
if(choice==0)
exit(0);
}
else
{
system("cls");
while(1)
{
cout<<"\n\n\t\t\t\t\tHi Admin!\n\t\t\t\tChoose your navigation";
cout<<"\n\n\t\t\t1.View Bus wise Bookings\n\n\t\t\t2.View Student wise Bookings\n\n\t\t\t";
cout<<"3.Add New Bus\n\n\t\t\t4.Exit\n\n\t\t\t";
int choice;
cin>>choice;
if(choice==1)
a.ViewBusBookings();

else if(choice==2)
a.ViewBusPasses(s);

else if(choice==3)
a.AddNewBus();

else if(choice==4)
exit(0);
}
}
}
}

void Admin :: ViewBusBookings()
{
system("cls");
cout<<"\n\n\n\n\n\t\t"<<"Bus Booking Details : \n";
cout<<"\n\tRouteNo\t"<<"\tBookedSeats\t"<<"\tBusName\n";
for(int i=0;i<bcnt;i++)
cout<<"\t"<<b[i].routeNo<<"\t\t"<<b[i].booked<<"\t\t\t"<<b[i].nameOfBus<<"\n";
}

void Admin :: ViewBusPasses(Student s[])
{
system("cls");
cout<<"\n\n\n\n\n\t\t"<<"Student Booking Details : \n";
cout<<"\nSno\t"<<"Name\t\t"<<"RollNumber\t"<<"Branch\t"<<"BloodGrp\t"<<"BoardingPoint\t\t"<<"RouteNo\n";
for(int i=0;i<s[0].cnt;i++)
{
cout<<s[i].sno<<"\t"<<s[i].name<<"\t\t"<<s[i].rollNo<<"\t"<<s[i].branch<<"\t";
cout<<s[i].bloodGrp<<"\t\t"<<s[i].boardingPt<<"\t\t"<<s[i].routeNo<<"\n";
}
}

void Admin :: AddNewBus()
{

b[bcnt].capacity=15;
b[bcnt].booked=0;
b[bcnt].routeNo=bcnt+1;
cout<<"\nEnter name of the bus : ";
cin>>b[bcnt].nameOfBus;
cout<<"\nEnter fare : ";
cin>>b[bcnt].fare;
cout<<"\nEnter start time : ";
cin>>b[bcnt].startTime;
cout<<"\nEnter reach time : ";
cin>>b[bcnt].reachTime;
cout<<"\nEnter 10 stops of the bus : ";
for(int i=0;i<10;i++)
cin>>b[bcnt].route[i];
ofstream busfile("C:\\Users\\Admin\\Downloads\\buses.txt",ios::app);
busfile<<b[bcnt].routeNo<<" "<<b[bcnt].nameOfBus<<" "<<b[bcnt].fare;
busfile<<" "<<b[bcnt].startTime<<" "<<b[bcnt].reachTime;
for(int i=0;i<10;i++)
busfile<<" "<<b[bcnt].route[i];
busfile<<"\n";
busfile.close();
bcnt++;
ofstream capfile("C:\\Users\\Admin\\Downloads\\capacity.txt",ios::app);
capfile<<b[bcnt].booked<<" ";
capfile.close();

ofstream buscount("C:\\Users\\Admin\\Downloads\\BusCount.txt");
buscount<<bcnt;
buscount.close();
}
void getStop()
{
cout<<"Enter nearest point : ";
    string point;
    cin>>point;
    b[0].search(point);
}

int main()
{
b[0].read();
s[0].read();
while(1)
{
cout<<"\n\n\n\t\t\t";
cout<<"\t\t\tVNR Vignana Jyothi Institute of Engineering and Technology\n\n\t\t\t"<<endl;
cout<<"\t\t\t\t\t\t\t\tWelcome to BookMyBus application\n\t\t\t"<<endl;
cout<<"\t\t\t1. View Buses available\n\t\t\t"<<endl;
cout<<"\t\t\t2. Search for buses by boarding point\n\t\t\t"<<endl;
cout<<"\t\t\t3. Book a seat in Bus\n\t\t\t"<<endl;
cout<<"\t\t\t4. Download bus pass\n\t\t\t"<<endl;
cout<<"\t\t\t5. Admin login\n\t\t\t"<<endl;
cout<<"\t\t\t6. Exit"<<endl;
cout<<"\n\t\t\t\t\t\tEnter your choice:-> ";
int choice;
cin>>choice;
switch(choice)
    {
    case 1: b[0].viewBusDetails();
      break;
    case 2: getStop();
       break;
    case 3: s[Student::cnt].book();
      break;
    case 4: s[0].downloadBusPass();
break;
case 5: a.loginCheck();
break;
    case 6:exit(0);
  }
}
return 0;
}

