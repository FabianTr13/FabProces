#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<qstringlist.h>
#include<QTableWidgetItem>
#include<QMessageBox>
#include<listaprocesos.h>

//------------------------------Variables globales-----------------------------
ListaProcesos listPro;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->panelNew->hide();

    //Tablas
    QStringList headerLabels;
    QStringList headerRun;
    headerLabels<<"Nombre"<<"Memoria"<<"Tiempo";
    ui->tbProcesos->setHorizontalHeaderLabels(headerLabels);
    headerRun<<"PID"<<"Nombre"<<"Memoria"<<"Tiempo";
    ui->tbProcesos_run->setHorizontalHeaderLabels(headerRun);

    ui->cmbTipoProceso->insertItem(0, "Memoria");
    ui->cmbTipoProceso->insertItem(1, "Tiempo");
    ui->cmbTipoProceso->insertItem(2, "Mixto");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_cmdNewProcess_clicked()
{
    ui->panelNew->setFixedSize(600, 525);
    ui->panelProcesos->hide();
    ui->panelNew->show();
}

void MainWindow::on_cmdGestor_clicked()
{
    ui->panelProcesos->setFixedSize(600, 525);
    ui->panelNew->hide();
    ui->panelProcesos->show();
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

void MainWindow::cargarTablaProcesos()
{
    if(listPro.Vacia())
        return;

    Nodo *aux;
    aux = listPro.inicio;

    while (aux != NULL)
    {
        ui->tbProcesos_run->insertRow(ui->tbProcesos_run->rowCount());
        int rowindex = ui->tbProcesos_run->rowCount() -1;
        ui->tbProcesos_run->setItem(rowindex, 0, new QTableWidgetItem(QString::number(aux->pId)));
        ui->tbProcesos_run->setItem(rowindex, 1, new QTableWidgetItem(aux->nombre));
        ui->tbProcesos_run->setItem(rowindex, 2, new QTableWidgetItem(QString::number(aux->memoria)));
        ui->tbProcesos_run->setItem(rowindex, 3, new QTableWidgetItem(QString::number(aux->tiempo)));
        aux = aux->sig;
    }
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
    if(ui->tbProcesos->currentRow() == 0)
        return;

    int rowindex = ui->tbProcesos->currentRow();
    QString v_nombre = ui->tbProcesos->item(rowindex, 0)->text();
    QString v_memoria = ui->tbProcesos->item(rowindex, 1)->text();
    QString v_tiempo = ui->tbProcesos->item(rowindex, 2)->text();

    QString v_nombre_2 = ui->tbProcesos->item(rowindex - 1, 0)->text();
    QString v_memoria_2 = ui->tbProcesos->item(rowindex - 1, 1)->text();
    QString v_tiempo_2 = ui->tbProcesos->item(rowindex - 1, 2)->text();

     ui->tbProcesos->setItem(rowindex - 1, 0, new QTableWidgetItem(v_nombre));
     ui->tbProcesos->setItem(rowindex - 1, 1, new QTableWidgetItem(v_memoria));
     ui->tbProcesos->setItem(rowindex - 1, 2, new QTableWidgetItem(v_tiempo));

     ui->tbProcesos->setItem(rowindex, 0, new QTableWidgetItem(v_nombre_2));
     ui->tbProcesos->setItem(rowindex, 1, new QTableWidgetItem(v_memoria_2));
     ui->tbProcesos->setItem(rowindex, 2, new QTableWidgetItem(v_tiempo_2));
}

void MainWindow::on_cmdBajar_clicked()
{
    if(ui->tbProcesos->rowCount() -1 == ui->tbProcesos->currentRow())
        return;

    int rowindex = ui->tbProcesos->currentRow();
    QString v_nombre = ui->tbProcesos->item(rowindex, 0)->text();
    QString v_memoria = ui->tbProcesos->item(rowindex, 1)->text();
    QString v_tiempo = ui->tbProcesos->item(rowindex, 2)->text();

    QString v_nombre_2 = ui->tbProcesos->item(rowindex + 1, 0)->text();
    QString v_memoria_2 = ui->tbProcesos->item(rowindex + 1, 1)->text();
    QString v_tiempo_2 = ui->tbProcesos->item(rowindex + 1, 2)->text();

     ui->tbProcesos->setItem(rowindex + 1, 0, new QTableWidgetItem(v_nombre));
     ui->tbProcesos->setItem(rowindex + 1, 1, new QTableWidgetItem(v_memoria));
     ui->tbProcesos->setItem(rowindex + 1, 2, new QTableWidgetItem(v_tiempo));

     ui->tbProcesos->setItem(rowindex, 0, new QTableWidgetItem(v_nombre_2));
     ui->tbProcesos->setItem(rowindex, 1, new QTableWidgetItem(v_memoria_2));
     ui->tbProcesos->setItem(rowindex, 2, new QTableWidgetItem(v_tiempo_2));
}



void MainWindow::on_cmbTipoProceso_currentIndexChanged(int index)
{
    for(int i = 0; i< ui->tbProcesos->rowCount(); i++)
    {
        listPro.apilar(new Nodo(i,
                                ui->tbProcesos->item(i, 0)->text(),
                                ui->tbProcesos->item(i, 2)->text().toInt(),
                                ui->tbProcesos->item(i, 1)->text().toInt()
                                )
                      );
    }
    listPro.ordernaTiempo();
    cargarTablaProcesos();
}
