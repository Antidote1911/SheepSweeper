#include <view/CSettingsDialog.h>
#include <ui_CSettingsDialog.h>
#include <Constants.h>
#include <QCheckBox>
#include <QSpinBox>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>

namespace SSw
{

CSettingsDialog::CSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CSettingsDialog)
{
    ui->setupUi(this);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &CSettingsDialog::accept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &CSettingsDialog::reject);
    connect(ui->heightSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateRange()));
    connect(ui->widthSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateRange()));
    connect(ui->CustomCheckBox, SIGNAL(stateChanged(int)), this, SLOT(personalRange()));
    connect(ui->LevelComboBox, SIGNAL(activated(int)), this, SLOT(setLevel(int)));

    ui->heightSpinBox->setMinimum(3);
    ui->widthSpinBox->setMinimum(3);

    personalRange();
    //setLevel(ui->LevelComboBox->currentIndex());

    setWindowTitle(tr("Preferences"));
}

CSettingsDialog::~CSettingsDialog()
{
    delete ui;
}

bool CSettingsDialog::getPreferences(SPreferences &prefs, QWidget *parent)
{
    bool retValue = false;

    CSettingsDialog dialog(parent);

    dialog.ui->heightSpinBox->setValue(prefs.width);
    dialog.ui->widthSpinBox->setValue(prefs.height);
    dialog.ui->sheepSpinBox->setValue(prefs.sheep);
    dialog.ui->LevelComboBox->setCurrentIndex(prefs.level);
    dialog.ui->CustomCheckBox->setChecked(prefs.perso);

    if (dialog.exec() == QDialog::Accepted)
    {
        prefs.width   = dialog.ui->heightSpinBox->value();
        prefs.height  = dialog.ui->widthSpinBox->value();
        prefs.sheep   = dialog.ui->sheepSpinBox->value();
        prefs.level   = dialog.ui->LevelComboBox->currentIndex();
        prefs.perso   = dialog.ui->CustomCheckBox->isChecked();
        retValue = true;
    }

    return retValue;
}

void CSettingsDialog::updateRange()
{
    int32_t min = MIN_DENSITY * ui->heightSpinBox->value() * ui->widthSpinBox->value();
    int32_t max = MAX_DENSITY * ui->heightSpinBox->value() * ui->widthSpinBox->value();
    ui->sheepSpinBox->setRange(1, max);
}

void CSettingsDialog::personalRange()
{
    if (ui->CustomCheckBox->isChecked())
    {
        ui->LevelComboBox->setDisabled(true);
        ui->heightSpinBox->setDisabled(false);
        ui->widthSpinBox->setDisabled(false);
        ui->sheepSpinBox->setDisabled(false);
    }
    else
    {
        ui->LevelComboBox->setDisabled(false);
        ui->heightSpinBox->setDisabled(true);
        ui->widthSpinBox->setDisabled(true);
        ui->sheepSpinBox->setDisabled(true);
    }
    setLevel(ui->LevelComboBox->currentIndex());
}

void CSettingsDialog::setLevel(int lvl)  // 3,10,20,30,60,100
{
    if (lvl == 0) //ultra debutant
    {
        ui->heightSpinBox->setValue(7);
        ui->widthSpinBox->setValue(7);
        ui->sheepSpinBox->setValue(3);
    }

    if (lvl == 1) //debutant
    {
        ui->heightSpinBox->setValue(10);
        ui->widthSpinBox->setValue(10);
        ui->sheepSpinBox->setValue(10);
    }

    if (lvl == 2) //normal
    {
        ui->heightSpinBox->setValue(15);
        ui->widthSpinBox->setValue(15);
        ui->sheepSpinBox->setValue(20);
    }

    if (lvl == 3) //dificile
    {
        ui->heightSpinBox->setValue(20);
        ui->widthSpinBox->setValue(15);
        ui->sheepSpinBox->setValue(30);
    }

    if (lvl == 4) //Ultra Difficile
    {
        ui->heightSpinBox->setValue(25);
        ui->widthSpinBox->setValue(20);
        ui->sheepSpinBox->setValue(60);
    }

    if (lvl == 5) //Chuck Norris
    {
        ui->heightSpinBox->setValue(30);
        ui->widthSpinBox->setValue(20);
        ui->sheepSpinBox->setValue(100);
    }

}

} // namespace SSw
