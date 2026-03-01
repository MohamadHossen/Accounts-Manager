#include <iostream>
#include <iomanip>
#include<vector>
#include<string>
#include<cctype>
#include <fstream>
using namespace std;

const string File = "Acounts.txt";

enum enType {Gmail=1,FaceBook,WhatsApp,NetwWork, UnKnown};

enum enDo{Add=1,Delete,Change,Search,Show};

struct stAccountInfo {
	string UserName = "";
	string PassWord = "";
	enType Type;
};

enType ReadType() {
	short Type = 0;
	cout << "What Type Of Account Do Yo Want ? \n";
	cout << "1 : Gmail \n";
	cout << "2 : FaceBook \n";
	cout << "3 : WhatsApp \n";
	cout << "4 : NetWork \n";
	cout << "\nEnter Number Of Youe Choice : ";
	cin >> Type;
	cout << endl;
	while (cin.fail()||Type>4||Type<1) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Error ,Enter Again : ";
		cin >> Type;
		cout << endl;
	}
	return enType(Type);
}

string ConvertenTypeToString(enType Type) {
	switch (Type) {
	case FaceBook:
		return "faceBook";
	case Gmail:
		return "Gmail";
	case WhatsApp:
		return "WhatsApp";
	case NetwWork:
		return "NetWork";
	}
}

enType ConverStringToEnum(string Type) {
	enType enType;
	Type == "faceBook" ? enType = FaceBook : 
	Type == "Gmail" ? enType = Gmail :
	Type == "WhatsApp" ? enType = WhatsApp :
	Type == "NetWork" ? enType = NetwWork :enType = UnKnown;
	return enType;
}

string ReadText(string Message) {
	string Info = "";
	cout << Message << endl;
	cin >> Info;
	return Info;
}

stAccountInfo GetAccountInfo() {
	stAccountInfo Info;
	Info.Type = ReadType();
	Info.UserName = ReadText("Please Enter UserName : ");
	Info.PassWord = ReadText("Please Enter PassWord : ");
	return Info;
}

string ConvertRecordToOneLine(stAccountInfo Info, string Seperator = "|*|") {
	string OneLine = "";
	OneLine =ConvertenTypeToString(Info.Type) + Seperator;
	OneLine += Info.UserName + Seperator;
	OneLine += Info.PassWord ;
	return OneLine;
}

vector <string> SplitString(string Text, string Delimiter) {
	vector <string> vText;
	short Position = 0;
	string SWord = "";
	while ((Position = Text.find(Delimiter)) != std::string::npos) {
		SWord = Text.substr(0, Position);

		if (SWord != "") {
			vText.push_back(SWord);
		}
		Text.erase(0, Position + Delimiter.length());
	}
	if (Text != "") {
		vText.push_back(Text);
	}
	return vText;
}

stAccountInfo ConvertOneLineToRecord(string Line, string Seperator = "|*|") {
	stAccountInfo AccountInfo;
	vector <string> vInfo = SplitString(Line, Seperator);
	AccountInfo.Type = ConverStringToEnum(vInfo[0]);
	AccountInfo.UserName = vInfo[1];
	AccountInfo.PassWord = vInfo[2];
	return AccountInfo;
}

void SaveAccountsInfoToFile(string Line) {
	fstream MyFile;
	MyFile.open(File, ios::out | ios::app);
	if (MyFile.is_open()) {
			MyFile << Line<<endl;
			MyFile.close();
	}
}

void SaveAccountsInfoToFile(vector<stAccountInfo>vAccounts) {
	fstream MyFile;
	MyFile.open(File, ios::out);
	if (MyFile.is_open()) {
		string Line = "";
		for (stAccountInfo Info : vAccounts) {
			Line=ConvertRecordToOneLine(Info);
			MyFile << Line << endl;
		}
		MyFile.close();
	}
}

vector <stAccountInfo> LoadAccountsInfoFromFile(vector <stAccountInfo> &vAccountsInfo) {
	fstream MyFile;
	stAccountInfo AccountInfo;
	MyFile.open(File, ios::in);
	if (MyFile.is_open()) {
		string Line = "";
		while (getline(MyFile, Line)) {
			AccountInfo = ConvertOneLineToRecord(Line);
			vAccountsInfo.push_back(AccountInfo);
		}
		MyFile.close();
	}
	return vAccountsInfo;
}

void ShowAccounts(vector<stAccountInfo> &vAccountsInfo) {
	if (!vAccountsInfo.empty()) {
		cout << "\n|------------------------------------------------------------------------|\n";
		cout << "|                                 Accounts                               |";
		cout << "\n|------------------------------------------------------------------------|\n";
		cout << "|Type           |" << "User Name                          |" << "Pass Word           |\n";
		cout << "|---------------|-----------------------------------|--------------------|\n";
		for (stAccountInfo& Info : vAccountsInfo) {
			cout << "|" << left << setw(15) << ConvertenTypeToString(Info.Type);
			cout << "|" << left << setw(35) << Info.UserName;
			cout << "|" << left << setw(20) << Info.PassWord << "|" << endl;
		}
		cout << "|------------------------------------------------------------------------|\n";
	}
	else {
		cout << "\nThere Are No Accounts\n";
	}
}

