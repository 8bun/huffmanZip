#ifndef TOOLS_DIALOG_H
#define TOOLS_DIALOG_H

#include <QMainWindow>

namespace Ui {
class tools_dialog;
}

class tools_dialog : public QMainWindow
{
    Q_OBJECT

public:
    explicit tools_dialog(QWidget *parent = nullptr);
    ~tools_dialog();

private slots:
    void on_btn_close_clicked();

    void on_btn_yes_clicked();

    void on_donate_clicked();

private:
    Ui::tools_dialog *ui;
};

#endif // TOOLS_DIALOG_H
