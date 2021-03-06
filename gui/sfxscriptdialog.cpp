/*
	Actiona
	Copyright (C) 2005-2016 Jonathan Mercier-Ganady

	Actiona is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Actiona is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program. If not, see <http://www.gnu.org/licenses/>.

	Contact : jmgr@jmgr.info
*/

#include "sfxscriptdialog.h"
#include "ui_sfxscriptdialog.h"

#include <QSettings>

SFXScriptDialog::SFXScriptDialog(QWidget *parent)
	: QDialog(parent),
	ui(new Ui::SFXScriptDialog)
{
	ui->setupUi(this);

	if(QSysInfo::WordSize == 32)
	{
		ui->use32BitBinariesLabel->setVisible(false);
		ui->use32BitBinaries->setVisible(false);
		adjustSize();
	}

	QSettings settings;
	ui->disableTrayIcon->setChecked(settings.value("sfxScript/disableTrayIcon", true).toBool());
	ui->showConsole->setChecked(settings.value("sfxScript/showConsole", false).toBool());
	ui->showExecutionWindow->setChecked(settings.value("sfxScript/showExecutionWindow", false).toBool());
	ui->closeAfterExecution->setChecked(settings.value("sfxScript/closeAfterExecution", true).toBool());
	ui->use32BitBinaries->setChecked(settings.value("sfxScript/use32BitBinaries", true).toBool());
    ui->requiresActiona->setChecked(settings.value("sfxScript/requiresActiona", false).toBool());

    on_requiresActiona_clicked();
}

SFXScriptDialog::~SFXScriptDialog()
{
	delete ui;
}

bool SFXScriptDialog::disableTrayIcon() const
{
	return ui->disableTrayIcon->isChecked();
}

bool SFXScriptDialog::showConsole() const
{
	return ui->showConsole->isChecked();
}

bool SFXScriptDialog::showExecutionWindow() const
{
	return ui->showExecutionWindow->isChecked();
}

bool SFXScriptDialog::closeAfterExecution() const
{
	return ui->closeAfterExecution->isChecked();
}

bool SFXScriptDialog::use32BitBinaries() const
{
	return ui->use32BitBinaries->isChecked();
}

bool SFXScriptDialog::requiresActiona() const
{
    return ui->requiresActiona->isChecked();
}

void SFXScriptDialog::accept()
{
	QSettings settings;
	settings.setValue("sfxScript/disableTrayIcon", ui->disableTrayIcon->isChecked());
	settings.setValue("sfxScript/showConsole", ui->showConsole->isChecked());
	settings.setValue("sfxScript/showExecutionWindow", ui->showExecutionWindow->isChecked());
	settings.setValue("sfxScript/closeAfterExecution", ui->closeAfterExecution->isChecked());
	settings.setValue("sfxScript/use32BitBinaries", ui->use32BitBinaries->isChecked());
    settings.setValue("sfxScript/requiresActiona", ui->requiresActiona->isChecked());

	QDialog::accept();
}

void SFXScriptDialog::on_requiresActiona_clicked()
{
    bool requiresActiona = ui->requiresActiona->isChecked();

    ui->use32BitBinaries->setEnabled(!requiresActiona);
    ui->use32BitBinariesLabel->setEnabled(!requiresActiona);
}
