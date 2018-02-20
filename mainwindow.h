#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_cmdNewProcess_clicked();

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_cmdAgregar_clicked();

    bool validador();

    void limpiarNuevo();

    void on_tbProcesos_doubleClicked(const QModelIndex &index);
    void on_cmdSubir_clicked();

    void on_cmdBajar_clicked();

    void on_cmdGestor_clicked();

    void on_cmbTipoProceso_currentIndexChanged(int index);

    void cargarTablaProcesos();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
