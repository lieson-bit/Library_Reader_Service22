#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->_checkBox_Home->setChecked(false);
    ui->username->setPlaceholderText("Username");
    ui->password->setPlaceholderText("Password");
    //ptrregisterdialog = new registerdialog(this);
    connect(ui->_checkBox_Home, &QCheckBox::stateChanged, this, &MainWindow::updateLoginButtonState);
    updateLoginButtonState(ui->_checkBox_Home->checkState());
    connect(ui->_checkBox_Home, &QCheckBox::clicked, this, &MainWindow::on__checkBox_Home_clicked);

    if(!connOpen()){
        ui->label_ho->setText("Failed to open database");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    //delete ptrregisterdialog;
}

void MainWindow::on_cancel_login_clicked()
{
    this->close();
}

void MainWindow::updateLoginButtonState(int state)
{
    // Enable or disable the login button based on the checkbox state
    ui->enter_login->setEnabled(state == Qt::Checked);
}
void MainWindow::on_enter_login_clicked()
{
    QString Username,Password;
    Username = ui->username->text();
    Password = ui->password->text();
    if(Username==QString::fromStdString("A1234-20") && Password == QString::fromStdString("owner")){
        connClose();
        this->hide();
        ownerDialog owner;
        owner.setModal(true);
        owner.exec();
    }else{

        if(!connOpen()){
            qDebug()<<"Failed to open the database";
            return;
        }

        connOpen();
        QSqlQuery qry;
        qry.prepare("select * from login_data where ID='"+Username+"' and Password='"+Password+"'");

        if(qry.exec( )){
            int c=0;
            while(qry.next()){
                c++;
            }
            if(c==1){
                QFile file("C:\\Users\\1\\OneDrive\\Desktop\\Library_Reader_Service\\credentials.txt");
                if (file.open(QIODevice::WriteOnly | QIODevice::Text))
                {
                    QTextStream out(&file);
                    out << Username << "\n";
                    out << Password << "\n";
                    file.close();

                }

                connClose();
                this->hide();
                portaldialog studentinf;
                studentinf.setModal(true);
                studentinf.exec();


            }
            if(c>1)
                ui->label_ho->setText("Дублируйте имя пользователя и пароль!!");
            if(c<1)
                ui->label_ho->setText("Неверные детали");
        }
    }

}

QString MainWindow::returnname(){
    return ui->username->text();
}

void MainWindow::on_Register_Home_clicked()
{
    //ptrregisterdialog->Show();
    connClose();
    this->hide();
    registerdialog owner;
    owner.setModal(true);
    owner.exec();
}


void MainWindow::on__checkBox_Home_clicked()
{
    if (ui->username->text().isEmpty() || ui->password->text().isEmpty()) {
            // If either field is empty, prevent the checkbox from being checked
            ui->_checkBox_Home->setChecked(false);
        }
}

