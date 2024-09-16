#pragma once
#include <iostream>

using namespace System;
using namespace System::Collections::Generic;
using namespace System::IO;
Dictionary<String^, String^>^ ParseCredentialsFile(String^ filePath);
bool writeFile(String^ usr, String^ data, String^ feedBK, bool phone, String^ filePath);
//cString^ readFile(String^ path);
Dictionary<String^, String^>^ ParsePropertyFile(String^ filePath);
void choose(String^ book);
bool writeFile(String^ usr, String^ feedBK, String^ filePath);
List<String^>^ ParseSingleWordFile(String^ filePath);
