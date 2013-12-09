#ifndef EDITPARTITION_H
#define EDITPARTITION_H

#include <QDialog>
#include <QTreeWidgetItem>

#include "ui_edit.h"

class QString;
class DisksWidget;

class EditPartition : public QDialog, public Ui::Edit
{
	Q_OBJECT
public:
	EditPartition(QTreeWidgetItem *currentItem, DisksWidget *parent = 0);
///	void setFsType(const QString &type)	{ fsTypeLabel->setText(type); }
///	void setSize(const QString &size)	{ sizeLabel->setText(size); }

private slots:
	void accept();
	void checkSwap(const QString &text);
	void checkMountPoint(const QString &mountPoint);
	void checkFree(bool checked);
	void setMountByFormatButton(bool checked);

private:
	DisksWidget 	*m_parent;
	QTreeWidgetItem *m_cur;
};

#endif
