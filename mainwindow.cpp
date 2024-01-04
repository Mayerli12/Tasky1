#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QDate hoy = QDate::currentDate();
    QTime ahora = QTime();

    ui->dateFecha->setMinimumDate(hoy);
    ui->dateFecha->setDate(hoy);
    ui->timeHora->setTime(ahora);
    //CONFIGURAR TABLA
    ui->tblTareas->setColumnCount(4);
    QStringList cabecera;
    cabecera<<"Tarea" << "Asignatura" << "Fecha" << "Hora";
    ui->tblTareas->setHorizontalHeaderLabels(cabecera);
    //cargar tareas desde el archivo
    cargar();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushAgregar_clicked()
{
    QString nom = ui->txtTarea->text(); //todo esta en mi objeto ui y despues llamamos al cuadro de texto
    QString asi = ui-> cmbAsignatura->currentText();
    QDate fec = ui->dateFecha->date();
    QTime hor = ui ->timeHora->time();
    /*Crea una tarea y Agrega una tarea a la lista*/
    tarea *t = new tarea(asi, fec, hor, nom);
    agregartarea(t);
    limpiar();
    guardar();
    if(nom.length()==0){
        ui->txtTarea->setFocus();
        QMessageBox::critical(0,"Agregar tarea","El nombre de la tarea no puede estar vacio");
        return;
    }
}

void MainWindow::agregartarea(tarea *t)
{
    /* Crea una tarea y Agrega una tarea a la lista */
    m_tareas.append(t);

    // Agrega una fila a la tabla y establece los elementos de la fila
    int fila = ui->tblTareas->rowCount();
    ui->tblTareas->insertRow(fila);
    ui->tblTareas->setItem(fila, TAREA, new QTableWidgetItem(t->nombre()));
    ui->tblTareas->setItem(fila, ASIGNATURA, new QTableWidgetItem(t->asginatura()));
    ui->tblTareas->setItem(fila, FECHA, new QTableWidgetItem(t->fecha().toString("dd/MM/yyyy")));
    ui->tblTareas->setItem(fila, HORA, new QTableWidgetItem(t->hora().toString("hh:mm")));

    // Limpia los campos de entrada después de agregar la tarea
    ui->txtTarea->clear();
    ui->cmbAsignatura->setCurrentIndex(0);
    ui->dateFecha->setDate(QDate::currentDate());
    ui->timeHora->setTime(QTime::currentTime());

    // Cambiar color por dia
    if (colorTarea(t))
    {
        QColor colorFondo(255, 153, 153);
        for (int i = 0; i < ui->tblTareas->columnCount(); ++i)
        {
            QTableWidgetItem *item = ui->tblTareas->item(fila, i);
            if (item)
            {
                item->setBackground(colorFondo);
            }
        }
    }
}

void MainWindow::limpiar()
{
    QDate hoy = QDate::currentDate();
    QTime ahora = QTime::currentTime();
    // Limpia los campos de entrada despues de agregar la tarea
    ui->txtTarea->clear();
    ui->cmbAsignatura->setCurrentIndex(0);
    ui->dateFecha->setDate(QDate::currentDate());
    ui->timeHora->setTime(QTime::currentTime());
    ui->txtTarea->setFocus();
}

void MainWindow::guardar()
{
    // Abrir el archivo y guardar
    QFile archivo(ARCHIVO);
    if (archivo.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream salida(&archivo);

        tarea *t;
        foreach(t, m_tareas){
            salida << t->nombre() << ";" << t->asginatura() << ";";
            salida << t->fecha().toString ("dd/MM/yyyy") << ";";
            salida << t->hora().toString("hh:mm") << "\n";
        }
        archivo.close();
        QMessageBox::information(this,"Guardar Tareas","Tareas guardadas con éxito");
    }else{
        QMessageBox::critical(this,"Guardar tareas", "No se puede escribir sobre " + ARCHIVO);
    }
}

void MainWindow::cargar()
{
    // Verificar si el archivo existe
    QFile archivo(ARCHIVO);
    if (!archivo.exists())
        return;

    // cargar datos
    if (archivo.open(QFile::ReadOnly)) {
        QTextStream entrada(&archivo);
        int fila;
        while(!entrada.atEnd()){
            //leer la linea del archivo
            QString linea = entrada.readLine();
            //separar loc campos por ";"
            QStringList datos = linea.split(";");
            //obtener el nombre y la asignatura
            //qDebug() <<datos;
            //obtener el nombre y la asignatura
            QString nom = datos[0];
            QString asi = datos[1];
            //obtener la fecha y
            QStringList fec = datos[2].split("/");
            QDate f(fec[2].toInt(), fec[1].toInt(), fec[0].toInt());
            //obtener la hora
            QStringList hor = datos[3].split(":");
            QTime h(hor[0].toInt(), hor[1].toInt());
            //crear la tarea
            tarea *t = new tarea(asi, f, h, nom);
            //agregar la tarea
            agregartarea(t);

        }
        archivo.close();
    }
}

bool MainWindow::colorTarea(const tarea *t)
{
    // Para la fecha actual
    QDate fechaActual = QDate::currentDate();
    // Para la fecha limite
    QDate fechaLimite = t->fecha();
    return (fechaLimite >= fechaActual && fechaLimite <= fechaActual.addDays(1));
}
