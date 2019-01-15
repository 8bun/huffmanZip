#include "uncompresswin.h"
#include "ui_uncompresswin.h"

unCompressWin::unCompressWin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::unCompressWin)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog|Qt::FramelessWindowHint);
    ui->hint_wait->setVisible(false);
    ui->show_wait->setVisible(false);
}

unCompressWin::~unCompressWin()
{
    delete ui;
}

void unCompressWin::unCompressFile(QString filename)
{
    src = filename;
}

void unCompressWin::on_btn_close_clicked()
{
    this->close();
}

void unCompressWin::on_btn_choose_dst_clicked()
{
    QString fileName = QFileDialog::getExistingDirectory(this,"请选择模板保存路径...");
    ui->edt_dst->setText(fileName);
}

void unCompressWin::on_btn_start_clicked()
{
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

    p = new QProcess;

    connect(p,SIGNAL(finished(int , QProcess::ExitStatus )), this, SLOT(process_finished(int , QProcess::ExitStatus )));

    p->setWorkingDirectory(QDir::currentPath()+"/ag");  //指定进程的工作目录
    QString command="./ag/cga.exe";
    QStringList args;
    args.append("-o");
    args.append(src);

    QString dirname = dst_dir + "/output";
    QDir the_dir(dirname);
    if(!the_dir.exists())
    {
        the_dir.mkpath(dirname);
    }

    args.append("-d");
    args.append(dirname);

    p->setProgram(command);//commmand是要执行的命令，args是参数
    p->setArguments(args);

    p->start();

    ui->hint_wait->setVisible(true);
    ui->show_wait->setVisible(true);
    QMovie * movie = new QMovie("./res/waiting_sec.gif");
    QMovie * movie_show = new QMovie("./res/show_sec.gif");
    ui->hint_wait->setMovie(movie);
    ui->show_wait->setMovie(movie_show);
    movie->start();
    movie_show->start();
}

void unCompressWin::process_finished(int exitCode,QProcess::ExitStatus exitStatus)
{
    if(exitCode!=0)
    {
        QMessageBox::critical(0 ,
        "Error" , "Path should be english please",
        QMessageBox::Ok | QMessageBox::Default ,
        QMessageBox::Cancel | QMessageBox::Escape , 	0 );
    }

    emit end();
    this->close();
}
