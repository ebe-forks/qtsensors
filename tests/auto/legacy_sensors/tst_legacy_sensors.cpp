/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtSensors module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtTest/QtTest>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QSensor>
#include "test_backends.h"

class tst_legacy_sensors : public QObject
{
    Q_OBJECT
public:
    tst_legacy_sensors(QObject *parent = 0)
        : QObject(parent)
    {
        qputenv("QT_SENSORS_LOAD_PLUGINS", "0"); // Do not load plugins
        register_test_backends();
    }

private slots:
    void initTestCase()
    {
    }

    void cleanupTestCase()
    {
    }

    void versions_data()
    {
        QTest::addColumn<QString>("version");
        QTest::addColumn<bool>("exists");

        QTest::newRow("1.0") << "1.0" << false;
        QTest::newRow("1.1") << "1.1" << true;
        QTest::newRow("1.2") << "1.2" << true;
        QTest::newRow("1.3") << "1.3" << true;
    }

    void versions()
    {
        QFETCH(QString, version);
        QFETCH(bool, exists);

        QQmlEngine engine;
        QString qml = QString("import QtQuick 2.0\nimport QtMobility.sensors %1\nItem {}").arg(version);
        QQmlComponent c(&engine);
        c.setData(qml.toLocal8Bit(), QUrl::fromLocalFile(QDir::currentPath()));
        if (!exists)
            QTest::ignoreMessage(QtWarningMsg, "QQmlComponent: Component is not ready");
        QObject *obj = c.create();
        QCOMPARE(exists, (obj != 0));
        delete obj;
        QList<QQmlError> errors = c.errors();
        if (exists) {
            QCOMPARE(errors.count(), 0);
        } else {
            QCOMPARE(errors.count(), 1);
            QString expected = QString("module \"QtMobility.sensors\" version %1 is not installed").arg(version);
            QString actual = errors.first().description();
            QCOMPARE(expected, actual);
        }
    }

