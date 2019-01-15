#include "compresswin.h"
#include "ui_compresswin.h"

compressWin::compressWin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::compressWin)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog|Qt::FramelessWindowHint);
    ui->hint_wait->setVisible(false);
    ui->show_wait->setVisible(false);
}

compressWin::~compressWin()
{
    delete ui;
}

void compressWin::compressFile(QStringList src_files)
{
    src = src_files;
}

void compressWin::on_btn_close_clicked()
{
    this->close();
}

void compressWin::on_rbtn_fast_clicked()
{
    fast = true;
}

void compressWin::on_btn_choose_dst_clicked()
{
    QString fileName = QFileDialog::getExistingDirectory(this,"请选择模板保存路径...");
    ui->edt_dst->setText(fileName);
}

//void waitforend(QProcess * p)
//{
//    p->waitForFinished();
//    emit end();
//    this->close();
//}

void compressWin::on_btn_start_clicked()
{
    QString mode;

    if(ui->edt_dst_filename->text().isEmpty())
    {
        dst_file = "agc.zip";
    }
    else
    {
        QStringList sections = ui->edt_dst_filename->text().split(".");
        if(sections.length()==1)
        {
            dst_file = ui->edt_dst_filename->text()+".zip";
        }
        else
        {
            if(sections[sections.length()-1]!="zip")
            {
                dst_file = ui->edt_dst_filename->text()+".zip";
            }
            else
            {
                dst_file = ui->edt_dst_filename->text();
            }
        }
    }

    if(ui->edt_dst->text().isEmpty())
    {
        QMessageBox::critical(0 ,
        "File path is none" , "Please confirm the file path",
        QMessageBox::Ok | QMessageBox::Default ,
        QMessageBox::Cancel | QMessageBox::Escape , 	0 );
        return;
    }
    else
    {
        dst_dir = ui->edt_dst->text();
    }

    if(fast)
    {
        mode="-1";
    }
    else
    {
        mode="-9";
    }

//    mode+="-j \""+dst_dir+"/"+dst_file+"\" "+src;

//    ui->edt_dst_filename->setText(mode);
//    QProcess *pro = new QProcess;
//    pro->start("./ag/agc.exe "+mode);
//    qDebug()<<mode;

    p = new QProcess;

    connect(p,SIGNAL(finished(int , QProcess::ExitStatus )), this, SLOT(process_finished(int , QProcess::ExitStatus )));

    p->setWorkingDirectory(QDir::currentPath()+"/ag");  //指定进程的工作目录
    QString command="./ag/agc.exe";
    QStringList args;
    args.append("-o");
    args.append(mode);
    args.append("-j");
    args.append(dst_dir+"/"+dst_file);
    foreach(QString file , src)
    {
        args<<file;
    }


    p->setProgram(command);//commmand是要执行的命令，args是参数
    p->setArguments(args);
    p->start();

    ui->hint_wait->setVisible(true);
    ui->show_wait->setVisible(true);
    QMovie * movie = new QMovie("./res/waiting.gif");
    QMovie * movie_show = new QMovie("./res/show.gif");
    ui->hint_wait->setMovie(movie);
    ui->show_wait->setMovie(movie_show);
    movie->start();
    movie_show->start();


}

void compressWin::process_finished(int exitCode,QProcess::ExitStatus exitStatus)
{
    if(exitCode!=0)
    {
        QMessageBox::critical(0 ,
        "Error" , "Error Code : "+QString::number(exitCode),
        QMessageBox::Ok | QMessageBox::Default ,
        QMessageBox::Cancel | QMessageBox::Escape , 	0 );
    }

    emit end();
    this->close();
}

void compressWin::on_rbtn_min_clicked()
{
    fast = false;
}
