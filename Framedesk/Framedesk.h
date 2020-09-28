#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Framedesk.h"

class Framedesk : public QMainWindow
{
    Q_OBJECT

public:
    Framedesk(QWidget *parent = Q_NULLPTR);

private:
    Ui::FramedeskClass ui;
};
