#pragma once

#include <QObject>

class GameController : public QObject {
    Q_OBJECT
    Q_PROPERTY(int selectedIndex READ selectedIndex NOTIFY selectedIndexChanged)

public:
    int selectedIndex() const;
    Q_INVOKABLE void selectTile(int index);

signals:
    void selectedIndexChanged();

private:
    int m_selectedIndex = -1;
};
