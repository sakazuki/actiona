/*
	Actionaz
	Copyright (C) 2008-2010 Jonathan Mercier-Ganady

	Actionaz is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Actionaz is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program. If not, see <http://www.gnu.org/licenses/>.

	Contact : jmgr@jmgr.info
*/

#include "actions/textinputinstance.h"
#include "actioninstanceexecutionhelper.h"
#include "script.h"

#include <QInputDialog>
#include <QApplication>
#include <QDesktopWidget>

namespace Actions
{
	TextInputInstance::TextInputInstance(const ActionTools::ActionDefinition *definition, QObject *parent)
		: ActionTools::ActionInstance(definition, parent),
		mInputDialog(0)
	{
	}

	void TextInputInstance::startExecution()
	{
		ActionTools::ActionInstanceExecutionHelper actionInstanceExecutionHelper(this, script(), scriptEngine());
		QString question;
		QString defaultValue;

		mInputDialog = 0;

		if(!actionInstanceExecutionHelper.evaluateString(question, "question") ||
			!actionInstanceExecutionHelper.evaluateString(defaultValue, "defaultValue") ||
			!actionInstanceExecutionHelper.evaluateVariable(mVariable, "variable"))
			return;

		mInputDialog = new QInputDialog();

		mInputDialog->setWindowModality(Qt::NonModal);
		mInputDialog->setLabelText(question);
		mInputDialog->setTextValue(defaultValue);

		mInputDialog->adjustSize();
		QRect screenGeometry = QApplication::desktop()->availableGeometry();
		mInputDialog->move(screenGeometry.center());
		mInputDialog->move(mInputDialog->pos().x() - mInputDialog->width()/2, mInputDialog->pos().y() - mInputDialog->height()/2);

		mInputDialog->open(this, SLOT(textEntered(const QString &)));
		connect(mInputDialog, SIGNAL(rejected()), this, SLOT(canceled()));
	}

	void TextInputInstance::stopExecution()
	{
		if(mInputDialog)
		{
			mInputDialog->close();
			mInputDialog->deleteLater();
		}
	}

	void TextInputInstance::textEntered(const QString &value)
	{
		ActionTools::ActionInstanceExecutionHelper actionInstanceExecutionHelper(this, script(), scriptEngine());

		actionInstanceExecutionHelper.setVariable(mVariable, value);

		mInputDialog->disconnect();
		mInputDialog->deleteLater();

		emit executionEnded();
	}

	void TextInputInstance::canceled()
	{
		textEntered(QString());
	}
}