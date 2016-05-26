#include "parameterspinbox.h"

ParameterSpinBox::ParameterSpinBox(ParameterObject *parameterobject)
{
    object=parameterobject;
    setName(QString::fromStdString(object->name));
    setValue();
    setDescription(QString::fromStdString(object->descritpion));
}

void ParameterSpinBox::on_doubleSpinBox1_valueChanged(double){
    object->value = ValuePtr(doubleSpinBox1->value());
    emit changed();
}

void ParameterSpinBox::setValue(){
    this->stackedWidget->setCurrentWidget(this->pageVector);
    this->doubleSpinBox1->setValue(object->value->toDouble());
    this->doubleSpinBox2->hide();
    this->doubleSpinBox3->hide();
    this->doubleSpinBox4->hide();
}
