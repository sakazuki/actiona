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

#ifndef TEXTDEFINITION_H
#define TEXTDEFINITION_H

#include "actiondefinition.h"
#include "textinstance.h"
#include "textparameterdefinition.h"

namespace ActionTools
{
	class ActionPack;
	class ActionInstance;
}

namespace Actions
{
	class TextDefinition : public QObject, public ActionTools::ActionDefinition
	{
	   Q_OBJECT
	
	public:
		explicit TextDefinition(ActionTools::ActionPack *pack)
		: ActionDefinition(pack)
		{
			ActionTools::TextParameterDefinition *text = new ActionTools::TextParameterDefinition("text", tr("Text"), this);
			text->setTooltip(tr("The text to write"));
			addElement(text);
	
			addException(TextInstance::FailedToSendInputException, tr("Send input failure"));
		}
	
		QString name() const													{ return QObject::tr("Text"); }
		QString id() const														{ return "ActionText"; }
		Flag flags() const														{ return ActionDefinition::flags() | Official; }
		QString description() const												{ return QObject::tr("Write some text"); }
		ActionTools::ActionInstance *newActionInstance() const					{ return new TextInstance(this); }
		Category category() const												{ return Device; }
		QPixmap icon() const													{ return QPixmap(":/actions/icons/text.png"); }
		bool requirementCheck(QStringList &missingRequirements) const			{ return requirementCheckXTest(missingRequirements); }
	
	private:
		Q_DISABLE_COPY(TextDefinition)
	};
}

#endif // TEXTDEFINITION_H