/*=========================================================================

  Library:   CTK

  Copyright (c) Kitware Inc. 
  All rights reserved.
  Distributed under a BSD License. See LICENSE.txt file.

  This software is distributed "AS IS" WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the above copyright notice for more information.

=========================================================================*/

// Qt includes
#include <QColorDialog>
#include <QIcon>
#include <QPainter>
#include <QPixmap>
#include <QStyle>

// CTK includes
#include "ctkColorPickerButton.h"

//-----------------------------------------------------------------------------
ctkColorPickerButton::ctkColorPickerButton(QWidget* _parent)
  :QPushButton(_parent)
{
  connect(this, SIGNAL(toggled(bool)), this, SLOT(changeColor(bool)));
  this->setColor(Qt::black);

  this->setCheckable(true);
}

//-----------------------------------------------------------------------------
ctkColorPickerButton::ctkColorPickerButton(const QString& _text, QWidget* _parent)
  :QPushButton(_text, _parent)
{
  connect(this, SIGNAL(clicked), this, SLOT(changeColor));
  this->setColor(Qt::black);

  // Customize
  this->setCheckable(true);
}

//-----------------------------------------------------------------------------
ctkColorPickerButton::ctkColorPickerButton(const QColor& _color,
                                             const QString& _text,
                                             QWidget* _parent)
  :QPushButton(_text, _parent)
{
  connect(this, SIGNAL(clicked), this, SLOT(changeColor));
  this->setColor(_color);

  // Customize
  this->setCheckable(true);
}

//-----------------------------------------------------------------------------
void ctkColorPickerButton::changeColor(bool change)
{
  if (change)
    {
    this->setColor(QColorDialog::getColor(this->Color));

    this->setChecked(false);
    }
}

//-----------------------------------------------------------------------------
void ctkColorPickerButton::setColor(const QColor& _color)
{
  if (_color == this->Color)
    {
    return;
    }

  int _iconSize = style()->pixelMetric(QStyle::PM_SmallIconSize);
  QPixmap pix(_iconSize, _iconSize);
  pix.fill(palette().button().color());
  QPainter p(&pix);
  p.setPen(QPen(Qt::gray));
  p.setBrush(_color);
  p.drawRect(2, 2, pix.width() - 5, pix.height() - 5);

  this->setIcon(QIcon(pix));
  this->setText(_color.name());
  
  this->Color = _color;
  emit colorChanged(this->Color);
}

//-----------------------------------------------------------------------------
QColor ctkColorPickerButton::color()const
{
  return this->Color;
}