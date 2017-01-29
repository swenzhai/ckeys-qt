/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the demonstration applications of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
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
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
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
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QGuiApplication>
#include <QtQuick/QQuickView>

#include <string>
#include <fstream>
#include <sstream>
using namespace std;

#include "squircle.h"
#include "jsmn.h"


static bool replK(string& str, const string& what, const string& to)
{
    size_t p = str.find(what);
    bool rep = p != string::npos;
    if (rep)
        str.replace(p, what.length(), to);
    return rep;
}


int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);

    //  find data path
	QString data = app.applicationDirPath();
    if (data.contains("build"))
        data += "/../../data/";
    else
    if (data.contains("bin"))
        data += "/../data/";
    else
        data += "/data/";

    //  qml gui create, load
    qmlRegisterType<Squircle>("OpenGLUnderQML", 1, 0, "Squircle");

    QQuickView view;
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    //view.setFlags();
    view.setSource(QUrl("qrc:///main.qml"));
    view.create();

//    Squircle* sq = view.findChild<Squircle*>("base");  //-
    const QVariant &parent = QVariant::fromValue<QObject*>(view.rootObject());
    QQmlComponent co(view.engine(), QUrl("qrc:///Button.qml"));



    //  info
    //-----------------------------------------------------------
    #if 1
    QObject *o = co.create();
    o->setProperty("xx", 20);  o->setProperty("yy", 20);
    o->setProperty("w", 100);  o->setProperty("h", 30);
    o->setProperty("sc", 16);
    o->setProperty("txt", "Info");
    o->setProperty("parent", parent);
    #endif

    //  run
    //-----------------------------------------------------------
    view.show();

    return app.exec();
}
