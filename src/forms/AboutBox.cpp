#include "AboutBox.h"
#include "ui_AboutBox.h"

AboutBox::AboutBox(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AboutBox)
{
    ui->setupUi(this);
    this->setFixedSize( this->size() );
    this->setAttribute( Qt::WA_DeleteOnClose, true );
    this->setWindowFlags( Qt::Dialog );
    connect( ui->btnAceptar, SIGNAL( clicked() ), this, SLOT( close() ) );
}

AboutBox::~AboutBox()
{
    delete ui;
}
