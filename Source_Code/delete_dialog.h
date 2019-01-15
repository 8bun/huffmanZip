#ifndef DELETE_DIALOG_H
#define DELETE_DIALOG_H

#include <QMainWindow>
#include <QDebug>
#include <QCloseEvent>
#include <QFileInfo>
#include <QDir>

namespace Ui {
class delete_Dialog;
}

class delete_Dialog : public QMainWindow
{
    Q_OBJECT

public:
    explicit delete_Dialog(QWidget *parent = nullptr);
    ~delete_Dialog();
    void deleteFile(QString src);

signals:
    void end();

private slots:
    void on_btn_close_clicked();

    void on_btn_yes_clicked();

    void on_btn_no_clicked();

private:
    Ui::delete_Dialog *ui;
    QString deleteFileName;
    bool delsucess = false;

    void closeEvent(QCloseEvent *event);
    bool DeleteDirectory(const QString &path);
};

#endif // DELETE_DIALOG_H