    void elements_data()
    {
        QTest::addColumn<QString>("version");
        QTest::addColumn<QString>("element");
        QTest::addColumn<bool>("exists");

        QTest::newRow("1.1 SensorReading") << "1.1" << "SensorReading" << false;
        QTest::newRow("1.1 Accelerometer") << "1.1" << "Accelerometer" << true;
        QTest::newRow("1.1 AccelerometerReading") << "1.1" << "AccelerometerReading" << true;
        QTest::newRow("1.1 AmbientLightSensor") << "1.1" << "AmbientLightSensor" << true;
        QTest::newRow("1.1 AmbientLightReading") << "1.1" << "AmbientLightReading" << true;
        QTest::newRow("1.1 Compass") << "1.1" << "Compass" << true;
        QTest::newRow("1.1 CompassReading") << "1.1" << "CompassReading" << true;
        QTest::newRow("1.1 Magnetometer") << "1.1" << "Magnetometer" << true;
        QTest::newRow("1.1 MagnetometerReading") << "1.1" << "MagnetometerReading" << true;
        QTest::newRow("1.1 OrientationSensor") << "1.1" << "OrientationSensor" << true;
        QTest::newRow("1.1 OrientationReading") << "1.1" << "OrientationReading" << true;
        QTest::newRow("1.1 ProximitySensor") << "1.1" << "ProximitySensor" << true;
        QTest::newRow("1.1 ProximityReading") << "1.1" << "ProximityReading" << true;
        QTest::newRow("1.1 RotationSensor") << "1.1" << "RotationSensor" << true;
        QTest::newRow("1.1 RotationReading") << "1.1" << "RotationReading" << true;
        QTest::newRow("1.1 TapSensor") << "1.1" << "TapSensor" << true;
        QTest::newRow("1.1 TapReading") << "1.1" << "TapReading" << true;

        QTest::newRow("1.2 SensorReading") << "1.2" << "SensorReading" << false;
        QTest::newRow("1.2 Accelerometer") << "1.2" << "Accelerometer" << true;
        QTest::newRow("1.2 AccelerometerReading") << "1.2" << "AccelerometerReading" << false;
        QTest::newRow("1.2 AmbientLightSensor") << "1.2" << "AmbientLightSensor" << true;
        QTest::newRow("1.2 AmbientLightReading") << "1.2" << "AmbientLightReading" << false;
        QTest::newRow("1.2 Compass") << "1.2" << "Compass" << true;
        QTest::newRow("1.2 CompassReading") << "1.2" << "CompassReading" << false;
        QTest::newRow("1.2 Magnetometer") << "1.2" << "Magnetometer" << true;
        QTest::newRow("1.2 MagnetometerReading") << "1.2" << "MagnetometerReading" << false;
        QTest::newRow("1.2 OrientationSensor") << "1.2" << "OrientationSensor" << true;
        QTest::newRow("1.2 OrientationReading") << "1.2" << "OrientationReading" << false;
        QTest::newRow("1.2 ProximitySensor") << "1.2" << "ProximitySensor" << true;
        QTest::newRow("1.2 ProximityReading") << "1.2" << "ProximityReading" << false;
        QTest::newRow("1.2 RotationSensor") << "1.2" << "RotationSensor" << true;
        QTest::newRow("1.2 RotationReading") << "1.2" << "RotationReading" << false;
        QTest::newRow("1.2 TapSensor") << "1.2" << "TapSensor" << true;
        QTest::newRow("1.2 TapReading") << "1.2" << "TapReading" << false;
        QTest::newRow("1.2 LightSensor") << "1.2" << "LightSensor" << true;
        QTest::newRow("1.2 LightReading") << "1.2" << "LightReading" << false;
        QTest::newRow("1.2 Gyroscope") << "1.2" << "Gyroscope" << true;
        QTest::newRow("1.2 GyroscopeReading") << "1.2" << "GyroscopeReading" << false;

        QTest::newRow("1.3 Range") << "1.3" << "Range" << false;
        QTest::newRow("1.3 OutputRange") << "1.3" << "OutputRange" << false;
        QTest::newRow("1.3 Sensor") << "1.3" << "Sensor" << false;
        QTest::newRow("1.3 SensorReading") << "1.3" << "SensorReading" << false;
        QTest::newRow("1.3 Accelerometer") << "1.3" << "Accelerometer" << true;
        QTest::newRow("1.3 AccelerometerReading") << "1.3" << "AccelerometerReading" << false;
        QTest::newRow("1.3 AmbientLightSensor") << "1.3" << "AmbientLightSensor" << true;
        QTest::newRow("1.3 AmbientLightReading") << "1.3" << "AmbientLightReading" << false;
        QTest::newRow("1.3 Compass") << "1.3" << "Compass" << true;
        QTest::newRow("1.3 CompassReading") << "1.3" << "CompassReading" << false;
        QTest::newRow("1.3 Magnetometer") << "1.3" << "Magnetometer" << true;
        QTest::newRow("1.3 MagnetometerReading") << "1.3" << "MagnetometerReading" << false;
        QTest::newRow("1.3 OrientationSensor") << "1.3" << "OrientationSensor" << true;
        QTest::newRow("1.3 OrientationReading") << "1.3" << "OrientationReading" << false;
        QTest::newRow("1.3 ProximitySensor") << "1.3" << "ProximitySensor" << true;
        QTest::newRow("1.3 ProximityReading") << "1.3" << "ProximityReading" << false;
        QTest::newRow("1.3 RotationSensor") << "1.3" << "RotationSensor" << true;
        QTest::newRow("1.3 RotationReading") << "1.3" << "RotationReading" << false;
        QTest::newRow("1.3 TapSensor") << "1.3" << "TapSensor" << true;
        QTest::newRow("1.3 TapReading") << "1.3" << "TapReading" << false;
        QTest::newRow("1.3 LightSensor") << "1.3" << "LightSensor" << true;
        QTest::newRow("1.3 LightReading") << "1.3" << "LightReading" << false;
        QTest::newRow("1.3 Gyroscope") << "1.3" << "Gyroscope" << true;
        QTest::newRow("1.3 GyroscopeReading") << "1.3" << "GyroscopeReading" << false;
        QTest::newRow("1.3 IRProximitySensor") << "1.3" << "IRProximitySensor" << true;
        QTest::newRow("1.3 IRProximityReading") << "1.3" << "IRProximityReading" << false;
        QTest::newRow("1.3 TiltSensor") << "1.3" << "TiltSensor" << true;
        QTest::newRow("1.3 TiltReading") << "1.3" << "TiltReading" << false;
    }

