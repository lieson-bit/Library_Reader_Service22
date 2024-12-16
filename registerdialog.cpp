#include "registerdialog.h"
#include "ui_registerdialog.h"
#include "mainwindow.h"
#include "hashtable.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <QMessageBox>

registerdialog::registerdialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registerdialog)
{
    ui->setupUi(this);

    for(int i=1;i<32;i++){
        ui->comboBoxDay_register->addItem(QString::number(i));
    }
    for(int i=1;i<13;i++){
        ui->comboBoxMonth_register->addItem(QString::number(i));
    }
}

registerdialog::~registerdialog()
{
    delete ui;
}

std::string registerdialog::generateString() {
     // Seed the random number generator based on the current time
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    // Get the current year
    std::time_t now = std::time(nullptr);
    std::tm localTime = {};
    localtime_s(&localTime, &now);
    int year = localTime.tm_year + 1900; // Years since 1900

    // Generate a random 4-digit number
    int randomDigits = rand() % 10000;

    // Format the string as "NNNN-YY"
    std::ostringstream oss;
    oss << std::setw(4) << std::setfill('0') << randomDigits << "-";
    oss << std::setw(2) << std::setfill('0') << (year % 100);

    return oss.str();
}

void registerdialog::Show()
{
    this->show();
}

void registerdialog::cleanScreen(){
    ui->nameedit_register->clear();
    ui->birthDateedit_register->clear();
    ui->emailedit_register->clear();
    ui->passwordedit_register->clear();
}

//globall variable for table
HashTable table;
void registerdialog::on_enter_register_clicked()
{
    MainWindow conn;

    QString date = ui->comboBoxDay_register->currentText();
    QString month = ui->comboBoxMonth_register->currentText();
    QString year = ui->birthDateedit_register->text();
    std::string fulldate = date.toStdString().append("."+month.toStdString()+"."+year.toStdString());

    std::string result = generateString();
    int key = 0;
    std::string finalstring;
    QString selectedText = ui->comboBox_register->currentText();

    if(selectedText == "A - subscription only"){
        std::string firststring= "A";
        finalstring = firststring.append(result);
    }else if(selectedText == "R - only reading hall"){
        std::string fstring= "R";
        finalstring = fstring.append(result);
    }else if(selectedText == "B - reading hall and subsccription"){
        std::string fstr= "B";
        finalstring = fstr.append(result);
    }

    for(char ch : finalstring){
        key += static_cast<int>(ch);
    }

    HashNode data;
    if(!(ui->nameedit_register->text().isEmpty() || ui->birthDateedit_register->text().isEmpty() || ui->emailedit_register->text().isEmpty() || ui->passwordedit_register->text().isEmpty())){
        if(!isValidDate(date.toInt(),month.toInt(),year.toInt())){
            ui->comment_register->setText("Неверная дата");
        }else{
            std::string email = ui->emailedit_register->text().toStdString();
            if(!isValidEmail(email)){
                ui->comment_register->setText("Адрес электронной почты указан неверно");
            }else{
                QString Name,birthday,email,address,password;
                Name=ui->nameedit_register->text();
                birthday=QString::fromStdString(fulldate);
                email=ui->emailedit_register->text();
                address= ui->addressedit_register->text();
                password= ui->passwordedit_register->text();

                data.key = key;
                std::string name = Name.toStdString();
                if (!name.empty()) {
                    name[0] = std::toupper(name[0]);
                    data.name = name;
                }
                data.birthDate = fulldate;             
                data.email = email.toStdString();
                data.address = address.toStdString();
                std::string pass = password.toStdString();
                data.password = pass;
                table.insert(data);

                if(!conn.connOpen()){
                    qDebug()<<"Failed to open the database";
                    return;
                }
                conn.connOpen();
                QSqlQuery qry;
                qry.prepare("insert into login_data (ID,Name,Birthday,Email,Address,Password) values ('"+QString::fromStdString(finalstring)+"','"+QString::fromStdString(name)+"','"+birthday+"','"+email+"','"+address+"','"+password+"')");
                if(qry.exec( )){
                    QMessageBox::critical(this,tr("Database"),tr("saved"));

                }else{
                    QMessageBox::critical(this,tr("Database"),tr("not saved"));
                }
                ui->getpersonal_data_2->setText("Ваше имя пользователя: " +QString::fromStdString(finalstring) +"\n" + "Ваш пароль: " + QString::fromStdString(pass));
                ui->comment_register->setText("Регистрация прошла успешно");
                conn.connClose();
                cleanScreen();
            }
        }

    }else{
        ui->comment_register->setText("Ваших данных недостаточно, регистрация не удалась");
    }
}

void registerdialog::upload(){

}

void registerdialog::on_exit_regi_clicked()
{
    cleanScreen();
    if(!mydb.open()){
        ui->comment_register->setText("Failed to open database");
    }else{
        ui->comment_register->setText("База данных подключена.....");
    }
    ui->getpersonal_data_2->clear();
    ui->getpersonal_data_2->setText("Примечание: Запомните свой пароль и имя пользователя,<br> которые появятся здесь");

    this->hide();

    // Create a new instance of MainWindow and show it
    MainWindow* mainWin = new MainWindow();
    mainWin->show();
}

