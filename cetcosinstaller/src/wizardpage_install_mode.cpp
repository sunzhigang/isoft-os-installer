#include <QtCore>
#include <QtGui>
#include "wizardpage_install_mode.h"
#include "ui_wizardpage_install_mode.h"
#include "installer_global.h"


WizardPage_installmode::WizardPage_installmode(QWidget *parent)
    :QWizardPage(parent), ui(new Ui::WizardPage_install_mode)
{
    ui->setupUi(this);

    QButtonGroup *bg = new QButtonGroup(this);
    bg->addButton(ui->rbDefault, 1);
    bg->addButton(ui->rbCustom, 2);

    bg->setExclusive(true);
}

void WizardPage_installmode::initializePage()
{
    ui->retranslateUi(this);
}

WizardPage_installmode::~WizardPage_installmode()
{
}

bool WizardPage_installmode::validatePage()
{
    if (ui->rbDefault->isChecked()) {
        //registerField("requiredSize", this, "requiredSize");
        setField("requiredSize", 7500);
    }
    return true;
}

int WizardPage_installmode::nextId() const
{
    if (ui->rbCustom->isChecked())
        return Page_ChooseGroup;
    else
        return Page_Partition_Advanced;
}
