#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QFileDialog>
#include <QUndoCommand>
#include <QClipboard>
#include <QMessageBox>
#include <QDialogButtonBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    setCentralWidget (ui->editor);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_actionUndo_triggered()
{
    ui ->editor->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->editor->redo();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->editor->copy();
}


void MainWindow::on_actionCut_triggered()
{
    ui->editor->cut();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->editor->paste();
}

void MainWindow::on_actionOpen_triggered()
{
    fileName = QFileDialog ::getOpenFileName(this , "choose a file" , "/home/mahtab/");
    ui->statusBar->showMessage(fileName);
    QFile file(fileName) ;
    file.open(QFile::ReadOnly | QFile::Text) ;

    QTextStream input (&file) ;

    ui->editor->setPlainText(input.readAll());
}


void MainWindow::on_actionSave_as_triggered()
{

     fileName = QFileDialog ::getSaveFileName(this , "save file" ,"myNote.txt" , "");
     QFile file(fileName) ;
     file.open(QFile::WriteOnly | QFile::Text) ;
     QTextStream out(&file);
     out << ui->editor->toPlainText();
     file.flush() ;
     file.close() ;

}

void MainWindow::on_actionNew_triggered()
{

     if (! ui->editor->toPlainText().isEmpty()){
          QMessageBox::StandardButton reply;
          reply = QMessageBox::question(this , "save" , "Save changes to document before closing?" , QMessageBox::Yes|QMessageBox::No  ) ;
          if(reply == QMessageBox::Yes)
          {
              if(fileName==NULL)
                  fileName = QFileDialog ::getSaveFileName(this , "save file" ,"myNote.txt" , "");

              QFile file(fileName) ;
              file.open(QFile::WriteOnly | QFile::Text) ;
              QTextStream out(&file);
              out << ui->editor->toPlainText();
              file.flush() ;
              file.close() ;
          }
     }
     ui->editor->clear();
}


void MainWindow::on_actionSave_triggered()
{
    if(fileName==NULL)
        fileName = QFileDialog ::getSaveFileName(this , "save file" ,"myNote.txt" , "");

    QFile file(fileName) ;
    file.open(QFile::WriteOnly | QFile::Text) ;
    QTextStream out(&file);
    out << ui->editor->toPlainText();
    file.flush() ;
    file.close() ;
}
