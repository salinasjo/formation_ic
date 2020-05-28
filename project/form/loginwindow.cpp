#include "loginwindow.h"
#include "mainwindow.h"
#include "ui_loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::LoginWindow)
{
	ui->setupUi(this);
	myUsers = new QMap<QString, User *>();
	bool loaded = User::loadUsers(myUsers);
	if(!loaded) {
		FileDump::WriteLine("Error while loading Users from file!");
	}
	else {
		FileDump::WriteLine("Successfully loaded Users from file!");
	}
}

LoginWindow::~LoginWindow()
{
	delete ui;
}

void LoginWindow::on_btn_Log_In_clicked()
{
	if(validUser()) {
		auto *u = myUsers->value(ui->txt_Login->text());
		MainWindow *mW = new MainWindow();
		mW->setUser(u);
		mW->show();
		this->close();
	}
}

bool LoginWindow::validUser() {
	User *u = myUsers->value(ui->txt_Login->text());
	if(u!=nullptr) {
		if(ui->txtx_Pwd->text().compare(u->getPassword())==0) {
			FileDump::WriteLine("Connection of user : " +u->getFirstName().toStdString() + " " + u->getLastName().toStdString());
			return true;
		}
	}
	FileDump::WriteLine("Error Connection : " + ui->txt_Login->text().toStdString());
	return false;
}
