#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include "../include/User.h"
#include "../include/FileDump.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit LoginWindow(QWidget *parent = nullptr);
	~LoginWindow();

private slots:
	void on_btn_Log_In_clicked();

private:
	Ui::LoginWindow *ui;
	QMap<QString, User *> *myUsers;
	bool validUser();
};

#endif // LOGINWINDOW_H
