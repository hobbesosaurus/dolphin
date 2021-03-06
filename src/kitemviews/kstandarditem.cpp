/***************************************************************************
 *   Copyright (C) 2012 by Peter Penz <peter.penz19@gmail.com>             *
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
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA            *
 ***************************************************************************/

#include "kstandarditem.h"
#include <QSet>
#include <QByteArray>
#include "kstandarditemmodel.h"

KStandardItem::KStandardItem(KStandardItem* parent) :
    m_parent(parent),
    m_children(),
    m_model(0),
    m_data()
{
}

KStandardItem::KStandardItem(const QString& text, KStandardItem* parent) :
    m_parent(parent),
    m_children(),
    m_model(0),
    m_data()
{
    setText(text);
}

KStandardItem::KStandardItem(const QString& icon, const QString& text, KStandardItem* parent) :
    m_parent(parent),
    m_children(),
    m_model(0),
    m_data()
{
    setIcon(icon);
    setText(text);
}

KStandardItem::KStandardItem(const KStandardItem& item) :
    m_parent(item.m_parent),
    m_children(item.m_children),
    m_model(item.m_model),
    m_data(item.m_data)
{
}

KStandardItem::~KStandardItem()
{
}

void KStandardItem::setText(const QString& text)
{
    setDataValue("text", text);
}

QString KStandardItem::text() const
{
    return m_data["text"].toString();
}

void KStandardItem::setIcon(const QString& icon)
{
    setDataValue("iconName", icon);
}

QString KStandardItem::icon() const
{
    return m_data["iconName"].toString();
}

void KStandardItem::setIconOverlays(const QStringList& overlays)
{
    setDataValue("iconOverlays", overlays);
}

QStringList KStandardItem::iconOverlays() const
{
    return m_data["iconOverlays"].toStringList();
}

void KStandardItem::setGroup(const QString& group)
{
    setDataValue("group", group);
}

QString KStandardItem::group() const
{
    return m_data["group"].toString();
}

void KStandardItem::setDataValue(const QByteArray& role, const QVariant& value)
{
    const QVariant previous = m_data.value(role);
    if (previous == value) {
        return;
    }

    m_data.insert(role, value);
    onDataValueChanged(role, value, previous);

    if (m_model) {
        const int index = m_model->index(this);
        QSet<QByteArray> changedRoles;
        changedRoles.insert(role);
        m_model->onItemChanged(index, changedRoles);
        emit m_model->itemsChanged(KItemRangeList() << KItemRange(index, 1), changedRoles);
    }
}

QVariant KStandardItem::dataValue(const QByteArray& role) const
{
    return m_data[role];
}

void KStandardItem::setParent(KStandardItem* parent)
{
    // TODO: not implemented yet
    m_parent = parent;
}

KStandardItem* KStandardItem::parent() const
{
    return m_parent;
}

void KStandardItem::setData(const QHash<QByteArray, QVariant>& values)
{
    const QHash<QByteArray, QVariant> previous = m_data;
    m_data = values;
    onDataChanged(values, previous);
}

QHash<QByteArray, QVariant> KStandardItem::data() const
{
    return m_data;
}

QList<KStandardItem*> KStandardItem::children() const
{
    return m_children;
}

void KStandardItem::onDataValueChanged(const QByteArray& role,
                                       const QVariant& current,
                                       const QVariant& previous)
{
    Q_UNUSED(role);
    Q_UNUSED(current);
    Q_UNUSED(previous);
}

void KStandardItem::onDataChanged(const QHash<QByteArray, QVariant>& current,
                                  const QHash<QByteArray, QVariant>& previous)
{
    Q_UNUSED(current);
    Q_UNUSED(previous);
}

