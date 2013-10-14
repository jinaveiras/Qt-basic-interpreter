#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QTextDocumentWriter>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    entrada = new Input(this);
    salida = new Output(ui->txtConsole);
    lblStatus = new QLabel("",ui->statusBar);

    connect(ui->actionCargar, SIGNAL(triggered()), this, SLOT(on_actionPbOnClick_triggered()));
    connect(ui->actionGuardar, SIGNAL(triggered()), this, SLOT(on_actionGuardarOnClick_triggered()));
    connect(ui->actionAcerca_de, SIGNAL(triggered()), this, SLOT(onAboutBox()));
    connect(ui->actionNuevo, SIGNAL(triggered()), this, SLOT(onNuevo()));
    ui->statusBar->addPermanentWidget(lblStatus,100);
    s = new Scanner(ui->plainTextEdit, entrada, salida);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete s;
    delete entrada;
    delete salida;
    delete lblStatus;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    event->accept();
}

void MainWindow::onNuevo()
{
    salida->limpiar();
    ui->plainTextEdit->clear();
    lblStatus->setText("");
}

void MainWindow::onAboutBox(){
    frmAbout = new AboutBox(this);
    frmAbout->setWindowModality(Qt::WindowModal);
    frmAbout->show();
    frmAbout->raise();
    frmAbout->activateWindow();
}

void MainWindow::on_actionLimpiarOnClick_triggered()
{
   ui->txtConsole->clear();
}

void MainWindow::on_actionGuardarOnClick_triggered()
{
    //salida->escribe(ui->statusBar->currentMessage().toStdString());
    if (lblStatus->text() != ""){
        QString filename = lblStatus->text();
        guardarPrograma( filename );
    } else {
        on_actionGuardar_como_triggered();
    }
}

void MainWindow::guardarPrograma(QString fichero)
{
    salida->limpiar();
    if ( ui->plainTextEdit->document()->isModified() ){
        QTextDocumentWriter programa( fichero, "plaintext" );
        bool guardado = programa.write( ui->plainTextEdit->document() );
        salida->limpiar();
        if (!guardado)
            salida->escribe( "No se ha podido guardar" );
        else {
            lblStatus->setText( fichero );
            salida->escribe( "Se ha guardado correctamente" );
        }
        ui->plainTextEdit->document()->setModified(!guardado);
    } else {
        salida->escribe("Nada que guardar.");
    }
}

void MainWindow::on_actionGuardar_como_triggered()
{
    QString filename = QFileDialog::getSaveFileName(
                this,
                tr("Guardar el programa"),
                QDir::currentPath(),
                tr("Programa basic (*.bas);;Otros ficheros(*.*)") );
    if (!filename.isNull()){
        if (filename != ""){
            guardarPrograma(filename);
        }else{
            salida->escribe("Debe seleccionar un nombre de fichero.");
        }
    }
}

void MainWindow::on_actionEjecutaOnClick_triggered()
{
    s->ejecuta();
}

void MainWindow::on_actionParseOnClick_triggered()
{
    s->scan();
}

void MainWindow::on_actionPbOnClick_triggered()
{
    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Abrir un fichero de programa BASIC"),
                QDir::currentPath(),
                tr("Programa basic (*.bas);;Otros ficheros(*.*)") );
    if (!filename.isNull()){
        lblStatus->setText(filename);
        try{
            ui->plainTextEdit->clear();
            QFile file(filename);
            if (file.open(QIODevice::ReadOnly)){
                QTextStream entrada( &file );
                QString linea;
                while ( !entrada.atEnd() ){
                    linea = entrada.readLine();
                    ui->plainTextEdit->appendPlainText(linea);
                }
                ui->plainTextEdit->document()->setModified(false);
            }
        } catch ( exception &e ){
            ui->txtConsole->appendPlainText(e.what());
        } catch (...) {
            ui->txtConsole->appendPlainText(QString(""));
        }
    }
}
