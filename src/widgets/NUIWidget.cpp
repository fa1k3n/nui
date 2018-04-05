/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NUIWidget.cpp
 * Author: jfalkens
 * 
 * Created on April 5, 2018, 9:28 AM
 */

#include "NUIWidget.hpp"
#include <NUIApp>

using namespace NUI;

NUIWidget::NUIWidget(NUIObject* parent) : NUIObject(parent),
    m_x(0),
    m_y(0),
    m_width(0),
    m_height(1) 
{
    NUIColorPair::setColorPair(NUIColorPair{m_objectID, COLOR_WHITE, COLOR_BLACK});

}

NUIWidget::~NUIWidget() {
}


NUIWidget& NUIWidget::setWidth(NUIReal width) {
	NUIBoundingRect oldRect = rect();
	m_width = width;
	NUIApp::NUIPostEvent(this, new NUIResizeEvent(oldRect, rect()));
	return *this;
}

NUIWidget& NUIWidget::setHeight(NUIReal height) {
	NUIBoundingRect oldRect = rect();
	m_height = height;
	NUIApp::NUIPostEvent(this, new NUIResizeEvent(oldRect, rect()));
	return *this;
}

NUIWidget& NUIWidget::setX(NUIReal x) {
	auto oldPos = NUIPoint(m_x, m_y);
	m_x = x;
	NUIApp::NUIPostEvent(this, new NUIMoveEvent(oldPos, NUIPoint(m_x, m_y)));
	emit xChanged(x);
	return *this;
}

NUIWidget& NUIWidget::setY(NUIReal y) {
	auto oldPos = NUIPoint(m_x, m_y);
	m_y = y;
	NUIApp::NUIPostEvent(this, new NUIMoveEvent(oldPos, NUIPoint(m_x, m_y)));
	emit yChanged(y);
	return *this;
}

NUIColor NUIWidget::getColor() {
	return NUIColorPair::getColorPair(m_objectID).bg;
}

NUIWidget& NUIWidget::setColor(NUIColor color) {
	NUIColorPair pair = NUIColorPair::getColorPair(m_objectID);
	pair.setBg(color);
	return *this;
}

void NUIWidget::update() {
	NUIApp::NUIPostEvent(this, new NUIPaintEvent(rect()));
}

void NUIWidget::repaint() {
	NUIApp::NUISendEvent(this, new NUIPaintEvent(rect()));
}

bool NUIWidget::event(NUIEvent* event) {
    if(event->type() == NUIEvent::Paint) {
            NUIPaintEvent* e = static_cast<NUIPaintEvent*>(event);
            paintEvent(e);
            return true;
    } else if(event->type() == NUIEvent::Resize) {
            NUIResizeEvent* e = static_cast<NUIResizeEvent*>(event);
            resizeEvent(e);
            return true;
    }  else if(event->type() == NUIEvent::Move) {
            NUIMoveEvent* e = static_cast<NUIMoveEvent*>(event);
            moveEvent(e);
            return true;
    } else if(event->type() == NUIEvent::KeyPress) {
            NUIKeyEvent* e = static_cast<NUIKeyEvent*>(event);
            keyEvent(e);
            return true;
    }

    return false;
}

void NUIWidget::paintEvent(NUIPaintEvent* event) {
	wrefresh(NUIApp::focusWindow()->m_pWin);
	refresh();
}

void NUIWidget::resizeEvent(NUIResizeEvent* event) {
	NUIBoundingRect r = event->newSize();
	m_width = r.width;
	m_height = r.height;
	repaint();
}

void NUIWidget::moveEvent(NUIMoveEvent* event) {
	// Clear old location
	mvwprintw(NUIApp::focusWindow()->m_pWin, event->oldPos().y(), event->oldPos().x(), std::string(getWidth()*getHeight(), ' ').c_str());
	m_x = event->newPos().x();
	m_y = event->newPos().y();
	repaint();
}

void NUIWidget::keyEvent(NUIKeyEvent* event) {
	emit keyPressed(event->key());
	repaint();
}