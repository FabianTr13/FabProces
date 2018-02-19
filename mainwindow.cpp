#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<qstringlist.h>
#include<QTableWidgetItem>
#include<QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->panelNew->hide();

    //Tablas
    QStringList headerLabels;
    headerLabels<<"Nombre"<<"Memoria"<<"Tiempo";
    ui->tbProcesos->setHorizontalHeaderLabels(headerLabels);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_cmdNewProcess_clicked()
{
    ui->panelNew->setFixedSize(600, 525);
    ui->panelNew->show();
}

bool MainWindow::validador()
{
    if(ui->txtNombre->toPlainText() == "")
        return false;
    else if (ui->upMemoria->value() == 0)
        return false;
    else if(ui->upTiempo->value() == 0)
        return false;

    return true;
}

void MainWindow::limpiarNuevo()
{
    ui->txtNombre->clear();
    ui->upMemoria->setValue(0);
    ui->upTiempo->setValue(0);
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    item->~QListWidgetItem();
}

void MainWindow::on_cmdAgregar_clicked()
{
    if(!validador())
    {
        QMessageBox mm;
        mm.setText("Campos pendientes");
        mm.exec();
        return;
    }

   ui->tbProcesos->insertRow(ui->tbProcesos->rowCount());
   int rowindex = ui->tbProcesos->rowCount() -1;
   ui->tbProcesos->setItem(rowindex, 0, new QTableWidgetItem(ui->txtNombre->toPlainText()));
   ui->tbProcesos->setItem(rowindex, 1, new QTableWidgetItem(QString::number(ui->upMemoria->value())));
   ui->tbProcesos->setItem(rowindex, 2, new QTableWidgetItem(QString::number(ui->upTiempo->value())));
   limpiarNuevo();
}

void MainWindow::on_tbProcesos_doubleClicked(const QModelIndex &index)
{
    ui->tbProcesos->removeRow(ui->tbProcesos->currentRow());
}

void MainWindow::on_cmdSubir_clicked()
{

}
