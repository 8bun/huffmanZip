#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initWindows();
}

void MainWindow::setAGCModel()
{
    model=new QDirModel();
    model->setReadOnly(true);
    //设置排序方式
    model->setSorting(QDir::DirsFirst | QDir::IgnoreCase | QDir::Name);

    ui->treeView->setModel(model);
    //当QTreeView的宽度大于所有列宽之和时，最后一列的宽度自动扩展以充满最后的边界
    ui->treeView->header()->setStretchLastSection(true);

    location = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    ui->info_file->setText("[Dir] "+location+"  ");

    QString filepath=location;
    ui->treeView->header()->setDefaultSectionSize(1000/4); //设置默认列等宽
    ui->treeView->header()->setDefaultAlignment(Qt::AlignCenter); //表头的对齐方式
    ui->treeView->setRootIndex(model->index(filepath));
}

void MainWindow::initWindows()
{
    setWindowFlags(Qt::Dialog|Qt::FramelessWindowHint);
    setAGCModel();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_exit_clicked()
{
    exit(0);
}

void MainWindow::on_btn_minline_clicked()
{
    setWindowState(Qt::WindowMinimized);
}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    src_files.clear();
    currentFilePath=model->filePath(index);

    QFileInfo fileinfo(currentFilePath);

    if(fileinfo.isDir())
    {
        QString currentDirPath = "";
        QString all_file = "";

        QModelIndex parentIndex=ui->treeView->currentIndex();
        int numRows=model->rowCount(parentIndex);
        if(numRows<=0)
        {
            src_files.clear();
        }
        else
        {
            QModelIndex subIndex;
            QString filename;
            for(int row=0;row<numRows;row++)
            {
                 subIndex = model->index(row, 0, parentIndex);
                 filename=model->data(subIndex).toString();
                 currentDirPath=model->filePath(index);
                 QFileInfo check_info(currentDirPath+"/"+filename);
                 if(check_info.isFile())
                 {
//                     all_file = all_file + " \"" + currentDirPath+"/"+filename+"\"";
                     all_file = currentDirPath+"/"+filename;
//                     all_file.trimmed();
                     src_files<<all_file;
                 }
            }
        }

        ui->info_file->setText("[Dir] "+currentFilePath+"  ");
    }
    else
    {
//        src_files = "\""+currentFilePath+"\"";
        src_files << currentFilePath ;

        qint64 size = fileinfo.size();
        QString change_size ;
        if(size>1048576)
        {
            change_size = QString::number(fileinfo.size()/1048576)+" MB";
        }
        else if(size>1024)
        {
            change_size = QString::number(fileinfo.size()/1024)+" KB";
        }
        else
        {
            change_size = QString::number(fileinfo.size())+" B";
        }
        ui->info_file->setText("[File] "+fileinfo.fileName()+" "+fileinfo.group()+" "+change_size+"  ");
    }

//    qDebug()<<"need to deal:                       "+src_files+"                                ";
}

void MainWindow::on_btn_delete_clicked()
{
    if(currentFilePath!="")
    {
        dialog_delete = new delete_Dialog(this);
        connect(dialog_delete,SIGNAL(end()),this,SLOT(delete_dialog_end()));
        dialog_delete->deleteFile(currentFilePath);
        dialog_delete->setWindowModality(Qt::WindowModal);
        dialog_delete->show();
    }
}

void MainWindow::delete_dialog_end()
{

    model->refresh();
    src_files.clear();
    currentFilePath="";
    ui->info_file->setText(currentFilePath);
}

void MainWindow::on_btn_refresh_clicked()
{
    model->refresh();
}

void MainWindow::on_btn_last_clicked()
{
    QDir dir(location);
    if(dir.cdUp())
    {
        location = dir.path();
        ui->treeView->setRootIndex(model->index(location));
    }
    else
    {
        location = "C:\\file../";
        ui->treeView->setRootIndex(model->index(location));
        location = "C:\\";
    }
}

void MainWindow::on_treeView_doubleClicked(const QModelIndex &index)
{
    QString url = model->filePath(index);
    QFileInfo fileinfo(url);
    if(fileinfo.isDir())
    {
        location = url;
        ui->treeView->setRootIndex(model->index(location));
    }
}

void MainWindow::on_btn_encode_clicked()
{
    if(!src_files.empty())
    {
        win_compress = new compressWin(this);
        connect(win_compress,SIGNAL(end()),this,SLOT(delete_dialog_end()));
        win_compress->compressFile(src_files);
        win_compress->setWindowModality(Qt::WindowModal);
        win_compress->show();
    }
}

void MainWindow::on_btn_decode_clicked()
{
    if(src_files.length()==1)
    {
        //先判断是不是zip
        QString filename = src_files[0];
        QStringList sub = filename.split(".");
        if(sub.length()==1)
        {
            QMessageBox::critical(0 ,
            "Tips" , "Need ZIP File",
            QMessageBox::Ok | QMessageBox::Default ,
            QMessageBox::Cancel | QMessageBox::Escape , 	0 );
            return;
        }
        else
        {
            if(!(sub[sub.length()-1]=="zip"))
            {
                QMessageBox::critical(0 ,
                "Tips" , "Need ZIP File",
                QMessageBox::Ok | QMessageBox::Default ,
                QMessageBox::Cancel | QMessageBox::Escape , 	0 );
                return;
            }
        }

        win_uncompress = new unCompressWin(this);
        connect(win_uncompress,SIGNAL(end()),this,SLOT(delete_dialog_end()));
        win_uncompress->unCompressFile(filename);
        win_uncompress->setWindowModality(Qt::WindowModal);
        win_uncompress->show();
    }
    else
    {
        QMessageBox::critical(0 ,
        "Tips" , "Need ZIP File",
        QMessageBox::Ok | QMessageBox::Default ,
        QMessageBox::Cancel | QMessageBox::Escape , 	0 );
    }
}

void MainWindow::on_btn_tools_clicked()
{
    dialog_tools = new tools_dialog(this);
    dialog_tools->setWindowModality(Qt::WindowModal);
    dialog_tools->show();
}
