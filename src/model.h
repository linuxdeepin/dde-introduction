/*
 * Copyright (C) 2017 ~ 2018 Deepin Technology Co., Ltd.
 *
 * Author:     kirigaya <kirigaya@mkacg.com>
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QJsonObject>
#include <QDebug>
#include <QPixmap>

struct IconStruct {
    QString Id;
    QString Path;
    bool Deletable;
    QPixmap Pixmap;

    bool operator ==(const IconStruct &icon) const {
        return Id == icon.Id;
    }

    bool operator <(const IconStruct &icon) const {
        return Id < icon.Id;
    }

    friend QDebug operator <<(QDebug debug, const IconStruct &icon) {
        debug << QString("{Id=%1,Path=%2,Deletable=%3}").arg(icon.Id)
                                                        .arg(icon.Path)
                                                        .arg(icon.Deletable);
        return debug;
    }

    static IconStruct fromJson(const QJsonObject &object) {
          IconStruct Icon;
          Icon.Id = object["Id"].toString();
          Icon.Path = object["Path"].toString();
          Icon.Deletable = object["Deletable"].toBool();
          Icon.Pixmap = QPixmap(object["Pixmap"].toString());

          return Icon;
    }
};

class Model : public QObject
{
    Q_OBJECT
public:
    static Model* Instance();

    enum DesktopMode {
        EfficientMode = 0,
        FashionMode = 1
    };

    enum WMType {
        WM_2D,
        WM_3D
    };

    inline IconStruct currentIcon() { return m_currentIcon; }
    inline QList<IconStruct> iconList() { return m_iconList; }
    inline WMType wmType() const { return m_wmType; }
    inline DesktopMode desktopMode() const { return m_desktopMode; }

Q_SIGNALS:
    void iconChanged(const IconStruct &icon) const;
    void iconAdded(const IconStruct &icon) const;
    void iconRemoved(const IconStruct &icon) const;
    void wmTypeChanged(WMType type) const;
    void desktopModeChanged(DesktopMode mode) const;

public Q_SLOTS:
    void addIcon(const IconStruct &icon);
    void removeIcon(const IconStruct &icon);
    void setCurrentIcon(const QString &icon);
    void setWmType(WMType wmType);
    void setDesktopMode(DesktopMode desktopMode);

private:
    explicit Model(QObject *parent = nullptr);

private:
    QList<IconStruct> m_iconList;
    IconStruct m_currentIcon;
    WMType m_wmType;
    DesktopMode m_desktopMode;
};

#endif // MODEL_H
