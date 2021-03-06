#include "Dictionary.h"

void ConsoleInit()
{
	setlocale(LC_ALL, "ru");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
}


void WaitNewMessage()
{
	cout << ">";
}

string LowerCase(const string& message)
{
	string result = "";
	for (size_t i = 0; i < message.size(); i++)
		result += tolower(message[i]);
	return result;
}

string GetTranslate(map<string, string> ::iterator it)
{
	return it->second;
}

void SaveChanges(map<string, string> _dictionary)
{
	ofstream dictionaryFile;
	dictionaryFile.open(DICTIONARY_FILENAME);
	for (auto item : _dictionary)
	{
		dictionaryFile << item.first << '\n' << item.second << '\n';
	}
	cout << SUCCESSFUL_SAVING_MESSAGE;
}

void ReadDictionary(map<string, string>& _dictionary)
{
	ifstream dictionaryFile;
	dictionaryFile.open(DICTIONARY_FILENAME);
	if (dictionaryFile.is_open())
	{
		string word, translate;
		while (!dictionaryFile.eof())
		{
			getline(dictionaryFile, word);
			if (word.size() != 0)
			{
				getline(dictionaryFile, translate);
				if (translate.size() != 0)
				{
					_dictionary.insert(make_pair(word, translate));
				}
			}
		}
	}
	else
	{
		dictionaryFile.close();
		ofstream createFile(DICTIONARY_FILENAME);
		createFile.close();
	}
}

void SaveTranslation(map <string, string>& _dictionary, const string& word, const string& translation)
{
	cout << "����� �" << word << "� ��������� � ������� ��� �" << translation << "�.\n";
	_dictionary.insert(make_pair(LowerCase(word), translation));
}

void RunTranslator(map <string, string>& _dictionary)
{
	bool isChanged = false;
	string message;
	string buffer;
	map <string, string> ::iterator it;

	while (true)
	{
		WaitNewMessage();
		getline(cin, message);
		if (message != "...")
		{
			it = _dictionary.find(LowerCase(message));
			if (it != _dictionary.end())
			{
				cout << GetTranslate(it) << '\n';
			}
			else
			{
				cout << "����������� ����� �" << message << "�. ������� ������� ��� ������ ������ ��� ������.\n";
				WaitNewMessage();
				buffer = message;
				getline(cin, message);
				if (message.size() != 0 && message != "...")
				{
					isChanged = true;
					SaveTranslation(_dictionary, buffer, message);
				}
				else
				{
					cout << "����� �" << buffer << "� ���������������.\n";
				}
			}
		}
		else
		{
			if (isChanged)
			{
				
				cout << SAVE_ALERT;
				WaitNewMessage();
				getline(cin, message);
				if (LowerCase(message) == AGREEMENT_MESSAGE)
				{
					SaveChanges(_dictionary);
					break;
				}
				else
				{
					cout << EXIT_WITHOUT_SAVING_MESSAGE;
					break;
				}
			}
			else
			{
				cout << NO_CHANGES_EXIT_MESSAGE;
				break;
			}
		}
	}
}