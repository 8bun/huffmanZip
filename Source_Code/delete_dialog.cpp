#include "delete_dialog.h"
#include "ui_delete_dialog.h"

delete_Dialog::delete_Dialog(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::delete_Dialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog|Qt::FramelessWindowHint);
}

delete_Dialog::~delete_Dialog()
{
    delete ui;
}

void delete_Dialog::deleteFile(QString src)
{
    deleteFileName = src;
}


void delete_Dialog::closeEvent(QCloseEvent *event)
{
    if(delsucess)
    {
        emit end();
    }
    event->accept();
}

void delete_Dialog::on_btn_close_clicked()
{
    this->close();
}

bool delete_Dialog::DeleteDirectory(const QString &path)
{
    QDir dir(path);
    if(!dir.exists())
    {
        return false;
    }
    dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    QFileInfoList fileList = dir.entryInfoList();
    foreach (QFileInfo fi, fileList)
    {
        if (fi.isFile())
        {
            fi.dir().remove(fi.fileName());
        }
        else
        {
            DeleteDirectory(fi.absoluteFilePath());
        }
    }
    return dir.rmpath(dir.absolutePath());
}

void delete_Dialog::on_btn_yes_clicked()
{
    if (deleteFileName.isEmpty())
    {
        delsucess = false;
        this->close();
        return;
    }

    QFileInfo * fileinfo = new QFileInfo(deleteFileName);

    if(fileinfo->isFile())
    {
        QFile file(deleteFileName);
        if(file.exists())
        {
            file.remove();
        }
    }
    else
    {
        DeleteDirectory(deleteFileName);
    }

    delsucess = true;

    this->close();
}

void delete_Dialog::on_btn_no_clicked()
{
    delsucess = false;
    this->close();
}
