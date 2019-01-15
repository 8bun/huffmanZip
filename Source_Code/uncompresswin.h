#ifndef UNCOMPRESSWIN_H
#define UNCOMPRESSWIN_H

#include <QMainWindow>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>
#include <QMovie>

namespace Ui {
class unCompressWin;
}

class unCompressWin : public QMainWindow
{
    Q_OBJECT

public:
    explicit unCompressWin(QWidget *parent = nullptr);
    ~unCompressWin();

    void unCompressFile(QString fielname);

    QProcess * p;

signals:
    void end();

private slots:
    void on_btn_close_clicked();

    void on_btn_choose_dst_clicked();

    void on_btn_start_clicked();

    void process_finished(int exitCode,QProcess::ExitStatus exitStatus);

private:
    Ui::unCompressWin *ui;

    QString src;
    QString dst_dir;
};

#endif // UNCOMPRESSWIN_H
