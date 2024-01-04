#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QDate>
#include<QTime>
#include<QMessageBox>
#include<QFile>
#include<QDebug>
#include <QTextStream>

#include<tarea.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushAgregar_clicked();


private:
    Ui::MainWindow *ui;
    //lista enlazada
    QList <tarea*> m_tareas;
    const QString ARCHIVO ="tarea.csv";
    enum  Columna
    {
        TAREA, ASIGNATURA, FECHA, HORA
    };
    void agregartarea(tarea *t);
    void limpiar();
    void guardar();
    void cargar();
    bool colorTarea(const tarea *t);
};
#endif
