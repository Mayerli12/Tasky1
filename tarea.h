#ifndef TAREA_H
#define TAREA_H

#include <QObject>
#include <QMainWindow>
#include<QDate>
#include<QTime>
class tarea
{
public:
    tarea();
    //nom, asi, fec, hor
    tarea(const QString &asginatura, const QDate &fecha, const QTime &hora, const QString &nombre);
    const QString &asginatura() const;
    void setAsginatura(const QString &newAsginatura);
    const QDate &fecha() const;
    void setFecha(const QDate &newFecha);
    const QTime &hora() const;
    void setHora(const QTime &newHora);
    const QString &nombre() const;
    void setNombre(const QString &newNombre);
private:
    QString m_asginatura;
    QDate m_fecha;
    QTime m_hora;
    QString m_nombre;
};

#endif // TAREA_H
