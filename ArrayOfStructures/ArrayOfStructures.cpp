//������ ��������� ������������ ������ �������� � ������������ ������, ������������ ����/����� �� �����.

#include "stdafx.h"
#include <iostream>
#include <fstream>
using namespace std;

struct Car {
	char name[50];
	char color[10];
	int power;
	int volume;
	Car* next;
}; //�������� ������ ������� �������� (��������� car)

struct ForCar {
	Car *cur, *prev, *first, *last;
}; //��������������� ��������� ��� ������ � �������� ��������

void Init(ForCar*);
void setCar (ForCar*, char[], int, int, char[]);
void GoFirst (ForCar*);
void GoNext (ForCar*);

int main()
{
	setlocale(LC_ALL, "rus");
	ifstream fin("cars.txt");
	ofstream fout("result.txt");

	char name[50];
	int power;
	int volume;
	char color[10];
	ForCar *p = new ForCar;

	Init(p);

	while(1)
	{
		if (fin.peek(),fin.eof()) break;
		fin>>name;
		fin>>power;
		fin>>volume;
		fin>>color;
		setCar(p, name, power, volume, color);
	}
	
	power = p->cur->power;
	memcpy(name, p->cur->name, sizeof(name));
	memcpy(color, p->cur->color, sizeof(color));
	volume = p->cur->volume;
	GoNext(p);
	while (p->cur != NULL){
		if (p->cur->power > power){
			power = p->cur->power;
			memcpy(name, p->cur->name, sizeof(name));
	        memcpy(color, p->cur->color, sizeof(color));
			volume = p->cur->volume;
		}
		GoNext(p);
	}

	cout<<"������ � ����� ������ ����������: ";
	fout<<"������ � ����� ������ ����������: ";
	for (int i=0; i<50; i++){
		if (name[i] == '\0') break;
		cout<<name[i];
		fout<<name[i];
	}
	cout<<endl;
	fout<<endl;
	cout<<"�������� ���������: "<<power<<endl;
	fout<<"�������� ���������: "<<power<<endl;
	cout<<"���� ������: ";
	fout<<"���� ������: ";
	for (int i=0; i<10; i++){
		if (color[i] == '\0') break;
		cout<<color[i];
		fout<<color[i];
	}
	cout<<endl;
	fout<<endl;
	cout<<"����� ����: "<<volume<<" ������"<<endl;
	fout<<"����� ����: "<<volume<<" ������"<<endl;

	fin.close();
	fout.close();
	
	GoFirst(p);
	while(p->cur != NULL){
		GoNext(p);
		delete p->prev;
	}

    system("pause");
	return 0;
}

void Init(ForCar *p){
	p->first=NULL;
	p->prev=NULL;
	p->cur=NULL;
	p->last=NULL;
} // ������������� ���������� ������� ��������

void setCar (ForCar* ptr, char name[], int power, int volume, char color[]){
	Car *car = new Car;
	car->power = power;
	car->volume = volume;
	memcpy(car->name, name, sizeof(car->name));
	memcpy(car->color, color, sizeof(car->color));
	car->next = NULL;

	if(ptr->first == NULL){
		ptr->first = car;
		ptr->cur = car;
		ptr->prev = car;
		ptr->last = car;
	} else {
		ptr->last->next=car;
		ptr->last=car;
	}
} // ���������� �������� (������) � ������ �������� (� ��� �����)

void GoFirst (ForCar *T)
{
	T->cur = T->first;
	T->prev = T->first;
} //��� ������ � ����������� ������� ��������

void GoNext (ForCar *T)
{
	T->prev=T->cur;
	T->cur=T->cur->next;
} //��� ������ � ����������� ������� ��������


