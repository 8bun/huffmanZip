#include "tools_dialog.h"
#include "ui_tools_dialog.h"

tools_dialog::tools_dialog(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::tools_dialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog|Qt::FramelessWindowHint);
    ui->donate->setVisible(false);
}

tools_dialog::~tools_dialog()
{
    delete ui;
}

void tools_dialog::on_btn_close_clicked()
{
    this->close();
}

void tools_dialog::on_btn_yes_clicked()
{
    ui->donate->setVisible(true);
}

void tools_dialog::on_donate_clicked()
{
    ui->donate->setVisible(false);
}
