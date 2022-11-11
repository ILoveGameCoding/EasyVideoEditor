#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_EasyVideoEditor.h"
#include "Widgets.h"

class EasyVideoEditor : public QMainWindow
{
    Q_OBJECT

public:
    EasyVideoEditor(QWidget *parent = nullptr);
    ~EasyVideoEditor();

private:
    Ui::EasyVideoEditorClass ui;
};