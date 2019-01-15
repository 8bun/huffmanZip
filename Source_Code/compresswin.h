#ifndef COMPRESSWIN_H
#define COMPRESSWIN_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <QProcess>
#include <QMovie>

namespace Ui {
class compressWin;
}

class compressWin : public QMainWindow
{
    Q_OBJECT

public:
    explicit compressWin(QWidget *parent = nullptr);
    ~compressWin();
    void compressFile(QStringList src_files);

    QProcess * p;

signals:
    void end();

private slots:
    void on_btn_close_clicked();

    void on_rbtn_fast_clicked();

    void on_rbtn_min_clicked();

    void on_btn_choose_dst_clicked();

    void on_btn_start_clicked();

    void process_finished(int exitCode,QProcess::ExitStatus exitStatus);

private:
    Ui::compressWin *ui;
    QStringList src;
    QString dst_dir;
    QString dst_file;

    bool fast = true;
};

#endif // COMPRESSWIN_H
