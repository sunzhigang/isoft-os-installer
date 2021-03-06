/***************************************************************************
 *   Copyright (C) 2008 by Weinzierl Stefan                                *
 *   Stefan@Weinzierl-Stefan.de                                            *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>

class Card;

class Scene : public QGraphicsScene
{
Q_OBJECT
public:
	Scene(QObject *parent = 0);
	~Scene();
	
signals:
	void gameReady();
	
public slots:	
	void init(int count);
	void setSize(int size);
	void resetCards();
	
protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
	void checkReady();
	
private:
	int m_size;
	QList<Card*> m_show;
	QTimer *m_timer;
	int m_zPos;
};

#endif
