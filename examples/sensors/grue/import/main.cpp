/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the QtSensors module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtDeclarative/qdeclarativeextensionplugin.h>
#include <QtDeclarative/qdeclarative.h>

#include <gruesensor.h>

QT_BEGIN_NAMESPACE

class GrueSensorQmlImport : public QDeclarativeExtensionPlugin
{
    Q_OBJECT
public:
    virtual void registerTypes(const char *uri)
    {
        char const * const package = "Grue";
        if (QLatin1String(uri) != QLatin1String(package)) return;
        int major;
        int minor;

        // Register the 1.0 interfaces
        major = 1;
        minor = 0;
        qmlRegisterType           <GrueSensor       >(package, major, minor, "GrueSensor");
        qmlRegisterUncreatableType<GrueSensorReading>(package, major, minor, "GrueSensorReading", QLatin1String("Cannot create GrueSensorReading"));
    }
};

QT_END_NAMESPACE

#include "main.moc"

Q_EXPORT_PLUGIN2(gruesensorqmlimport, QT_PREPEND_NAMESPACE(GrueSensorQmlImport));

/*
    \qmlclass GrueSensor GrueSensor
    \inqmlmodule Grue 1
    \brief The GrueSensor element reports on your chance of being eaten by a Grue.

    The GrueSensor element reports on your chance of being eaten by a Grue.

    This element wraps the GrueSensor class. Please see the documentation for
    GrueSensor for details.

    \sa {QtMobility.sensors QML Limitations}
*/

/*
    \qmlproperty GrueSensorReading Grue1::GrueSensor::reading
    Holds the most recent Grue sensor reading.
    Please see QSensor::reading for information about this property.
*/

/*
    \qmlsignal Grue1::GrueSensor::onReadingChanged()
    Called when the reading object changes.
    Please see QSensor::readingChanged() for information about this signal.
*/

/*
    \qmlclass GrueSensorReading GrueSensorReading
    \inqmlmodule Grue 1
    \inherits QtMobility.sensors1::SensorReading
    \brief The GrueSensorReading element holds the most recent GrueSensor reading.

    The GrueSensorReading element holds the most recent GrueSensor reading.

    This element wraps the GrueSensorReading class. Please see the documentation for
    GrueSensorReading for details.

    This element cannot be directly created.
*/

/*
    \qmlproperty qreal Grue1::GrueSensorReading::chanceOfBeingEaten
    Please see GrueSensorReading::chanceOfBeingEaten for information about this property.
*/