    void elements()
    {
        QFETCH(QString, version);
        QFETCH(QString, element);
        QFETCH(bool, exists);

        QQmlEngine engine;
        QString qml = QString("import QtQuick 2.0\nimport QtMobility.sensors %1\n%2 {}").arg(version).arg(element);
        QQmlComponent c(&engine);
        c.setData(qml.toLocal8Bit(), QUrl::fromLocalFile(QDir::currentPath()));
        if (!exists)
            QTest::ignoreMessage(QtWarningMsg, "QQmlComponent: Component is not ready");
        QObject *obj = c.create();
        QCOMPARE(exists, (obj != 0));
        delete obj;
        QList<QQmlError> errors = c.errors();
        if (exists) {
            QCOMPARE(errors.count(), 0);
        } else {
            QCOMPARE(errors.count(), 1);
            QString expected = QString("Cannot create %1").arg(element);
            QString actual = errors.first().description();
            QCOMPARE(expected, actual);
        }
    }

    void alwaysOn_data()
    {
        QTest::addColumn<QString>("version");
        QTest::addColumn<QString>("element");
        QTest::addColumn<bool>("validSyntax");

        QTest::newRow("1.1 Accelerometer") << "1.1" << "Accelerometer" << false;
        QTest::newRow("1.1 AmbientLightSensor") << "1.1" << "AmbientLightSensor" << false;
        QTest::newRow("1.1 Compass") << "1.1" << "Compass" << false;
        QTest::newRow("1.1 Magnetometer") << "1.1" << "Magnetometer" << false;
        QTest::newRow("1.1 OrientationSensor") << "1.1" << "OrientationSensor" << false;
        QTest::newRow("1.1 ProximitySensor") << "1.1" << "ProximitySensor" << false;
        QTest::newRow("1.1 RotationSensor") << "1.1" << "RotationSensor" << false;
        QTest::newRow("1.1 TapSensor") << "1.1" << "TapSensor" << false;

        QTest::newRow("1.2 Accelerometer") << "1.2" << "Accelerometer" << false;
        QTest::newRow("1.2 AmbientLightSensor") << "1.2" << "AmbientLightSensor" << false;
        QTest::newRow("1.2 Compass") << "1.2" << "Compass" << false;
        QTest::newRow("1.2 Magnetometer") << "1.2" << "Magnetometer" << false;
        QTest::newRow("1.2 OrientationSensor") << "1.2" << "OrientationSensor" << false;
        QTest::newRow("1.2 ProximitySensor") << "1.2" << "ProximitySensor" << false;
        QTest::newRow("1.2 RotationSensor") << "1.2" << "RotationSensor" << false;
        QTest::newRow("1.2 TapSensor") << "1.2" << "TapSensor" << false;
        QTest::newRow("1.2 LightSensor") << "1.2" << "LightSensor" << false;
        QTest::newRow("1.2 Gyroscope") << "1.2" << "Gyroscope" << false;

        QTest::newRow("1.3 Accelerometer") << "1.3" << "Accelerometer" << true;
        QTest::newRow("1.3 AmbientLightSensor") << "1.3" << "AmbientLightSensor" << true;
        QTest::newRow("1.3 Compass") << "1.3" << "Compass" << true;
        QTest::newRow("1.3 Magnetometer") << "1.3" << "Magnetometer" << true;
        QTest::newRow("1.3 OrientationSensor") << "1.3" << "OrientationSensor" << true;
        QTest::newRow("1.3 ProximitySensor") << "1.3" << "ProximitySensor" << true;
        QTest::newRow("1.3 RotationSensor") << "1.3" << "RotationSensor" << true;
        QTest::newRow("1.3 TapSensor") << "1.3" << "TapSensor" << true;
        QTest::newRow("1.3 LightSensor") << "1.3" << "LightSensor" << true;
        QTest::newRow("1.3 Gyroscope") << "1.3" << "Gyroscope" << true;
        QTest::newRow("1.3 IRProximitySensor") << "1.3" << "IRProximitySensor" << true;
        QTest::newRow("1.3 TiltSensor") << "1.3" << "TiltSensor" << true;
    }

