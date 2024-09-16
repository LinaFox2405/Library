// Включаем заголовочные файлы для CLR и Windows Forms
#pragma once
#include "DataBase.h"
#using <System.dll>
#using <System.Windows.Forms.dll>

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;
using namespace System::IO;
using namespace System::Drawing;


// Определение формы с заявкой на оформление заявки
public ref class PurchaseRequestForm : public Form
{
private:
    TextBox^ textBoxMessage = gcnew TextBox();
    TextBox^ textBoxDate = gcnew TextBox();
    //ComboBox^ comboBoxContactType = gcnew ComboBox();
    String^ usr;
public:
    PurchaseRequestForm(String^ username)
    {
        usr = username;
        // Создание компонентов формы
        Label^ labelContactType = gcnew Label();
        labelContactType->Text = "Ваш билет:";
        labelContactType->Location = System::Drawing::Point(10, 10);

        //comboBoxContactType->Items->Add("Телефон");
        //comboBoxContactType->Items->Add("Email");
        //comboBoxContactType->Location = System::Drawing::Point(150, 10);

        textBoxDate->Location = System::Drawing::Point(150, 10);
        textBoxDate->ReadOnly = true;
        textBoxDate->Text = username;

        Label^ labelMessage = gcnew Label();
        labelMessage->Text = "Выбранные книги:";
        labelMessage->Location = System::Drawing::Point(10, 40);

        textBoxMessage->Multiline = true;
        String^ str;
        for each (String ^ item in ParseSingleWordFile("chosen.txt"))
        {
            str += item;
            str += ", ";
        }
        str->TrimEnd();
        textBoxMessage->Text = str;
        textBoxMessage->ReadOnly = true;
        textBoxMessage->Size = System::Drawing::Size(300, 100);
        textBoxMessage->Location = System::Drawing::Point(10, 70);

        Button^ buttonSubmit = gcnew Button();
        buttonSubmit->Text = "Отправить";
        buttonSubmit->Location = System::Drawing::Point(10, 180);
        buttonSubmit->Click += gcnew EventHandler(this, &PurchaseRequestForm::SubmitButton_Click);

        // Добавление компонентов на форму
        this->Controls->Add(labelContactType);
        //this->Controls->Add(comboBoxContactType);
        this->Controls->Add(labelMessage);
        this->Controls->Add(textBoxMessage);
        this->Controls->Add(buttonSubmit);
        this->Controls->Add(textBoxDate);

        // Установка заголовка
        this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
        this->Text = "Заявка";
        this->Size = System::Drawing::Size(350, 250);
        this->StartPosition = FormStartPosition::CenterScreen;
    }

private:
    // Обработчик события нажатия кнопки Отправить
    void SubmitButton_Click(Object^ sender, EventArgs^ e)
    {
        // Ваш код для обработки заявки на оформление договора
        if (!(textBoxMessage->Text->Length == 0)) {
            String^ feedBK = textBoxMessage->Text;
            writeFile(usr, feedBK, "claimed.txt");
            MessageBox::Show("Заявка отправлена!", "Info", MessageBoxButtons::OK, MessageBoxIcon::Information);
            this->Close();
            remove("chosen.txt");
            exit(1);
        }
        else MessageBox::Show("Заявка не отправлена!Выберите хотя бы 1 книгу", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
};

// Определение формы с подробной информацией о недвижимости
public ref class PropertyDetailsForm : public Form
{
    String^ usr;
    Dictionary<String^, String^>^ books = ParsePropertyFile("books.txt");
    String^ bname;
    Dictionary<String^, String^>^ pics = ParsePropertyFile("books_images.txt");
public:
    PropertyDetailsForm(String^ propertyName, String^ propertyDescription, String^ username)
    {
        usr = username;
        bname = propertyName;
        // Создание компонентов формы с подробной информацией
        Label^ labelName = gcnew Label();
        labelName->Text = "Название книги: " + propertyName;
        labelName->Location = System::Drawing::Point(10, 10);
        labelName->AutoSize = true;

        TextBox^ textBoxDescription = gcnew TextBox();
        textBoxDescription->Multiline = true;
        textBoxDescription->ReadOnly = true;
        textBoxDescription->Text = propertyDescription;
        textBoxDescription->Size = System::Drawing::Size(300, 100);
        textBoxDescription->Location = System::Drawing::Point(10, 40);


        // Добавление фото (пример)
        PictureBox^ pictureBox = gcnew PictureBox();
        String^ path;
        pics->TryGetValue(propertyName, path);
        pictureBox->ImageLocation = path + ".jpg";
        pictureBox->SizeMode = PictureBoxSizeMode::Zoom;
        pictureBox->Size = System::Drawing::Size(200, 150);
        pictureBox->Location = System::Drawing::Point(320, 40);

        Button^ buttonBack = gcnew Button();
        buttonBack->Text = "Назад";
        buttonBack->Location = System::Drawing::Point(10, 210);
        buttonBack->Click += gcnew EventHandler(this, &PropertyDetailsForm::BackButton_Click);

        Button^ buttonBuy = gcnew Button();
        buttonBuy->Text = "Добавить в заявку";
        buttonBuy->Location = System::Drawing::Point(200, 210);
        buttonBuy->AutoSize = true;
        buttonBuy->Click += gcnew EventHandler(this, &PropertyDetailsForm::BuyButton_Click);

        // Добавление компонентов на форму
        this->Controls->Add(labelName);
        this->Controls->Add(textBoxDescription);
        this->Controls->Add(pictureBox);
        this->Controls->Add(buttonBack);
        this->Controls->Add(buttonBuy);

        // Установка заголовка
        this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
        this->Text = "Книга";
        this->Size = System::Drawing::Size(550, 300);
        this->StartPosition = FormStartPosition::CenterScreen;
    }

private:
    // Обработчик события нажатия кнопки Назад
    void BackButton_Click(Object^ sender, EventArgs^ e)
    {
        // Закрытие текущей формы
        this->Close();
    }

    // Обработчик события нажатия кнопки Добавить в заявку
    void BuyButton_Click(Object^ sender, EventArgs^ e)
    {
        if (!ParseSingleWordFile("chosen.txt")->Contains(bname)) {
            choose(bname);
        }
        else MessageBox::Show("Книга уже добалена в заявку!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
        this->Hide();
    }
};

//public ref class PropertyListForm : public Form
//{
//private:
//    ListBox^ listBoxProperties = gcnew ListBox();
//    String^ usr;
//    Dictionary<String^, String^>^ props = ParsePropertyFile("property.txt");
//public:
//    PropertyListForm(String^ username)
//    {
//        usr = username;
//        // Создание компонентов формы со списком недвижимости
//
//        listBoxProperties->Size = System::Drawing::Size(300, 200);
//        listBoxProperties->Location = System::Drawing::Point(10, 10);
//
//        // Заполнение списка недвижимости (пример)
//        for each (KeyValuePair<String^, String^> pair in props) {
//            listBoxProperties->Items->Add(pair.Key);
//        }
//        //listBoxProperties->Click += gcnew EventHandler(this, &PropertyListForm::SelectPropertyButton_Click);
//        listBoxProperties->Click += gcnew EventHandler(this, &PropertyListForm::ListBoxProperties_SelectedIndexChanged);
//        listBoxProperties->Font = gcnew System::Drawing::Font("Arial", 16, System::Drawing::FontStyle::Bold);
//
//        Button^ buttonClose = gcnew Button();
//        buttonClose->Text = "Выход";
//        buttonClose->Location = System::Drawing::Point(10, 220);
//        buttonClose->Click += gcnew EventHandler(this, &PropertyListForm::CloseButton_Click);
//
//        this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
//        this->MaximizeBox = false;
//
//        // Добавление компонентов на форму
//        this->Controls->Add(listBoxProperties);
//        this->Controls->Add(buttonClose);
//
//        // Установка заголовка
//        this->Text = "Property List";
//    }
//private:
//    void PropertyListForm::ListBoxProperties_SelectedIndexChanged(Object^ sender, EventArgs^ e)
//    {
//        // Проверка, выбран ли элемент в списке
//        if (listBoxProperties->SelectedIndex != -1)
//        {
//            // Получение выбранной недвижимости
//            String^ selectedProperty = listBoxProperties->SelectedItem->ToString();
//
//            // Ваш код для получения подробной информации о выбранной недвижимости
//            // Передайте эту информацию в конструктор PropertyDetailsForm
//
//            String^ propertyName = selectedProperty;
//            String^ propertyDescription;
//            props->TryGetValue(selectedProperty, propertyDescription);
//            String^ sellerInfo = "Имя продавца, контактная информация...";
//
//            // Создание и отображение формы с подробной информацией
//            PropertyDetailsForm^ propertyDetailsForm = gcnew PropertyDetailsForm(propertyName, propertyDescription, sellerInfo, usr);
//            this->Hide();
//            propertyDetailsForm->ShowDialog();
//            this->Show();
//        }
//    }
//    // Обработчик события нажатия кнопки Close
//    void CloseButton_Click(Object^ sender, EventArgs^ e)
//    {
//        // Закрытие текущей формы
//        this->Hide();
//    }
//};

public ref class SuccessForm : public Form
{
public:
    String^ usr;
    ListBox^ listBoxBooks = gcnew ListBox();
    Dictionary<String^, String^>^ books = ParsePropertyFile("books.txt");
    SuccessForm(String^ username)
    {
        usr = username;
        Label^ labelWelcome = gcnew Label();
        labelWelcome->Text = "Здравствуйте!\nВыберите книги:";
        labelWelcome->AutoSize = true;
        labelWelcome->Font = gcnew System::Drawing::Font("Arial", 16, System::Drawing::FontStyle::Bold);
        int centerX = (this->Width - labelWelcome->Width) / 2;
        int centerY = (this->Height - labelWelcome->Height) / 2;
        labelWelcome->Location = System::Drawing::Point(centerX - 100, centerY - 140);

        listBoxBooks->Size = System::Drawing::Size(300, 300);
        listBoxBooks->Location = System::Drawing::Point(0, 50);


        // Заполнение списка недвижимости (пример)
        for each (KeyValuePair<String^, String^> pair in books) {
            listBoxBooks->Items->Add(pair.Key);
        }
        //listBoxProperties->Click += gcnew EventHandler(this, &PropertyListForm::SelectPropertyButton_Click);
        listBoxBooks->DoubleClick += gcnew EventHandler(this, &SuccessForm::ListBoxBooks_SelectedIndexChanged);
        listBoxBooks->Font = gcnew System::Drawing::Font("Arial", 16, System::Drawing::FontStyle::Bold);

        //Кнопка имущества
        Button^ buttonOK = gcnew Button();
        buttonOK->Text = "Сформировать заявку";
        buttonOK->Font = gcnew System::Drawing::Font("Arial", 16, System::Drawing::FontStyle::Bold);
        buttonOK->Location = System::Drawing::Point(400, 0);
        buttonOK->Size = System::Drawing::Size(200, 60);
        buttonOK->Click += gcnew EventHandler(this, &SuccessForm::OKButton_Click);

        //Кнопка выхода
        Button^ buttonExit = gcnew Button();
        buttonExit->Text = "Выйти";
        Font = gcnew System::Drawing::Font("Arial", 16, System::Drawing::FontStyle::Bold);
        buttonExit->Location = System::Drawing::Point(250, 500);
        buttonExit->Size = System::Drawing::Size(90, 50);
        buttonExit->Click += gcnew EventHandler(this, &SuccessForm::ExitButton_Click);

        this->Controls->Add(labelWelcome);
        this->Controls->Add(buttonOK);
        this->Controls->Add(buttonExit);
        this->Controls->Add(listBoxBooks);

        this->ClientSize = System::Drawing::Size(600, 600);
        this->AcceptButton = buttonOK;
        this->CenterToScreen();
        this->FormClosing += gcnew FormClosingEventHandler(this, &SuccessForm::SuccessForm_FormClosing);
        this->BackColor = System::Drawing::Color::SandyBrown;
        this->Text = "";
        this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
        this->MaximizeBox = false;
    }

private:
    void SuccessForm::ListBoxBooks_SelectedIndexChanged(Object^ sender, EventArgs^ e)
    {
        // Проверка, выбран ли элемент в списке
        if (listBoxBooks->SelectedIndex != -1)
        {
            // Получение выбранной недвижимости
            String^ selectedProperty = listBoxBooks->SelectedItem->ToString();

            // Ваш код для получения подробной информации о выбранной недвижимости
            // Передайте эту информацию в конструктор PropertyDetailsForm

            String^ propertyName = selectedProperty;
            String^ propertyDescription;
            books->TryGetValue(propertyName, propertyDescription);
            //props->TryGetValue(selectedProperty, propertyDescription);

            // Создание и отображение формы с подробной информацией
            PropertyDetailsForm^ propertyDetailsForm = gcnew PropertyDetailsForm(propertyName, propertyDescription, usr);
            //this->Hide();
            propertyDetailsForm->ShowDialog();
            //this->Show();
        }
    }
    void SuccessForm_FormClosing(Object^ sender, FormClosingEventArgs^ e)
    {
        exit(0);
    }
    void OKButton_Click(Object^ sender, EventArgs^ e)
    {
        // Создание новой формы со списком недвижимости
        PurchaseRequestForm^ purchaseRequestForm = gcnew PurchaseRequestForm(usr);
        purchaseRequestForm->StartPosition = FormStartPosition::CenterScreen;
        //this->Hide();
        // Отображение формы со списком недвижимости
        purchaseRequestForm->ShowDialog();
        //this->Show();
    }
    void ExitButton_Click(Object^ sender, EventArgs^ e)
    {
        this->Close();
    }
private: System::Void InitializeComponent() {
    this->SuspendLayout();
    // 
    // SuccessForm
    // 
    this->ClientSize = System::Drawing::Size(400, 400);
    this->Name = L"SuccessForm";
    this->ResumeLayout(false);
}
};

// Определение формы
public ref class MyForm : public Form
{
private:
    // Объявление переменных для хранения данных
    Dictionary< String^, String^>^ users = ParseCredentialsFile("users.txt");
    // Определение компонентов формы
    Label^ labelUsername;
    TextBox^ textBoxUsername;
    Label^ labelPassword;
    TextBox^ textBoxPassword;
    Button^ buttonSubmit;

public:
    MyForm()
    {
        // Инициализация компонентов формы
        labelUsername = gcnew Label();
        labelUsername->Text = "Билет:";
        labelUsername->Location = Point(10, 10);

        textBoxUsername = gcnew TextBox();
        textBoxUsername->Location = Point(120, 10);

        labelPassword = gcnew Label();
        labelPassword->Text = "Пароль:";
        labelPassword->Location = Point(10, 40);

        textBoxPassword = gcnew TextBox();
        textBoxPassword->Location = Point(120, 40);
        textBoxPassword->PasswordChar = '*';

        buttonSubmit = gcnew Button();
        buttonSubmit->Text = "Войти";
        buttonSubmit->Location = Point(10, 70);
        buttonSubmit->Click += gcnew EventHandler(this, &MyForm::SubmitButton_Click);

        // Инициализация списка пользователей

        //Посередине
        MyForm::StartPosition = FormStartPosition::CenterScreen;

        // Добавление компонентов на форму
        this->Controls->Add(labelUsername);
        this->Controls->Add(textBoxUsername);
        this->Controls->Add(labelPassword);
        this->Controls->Add(textBoxPassword);
        this->Controls->Add(buttonSubmit);

        this->ClientSize = System::Drawing::Size(287, 100);
        this->AcceptButton = buttonSubmit;
        this->Text = "Login";
        this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
    }

private:
    // Обработчик события нажатия кнопки Submit
    void MyForm::SubmitButton_Click(Object^ sender, EventArgs^ e)
    {
        String^ usr = textBoxUsername->Text;
        String^ pwd = textBoxPassword->Text;
        String^ temp;
        if (textBoxUsername->Text->Length != 6) {
            MessageBox::Show("Ошибка входа. Билет должен состоять из 6 чисел", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            this->textBoxPassword->Clear();
            this->textBoxUsername->Clear();
        }
        else if (users->ContainsKey(usr) && users->TryGetValue(usr, temp) && temp == pwd) {
            SuccessForm^ successForm = gcnew SuccessForm(textBoxUsername->Text);
            this->Hide();

            successForm->StartPosition = FormStartPosition::CenterScreen;
            successForm->ShowDialog();
            successForm->Hide();
            this->textBoxPassword->Clear();
            this->textBoxUsername->Clear();
            this->Show();
        }
        else {
            MessageBox::Show("Login failed. Invalid username or password. Try again.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            this->textBoxPassword->Clear();
            this->textBoxUsername->Clear();
        }
    }
private: System::Void InitializeComponent() {
    this->SuspendLayout();
    this->ClientSize = System::Drawing::Size(287, 60);
    this->Name = L"Вход";
    this->Text = L"Вход";
    this->ResumeLayout(false);
}
};

