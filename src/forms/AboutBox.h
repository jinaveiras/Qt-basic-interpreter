#ifndef ABOUTBOX_H
#define ABOUTBOX_H

#include <QMainWindow>

namespace Ui {
class AboutBox;
}

/// Clase que representa una ventana con datos acerca de la aplicación
class AboutBox : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit AboutBox(QWidget *parent = 0);
    ~AboutBox();

private:
    Ui::AboutBox *ui;
};

#endif // ABOUTBOX_H
