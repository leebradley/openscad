#include "parameterslider.h"

ParameterSlider::ParameterSlider(ParameterObject *parameterobject, bool showDescription)
{
    object=parameterobject;
    setName(QString::fromStdString(object->name));
    setValue();
    connect(slider,SIGNAL(sliderReleased()),this,SLOT(on_Changed()));
    if(showDescription==true){
        setDescription(object->description);
    }
    else{
        slider->setToolTip(object->description);
    }
}

void ParameterSlider::on_Changed()
{
    double v = slider->value();
    object->value = ValuePtr(v);
    //to be corrected
    this->labelSliderValue->setText(QString::number(v, 'f', 0));
    emit changed();
}

void ParameterSlider::setValue()
{
    this->stackedWidget->setCurrentWidget(this->pageSlider);
    this->slider->setRange(object->values->toRange().begin_value(),object->values->toRange().end_value());
    this->slider->setValue(object->value->toDouble());
    this->slider->setSingleStep(object->values->toRange().step_value());
    this->labelSliderValue->setText(QString::number(object->value->toDouble(), 'f', 0));
}