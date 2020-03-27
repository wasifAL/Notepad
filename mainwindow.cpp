#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//new action trigger definition
void MainWindow::on_actionNew_triggered()
{
    currentFile.clear();
    ui->textEdit->setText(QString());
}

//open action trigger definition
void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open the file");
    QFile file(filename);
    currentFile = filename;
    if(!file.open(QIODevice::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning","Cannot open file : "+file.errorString());
    }
    setWindowTitle(filename);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

//save as action trigger definition
void MainWindow::on_actionSave_as_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,"Save as");
    QFile file(fileName);
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "Cannot save file : "+file.errorString());
    }
    currentFile = fileName;
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out<<text;
    file.close();
}

//print action trigger definition
void MainWindow::on_actionPrint_triggered()
{
    QPrinter printer;
    printer.setPrinterName("Printer Name");
    QPrintDialog pDialog(&printer, this);

    if(pDialog.exec() == QDialog::Rejected){
        QMessageBox::warning(this, "Warning","Cannot access printer");

        return;
    }
    ui->textEdit->print(&printer);
}

//copy action trigger definition
void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

//paste action trigger definition
void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

//cut action trigger definition
void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

//exit action trigger definition
void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

//undo action trigger definition
void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

//redo action trigger definition
void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}