    void alwaysOn()
    {
        QFETCH(QString, version);
        QFETCH(QString, element);
        QFETCH(bool, validSyntax);

        QQmlEngine engine;
        QString qml = QString("import QtQuick 2.0\nimport QtMobility.sensors %1\n%2 {\nalwaysOn: true\n}").arg(version).arg(element);
        QQmlComponent c(&engine);
        if (!validSyntax)
            QTest::ignoreMessage(QtWarningMsg, "QQmlComponent: Component is not ready");
        c.setData(qml.toLocal8Bit(), QUrl::fromLocalFile(QDir::currentPath()));
        QObject *obj = c.create();
        if (validSyntax) {
            QVERIFY(obj);
            QVariant alwaysOn = obj->property("alwaysOn");
            QCOMPARE(alwaysOn.isValid(), true);
            QCOMPARE(alwaysOn.toBool(), true);
            delete obj;
        } else {
            QCOMPARE(obj, static_cast<QObject*>(0));
        }
    }

    void namespace_api_data()
    {
        QTest::addColumn<QString>("qmlcode");
        QTest::addColumn<QVariant>("expected");

        QVariant expected;
        QStringList sl;
        foreach (const QByteArray &type, QSensor::sensorTypes()) {
            sl << QString::fromLocal8Bit(type);
            qDebug() << type;
        }
        expected = sl;
        QTest::newRow("Sensors.sensorTypes()")
                <<  "Item {\n"
                        "property var result\n"
                        "Component.onCompleted: {\n"
                            "result = Sensors.sensorTypes();\n"
                        "}\n"
                    "}"
                 << expected;

        foreach (const QByteArray &type, QSensor::sensorTypes()) {
            sl.clear();
            foreach (const QByteArray &identifier, QSensor::sensorsForType(type)) {
                sl << QString::fromLocal8Bit(identifier);
            }
            expected = sl;
            QTest::newRow(QString("Sensors.sensorsForType(\"%1\")").arg(QString::fromLocal8Bit(type)).toLocal8Bit().constData())
                    <<  QString(
                            "Item {\n"
                                "property var result\n"
                                "Component.onCompleted: {\n"
                                    "result = Sensors.sensorsForType(\"%1\");\n"
                                "}\n"
                            "}").arg(QString::fromLocal8Bit(type))
                     << expected;

            expected = QString::fromLocal8Bit(QSensor::defaultSensorForType(type));
            QTest::newRow(QString("Sensors.defaultSensorForType(\"%1\")").arg(QString::fromLocal8Bit(type)).toLocal8Bit().constData())
                    <<  QString(
                            "Item {\n"
                                "property var result\n"
                                "Component.onCompleted: {\n"
                                    "result = Sensors.defaultSensorForType(\"%1\");\n"
                                "}\n"
                            "}").arg(QString::fromLocal8Bit(type))
                     << expected;
        }
    }

    void namespace_api()
    {
        QFETCH(QString, qmlcode);
        QFETCH(QVariant, expected);

        QQmlEngine engine;
        QString qml = QString("import QtQuick 2.0\nimport QtMobility.sensors 1.3 as Sensors\n%1").arg(qmlcode);
        QQmlComponent c(&engine);
        c.setData(qml.toLocal8Bit(), QUrl::fromLocalFile(QDir::currentPath()));
        QObject *obj = c.create();
        QVERIFY(obj);
        QVariant result = obj->property("result");
        QCOMPARE(expected, result);
        delete obj;
    }

};

QTEST_MAIN(tst_legacy_sensors)

#include "tst_legacy_sensors.moc"
