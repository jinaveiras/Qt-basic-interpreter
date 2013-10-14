#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../Scanner.h"
#include "../Input.h"
#include "../Output.h"
#include "AboutBox.h"
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_actionPbOnClick_triggered();
    void on_actionLimpiarOnClick_triggered();
    void on_actionParseOnClick_triggered();
    void on_actionEjecutaOnClick_triggered();
    void on_actionGuardarOnClick_triggered();
    void on_actionGuardar_como_triggered();
    void onAboutBox();
    void onNuevo();

private:
    void guardarPrograma(QString fichero);
    Ui::MainWindow *ui;
    Scanner *s;
    Input *entrada;
    Output *salida;
    QLabel *lblStatus;
    AboutBox *frmAbout;

};

#endif // MAINWINDOW_H
