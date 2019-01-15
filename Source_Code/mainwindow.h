#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDirModel>
#include <QDebug>
#include <QFileInfo>
#include <QStandardPaths>

#include "delete_dialog.h"
#include "tools_dialog.h"
#include "compresswin.h"
#include "uncompresswin.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_exit_clicked();

    void on_btn_minline_clicked();

    void on_treeView_clicked(const QModelIndex &index);

    void on_btn_delete_clicked();

    void delete_dialog_end();

    void on_btn_refresh_clicked();

    void on_btn_last_clicked();

    void on_treeView_doubleClicked(const QModelIndex &index);

    void on_btn_encode_clicked();

    void on_btn_decode_clicked();

    void on_btn_tools_clicked();

private:
    Ui::MainWindow *ui;
    QDirModel * model;
    QStringList src_files;
    QString currentFilePath = "";
    QString location = "./";

    delete_Dialog * dialog_delete;
    tools_dialog * dialog_tools;
    compressWin * win_compress;
    unCompressWin * win_uncompress;

    void initWindows();
    void setAGCModel();
};

#endif // MAINWINDOW_H
