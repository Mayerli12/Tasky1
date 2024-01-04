#include "tarea.h"

tarea::tarea()
{

}

const QString &tarea::asginatura() const
{
    return m_asginatura;
}
void tarea::setAsginatura(const QString &newAsginatura)
{
    m_asginatura = newAsginatura;
}
const QDate &tarea::fecha() const
{
    return m_fecha;
}
void tarea::setFecha(const QDate &newFecha)
{
    m_fecha = newFecha;
}
const QTime &tarea::hora() const
{
    return m_hora;
}
void tarea::setHora(const QTime &newHora)
{
    m_hora = newHora;
}
const QString &tarea::nombre() const
{
    return m_nombre;
}
void tarea::setNombre(const QString &newNombre)
{
    m_nombre = newNombre;
}

tarea::tarea(const QString &asginatura, const QDate &fecha, const QTime &hora, const QString &nombre) : m_asginatura(asginatura),
    m_fecha(fecha),
    m_hora(hora),
    m_nombre(nombre)
{}
