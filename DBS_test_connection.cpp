/*
Name:		Rayyan Ahmed, Jeffery Sole, Kelvin Tam
Student ID: 140961202, 142280205, 108914201
Email:		rahmed102@myseneca.ca, jsole@myseneca.ca, ktam27@myseneca.ca
File:		milestone 1
Section:	NDD
Date:		12/07/2021
*/
#include <iostream>
#include <occi.h>
#include <iomanip>

using oracle::occi::Environment;
using oracle::occi::Connection;
using namespace oracle::occi;
using namespace std;


int getInteger(const char* prompt);
void display(ResultSet* rs);

int main()
{
	//OCCI Variables
	Environment* env = nullptr;
	Connection* conn = nullptr;

	string str;
	string usr = "dbs211_212d04";
	string pass = "26473162";
	string srv = "myoracle12c.senecacollege.ca:1521/oracle12c";

	try
	{
		int number,counter = 0;
		env = Environment::createEnvironment(Environment::DEFAULT);
		conn = env->createConnection(usr, pass, srv);
		cout << "Group 10: Rayyan Ahmed, Kelvin Tam, Jeffery Sole" << endl;

		Statement* stmt = conn->createStatement();

		//input
		number = getInteger("Enter the Employee Number: ");
		stmt->setSQL("SELECT e.employeeNumber, firstName, lastName, extension, email, FROM employees e OUTER JOIN employees r ON e.reportsTo = r.employeeNumber WHERE employeeNumber = (:1)");
		stmt->setInt(1, number);
		cout << endl;

		//header
		ResultSet* rs = stmt->executeQuery();
		if (rs->next())
		{
			cout << setw(3) << left << "#"
				<< setw(16) << left << "Employee Number "
				<< setw(11) << left << "First Name "
				<< setw(9) << left << "Last Name "
				<< setw(9) << left << "Extension "
				<< setw(32) << left << "Email "
				<< setw(11) << left << "Office Code "
				<< setw(11) << left << "Reports To "
				<< setw(9) << left << "Job Title" << endl;

			cout << setw(3) << left << "--"
				<< setw(16) << left << "--------------- "
				<< setw(11) << left << "---------- "
				<< setw(9) << left << "--------- "
				<< setw(9) << left << "--------- "
				<< setw(32) << left << "------------------------------- "
				<< setw(11) << left << "----------- "
				<< setw(11) << left << "---------- "
				<< setw(9) << left << "---------" << endl;
			display(rs);
		}
		else
		{
			cerr << "ERROR: No records exist!!";
		}
		while (rs->next())
		{
			display(rs);
		}

		conn->terminateStatement(stmt);
		env->terminateConnection(conn);
		Environment::terminateEnvironment(env);
	}
	catch (SQLException& sqlExcp)
	{
		cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
	}
	return 0;
}

int getInteger(const char* prompt)
{
	int flag, inputPrompt;

	if (prompt)
	{
		cout << prompt;
	}
	do
	{
		flag = 1;
		cin >> inputPrompt;

		if (cin.fail())
		{
			cerr << "Bad integer value, try again: ";
			flag = 0;
			cin.clear();
			cin.ignore(1000, '\n');
		}
		else if (cin.get() != '\n')
		{
			cerr << "Enter only an integer, try again: ";
			flag = 0;
			cin.clear();
			cin.ignore(1000, '\n');
		}
	} while (!flag);

	return inputPrompt;
}
void display(ResultSet* rs)
{
	int counter = 0;
	int employeeNumber = rs->getNumber(1);
	string lastName = rs->getString(2);
	string firstName = rs->getString(3);
	string extension = rs->getString(4);
	string email = rs->getString(5);
	string officeCode = rs->getString(6);
	int reportsTo = rs->getNumber(7);
	string jobTitle = rs->getString(8);
	counter++;

	cout << setw(3) << left << counter
		<< setw(16) << left << employeeNumber
		<< setw(11) << left << firstName
		<< setw(10) << left << lastName
		<< setw(10) << left << extension
		<< setw(32) << left << email
		<< setw(12) << left << officeCode
		<< setw(11) << left << reportsTo
		<< setw(9) << left << jobTitle << endl;
}