void AddNewAccounts(vector <stAccountInfo>&vAccounts) {
	stAccountInfo Info = GetAccountInfo();
	vAccounts.push_back(Info);
	SaveAccountsInfoToFile(vAccounts);
}

void AddAccounts(vector <stAccountInfo> &vAccounts) {
	char Answer = 'n';
	do {
		system("cls");
		AddNewAccounts(vAccounts);
		cout << "Do You Want To Add More Accounts ? Y or N : ";
		cin >> Answer;
	} while (tolower(Answer) == 'y');
}

bool IsExist(vector <stAccountInfo> vAccounts,string UserName) {
	for (stAccountInfo& Info : vAccounts) {
		if (Info.UserName == UserName)
			return true;
	}
	return false;
}

bool DeleteAccount(vector <stAccountInfo> &vAccountInfo,string UserName) {
	vector <stAccountInfo> vAccountsAfterDelete;
	bool IsExist = false;
	for (stAccountInfo &Info : vAccountInfo) {
		if (Info.UserName != UserName) {
			vAccountsAfterDelete.push_back(Info);
		}
		else {
			IsExist = true;
		}
	}
	vAccountInfo.clear();
	vAccountInfo = vAccountsAfterDelete;
	return IsExist;
}

void DeleteAccounts(vector<stAccountInfo>& vAccounts) {
	if (!vAccounts.empty()) {
	string Delete = ReadText("Please Enter The User Name Of Account That You Need To Delete It ? ");
		if (IsExist(vAccounts, Delete)) {
			DeleteAccount(vAccounts, Delete);
			SaveAccountsInfoToFile(vAccounts);
			cout << "\nDeleted Has Been Successfully \n";
		}
		else {
			cout << "\nAccount Is Not Found\n";
		}
	}
	else {
		cout << "\nThere Are No Accounts\n";
	}
}

void ChangeAccount(vector <stAccountInfo>& vAccounts) {
	if (!vAccounts.empty()) {
		string UserName = ReadText("Please Enter The User Name Of Account That You Need To Change It ?");
		if (IsExist(vAccounts, UserName)) {
			DeleteAccount(vAccounts, UserName);
			stAccountInfo Change = GetAccountInfo();
			vAccounts.push_back(Change);
			SaveAccountsInfoToFile(vAccounts);
			cout << "\nChanged Has Been Successfully\n";
		}
		else {
			cout << "\nAccount Is Not Found\n";
		}
	}
	else {
		cout << "\nThere Are No Accounts\n";
	}
}

bool SearchAccount(vector <stAccountInfo> &vAccount, string UserName,stAccountInfo &Find) {
	for (stAccountInfo& Account : vAccount) {
		if (Account.UserName == UserName) {
			Find = Account;
			return true;
		}
	}
	return false;
}

void SearchAccounts(vector <stAccountInfo>& vAccount) {
	if (!vAccount.empty()) {
		stAccountInfo Find;
		string UserName = ReadText("Please Enter The User Name Of Account That You Need To Search About It ? ");
		if (SearchAccount(vAccount, UserName, Find)) {
			cout << "\nAccount Found Successfully \n";
			cout << "\nType      : " << ConvertenTypeToString(Find.Type) << endl;
			cout << "\nUser Name : " << Find.UserName << endl;
			cout << "\nPassword  : " << Find.PassWord << endl;
		}
		else {
			cout << "\nAccount Is Not Found\n";
		}
	}
	else {
		cout << "\nThere Are No Accounts\n";
	}
}

enDo WhatToDo() {
	short Answer = 0;
	cout << "What Do You Want To Do ? \n";
	cout << "1 : Add Account \n";
	cout << "2 : Delete Account \n";
	cout << "3 : Change Account \n";
	cout << "4 : Search Account \n";
	cout << "5 : Show Accounts \n";
	cout << "\nI Want (Enter Number) : ";
	cin >> Answer;
	cout << endl;
	while (cin.fail()||Answer>5||Answer<1) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Error ,Enter Again : ";
		cin >> Answer;
		cout << endl;
	}
	return enDo(Answer);
}

void Begain() {
	vector <stAccountInfo> vAccounts;
	LoadAccountsInfoFromFile(vAccounts);
	char Answer = 'n';
	do {
		system("cls");
		switch (WhatToDo()) {
		case Add:
			AddAccounts(vAccounts);
			break;
		case Delete:
			DeleteAccounts(vAccounts);
			break;
		case Change:
			ChangeAccount(vAccounts);
			break;
		case Search:
			SearchAccounts(vAccounts);
			break;
		case Show:
			ShowAccounts(vAccounts);    
			break;
	
		}
		cout << "\n\nDo You Want To Do AnyThing Else ? Y/N ? ";
		cin >> Answer;
	} while (tolower(Answer) == 'y');
}

int main()
{
	Begain();
	return 0;
}