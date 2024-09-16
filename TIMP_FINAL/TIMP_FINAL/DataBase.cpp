#include "DataBase.h"

using namespace System;
using namespace System::IO;
using namespace System::Collections::Generic;
using namespace std;

// ������� ��� �������� ����� � �������� [PropertyName] {PropertyInformation};
Dictionary<String^, String^>^ ParsePropertyFile(String^ filePath)
{
    Dictionary<String^, String^>^ propertyList = gcnew Dictionary<String^, String^>();

    try
    {
        StreamReader^ sr = gcnew StreamReader(filePath);

        String^ currentLine;

        while ((currentLine = sr->ReadLine()) != nullptr)
        {
            if (currentLine->StartsWith("[") && currentLine->EndsWith("};"))
            {
                String^ propertyName = currentLine->Substring(1, currentLine->IndexOf("]") - 1)->Trim();
                String^ propertyInformation = currentLine->Substring(currentLine->IndexOf("{") + 1, currentLine->IndexOf("}") - currentLine->IndexOf("{") - 1)->Trim();

                propertyList->Add(propertyName, propertyInformation);
            }
        }

        sr->Close();
    }
    catch (Exception^ e)
    {
        Console::WriteLine("Error reading from file: " + e->Message);
    }

    return propertyList;
}

// ������� ��� �������� ����� ������� "username:password"
Dictionary<String^, String^>^ ParseCredentialsFile(String^ filePath)
{
    Dictionary<String^, String^>^ userCredentialsList = gcnew Dictionary<String^, String^>();

    try
    {
        // ���������� StreamReader ��� ������ �� �����
        StreamReader^ sr = gcnew StreamReader(filePath);

        // ������ ���� ���������
        while (!sr->EndOfStream)
        {
            String^ line = sr->ReadLine();

            // ��������� ������ �� �����, ��������� ����������� ":"
            System::Array^ parts = line->Split(':');
            // ���������, ��� � ��� ���� ��� ����� (username � password)
            if (parts->Length == 2)
            {
                String^ username = parts->GetValue(0)->ToString()->Trim();
                String^ password = parts->GetValue(1)->ToString()->Trim();
                userCredentialsList->Add(username, password);
            }
        }

        sr->Close();
    }
    catch (Exception^ e)
    {
        // ��������� ����������, ���� ���-�� ����� �� ���
        Console::WriteLine("Error reading from file: " + e->Message);
    }

    return userCredentialsList;
}

bool writeFile(String^ usr, String^ data, String^ feedBK, bool phone, String^ filePath) {
    try
    {
        // ���������� StreamWriter ��� ������ ������ � ����
        StreamWriter^ sw = gcnew StreamWriter(filePath, true);
        sw->Write("[" + usr + "]");
        sw->Write("{");
        if (phone) sw->WriteLine("phone: " + data);
        else sw->WriteLine("email: " + data);
        sw->Write(feedBK);
        sw->Write("};\n");
        sw->Close();
        return 1;
    }
    catch (Exception^ e)
    {
        // ��������� ����������, ���� ���-�� ����� �� ���
        Console::WriteLine("Error writing to file: " + e->Message);
    }
    return 0;
}

bool writeFile(String^ usr, String^ feedBK, String^ filePath) {
    try
    {
        // ���������� StreamWriter ��� ������ ������ � ����
        StreamWriter^ sw = gcnew StreamWriter(filePath, true);
        sw->Write("[" + usr + "]");
        sw->Write("{");
        sw->Write(feedBK);
        sw->Write("};\n");
        sw->Close();
        return 1;
    }
    catch (Exception^ e)
    {
        // ��������� ����������, ���� ���-�� ����� �� ���
        Console::WriteLine("Error writing to file: " + e->Message);
    }
    return 0;
}

void choose(String^ book) {
    try
    {
        // ���������� StreamWriter ��� ������ ������ � ����
        StreamWriter^ sw = gcnew StreamWriter("chosen.txt", true);
        sw->Write(book + "\n");
        sw->Close();
    }
    catch (Exception^ e)
    {
        // ��������� ����������, ���� ���-�� ����� �� ���
        Console::WriteLine("Error writing to file: " + e->Message);
    }
}

//bool writeLikeBD(String^ str, String^ filePath) {
//    writeFile(str,filePath)
//}

List<String^>^ ParseSingleWordFile(String^ filePath)
{
    List<String^>^ wordList = gcnew List<String^>();

    try
    {
        StreamReader^ sr = gcnew StreamReader(filePath);

        String^ currentLine;

        while ((currentLine = sr->ReadLine()) != nullptr)
        {
            // ��������� ����� � ������ (������ ������ �������)
            wordList->Add(currentLine->Trim());
        }

        sr->Close();
    }
    catch (Exception^ e)
    {
        Console::WriteLine("Error reading from file: " + e->Message);
    }

    return wordList;
}

//String^ readFile(String^ filePath) {
//    try
//    {
//        // ���������� StreamReader ��� ������ �� �����
//        StreamReader^ sr = gcnew StreamReader(filePath);
//        StreamWriter^ sw = gcnew StreamWriter("chosen.txt", false);
//        String^ content = sr->ReadToEnd();
//        sw->Write("");
//        sr->Close();
//        sw->Close();
//        return content;
//    }
//    catch (Exception^ e)
//    {
//        // ��������� ����������, ���� ���-�� ����� �� ���
//        Console::WriteLine("Error reading from file: " + e->Message);
//        return nullptr; // ���������� nullptr � ������ ������
//    }
//}